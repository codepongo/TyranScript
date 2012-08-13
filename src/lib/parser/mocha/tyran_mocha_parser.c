#include <tyranscript/parser/mocha/tyran_mocha_lexer.h>
#include <tyranscript/parser/mocha/tyran_mocha_lexer_debug.h>
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
		{TYRAN_MOCHA_TOKEN_FUNCTION_GLYPH, 1, 0},
		{TYRAN_MOCHA_TOKEN_FUNCTION_GLYPH_BOUND, 1, 0},
		{TYRAN_MOCHA_TOKEN_AND, 1, 0},
		{TYRAN_MOCHA_TOKEN_OR, 1, 0},
		{TYRAN_MOCHA_TOKEN_EQUAL, 1, 0},
		{TYRAN_MOCHA_TOKEN_NOT_EQUAL, 1, 0},
		{TYRAN_MOCHA_TOKEN_LESS, 1, 0},
		{TYRAN_MOCHA_TOKEN_LESS_EQUAL, 1, 0},
		{TYRAN_MOCHA_TOKEN_GREATER, 1, 0},
		{TYRAN_MOCHA_TOKEN_GREATER_EQUAL, 1, 0},
		{TYRAN_MOCHA_TOKEN_ASSIGNMENT, 1, 0},
		{TYRAN_MOCHA_TOKEN_IF, 1, 0},
		{TYRAN_MOCHA_TOKEN_WHILE, 1, 0},
		{TYRAN_MOCHA_TOKEN_UNTIL, 1, 0},
		{TYRAN_MOCHA_TOKEN_FOR, 1, 0},
		{TYRAN_MOCHA_TOKEN_CASE, 1, 0},
		{TYRAN_MOCHA_TOKEN_WHEN, 1, 0},
		{TYRAN_MOCHA_TOKEN_THEN, 1, 0},
		{TYRAN_MOCHA_TOKEN_ELSE, 1, 0},
		{TYRAN_MOCHA_TOKEN_BLOCK_START, 1, 1},
		{TYRAN_MOCHA_TOKEN_BLOCK_END, 1, 1},
		{TYRAN_MOCHA_TOKEN_NOT_EQUAL, 1, 0},
		{TYRAN_MOCHA_TOKEN_INVOKE, 1, 0},
		{TYRAN_MOCHA_TOKEN_IN, 1, 0},
		{TYRAN_MOCHA_TOKEN_COMMA, 1, 0},
		{TYRAN_MOCHA_TOKEN_ADD, 1, 0},
		{TYRAN_MOCHA_TOKEN_SUBTRACT, 1, 0},
		{TYRAN_MOCHA_TOKEN_MULTIPLY, 1, 0},
		{TYRAN_MOCHA_TOKEN_DIVIDE, 1, 0},
		{TYRAN_MOCHA_TOKEN_MEMBER, 1, 0},
		{TYRAN_MOCHA_TOKEN_RANGE_EXCLUSIVE, 1, 0},
		{TYRAN_MOCHA_TOKEN_RANGE_INCLUSIVE, 1, 0},
		{TYRAN_MOCHA_TOKEN_LINE_START, 1, 1},
		{TYRAN_MOCHA_TOKEN_BRACKET_RIGHT, 1, 1},
		{TYRAN_MOCHA_TOKEN_PARENTHESES_RIGHT, 1, 1},
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


typedef struct tyran_mocha_parser_enclosure_info {
	NODE* pointing_to_last_added_node;
	tyran_mocha_token_id start_token_id;
	int top_precedence;
	NODE* root;
} tyran_mocha_parser_enclosure_info;

typedef struct tyran_mocha_parser_enclosure_stack {
	tyran_mocha_parser_enclosure_info* nodes;
	int alloc_size;
	int length;
} tyran_mocha_parser_enclosure_stack;

typedef struct tyran_mocha_parser {
	tyran_mocha_parser_enclosure_stack* enclosure_stack;
	tyran_mocha_token_id waiting_for_start_enclosure_id;
	int top_precedence;
	NODE original_root;
	NODE* root;
	NODE* pointing_to_last_added_node;
	NODE* next_node_to_overwrite;
} tyran_mocha_parser;


tyran_mocha_parser_enclosure_stack* tyran_mocha_parser_enclosure_stack_new()
{
	tyran_mocha_parser_enclosure_stack* stack = TYRAN_MALLOC_TYPE(tyran_mocha_parser_enclosure_stack, 1);
	stack->length = 0;
	stack->alloc_size = 100;
	stack->nodes = TYRAN_MALLOC_TYPE(tyran_mocha_parser_enclosure_info, stack->alloc_size);
	return stack;
}

