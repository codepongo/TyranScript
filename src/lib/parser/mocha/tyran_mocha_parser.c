#include <tyranscript/parser/mocha/tyran_mocha_lexer.h>
#include <tyranscript/parser/mocha/tyran_mocha_lexer_debug.h>
#include <tyranscript/parser/mocha/tyran_parser_tree.h>

typedef struct tyran_mocha_operator_info {
	tyran_mocha_token_id token_id;
	int direction;
	int is_enclosing;
	int precedence;
} tyran_mocha_operator_info;


tyran_mocha_operator_info tyran_mocha_parser_get_operator_info(tyran_mocha_token_id token_id)
{
	tyran_mocha_operator_info operands_to_match[] = {
		{TYRAN_MOCHA_TOKEN_LINE_END, 1, 1},
		{TYRAN_MOCHA_TOKEN_EQUAL, 1, 0},
		{TYRAN_MOCHA_TOKEN_ASSIGNMENT, 1, 0},
		{TYRAN_MOCHA_TOKEN_IF, 1, 0},
		{TYRAN_MOCHA_TOKEN_WHILE, 1, 0},
		{TYRAN_MOCHA_TOKEN_THEN, 1, 0},
		{TYRAN_MOCHA_TOKEN_ELSE, 1, 0},
		{TYRAN_MOCHA_TOKEN_BLOCK_START, 1, 1},
		{TYRAN_MOCHA_TOKEN_BLOCK_END, 1, 1},
		{TYRAN_MOCHA_TOKEN_NOT_EQUAL, 1, 0},
		{TYRAN_MOCHA_TOKEN_INVOKE, 1, 0},
		{TYRAN_MOCHA_TOKEN_MEMBER, 1, 0},
		{TYRAN_MOCHA_TOKEN_COMMA, 1, 0},
		{TYRAN_MOCHA_TOKEN_ADD, 1, 0},
		{TYRAN_MOCHA_TOKEN_SUBTRACT, 1, 0},
		{TYRAN_MOCHA_TOKEN_MULTIPLY, 1, 0},
		{TYRAN_MOCHA_TOKEN_DIVIDE, 1, 0},
		{TYRAN_MOCHA_TOKEN_BRACKET_RIGHT, 1, 1},
		{TYRAN_MOCHA_TOKEN_PARENTHESES_LEFT, 1, 1},
	};

	int i;
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
	NODE* last_inserted_node;
	tyran_mocha_token_id start_token_id;
	int top_precedence;
	NODE* root_node;
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
	NODE* root_node;
	NODE root;
	NODE* last_inserted_node;
	NODE* empty_node;
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

void tyran_mocha_parser_enclosure_stack_push(tyran_mocha_parser_enclosure_stack* stack, NODE* last_inserted_node, NODE* root_node, tyran_mocha_token_id start_enclosure_id, int top_precedence)
{
	tyran_mocha_parser_enclosure_info* destination = &stack->nodes[stack->length++];
	destination->last_inserted_node = last_inserted_node;
	destination->start_token_id = start_enclosure_id;
	destination->top_precedence = top_precedence;
	destination->root_node = root_node;
}

tyran_mocha_parser_enclosure_info tyran_mocha_parser_enclosure_stack_pop(tyran_mocha_parser_enclosure_stack* stack)
{
	TYRAN_ASSERT(stack->length > 0, "You popped too much");
	return stack->nodes[--stack->length];
}

void tyran_mocha_parser_concat_push(tyran_mocha_parser* parser, NODE node) {
	tyran_parser_node_operand_binary* concat = tyran_parser_concat(node, *parser->root_node);
	*parser->root_node = (NODE)concat;
	parser->empty_node = 0;
	// parser->top_precedence = 99999;
	parser->last_inserted_node = &concat->left;
}

tyran_mocha_parser* tyran_mocha_parser_new()
{
	tyran_mocha_parser* parser = TYRAN_MALLOC_TYPE(tyran_mocha_parser, 1);
	parser->enclosure_stack = tyran_mocha_parser_enclosure_stack_new();
	parser->waiting_for_start_enclosure_id = TYRAN_MOCHA_TOKEN_END;
	tyran_parser_node_operand_unary* unary = tyran_parser_operand_unary(TYRAN_PARSER_UNARY_BLOCK, 0, 0);
	parser->root = (NODE)unary;
	parser->root_node = &parser->root;
	parser->last_inserted_node = parser->root_node;
	parser->empty_node = &unary->expression;
	parser->top_precedence = 999999;
	return parser;
}

void tyran_mocha_parser_debug(const char* description, tyran_mocha_parser* parser, tyran_mocha_token* operator)
{
	TYRAN_LOG_NO_LF("==== %s token:", description);
	if (operator) {
		tyran_mocha_lexer_debug_token(operator);
		TYRAN_LOG("");
	} else {
		TYRAN_LOG("===========");
	}

	char buf[512];
	tyran_parser_node_print(buf, parser->root);
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
	case TYRAN_MOCHA_TOKEN_THEN:
		operand = TYRAN_PARSER_THEN;
		break;
	case TYRAN_MOCHA_TOKEN_WHILE:
		operand = TYRAN_PARSER_WHILE;
		break;
	case TYRAN_MOCHA_TOKEN_ELSE:
		operand = TYRAN_PARSER_ELSE;
		break;
	case TYRAN_MOCHA_TOKEN_LINE_END:
		operand = TYRAN_PARSER_LINE;
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

tyran_parser_node_operand_binary* tyran_mocha_parser_binary_operator_cast(NODE node)
{
	if (!node || node->type != TYRAN_PARSER_NODE_TYPE_OPERAND_BINARY) {
		return 0;
	} else {
		tyran_parser_node_operand_binary* binary_operator = (tyran_parser_node_operand_binary*) node;
		return binary_operator;
	}
}


NODE tyran_mocha_parser_concat_pop(NODE root) {
	return 0;
}

NODE tyran_mocha_parser_reduce_while(tyran_mocha_parser* parser)
{
	NODE block = 0; //tyran_mocha_parser_concat_pop(parser->stack);
	NODE condition = 0; //tyran_mocha_parser_concat_pop(parser->stack);
	
	NODE result = tyran_parser_while(condition, block);
	
	return result;
}


NODE tyran_mocha_parser_reduce_if(tyran_mocha_parser* parser)
{
			NODE if_expression;
			NODE if_then;
			NODE if_else = 0;
			
			if_then = tyran_mocha_parser_concat_pop(*parser->root_node);
			tyran_parser_node_operand_binary* binary_operator = tyran_mocha_parser_binary_operator_cast(if_then);
			
			if (binary_operator && binary_operator->operator_type == TYRAN_PARSER_THEN) {
				if_expression = binary_operator->left;
				if_then = binary_operator->right;
				tyran_parser_node_operand_binary* potential_else = tyran_mocha_parser_binary_operator_cast(if_then);
				if (potential_else && potential_else->operator_type == TYRAN_PARSER_ELSE) {
					if_then = potential_else->left;
					if_else = potential_else->right;
				}
			} else {
				if_expression = tyran_mocha_parser_concat_pop(*parser->root_node);
			}
			if (binary_operator && binary_operator->operator_type == TYRAN_PARSER_ELSE) {
				if_then = binary_operator->left;
				if_else = binary_operator->right;
			} 
			
			NODE result;
			if (if_else) {
				result = tyran_parser_if_else(if_expression, if_then, if_else);
			} else {
				result = tyran_parser_if(if_expression, if_then);
			}
			
			return result;
}

void tyran_mocha_parser_push_root_right(tyran_mocha_parser* parser, tyran_parser_node_operand_binary* node)
{
	node->right = *parser->root_node;
	*parser->root_node = (NODE)node;
	tyran_parser_node_print("PushRootRight", (NODE) node);

	parser->last_inserted_node = parser->root_node;
	parser->empty_node = (NODE*) &node->left;
}

void tyran_mocha_parser_push_last_inserted_right(tyran_mocha_parser* parser, tyran_parser_node_operand_binary* node)
{
	NODE* last_node = parser->last_inserted_node;
	node->right = *last_node;
	tyran_parser_node_print("PushLastRight", (NODE)node);
	*last_node = (NODE) node;
	parser->last_inserted_node = (NODE*) &node;
	parser->empty_node = (NODE*) &node->left;
}

void tyran_mocha_parser_add_to_empty(tyran_mocha_parser* parser, NODE node)
{
	tyran_parser_node_print("AddToEmpty", (NODE) node);
	NODE* next_add_node = parser->empty_node;
	if (!next_add_node) {
		tyran_mocha_parser_concat_push(parser, node);
		
	} else {
		*next_add_node = node;
		parser->last_inserted_node = next_add_node;
		parser->empty_node = 0;
	}
}

void tyran_mocha_parser_add_default_operator(tyran_mocha_parser* parser, tyran_mocha_token_id token_id, int precedence)
{
	if (tyran_mocha_lexer_is_unary_operator(token_id)) {
		tyran_parser_node_operand_unary* node = tyran_parser_operand_unary(tyran_mocha_parser_convert_unary_operand(token_id), 0, 0);
		tyran_mocha_parser_add_to_empty(parser, (NODE)node);
		parser->empty_node = &node->expression;
		parser->last_inserted_node = &node->expression;
		parser->top_precedence = precedence;
	} else {
		tyran_parser_node_operand_binary* node = tyran_parser_operand_binary(tyran_mocha_parser_convert_binary_operand(token_id), 0, 0);
		TYRAN_LOG("Compare precedence %d  %d", precedence, parser->top_precedence);
		if (precedence <= parser->top_precedence) {
			tyran_mocha_parser_push_root_right(parser, node);
			parser->top_precedence = precedence;
		} else {
			tyran_mocha_parser_push_last_inserted_right(parser, node);
		}
	}
}

NODE tyran_mocha_parser_if(NODE root)
{
	NODE expression = tyran_mocha_parser_concat_pop(root);
	NODE block = tyran_mocha_parser_concat_pop(root);

	return tyran_parser_if(expression, block);
}

void tyran_mocha_parser_add_terminal(tyran_mocha_parser* parser, tyran_mocha_token_id token_id, int precedence)
{
	NODE node;
	switch (token_id) {
		case TYRAN_MOCHA_TOKEN_IF:
			node = tyran_mocha_parser_if(*parser->root_node);
			break;
		default:
			tyran_mocha_parser_add_default_operator(parser, token_id, precedence);
			return;
			break;
	}
	tyran_mocha_parser_add_to_empty(parser, node);
	parser->top_precedence = 99999;
	parser->empty_node = 0;
}

void tyran_mocha_parser_add_enclosure(tyran_mocha_parser* parser, tyran_mocha_token_id end_closure, tyran_mocha_token_id start_closure)
{
	tyran_mocha_token end_token;
	end_token.token_id = end_closure;
	TYRAN_LOG_NO_LF("Add enclosure:");
	tyran_mocha_lexer_debug_token(&end_token);
	TYRAN_LOG("");
	
	NODE* last_inserted_node = parser->last_inserted_node;
	tyran_mocha_parser_enclosure_stack_push(parser->enclosure_stack, parser->last_inserted_node, parser->root_node, parser->waiting_for_start_enclosure_id, parser->top_precedence);
	parser->waiting_for_start_enclosure_id = start_closure;
	parser->root_node = last_inserted_node;
}

void tyran_mocha_parser_end_enclosure(tyran_mocha_parser* parser, tyran_mocha_token_id start_closure)
{
	tyran_mocha_token end_token;
	end_token.token_id = start_closure;
	TYRAN_LOG_NO_LF("End enclosure:");
	tyran_mocha_lexer_debug_token(&end_token);
	TYRAN_LOG("");

	tyran_mocha_parser_enclosure_info info = tyran_mocha_parser_enclosure_stack_pop(parser->enclosure_stack);
	parser->waiting_for_start_enclosure_id = info.start_token_id;
	parser->last_inserted_node = info.last_inserted_node;
	parser->root_node = info.last_inserted_node;
}

void tyran_mocha_parser_add_token(tyran_mocha_parser* parser, tyran_mocha_token* token)
{
	tyran_mocha_parser_debug("before", parser, 0);
	if (parser->waiting_for_start_enclosure_id == token->token_id) {
		tyran_mocha_parser_end_enclosure(parser, token->token_id);
	} else {
		tyran_mocha_operator_info info = tyran_mocha_parser_get_operator_info(token->token_id);
		if (info.token_id != TYRAN_MOCHA_TOKEN_END) {
			tyran_mocha_parser_add_terminal(parser, token->token_id, info.precedence);
			tyran_mocha_token_id end_closing_token_id = tyran_mocha_enclosing_start_token(token->token_id);
			if (end_closing_token_id != TYRAN_MOCHA_TOKEN_END) {
				tyran_mocha_parser_add_enclosure(parser, token->token_id, end_closing_token_id);
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
	
	return (NODE)parser->root;
}