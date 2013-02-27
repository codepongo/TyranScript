#include <tyranscript/parser/common/tyran_parser_tree.h>
#include <tyranscript/parser/common/tyran_code.h>
#include <tyranscript/parser/common/tyran_generator.h>
#include <tyranscript/parser/common/tyran_variable_scope.h>
#include <tyranscript/tyran_constants.h>

#include <tyranscript/debug/parser/tyran_print_parser_tree.h>
#include <tyranscript/debug/tyran_print_opcodes.h>

tyran_reg_or_constant_index tyran_generator_traverse(tyran_memory* memory, tyran_code_state* code, tyran_parser_node* tree, tyran_label_id true_label, tyran_label_id false_label, tyran_label_id loop_start, tyran_label_id loop_end, tyran_reg_index self_index, tyran_reg_index comparison_index, tyran_boolean invert_logic);


void tyran_generator_ret(tyran_code_state* code, tyran_reg_or_constant_index reg)
{
	tyran_reg_index ret_register;

	if (tyran_opcodes_is_constant(reg)) {
		ret_register = tyran_variable_scopes_define_temporary_variable(code->scope);
		tyran_opcodes_op_ldc(code->opcodes, ret_register, reg);
	} else {
		ret_register = reg;
	}

	tyran_opcodes_op_ret(code->opcodes, ret_register, 1);

}

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
	TYRAN_ASSERT(label_index >= 0, "Wrong label:%d", label_index);
	tyran_code_add_label_index_reference(code, label_index);
	tyran_opcodes_op_jmp(code->opcodes, 0);
}

void tyran_generator_resolve_labels(tyran_code_state* code)
{
	tyran_code_fixup_label_references(code);
}

void tyran_generator_ld(tyran_opcodes* opcodes, tyran_reg_index target_index, tyran_reg_or_constant_index source_index)
{
	if (tyran_opcodes_is_constant(source_index)) {
		tyran_opcodes_op_ldc(opcodes, target_index, source_index);
	} else {
		tyran_opcodes_op_ld(opcodes, target_index, source_index);
	}

}

tyran_generator* tyran_generator_new(tyran_memory* memory, tyran_memory_pool* generator_pool, tyran_parser_node* tree, tyran_code_state* code)
{
	tyran_generator* generator = TYRAN_CALLOC_TYPE(generator_pool, tyran_generator);
	tyran_label_id false_label = tyran_generator_prepare_label(code);
	tyran_reg_or_constant_index return_index = tyran_generator_traverse(memory, code, tree, 0, false_label, -1, -1, 0, -1, TYRAN_FALSE);

	tyran_generator_define_label(code, false_label);
	tyran_generator_ret(code, return_index);
	tyran_generator_resolve_labels(code);

	return generator;
}

tyran_constant_index tyran_generator_literal_to_constant_index(tyran_constants* constants, struct tyran_runtime* runtime, tyran_memory_pool* string_pool, tyran_memory* memory, tyran_parser_node* node)
{
	tyran_constant_index result;
	switch (node->type) {
		case TYRAN_PARSER_NODE_TYPE_BOOLEAN: {
			tyran_parser_node_boolean* boolean = (tyran_parser_node_boolean*) node;
			result = tyran_constants_add_boolean(constants, boolean->boolean);
		}
		break;
		case TYRAN_PARSER_NODE_TYPE_STRING: {
			tyran_parser_node_string* string = (tyran_parser_node_string*) node;
			const struct tyran_string* str = tyran_string_from_c_str(string_pool, memory, string->string);
			result = tyran_constants_add_string(constants, runtime, str);
		}
		break;
		case TYRAN_PARSER_NODE_TYPE_NIL:
			result = tyran_constants_add_nil(constants);
			break;
		case TYRAN_PARSER_NODE_TYPE_NUMBER: {
			tyran_parser_node_number* number = (tyran_parser_node_number*) node;
			result = tyran_constants_add_number(constants, number->number);
		}
		break;
		default:
			TYRAN_ERROR("Unknown constant:%d", node->type);
			return TYRAN_OPCODE_REGISTER_ILLEGAL;
	}

	return result;
}

tyran_reg_or_constant_index tyran_generator_logical_operator(tyran_memory* memory, tyran_code_state* code, tyran_parser_node_operand_binary* binary, tyran_label_id true_label, tyran_label_id false_label, tyran_reg_index self_index)
{
	tyran_reg_index result = tyran_variable_scopes_define_temporary_variable(code->scope);

	switch (binary->operator_type) {
		case TYRAN_PARSER_AND: {
			tyran_label_id and_false = tyran_generator_prepare_label(code);
			tyran_label_id and_true = -1;
			tyran_reg_or_constant_index left_index = tyran_generator_traverse(memory, code, binary->left, TYRAN_OPCODE_REGISTER_ILLEGAL, and_false, -1, -1, self_index, result, TYRAN_FALSE);
			tyran_opcodes_op_jbld(code->opcodes, result, left_index, TYRAN_FALSE);
			tyran_generator_label_reference(code, and_false);
			tyran_reg_or_constant_index right_index = tyran_generator_traverse(memory, code, binary->right, and_true, and_false, -1, -1, 0, result, TYRAN_FALSE);
			tyran_generator_ld(code->opcodes, result, right_index);
			tyran_generator_define_label(code, and_false);
		}
		break;
		case TYRAN_PARSER_OR: {
			TYRAN_LOG("GENERATE OR!!!!!");
			tyran_label_id or_true = tyran_generator_prepare_label(code);
			tyran_label_id or_false = false_label;
			tyran_reg_or_constant_index left_index = tyran_generator_traverse(memory, code, binary->left, TYRAN_OPCODE_REGISTER_ILLEGAL, or_true, -1, -1, self_index, result, TYRAN_TRUE);
			tyran_opcodes_op_jbld(code->opcodes, result, left_index, TYRAN_TRUE);
			tyran_generator_label_reference(code, or_true);
			tyran_reg_or_constant_index right_index = tyran_generator_traverse(memory, code, binary->right, TYRAN_OPCODE_REGISTER_ILLEGAL, or_false, -1, -1, self_index, result, TYRAN_FALSE);
			tyran_generator_ld(code->opcodes, result, right_index);
			tyran_generator_define_label(code, or_true);
		}
		break;
		default:
			result = TYRAN_OPCODE_REGISTER_ILLEGAL;
			TYRAN_ERROR("Unhandled logical operator");
	}

	return result;
}