void tyran_mocha_parser_enclosure_stack_free(tyran_mocha_parser_enclosure_stack* stack)
{
	tyran_free(stack->nodes);
	tyran_free(stack);
}

void tyran_mocha_parser_enclosure_stack_push(tyran_mocha_parser_enclosure_stack* stack, NODE* pointing_to_last_added_node, NODE* root, tyran_mocha_token_id start_enclosure_id, int top_precedence)
{
	tyran_mocha_parser_enclosure_info* destination = &stack->nodes[stack->length++];
	destination->pointing_to_last_added_node = pointing_to_last_added_node;
	destination->start_token_id = start_enclosure_id;
	destination->top_precedence = top_precedence;
	destination->root = root;
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

void tyran_mocha_parser_push_root_right(tyran_mocha_parser* parser, tyran_parser_node_operand_binary* node)
{
	NODE* actual_root = tyran_mocha_parser_actual_root(parser);
	tyran_parser_node_print("PushRootRight", (NODE) node, *actual_root);
	tyran_mocha_parser_push_right(parser, node, actual_root);
}

void tyran_mocha_parser_push_last_inserted_right(tyran_mocha_parser* parser, tyran_parser_node_operand_binary* node)
{
	tyran_parser_node_print("PushLastRight", (NODE)node, *parser->root);
	tyran_mocha_parser_push_right(parser, node, parser->pointing_to_last_added_node);
}


void tyran_mocha_parser_add_to_empty(tyran_mocha_parser* parser, NODE node)
{
	tyran_parser_node_print("AddToEmpty", (NODE) node, *parser->root);
	
	if (!parser->next_node_to_overwrite) {
		NODE* actual_root = tyran_mocha_parser_actual_root(parser);
		tyran_parser_node_operand_binary* binary = tyran_parser_concat(0, *actual_root);
		tyran_mocha_parser_push_root_right(parser, binary);
		tyran_mocha_parser_add_to_empty(parser, node);
	} else {
		tyran_parser_node_operand_unary* unary = 0;
		if (node->type == TYRAN_PARSER_NODE_TYPE_OPERAND_UNARY) {
			unary = (tyran_parser_node_operand_unary*) node;
		}
	
		*parser->next_node_to_overwrite = node;
		parser->pointing_to_last_added_node = parser->next_node_to_overwrite;
		if (unary) {
			parser->next_node_to_overwrite = &unary->expression;
		} else {
			parser->next_node_to_overwrite = 0;
		}
	}
}

tyran_mocha_parser* tyran_mocha_parser_new()
{
	tyran_mocha_parser* parser = TYRAN_MALLOC_TYPE(tyran_mocha_parser, 1);
	parser->enclosure_stack = tyran_mocha_parser_enclosure_stack_new();
	parser->waiting_for_start_enclosure_id = TYRAN_MOCHA_TOKEN_END;
	tyran_parser_node_operand_unary* unary = tyran_parser_operand_unary(TYRAN_PARSER_UNARY_BLOCK, 0, 0);
	parser->original_root = (NODE)unary;
	parser->root = &unary->expression;
	parser->pointing_to_last_added_node = parser->root;
	parser->next_node_to_overwrite = &unary->expression;
	parser->top_precedence = 99999;
	return parser;
}

void tyran_mocha_parser_debug(const char* description, tyran_mocha_parser* parser, tyran_mocha_token* operator)
{
	TYRAN_LOG_NO_LF("==== %s token:", description);
	if (operator) {
		tyran_mocha_lexer_debug_token(operator);
		TYRAN_LOG(" ");
	} else {
		TYRAN_LOG("===========");
	}

	tyran_parser_node_print(description, parser->original_root, *parser->root);
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
	case TYRAN_MOCHA_TOKEN_BRACKET_LEFT:
		operand = TYRAN_PARSER_INDEX;
		break;
	case TYRAN_MOCHA_TOKEN_MEMBER:
		operand = TYRAN_PARSER_INDEX;
		break;
	case TYRAN_MOCHA_TOKEN_COMMA:
		operand = TYRAN_PARSER_COMMA;
		break;
	case TYRAN_MOCHA_TOKEN_ASSIGNMENT:
		operand = TYRAN_PARSER_ASSIGNMENT;
		break;
	case TYRAN_MOCHA_TOKEN_INVOKE:
		operand = TYRAN_PARSER_INVOKE;
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
	default:
		TYRAN_ERROR("unknown token to convert");
	}
	
	return operand;
}


