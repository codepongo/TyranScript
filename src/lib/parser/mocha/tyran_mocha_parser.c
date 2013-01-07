#include <tyranscript/parser/mocha/tyran_mocha_lexer.h>
#include <tyranscript/parser/mocha/tyran_mocha_parser.h>
#include <tyranscript/debug/mocha/tyran_mocha_lexer_debug.h>
#include <tyranscript/debug/mocha/tyran_mocha_parser_debug.h>
#include <tyranscript/debug/parser/tyran_print_parser_tree.h>
#include <tyranscript/parser/common/tyran_parser_tree.h>

typedef struct tyran_mocha_operator_info {
	tyran_mocha_token_id token_id;
	int direction;
	int is_enclosing;
	int precedence;
} tyran_mocha_operator_info;


tyran_mocha_operator_info tyran_mocha_parser_get_operator_info(tyran_mocha_token_id token_id)
{
	tyran_mocha_operator_info operands_to_match[] = {
		{TYRAN_MOCHA_TOKEN_ASSIGNMENT, 1, 0},
		{TYRAN_MOCHA_TOKEN_AND, 1, 0},
		{TYRAN_MOCHA_TOKEN_OR, 1, 0},
		{TYRAN_MOCHA_TOKEN_EQUAL, 1, 0},
		{TYRAN_MOCHA_TOKEN_NOT_EQUAL, 1, 0},
		{TYRAN_MOCHA_TOKEN_LESS, 1, 0},
		{TYRAN_MOCHA_TOKEN_LESS_EQUAL, 1, 0},
		{TYRAN_MOCHA_TOKEN_GREATER, 1, 0},
		{TYRAN_MOCHA_TOKEN_GREATER_EQUAL, 1, 0},
		{TYRAN_MOCHA_TOKEN_IF, 1, 0},
		{TYRAN_MOCHA_TOKEN_UNLESS, 1, 0},
		{TYRAN_MOCHA_TOKEN_WHILE, 1, 0},
		{TYRAN_MOCHA_TOKEN_UNTIL, 1, 0},
		{TYRAN_MOCHA_TOKEN_FOR, 1, 0},
		{TYRAN_MOCHA_TOKEN_CASE, 1, 0},
		{TYRAN_MOCHA_TOKEN_WHEN, 1, 0},
		{TYRAN_MOCHA_TOKEN_RETURN, 1, 0},
		{TYRAN_MOCHA_TOKEN_THEN, 1, 0},
		{TYRAN_MOCHA_TOKEN_ELSE, 1, 0},
		{TYRAN_MOCHA_TOKEN_BLOCK_START, 1, 1},
		{TYRAN_MOCHA_TOKEN_BLOCK_END, 1, 1},
		{TYRAN_MOCHA_TOKEN_NOT_EQUAL, 1, 0},
		{TYRAN_MOCHA_TOKEN_IN, 1, 0},
		{TYRAN_MOCHA_TOKEN_COMMA, 1, 0},
		{TYRAN_MOCHA_TOKEN_COLON, 1, 0},
		{TYRAN_MOCHA_TOKEN_ADD, 1, 0},
		{TYRAN_MOCHA_TOKEN_SUBTRACT, 1, 0},
		{TYRAN_MOCHA_TOKEN_MULTIPLY, 1, 0},
		{TYRAN_MOCHA_TOKEN_MODULUS, 1, 0},
		{TYRAN_MOCHA_TOKEN_DIVIDE, 1, 0},
		{TYRAN_MOCHA_TOKEN_CALL, 1, 0},
		{TYRAN_MOCHA_TOKEN_INDEX, 1, 0},
		{TYRAN_MOCHA_TOKEN_MEMBER, 1, 0},
		{TYRAN_MOCHA_TOKEN_RANGE_EXCLUSIVE, 1, 0},
		{TYRAN_MOCHA_TOKEN_RANGE_INCLUSIVE, 1, 0},
		{TYRAN_MOCHA_TOKEN_LINE_START, 1, 1},
		{TYRAN_MOCHA_TOKEN_FUNCTION_GLYPH, 1, 0},
		{TYRAN_MOCHA_TOKEN_FUNCTION_GLYPH_BOUND, 1, 0},
		{TYRAN_MOCHA_TOKEN_BRACKET_RIGHT, 1, 1},
		{TYRAN_MOCHA_TOKEN_PARENTHESES_RIGHT, 1, 1},
		{TYRAN_MOCHA_TOKEN_OBJECT_END, 1, 1},
	};

	size_t i;
	for (i = 0; i < sizeof(operands_to_match) / sizeof(tyran_mocha_operator_info); ++i) {
		if (operands_to_match[i].token_id == token_id) {
			operands_to_match[i].precedence = i;
			return operands_to_match[i];
		}
	}
	
	tyran_mocha_operator_info empty;
	
	empty.token_id = TYRAN_MOCHA_TOKEN_END;
	
	return empty;
}