tyran_reg_index tyran_generator_comparison_operator(tyran_code_state* code, tyran_parser_binary_operand_type operator_type, tyran_reg_index result, tyran_reg_or_constant_index left, tyran_reg_or_constant_index right, tyran_label_id true_label, tyran_label_id false_label, tyran_boolean invert_logic)
{
	tyran_opcodes* codes = code->opcodes;

	switch (operator_type) {
		case TYRAN_PARSER_EQUAL:
			tyran_opcodes_op_eq(codes, result, left, right, TYRAN_FALSE);
			break;
		case TYRAN_PARSER_NOT_EQUAL:
			TYRAN_LOG("Inserting NEQ $$$$");
			tyran_opcodes_op_eq(codes, result, left, right, TYRAN_TRUE);
			break;
		case TYRAN_PARSER_LESS:
			tyran_opcodes_op_lt(codes, result, left, right, TYRAN_FALSE);
			break;
		case TYRAN_PARSER_LESS_EQUAL:
			tyran_opcodes_op_le(codes, result, left, right, TYRAN_FALSE);
			break;
		case TYRAN_PARSER_GREATER_EQUAL:
			tyran_opcodes_op_lt(codes, result, left, right, TYRAN_TRUE);
			break;
		case TYRAN_PARSER_GREATER:
			tyran_opcodes_op_le(codes, result, left, right, TYRAN_TRUE);
			break;
		default:
			TYRAN_ERROR("Unhandled comparison operator");
	}

	return result;
}


tyran_reg_index tyran_generator_call_or_new(tyran_memory* memory, tyran_code_state* code, tyran_reg_or_constant_index function_register, tyran_reg_or_constant_index self_index, tyran_boolean is_constructor, NODE* arguments, int argument_count)
{
	int i;
	int return_value_count = 1;

	tyran_reg_index start_register = tyran_variable_scopes_top_reserve_variables(code->scope, argument_count + 1);
	tyran_opcodes_op_ld(code->opcodes, start_register, function_register);
	tyran_opcodes_op_ld(code->opcodes, start_register + 1, self_index);
	for (i = 0; i < argument_count; ++i) {
		tyran_reg_index target_index = start_register + i + 2;
		NODE node = arguments[i];
		tyran_reg_or_constant_index arg_register = tyran_generator_traverse(memory, code, node, 0, 0, -1, -1, 0, -1, TYRAN_FALSE);
		if (tyran_opcodes_is_constant(arg_register)) {
			tyran_opcodes_op_ldc(code->opcodes, target_index, arg_register);
		} else {
			tyran_opcodes_op_ld(code->opcodes, target_index, arg_register);
		}

	}
	if (is_constructor) {
		tyran_opcodes_op_new(code->opcodes, start_register, argument_count, return_value_count);
	} else {
		tyran_opcodes_op_call(code->opcodes, start_register, argument_count, return_value_count);
	}
	TYRAN_LOG("After call undefine variables");
	tyran_variable_scopes_top_undefine_variables(code->scope, start_register + 1, argument_count);
	TYRAN_LOG("After call undefine variables - done");

	return start_register;
}

void tyran_generator_argument_nodes(NODE* argument_nodes, int* index, NODE node)
{
	tyran_parser_node_operand_binary* comma = tyran_parser_binary_operator_type_cast(node, TYRAN_PARSER_COMMA);
	if (comma) {
		tyran_generator_argument_nodes(argument_nodes, index, comma->left);
		tyran_generator_argument_nodes(argument_nodes, index, comma->right);
	} else {
		tyran_parser_node_operand_unary* parentheses = tyran_parser_unary_operator_type_cast(node, TYRAN_PARSER_UNARY_PARENTHESES);
		if (parentheses) {
			tyran_generator_argument_nodes(argument_nodes, index, parentheses->expression);
		} else {
			if (node == 0) {
				return;
			}
			argument_nodes[*index] = node;
			*index = *index + 1;
		}
	}
}


tyran_reg_index tyran_generator_traverse_call(tyran_memory* memory, tyran_code_state* code, NODE function_node, NODE arguments)
{
	NODE argument_nodes[100];
	int argument_count = 0;

	tyran_generator_argument_nodes(argument_nodes, &argument_count, arguments);

	tyran_reg_or_constant_index function_register = tyran_generator_traverse(memory, code, function_node, 0, 0, -1, -1, 0, -1, TYRAN_FALSE);
	tyran_reg_index result = tyran_generator_call_or_new(memory, code, function_register, code->last_self_index, code->last_call_was_new, argument_nodes, argument_count);
	code->last_call_was_new = TYRAN_FALSE;
	code->last_self_index = 0;

	return result;
}



