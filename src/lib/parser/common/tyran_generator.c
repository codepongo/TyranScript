#include <tyranscript/parser/common/tyran_parser_tree.h>
#include <tyranscript/parser/common/tyran_code.h>
#include <tyranscript/parser/common/tyran_generator.h>
#include <tyranscript/parser/common/tyran_variable_scope.h>
#include <tyranscript/tyran_constants.h>

tyran_reg_or_constant_index tyran_generator_traverse(tyran_code_state* code, tyran_parser_node* tree, tyran_label_id true_label, tyran_label_id false_label, tyran_boolean invert_logic);


int tyran_generator_prepare_label(tyran_code_state* code)
{
	return tyran_code_prepare_label(code);
}

void tyran_generator_define_label(tyran_code_state* code, tyran_label_id label_index)
{
	tyran_code_define_label(code, label_index);
}

void tyran_generator_label_reference(tyran_code_state* code, tyran_label_id label_index)
{
	tyran_code_add_label_index_reference(code, label_index);
	tyran_opcodes_op_jmp(code->opcodes, 0);
}

void tyran_generator_resolve_labels(tyran_code_state* code)
{
	tyran_code_fixup_label_references(code);
}

tyran_generator* tyran_generator_new(tyran_parser_node* tree, tyran_code_state* code) {
	tyran_generator* generator = TYRAN_CALLOC(tyran_generator);
	tyran_reg_or_constant_index return_index = tyran_generator_traverse(code, tree, 0, 0, 0);
	tyran_opcodes_op_ret(code->opcodes, return_index, 1);
	
	return generator;
}

tyran_constant_index tyran_generator_literal_to_constant_index(tyran_constants* constants, tyran_parser_node* node)
{
	tyran_constant_index result;
	switch (node->type)
	{
	case TYRAN_PARSER_NODE_TYPE_BOOLEAN: {
		tyran_parser_node_boolean* boolean = (tyran_parser_node_boolean*) node;
		result = tyran_constants_add_boolean(constants, boolean->boolean);
		}
		break;
	case TYRAN_PARSER_NODE_TYPE_NULL:
		break;
	case TYRAN_PARSER_NODE_TYPE_STRING: {
		tyran_parser_node_string* string = (tyran_parser_node_string*) node;
		const struct tyran_string* str = tyran_string_from_c_str(string->string);
		result = tyran_constants_add_string(constants, str);
		}
		break;
	case TYRAN_PARSER_NODE_TYPE_UNDEFINED:
		break;
	case TYRAN_PARSER_NODE_TYPE_NUMBER: {
		tyran_parser_node_number* number = (tyran_parser_node_number*) node;
		result = tyran_constants_add_number(constants, number->number);
		}
		break;
	default:
		TYRAN_ERROR("Unknown constant:%d", node->type);
	}
	
	return result;
}

void tyran_generator_comparison_operator(tyran_code_state* code, tyran_parser_binary_operand_type operator_type, tyran_reg_or_constant_index left, tyran_reg_or_constant_index right, tyran_label_id true_label, tyran_label_id false_label, tyran_boolean invert_logic)
{
	tyran_opcodes* codes = code->opcodes;
	
	switch (operator_type) {
	case TYRAN_PARSER_EQUAL:
		tyran_opcodes_op_jeq(codes, left, right, invert_logic);
		break;
	case TYRAN_PARSER_NOT_EQUAL:
		tyran_opcodes_op_jeq(codes, left, right, !invert_logic);
		break;
	case TYRAN_PARSER_LESS:
		tyran_opcodes_op_jlt(codes, left, right, invert_logic);
		break;
	case TYRAN_PARSER_LESS_EQUAL:
		tyran_opcodes_op_jle(codes, left, right, invert_logic);
		break;
	case TYRAN_PARSER_GREATER_EQUAL:
		tyran_opcodes_op_jlt(codes, left, right, !invert_logic);
		break;
	case TYRAN_PARSER_GREATER:
		tyran_opcodes_op_jle(codes, left, right, !invert_logic);
		break;
	}
	
	tyran_generator_label_reference(code, false_label);
}