tyran_mocha_parser_enclosure_stack* tyran_mocha_parser_enclosure_stack_new(tyran_memory_pool* enclosure_pool, tyran_memory* memory, tyran_memory_pool* enclosure_info_pool)
{
	tyran_mocha_parser_enclosure_stack* stack = TYRAN_MALLOC_TYPE(enclosure_pool, tyran_mocha_parser_enclosure_stack);
	stack->length = 0;
	stack->alloc_size = 100;
	stack->nodes = TYRAN_MALLOC_NO_POOL_TYPE_COUNT(memory, tyran_mocha_parser_enclosure_info, stack->alloc_size);
	return stack;
}

void tyran_mocha_parser_enclosure_stack_free(tyran_mocha_parser_enclosure_stack* stack)
{
	TYRAN_MALLOC_FREE(stack->nodes);
	TYRAN_MALLOC_FREE(stack);
}

void tyran_mocha_parser_enclosure_stack_push(tyran_mocha_parser_enclosure_stack* stack, NODE* root, tyran_parser_node_operand_unary* enclosure_node, tyran_mocha_token_id start_enclosure_id)
{
	tyran_mocha_parser_enclosure_info* destination = &stack->nodes[stack->length++];
	destination->start_token_id = start_enclosure_id;
	destination->root = root;
	destination->enclosure_node = enclosure_node;
}

NODE tyran_mocha_parser_concat_peek_helper(NODE node, int* count)
{
	NODE result = 0;
	tyran_parser_node_operand_binary* binary = tyran_parser_binary_operator_type_cast(node, TYRAN_PARSER_CONCAT);
	if (binary) {
		result = tyran_mocha_parser_concat_peek_helper(binary->left, count);
		*count = *count - 1;
		if (*count >= 0) {
			result = tyran_mocha_parser_concat_peek_helper(binary->right, count);
			*count = *count - 1;
		}
		
	} else if (*count == 0) {
		result = node;
	}
	
	return result;
}


NODE tyran_mocha_parser_concat_peek_position(tyran_mocha_parser* parser, int position) {
	// tyran_parser_node_print("PEEK_POSITION", &parser->original_root, parser->root);
	return tyran_mocha_parser_concat_peek_helper(*parser->root, &position);
}


NODE tyran_mocha_parser_concat_peek(tyran_mocha_parser* parser) {
	// tyran_parser_node_print("PEEK", &parser->original_root, parser->root);
	return tyran_mocha_parser_concat_peek_position(parser, 0);
}

NODE* tyran_mocha_parser_last_node_helper(NODE* parent, NODE* node, tyran_boolean use_operator)
{
	tyran_parser_node_operand_binary* binary = tyran_parser_binary_operator_cast(*node);
	if (binary) {
		return tyran_mocha_parser_last_node_helper(node, &binary->left, use_operator);
	}
	if (use_operator) {
		return parent;
	} else {
		return node;
	}
}

NODE* tyran_mocha_parser_last_node(tyran_mocha_parser* parser)
{
	return tyran_mocha_parser_last_node_helper(parser->root, parser->root, TYRAN_FALSE);
}

NODE* tyran_mocha_parser_last_operator_node(tyran_mocha_parser* parser)
{
	return tyran_mocha_parser_last_node_helper(parser->root, parser->root, TYRAN_TRUE);
}

tyran_mocha_parser_enclosure_info tyran_mocha_parser_enclosure_stack_pop(tyran_mocha_parser_enclosure_stack* stack)
{
	TYRAN_ASSERT(stack->length > 0, "You popped too much");
	return stack->nodes[--stack->length];
}


void tyran_mocha_parser_push_right(tyran_mocha_parser* parser,tyran_parser_node_operand_binary* node, NODE* old_parent)
{
	node->right = *old_parent;
	*old_parent = (NODE)node;
	parser->next_node_to_overwrite = &node->left;
	TYRAN_LOG("**overwrite = %lu", (unsigned long) parser->next_node_to_overwrite);
}

NODE* tyran_mocha_parser_actual_root_helper(NODE* node)
{
	tyran_parser_node_operand_binary* binary = tyran_parser_binary_operator_type_cast(*node, TYRAN_PARSER_CONCAT);
	if (binary) {
		return tyran_mocha_parser_actual_root_helper(&binary->left);
	}
	
	return node;
}

NODE* tyran_mocha_parser_actual_root(tyran_mocha_parser* parser)
{
	NODE* actual_root = tyran_mocha_parser_actual_root_helper(parser->root);
	return actual_root;
}

void tyran_mocha_parser_push_root_right(tyran_mocha_parser* parser, tyran_parser_node_operand_binary* node, int precedence)
{
	NODE* actual_root = tyran_mocha_parser_actual_root(parser);
	NODE print_node= (NODE) node;
	tyran_parser_node_print("PUSH ROOT DOWN:", parser->root, &print_node);
	parser->root_precedence = precedence;
	parser->last_precedence = -1;
	tyran_mocha_parser_push_right(parser, node, actual_root);
}