tyran_reg_or_constant_index tyran_generator_colon(tyran_memory* memory, tyran_code_state* code, NODE identifier_node, NODE expression, tyran_reg_index self_index)
{
	tyran_parser_node_identifier* identifier = (tyran_parser_node_identifier*) identifier_node;
	tyran_constant_index member_constant = tyran_constants_add_symbol_from_c_string(code->constants, identifier->string);
	tyran_reg_or_constant_index expression_index = tyran_generator_traverse(memory, code, expression, -1, -1, -1, -1, self_index, -1, TYRAN_FALSE);
	tyran_opcodes_op_set(code->opcodes, self_index, member_constant, expression_index);
	return expression_index;
}




tyran_reg_or_constant_index tyran_generator_create_object_with_arguments(const char* klass, tyran_memory* memory, tyran_code_state* code, int argument_count, NODE* argument_nodes)
{
	tyran_constant_index array_symbol = tyran_constants_add_symbol_from_c_string(code->constants, klass);
	tyran_constant_index constructor_symbol = tyran_constants_add_symbol_from_c_string(code->constants, "constructor");
	tyran_reg_index target = tyran_variable_scopes_define_temporary_variable(code->scope);
	tyran_reg_index self_index = tyran_variable_scopes_define_temporary_variable(code->scope);
	tyran_opcodes_op_get(code->opcodes, self_index, 0, array_symbol);
	tyran_opcodes_op_get(code->opcodes, target, self_index, constructor_symbol);


	tyran_boolean is_constructor = TYRAN_TRUE;

	tyran_reg_or_constant_index result = tyran_generator_call_or_new(memory, code, target, self_index, is_constructor, argument_nodes, argument_count);
	tyran_variable_scopes_undefine_variable(code->scope, target);
	tyran_variable_scopes_undefine_variable(code->scope, self_index);

	return result;
}

tyran_reg_or_constant_index tyran_generator_create_object(const char* klass, tyran_memory* memory, tyran_code_state* code, NODE arguments)
{
	NODE argument_nodes[100];
	int argument_count = 0;

	if (arguments) {
		tyran_generator_argument_nodes(argument_nodes, &argument_count, arguments);
	}
	return tyran_generator_create_object_with_arguments(klass, memory, code, argument_count, argument_nodes);
}

tyran_reg_or_constant_index tyran_generator_range(tyran_memory* memory, tyran_code_state* code, NODE left, NODE right, tyran_boolean inclusive)
{
	NODE arguments[3];

	arguments[0] = left;
	arguments[1] = right;
	arguments[2] = tyran_parser_bool(memory, inclusive);

	return tyran_generator_create_object_with_arguments("Range", memory, code, 3, arguments);
}


tyran_reg_or_constant_index tyran_generator_array(tyran_memory* memory, tyran_code_state* code, NODE arguments)
{
	return tyran_generator_create_object("Array", memory, code, arguments);
}

tyran_reg_or_constant_index tyran_generator_object(tyran_memory* memory, tyran_code_state* code, NODE expression)
{
	tyran_reg_or_constant_index self_index = tyran_generator_create_object("Object", memory, code, 0);
	if (expression) {
		tyran_generator_traverse(memory, code, expression, -1, -1, -1, -1, self_index, -1, TYRAN_FALSE);
	}
	return self_index;
}

tyran_reg_index tyran_generator_self_member(tyran_code_state* code, const char* string)
{
	tyran_constant_index lookup_string = tyran_constants_add_symbol_from_c_string(code->constants, string);
	tyran_reg_index self = 0;
	tyran_reg_index target = tyran_variable_scopes_define_temporary_variable(code->scope);
	tyran_opcodes_op_get(code->opcodes, target, self, lookup_string);
	return target;
}

tyran_reg_or_constant_index tyran_generator_member(tyran_memory* memory, tyran_code_state* code, NODE obj, NODE lookup, tyran_reg_index self_index)
{
	tyran_reg_index obj_register = tyran_generator_traverse(memory, code, obj, -1, -1, -1, -1, self_index, -1, TYRAN_FALSE);
	tyran_parser_node_identifier* identifier = (tyran_parser_node_identifier*) lookup;
	const char* member_name = identifier->string;

	if (tyran_strncmp(member_name, "new", 3) == 0) {
		member_name = "constructor";
		code->last_call_was_new = TYRAN_TRUE;
	} else {
		code->last_call_was_new = TYRAN_FALSE;
	}

	tyran_constant_index lookup_string = tyran_constants_add_symbol_from_c_string(code->constants, member_name);

	tyran_reg_index target = tyran_variable_scopes_define_temporary_variable(code->scope);
	code->last_self_index = obj_register;

	tyran_opcodes_op_get(code->opcodes, target, obj_register, lookup_string);

	return target;
}

tyran_reg_index tyran_generator_emit_unary_operator(tyran_code_state* code, tyran_parser_unary_operand_type operator_type, tyran_reg_or_constant_index expression)
{
	tyran_reg_index target = tyran_variable_scopes_define_temporary_variable(code->scope);
	switch (operator_type) {
		case TYRAN_PARSER_UNARY_NOT:
			tyran_opcodes_op_not(code->opcodes, target, expression);
			break;
		default:
			target = TYRAN_OPCODE_REGISTER_ILLEGAL;
			TYRAN_ERROR("Unhandled unary operator:%d", operator_type);
	}
	return target;
}