tyran_parser_unary_operand_type tyran_mocha_parser_convert_unary_operand(tyran_mocha_token_id token_id)
{
	tyran_parser_unary_operand_type operand;
	
	switch (token_id)
	{
	case TYRAN_MOCHA_TOKEN_ADD:
		operand = TYRAN_PARSER_UNARY_OPERAND_ADD;
		break;
	case TYRAN_MOCHA_TOKEN_SUBTRACT:
		operand = TYRAN_PARSER_UNARY_OPERAND_SUBTRACT;
		break;
	case TYRAN_MOCHA_TOKEN_PARENTHESES_RIGHT:
		operand = TYRAN_PARSER_UNARY_PARENTHESES;
		break;
	case TYRAN_MOCHA_TOKEN_BLOCK_END:
		operand = TYRAN_PARSER_UNARY_BLOCK;
		break;
	case TYRAN_MOCHA_TOKEN_BRACKET_RIGHT:
		operand = TYRAN_PARSER_UNARY_BRACKET;
		break;
	case TYRAN_MOCHA_TOKEN_IF:
		operand = TYRAN_PARSER_UNARY_IF;
		break;
	default:
		TYRAN_ERROR("unknown token to convert");
	}
	
	return operand;
}

NODE tyran_mocha_parser_token_to_literal(tyran_mocha_token* first)
{
	switch (first->token_id) {
		case TYRAN_MOCHA_TOKEN_IDENTIFIER:
			return tyran_parser_literal_identifier(first->token_data);
		case TYRAN_MOCHA_TOKEN_STRING:
			return tyran_parser_literal_string(first->token_data);
		case TYRAN_MOCHA_TOKEN_NUMBER:
			return tyran_parser_literal_number(first->token_data);
		case TYRAN_MOCHA_TOKEN_TRUE:
			return tyran_parser_bool(1);
		case TYRAN_MOCHA_TOKEN_FALSE:
			return tyran_parser_bool(0);
		case TYRAN_MOCHA_TOKEN_UNDEFINED:
			return tyran_parser_undefined();
		default:
			TYRAN_ERROR("Illegal token:%d", first->token_id);
			return 0;
	}
}

NODE tyran_mocha_parser_concat_pop_helper(tyran_mocha_parser* parser, NODE* pointer_to_root, NODE* root, NODE replace_with) {
	tyran_parser_node_print("POP", parser->original_root, *root);
	tyran_parser_node_operand_binary* binary = tyran_parser_binary_operator_type_cast(*root, TYRAN_PARSER_CONCAT);
	NODE result;
	if (binary) {
		tyran_parser_node_print("XXX", parser->original_root, (NODE)binary);
		return tyran_mocha_parser_concat_pop_helper(parser, root, &binary->left, binary->right);
	} else {
		result = *root;
		if (pointer_to_root) {
			*pointer_to_root = replace_with;
		}
		if (!replace_with) {
			parser->next_node_to_overwrite = pointer_to_root;
		}
	}
	tyran_parser_node_print("POP AFTER", parser->original_root, *root);
	return result;
}

NODE tyran_mocha_parser_concat_pop(tyran_mocha_parser* parser) {
	NODE result = tyran_mocha_parser_concat_pop_helper(parser, parser->root, parser->root, 0);
	return result;
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
	tyran_parser_node_print("PEEK_POSITION", parser->original_root, *parser->root);
	return tyran_mocha_parser_concat_peek_helper(*parser->root, &position);
}


NODE tyran_mocha_parser_concat_peek(tyran_mocha_parser* parser) {
	tyran_parser_node_print("PEEK", parser->original_root, *parser->root);
	return tyran_mocha_parser_concat_peek_position(parser, 0);
}


NODE tyran_mocha_parser_reduce_while(tyran_mocha_parser* parser)
{
	NODE block = 0; //tyran_mocha_parser_concat_pop(parser->stack);
	NODE condition = 0; //tyran_mocha_parser_concat_pop(parser->stack);
	
	NODE result = tyran_parser_while(condition, block);
	
	return result;
}