void tyran_mocha_parser_push_last_inserted_right(tyran_mocha_parser* parser, tyran_parser_node_operand_binary* node, int precedence)
{
	NODE print_node= (NODE) node;
	tyran_parser_node_print("PUSH LAST DOWN:", parser->root, &print_node);
	NODE* last_node = tyran_mocha_parser_last_node(parser);
	parser->last_precedence = precedence;
	tyran_mocha_parser_push_right(parser, node, last_node);
}

void tyran_mocha_parser_push_last_operator_right(tyran_mocha_parser* parser, tyran_parser_node_operand_binary* node, int precedence)
{
	NODE print_node= (NODE) node;
	tyran_parser_node_print("PUSH LAST OPERATOR DOWN:", parser->root, &print_node);
	NODE* last_node = tyran_mocha_parser_last_operator_node(parser);
	tyran_mocha_parser_push_right(parser, node, last_node);
	parser->last_precedence = precedence;
}


NODE tyran_mocha_parser_concat_pop_helper(tyran_mocha_parser* parser, NODE* parent, NODE* node, NODE* sibling) {
	NODE result;
	tyran_parser_node_operand_binary* binary = tyran_parser_binary_operator_type_cast(*node, TYRAN_PARSER_CONCAT);
	if (binary) {
		return tyran_mocha_parser_concat_pop_helper(parser, node, &binary->left, &binary->right);
	}

	result = *node;

	if (sibling) {
		*parent = *sibling;
		*sibling = 0;
		*node = 0;
		parser->next_node_to_overwrite = 0;
	} else {
		parser->next_node_to_overwrite = parent;
	}
	return result;
}

NODE tyran_mocha_parser_concat_pop(tyran_mocha_parser* parser) {
	// tyran_mocha_parser_node_print_tree(parser, "BEFORE CONCAT POP", 0);
	NODE result = tyran_mocha_parser_concat_pop_helper(parser, parser->root, parser->root, 0);
	// tyran_mocha_parser_node_print_tree(parser, "AFTER CONCAT POP", 0);
	return result;
}

void tyran_mocha_parser_parameters(tyran_parser_node_parameter* parameter_nodes, int* index, NODE node)
{
	tyran_parser_node_operand_binary* binary = tyran_parser_binary_operator_cast(node);
	if (binary && (binary->operator_type == TYRAN_PARSER_COMMA || binary->operator_type == TYRAN_PARSER_CONCAT)) {
		tyran_mocha_parser_parameters(parameter_nodes, index, binary->left);
		tyran_mocha_parser_parameters(parameter_nodes, index, binary->right);
	} else {
		tyran_parser_node_parameter parameter_node;
		if (binary && (binary->operator_type ==  TYRAN_PARSER_ASSIGNMENT)) {
			parameter_node.default_value = binary->right;
			node = binary->left;
		} else {
			parameter_node.default_value = 0;
		}
		parameter_node.identifier = (tyran_parser_node_identifier*) node;
		parameter_nodes[*index] = parameter_node;
		*index = *index + 1;
	}
}

void tyran_mocha_parser_define_function_parameters(tyran_memory* memory, tyran_parser_node_function* function, NODE arguments)
{
	tyran_parser_node_parameter parameter_nodes[100];
	int parameter_node_count = 0;

	tyran_mocha_parser_parameters(parameter_nodes, &parameter_node_count, arguments);

	function->parameters = TYRAN_MALLOC_NO_POOL_TYPE_COUNT(memory, tyran_parser_node_parameter, parameter_node_count);
	tyran_memcpy_type(tyran_parser_node_parameter, function->parameters, parameter_nodes, parameter_node_count);
	function->parameter_count = parameter_node_count;
}

void tyran_mocha_check_postfix(tyran_mocha_parser* parser)
{
	NODE node = tyran_mocha_parser_concat_peek_position(parser, 1);
	if (node && node->type == TYRAN_PARSER_NODE_TYPE_IF) {
		tyran_parser_node_if* if_node = (tyran_parser_node_if*) node;
		if (!if_node->then_block) {
			if_node->then_block = tyran_mocha_parser_concat_pop(parser);
		}
	}
}

void tyran_mocha_parser_new_node_on_stack(tyran_mocha_parser* parser)
{
	tyran_mocha_check_postfix(parser);
}