tyran_reg_index tyran_generator_emit_binary_operator(tyran_code_state* code, tyran_parser_binary_operand_type operator_type, tyran_reg_or_constant_index left, tyran_reg_or_constant_index right, tyran_label_id true_label, tyran_label_id false_label, tyran_reg_index comparison_index, tyran_boolean invert_logic)
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
			if (left == TYRAN_OPCODE_REGISTER_ILLEGAL) {
				tyran_opcodes_op_neg(codes, target, right);
			} else {
				tyran_opcodes_op_sub(codes, target, left, right);
			}
			break;
		case TYRAN_PARSER_INDEX:
			tyran_opcodes_op_index(codes, target, left, right);
			break;
		case TYRAN_PARSER_ASSIGNMENT:
			// tyran_opcodes_op_set(codes, target, left, right);
			break;
		case TYRAN_PARSER_EQUAL:
		case TYRAN_PARSER_NOT_EQUAL:
		case TYRAN_PARSER_LESS:
		case TYRAN_PARSER_LESS_EQUAL:
		case TYRAN_PARSER_GREATER:
		case TYRAN_PARSER_GREATER_EQUAL:
			tyran_generator_comparison_operator(code, operator_type, target, left, right, true_label, false_label, invert_logic);
			break;
		case TYRAN_PARSER_COMMA:
			break;
		default:
			TYRAN_ERROR("Unhandled operator:%d", operator_type);
	}

	return target;
}

tyran_reg_or_constant_index tyran_generator_handle_node(tyran_code_state* code, tyran_parser_node* node, tyran_memory_pool* string_pool, tyran_memory* memory)
{
	tyran_reg_or_constant_index result;

	if (tyran_parser_node_is_constant(node)) {
		result = tyran_generator_literal_to_constant_index(code->constants, code->runtime, string_pool, memory, node);
	} else if (node->type == TYRAN_PARSER_NODE_TYPE_IDENTIFIER) {
		tyran_parser_node_identifier* identifier = (tyran_parser_node_identifier*) node;
		result = tyran_variable_scopes_get_identifier(code->scope, identifier->string);
		if (result == TYRAN_OPCODE_REGISTER_ILLEGAL) {
			code->last_self_index = 0;
			result = tyran_generator_self_member(code, identifier->string);
		}
	} else {
		TYRAN_ERROR("Illegal node");
		result = TYRAN_OPCODE_REGISTER_ILLEGAL;
	}

	return result;
}

tyran_reg_or_constant_index tyran_generator_handle_binary_operator(tyran_code_state* code, tyran_parser_node_operand_binary* binary, tyran_reg_or_constant_index left, tyran_reg_or_constant_index right, tyran_label_id true_label, tyran_label_id false_label, tyran_reg_index comparison_index, tyran_boolean invert_logic)
{
	return tyran_generator_emit_binary_operator(code, binary->operator_type, left, right, true_label, false_label, comparison_index, invert_logic);
}

tyran_reg_or_constant_index tyran_generator_traverse_default_binary(tyran_memory* memory, tyran_code_state* code, tyran_parser_node_operand_binary* binary, tyran_label_id true_label, tyran_label_id false_label, tyran_label_id loop_start, tyran_label_id loop_end, tyran_reg_index self_index, tyran_reg_index comparison_index, tyran_boolean invert_logic)
{
	tyran_reg_or_constant_index left_index = TYRAN_OPCODE_REGISTER_ILLEGAL;
	if (binary->left) {
		left_index = tyran_generator_traverse(memory, code, binary->left, true_label, false_label, loop_start, loop_end, self_index, -1, invert_logic);
	}
	tyran_reg_or_constant_index right_index = tyran_generator_traverse(memory, code, binary->right, true_label, false_label, loop_start, loop_end, self_index, -1, invert_logic);

	tyran_reg_or_constant_index target_index;
	if (binary->operator_type != TYRAN_PARSER_CONCAT) {
		target_index = tyran_generator_handle_binary_operator(code, binary, left_index, right_index, true_label, false_label, comparison_index, invert_logic);
	} else {
		target_index = right_index;
	}
	return target_index;
}

void tyran_generator_assignment_opcode(tyran_opcodes* opcodes, tyran_parser_binary_operand_type type, tyran_reg_index target_index, tyran_reg_or_constant_index source_index)
{
	switch (type) {
		case TYRAN_PARSER_ASSIGNMENT:
			tyran_generator_ld(opcodes, target_index, source_index);
			break;
		case TYRAN_PARSER_ASSIGNMENT_ADD:
			tyran_opcodes_op_add(opcodes, target_index, target_index, source_index);
			break;
		case TYRAN_PARSER_ASSIGNMENT_SUBTRACT:
			tyran_opcodes_op_sub(opcodes, target_index, target_index, source_index);
			break;
		case TYRAN_PARSER_ASSIGNMENT_MULTIPLY:
			tyran_opcodes_op_mul(opcodes, target_index, target_index, source_index);
			break;
		case TYRAN_PARSER_ASSIGNMENT_DIVIDE:
			tyran_opcodes_op_div(opcodes, target_index, target_index, source_index);
			break;
		case TYRAN_PARSER_ASSIGNMENT_MODULUS:
			tyran_opcodes_op_mod(opcodes, target_index, target_index, source_index);
			break;
		default:
			break;
	}
}