NODE tyran_mocha_parser_add_default_operator(tyran_mocha_parser* parser, tyran_mocha_token_id token_id, int precedence)
{
	if (tyran_mocha_lexer_is_unary_operator(token_id)) {
		tyran_parser_node_operand_unary* node = tyran_parser_operand_unary(tyran_mocha_parser_convert_unary_operand(token_id), 0, 0);
		tyran_mocha_parser_add_to_empty(parser, (NODE)node);
		return (NODE)node;
	} else {
		tyran_parser_node_operand_binary* node = tyran_parser_operand_binary(tyran_mocha_parser_convert_binary_operand(token_id), 0, 0);
		TYRAN_LOG("Compare precedence %d  %d", precedence, parser->top_precedence);
		if (precedence < parser->top_precedence) {
			tyran_mocha_parser_push_root_right(parser, node);
			parser->top_precedence = precedence;
		} else {
			tyran_mocha_parser_push_last_inserted_right(parser, node);
		}
		return (NODE)node;
	}
}

NODE tyran_mocha_parser_if(tyran_mocha_parser* parser)
{
	NODE expression = tyran_mocha_parser_concat_pop(parser);
	NODE block = tyran_mocha_parser_concat_pop(parser);
	NODE else_block = tyran_mocha_parser_concat_peek(parser);
	if (else_block && else_block->type == TYRAN_PARSER_NODE_TYPE_ELSE) {
		else_block = tyran_mocha_parser_concat_pop(parser);
		return tyran_parser_if_else(expression, block, ((tyran_parser_node_else*)else_block)->block);
	} else {
		return tyran_parser_if(expression, block);
	}
}

NODE tyran_mocha_parser_else(tyran_mocha_parser* parser)
{
	NODE block = tyran_mocha_parser_concat_pop(parser);
	return tyran_parser_else(block);
}


NODE tyran_mocha_parser_while(tyran_mocha_parser* parser)
{
	NODE expression = tyran_mocha_parser_concat_pop(parser);
	NODE block = tyran_mocha_parser_concat_pop(parser);
	return tyran_parser_while(expression, block);
}

NODE tyran_mocha_parser_for(tyran_mocha_parser* parser)
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
	return tyran_parser_for(key_variable, value_variable, for_in->right, block);
}

NODE tyran_mocha_parser_when(tyran_mocha_parser* parser)
{
	NODE expression = tyran_mocha_parser_concat_pop(parser);
	NODE block = tyran_mocha_parser_concat_pop(parser);
	return tyran_parser_when(expression, block);
}