void tyran_mocha_parser_add_to_empty(tyran_memory* memory, tyran_mocha_parser* parser, NODE node, int precedence)
{
	// tyran_mocha_parser_node_print_tree(parser, "AddToEmpty", node);
	
	if (!parser->next_node_to_overwrite) {
		NODE* actual_root = tyran_mocha_parser_actual_root(parser);
		tyran_mocha_parser_new_node_on_stack(parser);
		tyran_parser_node_operand_binary* binary = tyran_parser_concat(memory, 0, *actual_root);
		tyran_mocha_parser_push_root_right(parser, binary, -1);
		// tyran_mocha_parser_node_print_tree(parser, "AFTER ADD TO EMPTY (before insert)", 0);
		tyran_mocha_parser_add_to_empty(memory, parser, node, precedence);
		// tyran_mocha_parser_node_print_tree(parser, "AFTER ADD TO EMPTY (after insert)", 0);
	} else {
		tyran_parser_node_operand_unary* unary = 0;
		if (node->type == TYRAN_PARSER_NODE_TYPE_OPERAND_UNARY) {
			unary = (tyran_parser_node_operand_unary*) node;
		}
	
		TYRAN_LOG("Overwriting overwrite %lu", (unsigned long) parser->next_node_to_overwrite);
		*parser->next_node_to_overwrite = node;
		if (unary) {
			parser->next_node_to_overwrite = &unary->expression;
			TYRAN_LOG("unary overwrite %lu", (unsigned long) parser->next_node_to_overwrite);
		} else {
			parser->next_node_to_overwrite = 0;
			TYRAN_LOG("not unary overwrite %lu", (unsigned long) parser->next_node_to_overwrite);
		}
		//tyran_mocha_parser_node_print_tree(parser, "AFTER ADD TO EMPTY (overwrite)", 0);
	}

}

tyran_mocha_parser* tyran_mocha_parser_new(tyran_memory_pool* mocha_parser_pool, tyran_memory_pool* enclosure_stack_pool, tyran_memory_pool* enclosure_info_pool, tyran_memory_pool* parser_parameter_pool, tyran_memory_pool* mocha_token_pool, tyran_memory* memory)
{
	tyran_mocha_parser* parser = TYRAN_MALLOC_TYPE(mocha_parser_pool, tyran_mocha_parser);
	parser->enclosure_stack = tyran_mocha_parser_enclosure_stack_new(enclosure_stack_pool, memory, enclosure_info_pool);
	parser->waiting_for_start_enclosure_id = TYRAN_MOCHA_TOKEN_END;
	tyran_parser_node_operand_unary* unary = tyran_parser_operand_unary(memory, TYRAN_PARSER_UNARY_BLOCK, 0, 0);
	parser->original_root = (NODE)unary;
	parser->root = &unary->expression;
	parser->next_node_to_overwrite = &unary->expression;
	parser->parser_parameter_pool = parser_parameter_pool;
	parser->mocha_token_pool = mocha_token_pool;
	parser->last_precedence = -1;
	parser->root_precedence = -1;
	return parser;
}

NODE tyran_mocha_parser_return(tyran_memory* memory, tyran_mocha_parser* parser)
{
	NODE expression = tyran_mocha_parser_concat_pop(parser);
	return tyran_parser_return(memory, expression);
}


void tyran_mocha_parser_debug(const char* description, tyran_mocha_parser* parser, tyran_mocha_token* operator_token)
{
	TYRAN_LOG_NO_LF("==== %s token:", description);
	if (operator_token) {
		tyran_mocha_lexer_debug_token(operator_token);
		TYRAN_LOG(" ");
	} else {
		TYRAN_LOG("===========");
	}

	//tyran_parser_node_print(description, parser->original_root, *parser->root);
	TYRAN_LOG("==============");
}