tyran_reg_or_constant_index tyran_generator_traverse_assignment(tyran_memory* memory, tyran_code_state* code, tyran_parser_node_operand_binary* binary, tyran_label_id true_label, tyran_label_id false_label, tyran_label_id loop_start, tyran_label_id loop_end, tyran_reg_index self_index)
{
	tyran_reg_or_constant_index source_index = tyran_generator_traverse(memory, code, binary->right, -1, -1, loop_start, loop_end, self_index, -1, TYRAN_FALSE);

	if (binary->left->type == TYRAN_PARSER_NODE_TYPE_IDENTIFIER) {
		tyran_parser_node_identifier* identifier = (tyran_parser_node_identifier*) binary->left;
		tyran_reg_index target_index = tyran_variable_scopes_define_identifier(memory, code->scope, identifier->string);
		tyran_generator_assignment_opcode(code->opcodes, binary->operator_type, target_index, source_index);
		return source_index;
	} else {
		tyran_parser_node_operand_binary* index = tyran_parser_binary_operator_type_cast(binary->left, TYRAN_PARSER_INDEX);
		if (index) {
			tyran_reg_index object_index = tyran_generator_traverse(memory, code, index->left, true_label, false_label, loop_start, loop_end, self_index, -1, TYRAN_FALSE);
			tyran_reg_or_constant_index lookup_index = tyran_generator_traverse(memory, code, index->right, true_label, false_label, loop_start, loop_end, self_index, -1, TYRAN_FALSE);
			if (binary->operator_type != TYRAN_PARSER_ASSIGNMENT) {
				tyran_reg_index target_index = tyran_variable_scopes_define_temporary_variable(code->scope);
				tyran_opcodes_op_index(code->opcodes, target_index, object_index, lookup_index);
				tyran_generator_assignment_opcode(code->opcodes, binary->operator_type, target_index, source_index);
				tyran_opcodes_op_index_set(code->opcodes, object_index, lookup_index, target_index);
				// tyran_variable_scopes_undefine_variable(code->scope, target_index);
				return source_index;
			} else {
				tyran_opcodes_op_index_set(code->opcodes, object_index, lookup_index, source_index);
				return source_index;
			}
		} else {
			tyran_parser_node_operand_binary* member = tyran_parser_binary_operator_type_cast(binary->left, TYRAN_PARSER_MEMBER);
			if (member) {
				tyran_reg_index object_index = tyran_generator_traverse(memory, code, member->left, true_label, false_label, loop_start, loop_end, self_index, -1, TYRAN_FALSE);
				tyran_parser_node_identifier* identifier = (tyran_parser_node_identifier*) member->right;

				tyran_constant_index lookup_index = tyran_constants_add_symbol_from_c_string(code->constants, identifier->string);
				if (binary->operator_type != TYRAN_PARSER_ASSIGNMENT) {
					tyran_reg_index target_index = tyran_variable_scopes_define_temporary_variable(code->scope);
					tyran_opcodes_op_get(code->opcodes, target_index, object_index, lookup_index);
					tyran_generator_assignment_opcode(code->opcodes, binary->operator_type, target_index, source_index);
					tyran_opcodes_op_set(code->opcodes, object_index, lookup_index, target_index);
					// tyran_variable_scopes_undefine_variable(code->scope, target_index);
					return source_index;
				} else {
					tyran_opcodes_op_set(code->opcodes, object_index, lookup_index, source_index);
					return source_index;
				}
			} else {
				tyran_parser_node_print("Unknown", &binary->left, 0);
				TYRAN_ERROR("Unknown type:%d", binary->left->type);
			}
		}
	}

	return TYRAN_OPCODE_REGISTER_ILLEGAL;
}

tyran_reg_or_constant_index tyran_generator_traverse_binary(tyran_memory* memory, tyran_code_state* code, tyran_parser_node_operand_binary* binary, tyran_label_id true_label, tyran_label_id false_label, tyran_label_id loop_start, tyran_label_id loop_end, tyran_reg_index self_index, tyran_reg_index comparison_index, tyran_boolean invert_logic)
{
	tyran_reg_or_constant_index result;
	switch (binary->operator_type) {
		case TYRAN_PARSER_ASSIGNMENT:
		case TYRAN_PARSER_ASSIGNMENT_ADD:
		case TYRAN_PARSER_ASSIGNMENT_SUBTRACT:
		case TYRAN_PARSER_ASSIGNMENT_MULTIPLY:
		case TYRAN_PARSER_ASSIGNMENT_DIVIDE:
		case TYRAN_PARSER_ASSIGNMENT_MODULUS:
			result = tyran_generator_traverse_assignment(memory, code, binary, true_label, false_label, -1, -1, self_index);
			break;
		case TYRAN_PARSER_AND:
		case TYRAN_PARSER_OR:
			result = tyran_generator_logical_operator(memory, code, binary, true_label, false_label, self_index);
			break;
		case TYRAN_PARSER_CALL:
			result = tyran_generator_traverse_call(memory, code, binary->left, binary->right);
			break;
		case TYRAN_PARSER_MEMBER:
			result = tyran_generator_member(memory, code, binary->left, binary->right, self_index);
			break;
		case TYRAN_PARSER_COLON:
			result = tyran_generator_colon(memory, code, binary->left, binary->right, self_index);
			break;
		case TYRAN_PARSER_RANGE_INCLUSIVE:
			result = tyran_generator_range(memory, code, binary->left, binary->right, TYRAN_TRUE);
			break;
		case TYRAN_PARSER_RANGE:
			result = tyran_generator_range(memory, code, binary->left, binary->right, TYRAN_FALSE);
			break;
		default:
			result = tyran_generator_traverse_default_binary(memory, code, binary, true_label, false_label, loop_start, loop_end, self_index, comparison_index, invert_logic);
			break;
	}

	return result;
}