tyran_reg_index tyran_generator_emit_operator(tyran_code_state* code, tyran_parser_binary_operand_type operator_type, tyran_reg_or_constant_index left, tyran_reg_or_constant_index right, tyran_label_id true_label, tyran_label_id false_label, tyran_boolean invert_logic)
{
	tyran_opcodes* codes = code->opcodes;
	
	tyran_reg_index target = tyran_variable_scopes_define_temporary_variable(code->scope);
	
	switch (operator_type) {
	case TYRAN_PARSER_DIVIDE:
		tyran_opcodes_op_div(codes, target, left, right);
		break;
	case TYRAN_PARSER_MULTIPLY:
		tyran_opcodes_op_mul(codes, target, left, right);
		break;
	case TYRAN_PARSER_MODULUS:
		tyran_opcodes_op_mod(codes, target, left, right);
		break;
	case TYRAN_PARSER_ADD:
		tyran_opcodes_op_add(codes, target, left, right);
		break;
	case TYRAN_PARSER_SUBTRACT:
		tyran_opcodes_op_sub(codes, target, left, right);
		break;
	case TYRAN_PARSER_ASSIGNMENT:
		tyran_opcodes_op_set(codes, target, left, right);
		break;
	case TYRAN_PARSER_EQUAL:
	case TYRAN_PARSER_NOT_EQUAL:
	case TYRAN_PARSER_LESS:
	case TYRAN_PARSER_LESS_EQUAL:
	case TYRAN_PARSER_GREATER:
	case TYRAN_PARSER_GREATER_EQUAL:
		tyran_variable_scopes_undefine_variable(code->scope, target);
		target = TYRAN_OPCODE_REGISTER_ILLEGAL;
		tyran_generator_comparison_operator(code, operator_type, left, right, true_label, false_label, invert_logic);
		break;
	}
	
	return target;
}

tyran_reg_or_constant_index tyran_generator_handle_node(tyran_code_state* code, tyran_parser_node* node)
{
	tyran_reg_or_constant_index result;
	
	if (tyran_parser_node_is_constant(node)) {
		result = tyran_generator_literal_to_constant_index(code->constants, node);
	} else if (node->type == TYRAN_PARSER_NODE_TYPE_IDENTIFIER) {
		tyran_parser_node_identifier* identifier = (tyran_parser_node_identifier*) node;
		result = tyran_variable_scopes_get_identifier(code->scope, identifier->string);
		if (result == TYRAN_OPCODE_REGISTER_ILLEGAL) {
			TYRAN_SOFT_ERROR("illegal variable: '%s'", identifier->string);
		}
	}
	
	return result;
}

tyran_reg_index tyran_generator_handle_operator(tyran_code_state* code, tyran_parser_node_operand_binary* binary, tyran_reg_or_constant_index left, tyran_reg_or_constant_index right, tyran_label_id true_label, tyran_label_id false_label, tyran_boolean invert_logic)
{
	return tyran_generator_emit_operator(code, binary->operator_type, left, right, true_label, false_label, invert_logic);
}

tyran_reg_index tyran_generator_traverse_default_binary(tyran_code_state* code, tyran_parser_node_operand_binary* binary, tyran_label_id true_label, tyran_label_id false_label, tyran_boolean invert_logic) {
	tyran_reg_or_constant_index left_index = tyran_generator_traverse(code, binary->left, true_label, false_label, invert_logic);
	tyran_reg_or_constant_index right_index = tyran_generator_traverse(code, binary->right, true_label, false_label, invert_logic);
	
	tyran_reg_index target_index = tyran_generator_handle_operator(code, binary, left_index, right_index, true_label, false_label, invert_logic);
	
	if (!tyran_opcodes_is_constant(right_index)) {
		tyran_variable_scopes_undefine_variable(code->scope, (tyran_reg_index)right_index);
	}
	if (!tyran_opcodes_is_constant(left_index)) {
		tyran_variable_scopes_undefine_variable(code->scope, (tyran_reg_index)left_index);
	}
	return target_index;
}

tyran_reg_or_constant_index tyran_generator_traverse_assignment(tyran_code_state* code, tyran_parser_node_operand_binary* binary, tyran_label_id true_label, tyran_label_id false_label)
{
	tyran_reg_or_constant_index source_index = tyran_generator_traverse(code, binary->right, true_label, false_label, 0);

	if (binary->left->type == TYRAN_PARSER_NODE_TYPE_IDENTIFIER) {
		tyran_parser_node_identifier* identifier = (tyran_parser_node_identifier*) binary->left;
		tyran_reg_index target_index = tyran_variable_scopes_define_identifier(code->scope, identifier->string);
		if (tyran_opcodes_is_constant(source_index)) {
			tyran_opcodes_op_ldc(code->opcodes, target_index, source_index);
		} else {
			tyran_opcodes_op_ld(code->opcodes, target_index, source_index);
		}
		
		return target_index;
	}
	return TYRAN_OPCODE_REGISTER_ILLEGAL;
}

tyran_reg_or_constant_index tyran_generator_traverse_binary(tyran_code_state* code, tyran_parser_node_operand_binary* binary, tyran_label_id true_label, tyran_label_id false_label, tyran_boolean invert_logic) {
	tyran_reg_or_constant_index result;
	switch (binary->operator_type) {
		case TYRAN_PARSER_ASSIGNMENT:
			result = tyran_generator_traverse_assignment(code, binary, true_label, false_label);
			break;
		default:
			result = tyran_generator_traverse_default_binary(code, binary, true_label, false_label, invert_logic);
			break;
	}
	
	return result;
}