tyran_parser_binary_operand_type tyran_mocha_parser_convert_binary_operand(tyran_mocha_token_id token_id)
{
	tyran_parser_binary_operand_type operand;
	
	switch (token_id)
	{
	case TYRAN_MOCHA_TOKEN_DIVIDE:
		operand = TYRAN_PARSER_DIVIDE;
		break;
	case TYRAN_MOCHA_TOKEN_MULTIPLY:
		operand = TYRAN_PARSER_MULTIPLY;
		break;
	case TYRAN_MOCHA_TOKEN_MODULUS:
		operand = TYRAN_PARSER_MODULUS;
		break;
	case TYRAN_MOCHA_TOKEN_ADD:
		operand = TYRAN_PARSER_ADD;
		break;
	case TYRAN_MOCHA_TOKEN_SUBTRACT:
		operand = TYRAN_PARSER_SUBTRACT;
		break;
	case TYRAN_MOCHA_TOKEN_MEMBER:
		operand = TYRAN_PARSER_MEMBER;
		break;
	case TYRAN_MOCHA_TOKEN_INDEX:
		operand = TYRAN_PARSER_INDEX;
		break;
	case TYRAN_MOCHA_TOKEN_COMMA:
		operand = TYRAN_PARSER_COMMA;
		break;
	case TYRAN_MOCHA_TOKEN_ASSIGNMENT:
		operand = TYRAN_PARSER_ASSIGNMENT;
		break;
	case TYRAN_MOCHA_TOKEN_CALL:
		operand = TYRAN_PARSER_CALL;
		break;
	case TYRAN_MOCHA_TOKEN_EQUAL:
		operand = TYRAN_PARSER_EQUAL;
		break;
	case TYRAN_MOCHA_TOKEN_NOT_EQUAL:
		operand = TYRAN_PARSER_NOT_EQUAL;
		break;
	case TYRAN_MOCHA_TOKEN_LESS:
		operand = TYRAN_PARSER_LESS;
		break;
	case TYRAN_MOCHA_TOKEN_LESS_EQUAL:
		operand = TYRAN_PARSER_LESS_EQUAL;
		break;
	case TYRAN_MOCHA_TOKEN_GREATER:
		operand = TYRAN_PARSER_GREATER;
		break;
	case TYRAN_MOCHA_TOKEN_GREATER_EQUAL:
		operand = TYRAN_PARSER_GREATER_EQUAL;
		break;
	case TYRAN_MOCHA_TOKEN_AND:
		operand = TYRAN_PARSER_AND;
		break;
	case TYRAN_MOCHA_TOKEN_OR:
		operand = TYRAN_PARSER_OR;
		break;
	case TYRAN_MOCHA_TOKEN_THEN:
		operand = TYRAN_PARSER_THEN;
		break;
	case TYRAN_MOCHA_TOKEN_WHILE:
		operand = TYRAN_PARSER_WHILE;
		break;
	case TYRAN_MOCHA_TOKEN_UNTIL:
		operand = TYRAN_PARSER_UNTIL;
		break;
	case TYRAN_MOCHA_TOKEN_WHEN:
		operand = TYRAN_PARSER_WHEN;
		break;
	case TYRAN_MOCHA_TOKEN_CASE:
		operand = TYRAN_PARSER_CASE;
		break;
	case TYRAN_MOCHA_TOKEN_ELSE:
		operand = TYRAN_PARSER_ELSE;
		break;
	case TYRAN_MOCHA_TOKEN_IN:
		operand = TYRAN_PARSER_IN;
		break;
	case TYRAN_MOCHA_TOKEN_RANGE_INCLUSIVE:
		operand = TYRAN_PARSER_RANGE_INCLUSIVE;
		break;
	case TYRAN_MOCHA_TOKEN_RANGE_EXCLUSIVE:
		operand = TYRAN_PARSER_RANGE;
		break;
	case TYRAN_MOCHA_TOKEN_COLON:
		operand = TYRAN_PARSER_COLON;
		break;
	default:
		TYRAN_ERROR("unknown binary token to convert:%d", token_id);
	}
	
	return operand;
}


tyran_parser_unary_operand_type tyran_mocha_parser_convert_unary_operand(tyran_mocha_token_id token_id)
{
	tyran_parser_unary_operand_type operand;
	
	switch (token_id)
	{
	case TYRAN_MOCHA_TOKEN_PARENTHESES_RIGHT:
		operand = TYRAN_PARSER_UNARY_PARENTHESES;
		break;
	case TYRAN_MOCHA_TOKEN_BLOCK_END:
		operand = TYRAN_PARSER_UNARY_BLOCK;
		break;
	case TYRAN_MOCHA_TOKEN_OBJECT_END:
		operand = TYRAN_PARSER_UNARY_OBJECT;
		break;
	case TYRAN_MOCHA_TOKEN_BRACKET_RIGHT:
		operand = TYRAN_PARSER_UNARY_BRACKET;
		break;
	case TYRAN_MOCHA_TOKEN_IF:
		operand = TYRAN_PARSER_UNARY_IF;
		break;
	case TYRAN_MOCHA_TOKEN_UNLESS:
		operand = TYRAN_PARSER_UNARY_UNLESS;
		break;
	default:
		TYRAN_ERROR("unknown unary token to convert:%d", token_id);
	}
	
	return operand;
}

NODE tyran_mocha_parser_token_to_literal(tyran_memory* memory, tyran_mocha_token* first)
{
	switch (first->token_id) {
		case TYRAN_MOCHA_TOKEN_IDENTIFIER:
			return tyran_parser_literal_identifier(memory, (const char*)first->token_data);
		case TYRAN_MOCHA_TOKEN_STRING:
			return tyran_parser_literal_string(memory, (const char*)first->token_data);
		case TYRAN_MOCHA_TOKEN_NUMBER:
			return tyran_parser_literal_number(memory, (tyran_number *)first->token_data);
		case TYRAN_MOCHA_TOKEN_TRUE:
			return tyran_parser_bool(memory, 1);
		case TYRAN_MOCHA_TOKEN_FALSE:
			return tyran_parser_bool(memory, 0);
		case TYRAN_MOCHA_TOKEN_UNDEFINED:
			return tyran_parser_undefined(memory);
		case TYRAN_MOCHA_TOKEN_SELF:
			return tyran_parser_self(memory);
		default:
			TYRAN_ERROR("Illegal literal token:%d", first->token_id);
			return 0;
	}
}