tyran_reg_or_constant_index tyran_generator_traverse_default_unary(tyran_memory* memory, tyran_code_state* code, tyran_parser_node_operand_unary* unary,tyran_label_id true_label, tyran_label_id false_label, tyran_label_id loop_start, tyran_label_id loop_end, tyran_reg_index self_index, tyran_reg_index comparison_index, tyran_boolean invert_logic)
{
	tyran_reg_or_constant_index expression_index = tyran_generator_traverse(memory, code, unary->expression, true_label, false_label, loop_start, loop_end, self_index, comparison_index, invert_logic);
	return tyran_generator_emit_unary_operator(code, unary->operator_type, expression_index);
}

tyran_reg_or_constant_index tyran_generator_traverse_unary(tyran_memory* memory, tyran_code_state* code, tyran_parser_node_operand_unary* unary, tyran_label_id true_label, tyran_label_id false_label, tyran_label_id loop_start, tyran_label_id loop_end, tyran_reg_index self_index, tyran_reg_index comparison_index, tyran_boolean invert_logic)
{
	switch (unary->operator_type) {
		case TYRAN_PARSER_UNARY_ARRAY:
			return tyran_generator_array(memory, code, unary->expression);
		case TYRAN_PARSER_UNARY_OBJECT:
			return tyran_generator_object(memory, code, unary->expression);
		case TYRAN_PARSER_UNARY_BLOCK:
			if (!unary->expression) {
				tyran_reg_or_constant_index result = tyran_variable_scopes_define_temporary_variable(code->scope);
				
				return result;
			}
		case TYRAN_PARSER_UNARY_IF:
		case TYRAN_PARSER_UNARY_UNLESS:
		case TYRAN_PARSER_UNARY_PARENTHESES:
		case TYRAN_PARSER_UNARY_BRACKET:
			return tyran_generator_traverse(memory, code, unary->expression, true_label, false_label, loop_start, loop_end, self_index, comparison_index, invert_logic);
		default:
			return tyran_generator_traverse_default_unary(memory, code, unary, true_label, false_label, loop_start, loop_end, self_index, comparison_index, invert_logic);
	}
}

tyran_reg_or_constant_index tyran_generator_traverse_if(tyran_memory* memory, tyran_code_state* code, tyran_parser_node* expression, tyran_parser_node* then_node, tyran_parser_node* else_node, tyran_label_id loop_start, tyran_label_id loop_end, tyran_reg_index self_index, tyran_boolean invert)
{
	tyran_label_id if_false_label = tyran_generator_prepare_label(code);

	tyran_reg_or_constant_index expression_index = tyran_generator_traverse(memory, code, expression, -1, -1, loop_start, loop_end, self_index, -1, invert);

	tyran_opcodes_op_jb(code->opcodes, expression_index, invert);
	tyran_generator_label_reference(code, if_false_label);

	tyran_reg_or_constant_index result = tyran_variable_scopes_define_temporary_variable(code->scope);


	tyran_reg_or_constant_index then_index = tyran_generator_traverse(memory, code, then_node, -1, -1, loop_start, loop_end, self_index, -1, TYRAN_TRUE);
	if (then_index != TYRAN_OPCODE_REGISTER_ILLEGAL) {
		tyran_generator_ld(code->opcodes, result, then_index);
	}
	if (else_node) {
		int end_of_if = tyran_generator_prepare_label(code);
		tyran_generator_label_reference(code, end_of_if);
		tyran_generator_define_label(code, if_false_label);

		tyran_reg_or_constant_index else_index = tyran_generator_traverse(memory, code, else_node, -1, -1, loop_start, loop_end, self_index, -1, TYRAN_TRUE);
		tyran_generator_ld(code->opcodes, result, else_index);

		tyran_generator_define_label(code, end_of_if);
	} else {
		tyran_generator_define_label(code, if_false_label);
	}

	return result;
}

tyran_reg_or_constant_index tyran_generator_traverse_while(tyran_memory* memory, tyran_code_state* code, tyran_parser_node_while* while_node, tyran_label_id true_label, tyran_label_id false_label, tyran_reg_index self_index, tyran_boolean invert_logic)
{
	tyran_label_id while_true_label = tyran_generator_prepare_label(code);
	tyran_label_id while_false_label = tyran_generator_prepare_label(code);
	tyran_label_id while_loop_label = tyran_generator_prepare_label(code);

	tyran_generator_define_label(code, while_loop_label);

	tyran_reg_or_constant_index expression_index = tyran_generator_traverse(memory, code, while_node->condition, while_true_label, while_false_label, while_loop_label, while_false_label, self_index, -1, invert_logic);
	tyran_opcodes_op_jb(code->opcodes, expression_index, invert_logic);
	tyran_generator_label_reference(code, while_false_label);

	tyran_generator_define_label(code, while_true_label);

	tyran_reg_or_constant_index result;

	result = tyran_generator_traverse(memory, code, while_node->block, 0, 0, while_loop_label, while_false_label, self_index, -1, TYRAN_TRUE);
	tyran_generator_label_reference(code, while_loop_label);
	tyran_generator_define_label(code, while_false_label);
	return result;
}