NODE tyran_mocha_parser_function(tyran_mocha_parser* parser, tyran_boolean bound)
{
	NODE block = tyran_mocha_parser_concat_pop(parser);
	NODE parameters = 0;
	return tyran_parser_function(parameters, block, bound);
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

NODE tyran_mocha_parser_case(tyran_mocha_parser* parser)
{
	NODE expression = tyran_mocha_parser_concat_pop(parser);
	NODE block_node = tyran_mocha_parser_concat_pop(parser);

	tyran_parser_node_operand_unary* block = tyran_parser_unary_operator_type_cast(block_node, TYRAN_PARSER_UNARY_BLOCK);

	tyran_parser_node_when* when_nodes[100];
	int when_node_count = 0;

	tyran_mocha_parser_when_nodes(when_nodes, &when_node_count, block->expression);

	return tyran_parser_case(expression, when_nodes, when_node_count);
}

NODE tyran_mocha_parser_add_terminal(tyran_mocha_parser* parser, tyran_mocha_token_id token_id, int precedence)
{
	NODE node;
	switch (token_id) {
		case TYRAN_MOCHA_TOKEN_IF:
			node = tyran_mocha_parser_if(parser);
			break;
		case TYRAN_MOCHA_TOKEN_ELSE:
			node = tyran_mocha_parser_else(parser);
			break;
		case TYRAN_MOCHA_TOKEN_WHILE:
		case TYRAN_MOCHA_TOKEN_UNTIL:
			node = tyran_mocha_parser_while(parser);
			if (token_id == TYRAN_MOCHA_TOKEN_UNTIL) {
				((tyran_parser_node_while*)node)->node.type = TYRAN_PARSER_NODE_TYPE_UNTIL;
			}
			break;
		case TYRAN_MOCHA_TOKEN_FOR:
			node = tyran_mocha_parser_for(parser);
			break;
		case TYRAN_MOCHA_TOKEN_CASE:
			node = tyran_mocha_parser_case(parser);
			break;
		case TYRAN_MOCHA_TOKEN_WHEN:
			node = tyran_mocha_parser_when(parser);
			break;
		case TYRAN_MOCHA_TOKEN_FUNCTION_GLYPH:
		case TYRAN_MOCHA_TOKEN_FUNCTION_GLYPH_BOUND:
			node = tyran_mocha_parser_function(parser, (token_id == TYRAN_MOCHA_TOKEN_FUNCTION_GLYPH_BOUND));
			break;
		default:
			return tyran_mocha_parser_add_default_operator(parser, token_id, precedence);
			break;
	}
	tyran_mocha_parser_add_to_empty(parser, node);
	parser->top_precedence = 99999;
	parser->next_node_to_overwrite = 0;
	
	return node;
}

void tyran_mocha_parser_add_enclosure(tyran_mocha_parser* parser, tyran_parser_node_operand_unary* enclosure_node, tyran_mocha_token_id end_closure, tyran_mocha_token_id start_closure)
{
	tyran_mocha_token end_token;
	end_token.token_id = end_closure;
	TYRAN_LOG_NO_LF("Add enclosure:");
	tyran_mocha_lexer_debug_token(&end_token);
	TYRAN_LOG(" ");
	
	tyran_mocha_parser_enclosure_stack_push(parser->enclosure_stack, parser->pointing_to_last_added_node, parser->root, parser->waiting_for_start_enclosure_id, parser->top_precedence);
	parser->waiting_for_start_enclosure_id = start_closure;
	parser->root = &enclosure_node->expression;
	parser->top_precedence = 999999;
}

void tyran_mocha_parser_end_enclosure(tyran_mocha_parser* parser, tyran_mocha_token_id start_closure)
{
	tyran_mocha_token end_token;
	end_token.token_id = start_closure;
	TYRAN_LOG_NO_LF("End enclosure:");
	tyran_mocha_lexer_debug_token(&end_token);
	TYRAN_LOG(" ");

	tyran_mocha_parser_enclosure_info info = tyran_mocha_parser_enclosure_stack_pop(parser->enclosure_stack);
	parser->waiting_for_start_enclosure_id = info.start_token_id;
	parser->pointing_to_last_added_node = info.pointing_to_last_added_node;
	parser->root = info.root;
}

void tyran_mocha_parser_line(tyran_mocha_parser* parser)
{
	TYRAN_LOG("LINE");
	NODE node = tyran_mocha_parser_concat_peek_position(parser, 1);
	if (node && node->type == TYRAN_PARSER_NODE_TYPE_IF) {
		TYRAN_LOG("FOUND IF");
		tyran_parser_node_if* if_node = (tyran_parser_node_if*) node;
		if (!if_node->then_block) {
			if_node->then_block = tyran_mocha_parser_concat_pop(parser);
		}
	}
}

void tyran_mocha_parser_add_token(tyran_mocha_parser* parser, tyran_mocha_token* token)
{
	if (token->token_id == TYRAN_MOCHA_TOKEN_LINE_START) {
		tyran_mocha_parser_line(parser);
		return;
	}
	tyran_mocha_parser_debug("before", parser, 0);
	if (parser->waiting_for_start_enclosure_id == token->token_id) {
		tyran_mocha_parser_end_enclosure(parser, token->token_id);
	} else {
		tyran_mocha_operator_info info = tyran_mocha_parser_get_operator_info(token->token_id);
		if (info.token_id != TYRAN_MOCHA_TOKEN_END) {
			NODE terminal = tyran_mocha_parser_add_terminal(parser, token->token_id, info.precedence);
			tyran_mocha_token_id end_closing_token_id = tyran_mocha_enclosing_start_token(token->token_id);
			if (end_closing_token_id != TYRAN_MOCHA_TOKEN_END) {
				tyran_mocha_parser_add_enclosure(parser, (tyran_parser_node_operand_unary*)terminal, token->token_id, end_closing_token_id);
			}
		} else {
			NODE literal = tyran_mocha_parser_token_to_literal(token);
			tyran_mocha_parser_add_to_empty(parser, literal);
		}
	}
	tyran_mocha_parser_debug("after", parser, 0);
}


void tyran_mocha_parser_add_all(tyran_mocha_parser* parser, tyran_mocha_token* first, tyran_mocha_token* last)
{
	tyran_mocha_token* token;
	for (token = last - 1; ; token--)
	{
		tyran_mocha_parser_add_token(parser, token);
		if (token == first) {
			break;
		}
	}
}

NODE tyran_mocha_parser_parse(tyran_mocha_lexer* lexer)
{
	tyran_mocha_token* first = tyran_mocha_lexer_first(lexer);
	tyran_mocha_token* last = tyran_mocha_lexer_last(lexer);
	
	tyran_mocha_parser* parser = tyran_mocha_parser_new();
	tyran_mocha_parser_add_all(parser, first, last);
	
	return parser->original_root;
}