NODE tyran_mocha_parser_reduce_while(tyran_memory* memory, tyran_mocha_parser* parser)
{
	NODE block = 0; //tyran_mocha_parser_concat_pop(parser->stack);
	NODE condition = 0; //tyran_mocha_parser_concat_pop(parser->stack);
	
	NODE result = tyran_parser_while(memory, condition, block);
	
	return result;
}



NODE tyran_mocha_parser_add_default_operator(tyran_memory* memory, tyran_mocha_parser* parser, tyran_mocha_token_id token_id, int precedence)
{
	if (tyran_mocha_lexer_is_unary_operator(token_id)) {
		tyran_parser_node_operand_unary* node = tyran_parser_operand_unary(memory, tyran_mocha_parser_convert_unary_operand(token_id), 0, 0);
		tyran_mocha_parser_add_to_empty(memory, parser, (NODE)node, precedence);
		return (NODE)node;
	} else {
		tyran_parser_node_operand_binary* node = tyran_parser_operand_binary(memory, tyran_mocha_parser_convert_binary_operand(token_id), 0, 0);
		TYRAN_LOG("Compare precedence %d %d token:%d, %d", precedence, parser->root_precedence, token_id, parser->last_overwrite_operator_token);
		if (precedence < parser->root_precedence) {
			tyran_mocha_parser_push_root_right(parser, node, precedence);
		} else if (parser->next_node_to_overwrite == 0 && (precedence < parser->last_precedence)) {
			tyran_mocha_parser_push_last_operator_right(parser, node, precedence);
		} else {
			tyran_mocha_parser_push_last_inserted_right(parser, node, precedence);
		}
		if (parser->last_precedence == -1) {
			parser->last_precedence = precedence;
		}
		if (parser->root_precedence == -1) {
			parser->root_precedence = precedence;
		}
		parser->last_overwrite_operator_token = token_id;
		return (NODE)node;
	}
}


NODE tyran_mocha_parser_if(tyran_memory* memory, tyran_mocha_parser* parser, tyran_boolean invert)
{
	NODE expression = tyran_mocha_parser_concat_pop(parser);
	NODE block = tyran_mocha_parser_concat_pop(parser);
	NODE else_block = tyran_mocha_parser_concat_peek(parser);
	if (else_block && else_block->type == TYRAN_PARSER_NODE_TYPE_ELSE) {
		else_block = tyran_mocha_parser_concat_pop(parser);
		return tyran_parser_if_else(memory, expression, block, ((tyran_parser_node_else*)else_block)->block, invert);
	} else {
		return tyran_parser_if(memory, expression, block, invert);
	}
}

NODE tyran_mocha_parser_else(tyran_memory* memory, tyran_mocha_parser* parser)
{
	NODE block = tyran_mocha_parser_concat_pop(parser);
	return tyran_parser_else(memory, block);
}


NODE tyran_mocha_parser_while(tyran_memory* memory, tyran_mocha_parser* parser)
{
	NODE expression = tyran_mocha_parser_concat_pop(parser);
	NODE block = tyran_mocha_parser_concat_pop(parser);
	return tyran_parser_while(memory, expression, block);
}

NODE tyran_mocha_parser_for(tyran_memory* memory, tyran_mocha_parser* parser)
{
	NODE for_in_node = tyran_mocha_parser_concat_pop(parser);
	NODE block = tyran_mocha_parser_concat_pop(parser);
	tyran_parser_node_operand_binary* for_in = tyran_parser_binary_operator_type_cast(for_in_node, TYRAN_PARSER_IN);
	tyran_parser_node_operand_binary* variables = tyran_parser_binary_operator_type_cast(for_in->left, TYRAN_PARSER_COMMA);
	tyran_parser_node_identifier* key_variable;
	tyran_parser_node_identifier* value_variable;
	if (variables) {
		key_variable = (tyran_parser_node_identifier*) variables->left;
		value_variable = (tyran_parser_node_identifier*) variables->right;
	} else {
		value_variable = (tyran_parser_node_identifier*) for_in->left;
		key_variable = 0;
	}
	return tyran_parser_for(memory, key_variable, value_variable, for_in->right, block);
}

NODE tyran_mocha_parser_when(tyran_memory* memory, tyran_mocha_parser* parser)
{
	NODE expression = tyran_mocha_parser_concat_pop(parser);
	NODE block = tyran_mocha_parser_concat_pop(parser);
	return tyran_parser_when(memory, expression, block);
}


NODE tyran_mocha_parser_function(tyran_memory* memory, tyran_mocha_parser* parser, tyran_boolean bound)
{
	NODE block = tyran_mocha_parser_concat_pop(parser);
	return tyran_parser_function(memory, block, bound);
}