tyran_reg_or_constant_index tyran_generator_traverse_return(tyran_memory* memory, tyran_code_state* code, tyran_parser_node_return* return_node, tyran_label_id true_label, tyran_label_id false_label, tyran_reg_index self_index, tyran_boolean invert_logic)
{
	tyran_reg_or_constant_index return_index;
	if (return_node->expression) {
		return_index = tyran_generator_traverse(memory, code, return_node->expression, true_label, false_label, -1, -1, self_index, -1, invert_logic);
	} else {
		return_index = tyran_variable_scopes_define_temporary_variable(code->scope);
	}

	tyran_generator_ret(code, return_index);

	return return_index;
}


void tyran_generator_traverse_when(tyran_memory* memory, tyran_code_state* code, tyran_reg_or_constant_index compare_register, tyran_parser_node_when* when_node, tyran_label_id end_of_case_label, tyran_label_id loop_start, tyran_label_id loop_end, tyran_reg_index comparison_index, tyran_reg_index self_index)
{
	tyran_reg_index target = tyran_variable_scopes_define_temporary_variable(code->scope);

	tyran_reg_or_constant_index value_register = tyran_generator_traverse(memory, code, when_node->expression, TYRAN_OPCODE_REGISTER_ILLEGAL, TYRAN_OPCODE_REGISTER_ILLEGAL, loop_start, loop_end, self_index, -1, TYRAN_FALSE);
	tyran_opcodes_op_eq(code->opcodes, target, compare_register, value_register, TYRAN_FALSE);
	tyran_label_id end_of_when_label = tyran_generator_prepare_label(code);

	tyran_opcodes_op_jb(code->opcodes, target, TYRAN_FALSE);
	tyran_generator_label_reference(code, end_of_when_label);

	tyran_generator_traverse(memory, code, when_node->block, TYRAN_OPCODE_REGISTER_ILLEGAL, TYRAN_OPCODE_REGISTER_ILLEGAL, loop_start, loop_end, self_index, -1, TYRAN_FALSE);
	tyran_generator_label_reference(code, end_of_case_label);
	tyran_generator_define_label(code, end_of_when_label);
}

tyran_reg_or_constant_index tyran_generator_traverse_case(tyran_memory* memory, tyran_code_state* code, tyran_parser_node_case* case_node, tyran_reg_index self_index)
{
	tyran_reg_or_constant_index compare_register = tyran_generator_traverse(memory, code, case_node->expression, 0, 0, -1, -1, self_index, -1, TYRAN_FALSE);
	TYRAN_LOG("Compare register:%d", compare_register);
	tyran_label_id end_of_case_label = tyran_generator_prepare_label(code);

	for (int i = 0; i < case_node->when_count; ++i) {
		TYRAN_LOG("When:%d", compare_register);
		tyran_generator_traverse_when(memory, code, compare_register, case_node->whens[i], end_of_case_label, -1, -1, -1, self_index);
	}

	tyran_generator_define_label(code, end_of_case_label);
	return compare_register;
}




void tyran_generator_traverse_function_parameters(tyran_memory* memory, tyran_code_state* code, tyran_parser_node_function* func_node)
{
	for (int i = 0; i < func_node->parameter_count; ++i) {
		tyran_parser_node_parameter parameter = func_node->parameters[i];
		tyran_reg_index parameter_index = tyran_variable_scopes_define_identifier(memory, code->scope, parameter.identifier->string);
		if (parameter.default_value) {
			tyran_constant_index constant_index = tyran_generator_literal_to_constant_index(code->constants, code->runtime, code->string_pool, memory, parameter.default_value);
			tyran_opcodes_op_ldcn(code->opcodes, parameter_index, constant_index);
		}
	}
}


tyran_reg_or_constant_index tyran_generator_traverse_function(tyran_code_state* original_code, tyran_parser_node_function* func_node, tyran_memory_pool* opcodes_pool, tyran_memory_pool* function_pool, tyran_memory_pool* variable_info_pool, tyran_memory_pool* register_pool, tyran_memory* memory)
{
	tyran_code_state* code = tyran_code_clone(original_code);

	tyran_variable_scopes_push_scope(code->scope, memory, variable_info_pool, register_pool);

	tyran_generator_traverse_function_parameters(memory, code, func_node);

	tyran_reg_or_constant_index temp_index = tyran_generator_traverse(memory, code, func_node->block, TYRAN_OPCODE_REGISTER_ILLEGAL, TYRAN_OPCODE_REGISTER_ILLEGAL, -1, -1, 0, -1, 0);
	tyran_generator_ret(code, temp_index);

	tyran_variable_scopes_pop_scope(code->scope);
	tyran_generator_resolve_labels(code);
	tyran_print_opcodes(code->opcodes, 0, code->constants);

	tyran_reg_index function_object_index = tyran_variable_scopes_define_temporary_variable(original_code->scope);
	tyran_constant_index function_constant_index = tyran_constants_add_function(function_pool, original_code->constants, code->constants, code->opcodes);
	tyran_opcodes_op_func(original_code->opcodes, function_object_index, function_constant_index);

	return function_object_index;
}