tyran_reg_or_constant_index tyran_generator_traverse_unary(tyran_code_state* code, tyran_parser_node_operand_unary* unary, tyran_label_id true_label, tyran_label_id false_label, tyran_boolean invert_logic) {
	return tyran_generator_traverse(code, unary->expression, true_label, false_label, invert_logic);
}

tyran_reg_or_constant_index tyran_generator_traverse_if(tyran_code_state* code, tyran_parser_node* expression, tyran_parser_node* then_node, tyran_parser_node* else_node) {
	tyran_label_id if_true_label = tyran_generator_prepare_label(code);
	tyran_label_id if_false_label = tyran_generator_prepare_label(code);
	tyran_generator_traverse(code, expression, if_true_label, if_false_label, TYRAN_FALSE);
	
	/*
	tyran_opcodes_op_jb(code->opcodes, expression_index, 0);
	tyran_generator_label_reference(code, code->false_label);
	*/
	
	tyran_reg_or_constant_index result;
	
	tyran_generator_define_label(code, if_true_label);
	result = tyran_generator_traverse(code, then_node, 0, 0, TYRAN_TRUE);
	if (else_node) {
		int end_of_if = tyran_generator_prepare_label(code);
		tyran_generator_label_reference(code, end_of_if);
		tyran_generator_define_label(code, if_false_label);

		tyran_generator_traverse(code, else_node, 0, 0, TYRAN_TRUE);

		tyran_generator_define_label(code, end_of_if);
	} else {
		tyran_generator_define_label(code, if_false_label);
	}
	tyran_generator_resolve_labels(code);
	return result;
}

tyran_reg_or_constant_index tyran_generator_traverse_while(tyran_code_state* code, tyran_parser_node_while* while_node, tyran_label_id true_label, tyran_label_id false_label) {
	tyran_label_id while_true_label = tyran_generator_prepare_label(code);
	tyran_label_id while_false_label = tyran_generator_prepare_label(code);
	tyran_label_id while_loop_label = tyran_generator_prepare_label(code);
	
	tyran_generator_define_label(code, while_loop_label);

	tyran_generator_traverse(code, while_node->condition, while_true_label, while_false_label, TYRAN_FALSE);
	tyran_generator_define_label(code, while_true_label);
	
	tyran_reg_or_constant_index result;
	
	result = tyran_generator_traverse(code, while_node->block, 0, 0, TYRAN_TRUE);
	tyran_generator_label_reference(code, while_loop_label);
	tyran_generator_define_label(code, while_false_label);
	tyran_generator_resolve_labels(code);
	return result;
}

tyran_reg_or_constant_index tyran_generator_traverse(tyran_code_state* code, tyran_parser_node* node, tyran_label_id true_label, tyran_label_id false_label, tyran_boolean invert_logic) {
	tyran_reg_or_constant_index result;
	
	switch (node->type) {
		case TYRAN_PARSER_NODE_TYPE_OPERAND_BINARY: {
			tyran_parser_node_operand_binary* binary = (tyran_parser_node_operand_binary*)node;
			result = tyran_generator_traverse_binary(code, binary, true_label, false_label, invert_logic);
		}
		break;
		case TYRAN_PARSER_NODE_TYPE_OPERAND_UNARY: {
			tyran_parser_node_operand_unary* unary = (tyran_parser_node_operand_unary*)node;
			result = tyran_generator_traverse_unary(code, unary, true_label, false_label, invert_logic);
		}
		break;
		case TYRAN_PARSER_NODE_TYPE_IF: {
			tyran_parser_node_if* if_node = (tyran_parser_node_if*)node;
			result = tyran_generator_traverse_if(code, if_node->expression, if_node->then_block, 0);
		}
		break;
		case TYRAN_PARSER_NODE_TYPE_IF_ELSE: {
			tyran_parser_node_if_else* if_node = (tyran_parser_node_if_else*)node;
			result = tyran_generator_traverse_if(code, if_node->expression, if_node->then_block, if_node->else_block);
		}
		break;
		case TYRAN_PARSER_NODE_TYPE_WHILE: {
			tyran_parser_node_while* while_node = (tyran_parser_node_while*)node;
			result = tyran_generator_traverse_while(code, while_node, true_label, false_label);
		}
		break;
		default: {
			result = tyran_generator_handle_node(code, node);
		}
			
	}
	tyran_parser_node_print("traverse", node, 0);
	
	return result;
}