void tyran_mocha_parser_when_nodes(tyran_parser_node_when** when_nodes, int* index, NODE node)
{
	tyran_parser_node_operand_binary* concat = tyran_parser_binary_operator_type_cast(node, TYRAN_PARSER_CONCAT);
	if (concat) {
		tyran_mocha_parser_when_nodes(when_nodes, index, concat->left);
		tyran_mocha_parser_when_nodes(when_nodes, index, concat->right);
	} else {
		tyran_parser_node_when* when_node = (tyran_parser_node_when*) node;
		when_nodes[*index] = when_node;
		*index = *index + 1;
	}
}

NODE tyran_mocha_parser_case(tyran_memory* memory, tyran_mocha_parser* parser)
{
	NODE expression = tyran_mocha_parser_concat_pop(parser);
	NODE block_node = tyran_mocha_parser_concat_pop(parser);

	tyran_parser_node_operand_unary* block = tyran_parser_unary_operator_type_cast(block_node, TYRAN_PARSER_UNARY_BLOCK);

	tyran_parser_node_when* when_nodes[100];
	int when_node_count = 0;

	tyran_mocha_parser_when_nodes(when_nodes, &when_node_count, block->expression);

	return tyran_parser_case(memory, expression, when_nodes, when_node_count);
}

NODE tyran_mocha_parser_add_terminal(tyran_memory* memory, tyran_mocha_parser* parser, tyran_mocha_token_id token_id, int precedence)
{
	NODE node;
	switch (token_id) {
		case TYRAN_MOCHA_TOKEN_UNLESS:
			node = tyran_mocha_parser_if(memory, parser, TYRAN_TRUE);
			break;
		case TYRAN_MOCHA_TOKEN_IF:
			node = tyran_mocha_parser_if(memory, parser, TYRAN_FALSE);
			break;
		case TYRAN_MOCHA_TOKEN_ELSE:
			node = tyran_mocha_parser_else(memory, parser);
			break;
		case TYRAN_MOCHA_TOKEN_WHILE:
		case TYRAN_MOCHA_TOKEN_UNTIL:
			node = tyran_mocha_parser_while(memory, parser);
			if (token_id == TYRAN_MOCHA_TOKEN_UNTIL) {
				((tyran_parser_node_while*)node)->node.type = TYRAN_PARSER_NODE_TYPE_UNTIL;
			}
			break;
		case TYRAN_MOCHA_TOKEN_FOR:
			node = tyran_mocha_parser_for(memory, parser);
			break;
		case TYRAN_MOCHA_TOKEN_CASE:
			node = tyran_mocha_parser_case(memory, parser);
			break;
		case TYRAN_MOCHA_TOKEN_WHEN:
			node = tyran_mocha_parser_when(memory, parser);
			break;
		case TYRAN_MOCHA_TOKEN_RETURN:
			node = tyran_mocha_parser_return(memory, parser);
			break;
		case TYRAN_MOCHA_TOKEN_FUNCTION_GLYPH:
		case TYRAN_MOCHA_TOKEN_FUNCTION_GLYPH_BOUND:
			node = tyran_mocha_parser_function(memory, parser, (token_id == TYRAN_MOCHA_TOKEN_FUNCTION_GLYPH_BOUND));
			break;
		default:
			return tyran_mocha_parser_add_default_operator(memory, parser, token_id, precedence);
			break;
	}
	tyran_mocha_parser_add_to_empty(memory, parser, node, precedence);
	parser->next_node_to_overwrite = 0;
	
	return node;
}



void tyran_mocha_parser_add_enclosure(tyran_mocha_parser* parser, tyran_parser_node_operand_unary* enclosure_node, tyran_mocha_token_id end_closure, tyran_mocha_token_id start_closure)
{
	tyran_mocha_token end_token;
	end_token.token_id = end_closure;
	// TYRAN_LOG_NO_LF("Add enclosure:");
	// tyran_mocha_lexer_debug_token(&end_token);
	// TYRAN_LOG(" ");

	tyran_mocha_parser_enclosure_stack_push(parser->enclosure_stack, parser->root, enclosure_node, parser->waiting_for_start_enclosure_id);
	parser->waiting_for_start_enclosure_id = start_closure;
	parser->root = &enclosure_node->expression;
}