tyran_reg_or_constant_index tyran_generator_traverse_for(tyran_memory* memory, tyran_code_state* code, tyran_parser_node_for* for_node, tyran_reg_index self_index)
{
	tyran_reg_or_constant_index collection_register = tyran_generator_traverse(memory, code, for_node->collection, TYRAN_OPCODE_REGISTER_ILLEGAL, TYRAN_OPCODE_REGISTER_ILLEGAL, -1, -1, self_index, -1, TYRAN_FALSE);


	const char* key_variable_name = for_node->value_variable->string;
	tyran_reg_index key_register = tyran_variable_scopes_define_identifier(memory, code->scope, key_variable_name);
	// tyran_reg_or_constant_index key = tyran_variable_scopes_define_identifier(memory, code->scope, key_variable_name);


	tyran_reg_index iterator_register = tyran_variable_scopes_define_temporary_variable(code->scope);
	tyran_opcodes_op_iter(code->opcodes, iterator_register, collection_register);

	tyran_label_id start_of_for_loop = tyran_generator_prepare_label(code);
	tyran_generator_define_label(code, start_of_for_loop);

	tyran_label_id end_of_for_loop = tyran_generator_prepare_label(code);
	tyran_opcodes_op_next(code->opcodes, key_register, iterator_register);
	tyran_generator_label_reference(code, end_of_for_loop);

	tyran_generator_traverse(memory, code, for_node->block, start_of_for_loop, end_of_for_loop, start_of_for_loop, end_of_for_loop, self_index, -1, TYRAN_FALSE);
	tyran_generator_label_reference(code, start_of_for_loop);
	tyran_generator_define_label(code, end_of_for_loop);

	tyran_variable_scopes_undefine_variable(code->scope, iterator_register);

	return key_register;
}

tyran_reg_or_constant_index tyran_generator_traverse(tyran_memory* memory, tyran_code_state* code, tyran_parser_node* node, tyran_label_id true_label, tyran_label_id false_label, tyran_label_id loop_start, tyran_label_id loop_end, tyran_reg_index self_index, tyran_reg_index comparison_index, tyran_boolean invert_logic)
{
	tyran_reg_or_constant_index result;

	switch (node->type) {
		case TYRAN_PARSER_NODE_TYPE_OPERAND_BINARY: {
			tyran_parser_node_operand_binary* binary = (tyran_parser_node_operand_binary*)node;
			result = tyran_generator_traverse_binary(memory, code, binary, true_label, false_label, loop_start, loop_end, self_index, comparison_index, invert_logic);
		}
		break;
		case TYRAN_PARSER_NODE_TYPE_OPERAND_UNARY: {
			tyran_parser_node_operand_unary* unary = (tyran_parser_node_operand_unary*)node;
			result = tyran_generator_traverse_unary(memory, code, unary, true_label, false_label, loop_start, loop_end, self_index, comparison_index, invert_logic);
		}
		break;
		case TYRAN_PARSER_NODE_TYPE_IF: {
			tyran_parser_node_if* if_node = (tyran_parser_node_if*)node;
			result = tyran_generator_traverse_if(memory, code, if_node->expression, if_node->then_block, 0, loop_start, loop_end, self_index, if_node->invert);
		}
		break;
		case TYRAN_PARSER_NODE_TYPE_IF_ELSE: {
			tyran_parser_node_if_else* if_node = (tyran_parser_node_if_else*)node;
			result = tyran_generator_traverse_if(memory, code, if_node->expression, if_node->then_block, if_node->else_block, loop_start, loop_end, self_index, if_node->invert);
		}
		break;
		case TYRAN_PARSER_NODE_TYPE_WHILE:
		case TYRAN_PARSER_NODE_TYPE_UNTIL: {
			tyran_parser_node_while* while_node = (tyran_parser_node_while*)node;
			result = tyran_generator_traverse_while(memory, code, while_node, true_label, false_label, self_index, node->type == TYRAN_PARSER_NODE_TYPE_UNTIL);
		}
		break;
		case TYRAN_PARSER_NODE_TYPE_RETURN: {
			tyran_parser_node_return* return_node = (tyran_parser_node_return*)node;
			result = tyran_generator_traverse_return(memory, code, return_node, true_label, false_label, self_index, TYRAN_FALSE);
		}
		break;
		case TYRAN_PARSER_NODE_TYPE_CASE: {
			tyran_parser_node_case* case_node = (tyran_parser_node_case*)node;
			result = tyran_generator_traverse_case(memory, code, case_node, self_index);
		}
		break;
		case TYRAN_PARSER_NODE_TYPE_FOR: {
			tyran_parser_node_for* for_node = (tyran_parser_node_for*)node;
			result = tyran_generator_traverse_for(memory, code, for_node, self_index);
		}
		break;
		case TYRAN_PARSER_NODE_TYPE_FUNCTION: {
			tyran_parser_node_function* func_node = (tyran_parser_node_function*)node;
			result = tyran_generator_traverse_function(code, func_node, code->opcodes_pool, code->function_pool, code->variable_info_pool, code->register_pool, code->memory);
		}
		break;
		case TYRAN_PARSER_NODE_TYPE_SELF: {
			result = self_index;
		}
		break;
		case TYRAN_PARSER_NODE_TYPE_BREAK: {
			result = TYRAN_OPCODE_REGISTER_ILLEGAL;
			tyran_generator_label_reference(code, loop_end);
		}
		break;
		case TYRAN_PARSER_NODE_TYPE_CONTINUE: {
			result = TYRAN_OPCODE_REGISTER_ILLEGAL;
			tyran_generator_label_reference(code, loop_start);
		}
		break;
		default: {
			result = tyran_generator_handle_node(code, node, code->string_pool, code->memory);
		}

	}

	return result;
}