void tyran_mocha_parser_end_enclosure(tyran_mocha_parser* parser, tyran_memory* memory, tyran_mocha_token_id start_closure)
{
	tyran_mocha_token end_token;
	end_token.token_id = start_closure;

	tyran_mocha_parser_enclosure_info info = tyran_mocha_parser_enclosure_stack_pop(parser->enclosure_stack);
	parser->waiting_for_start_enclosure_id = info.start_token_id;
	parser->next_node_to_overwrite = 0;
	parser->root = info.root;


	tyran_parser_node_operand_unary* bracket = tyran_parser_unary_operator_type_cast(&(info.enclosure_node->node), TYRAN_PARSER_UNARY_BRACKET);

	if (bracket) {
		parser->last_bracket_node = bracket;
	}


	NODE node = tyran_mocha_parser_concat_peek(parser);
	tyran_parser_node_operand_unary* parentheses = tyran_parser_unary_operator_type_cast(node, TYRAN_PARSER_UNARY_PARENTHESES);
	if (parentheses) {
		NODE node = tyran_mocha_parser_concat_peek_position(parser, 1);
		if (node && node->type == TYRAN_PARSER_NODE_TYPE_FUNCTION) {
			TYRAN_LOG("==========> FUNCTION FOUND!");
			tyran_mocha_parser_concat_pop(parser);
			tyran_parser_node_function* function = (tyran_parser_node_function*) node;
			tyran_mocha_parser_define_function_parameters(memory, function, parentheses->expression);
		}
	}
}



void tyran_mocha_parser_line(tyran_mocha_parser* parser)
{
	TYRAN_LOG("LINE");
	tyran_mocha_check_postfix(parser);
}

void tyran_mocha_parser_add_token(tyran_memory* memory, tyran_mocha_parser* parser, tyran_mocha_token* token)
{
	tyran_mocha_lexer_debug_token(token);
	static tyran_boolean last_literal = 0;
	if (token->token_id == TYRAN_MOCHA_TOKEN_LINE_START) {
		tyran_mocha_parser_line(parser);
		last_literal = TYRAN_FALSE;
		return;
	}
	tyran_parser_node_print("before", &parser->original_root, parser->root);
	if (parser->waiting_for_start_enclosure_id == token->token_id) {
		tyran_mocha_parser_end_enclosure(parser, memory, token->token_id);
		last_literal = TYRAN_FALSE;
		if (token->token_id == TYRAN_MOCHA_TOKEN_PARENTHESES_LEFT) {
			last_literal = TYRAN_TRUE;
		}
	} else {
		tyran_mocha_operator_info info = tyran_mocha_parser_get_operator_info(token->token_id);
		if (info.token_id != TYRAN_MOCHA_TOKEN_END) {
			tyran_parser_node_operand_unary* last_bracket = parser->last_bracket_node;
			parser->last_bracket_node = 0;
			if (last_bracket) {
				last_bracket->operator_type = TYRAN_PARSER_UNARY_ARRAY;
			}
			NODE terminal = tyran_mocha_parser_add_terminal(memory, parser, token->token_id, info.precedence);
			tyran_mocha_token_id end_closing_token_id = tyran_mocha_enclosing_start_token(token->token_id);
			if (end_closing_token_id != TYRAN_MOCHA_TOKEN_END) {
				tyran_mocha_parser_add_enclosure(parser, (tyran_parser_node_operand_unary*)terminal, token->token_id, end_closing_token_id);
			}
			last_literal = TYRAN_FALSE;
		} else {
			if (parser->last_bracket_node) {
				parser->last_bracket_node = 0;
				tyran_mocha_token index_token;
				index_token.token_id = TYRAN_MOCHA_TOKEN_INDEX;
				tyran_mocha_parser_add_token(memory, parser, &index_token);
			}
			if (last_literal) {
				tyran_mocha_token* token = TYRAN_CALLOC_TYPE(parser->mocha_token_pool, tyran_mocha_token);
				token->token_id = TYRAN_MOCHA_TOKEN_CALL;
				tyran_mocha_parser_add_token(memory, parser, token);
			}
			NODE literal = tyran_mocha_parser_token_to_literal(memory, token);
			tyran_mocha_parser_add_to_empty(memory, parser, literal, 99);
			parser->last_was_colon = TYRAN_FALSE;
			last_literal = TYRAN_TRUE;
		}
	}

//	tyran_mocha_parser_debug("after", parser, 0);
}


void tyran_mocha_parser_add_all(tyran_memory* memory, tyran_mocha_parser* parser, tyran_mocha_token* first, tyran_mocha_token* last)
{
	tyran_mocha_token* token;
	for (token = last - 1; ; token--)
	{
		tyran_mocha_parser_add_token(memory, parser, token);
		if (token == first) {
			break;
		}
	}
}

NODE tyran_mocha_parser_parse(tyran_memory* memory, tyran_mocha_lexer* lexer, tyran_memory_pool* mocha_parser_pool, tyran_memory_pool* enclosure_pool, tyran_memory_pool* enclosure_info_pool,  tyran_memory_pool* parser_parameter_pool, tyran_memory_pool* mocha_token_pool)
{
	tyran_mocha_token* first = tyran_mocha_lexer_first(lexer);
	tyran_mocha_token* last = tyran_mocha_lexer_last(lexer);
	
	tyran_mocha_parser* parser = tyran_mocha_parser_new(mocha_parser_pool, enclosure_pool, enclosure_info_pool, parser_parameter_pool, mocha_token_pool, memory);
	tyran_mocha_parser_add_all(memory, parser, first, last);
	
	return parser->original_root;
}
