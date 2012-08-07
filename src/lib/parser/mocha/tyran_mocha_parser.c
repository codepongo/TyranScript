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
		{TYRAN_MOCHA_TOKEN_ASSIGNMENT, 1, 0},
		{TYRAN_MOCHA_TOKEN_IF, 1, 0},
		{TYRAN_MOCHA_TOKEN_THEN, 1, 0},
		{TYRAN_MOCHA_TOKEN_ELSE, 1, 0},
		{TYRAN_MOCHA_TOKEN_BLOCK_START, 1, 1},
		{TYRAN_MOCHA_TOKEN_EQUAL, 1, 0},
		{TYRAN_MOCHA_TOKEN_NOT_EQUAL, 1, 0},
		{TYRAN_MOCHA_TOKEN_INVOKE, 1, 0},
		{TYRAN_MOCHA_TOKEN_MEMBER, 1, 0},
		{TYRAN_MOCHA_TOKEN_COMMA, 1, 0},
		{TYRAN_MOCHA_TOKEN_ADD, 1, 0},
		{TYRAN_MOCHA_TOKEN_SUBTRACT, 1, 0},
		{TYRAN_MOCHA_TOKEN_MULTIPLY, 1, 0},
		{TYRAN_MOCHA_TOKEN_DIVIDE, 1, 0},
		{TYRAN_MOCHA_TOKEN_BRACKET_LEFT, 1, 1},
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


typedef struct tyran_mocha_parser_stack {
	NODE* nodes;
	int alloc_size;
	int length;
} tyran_mocha_parser_stack;

typedef struct tyran_mocha_parser {
	tyran_mocha_parser_stack* stack;
	int top_precedence;
	NODE* last_inserted_node;
	NODE* empty_node;
} tyran_mocha_parser;


tyran_mocha_parser_stack* tyran_mocha_parser_stack_new()
{
	tyran_mocha_parser_stack* stack = TYRAN_MALLOC_TYPE(tyran_mocha_parser_stack, 1);
	stack->length = 0;
	stack->alloc_size = 100;
	stack->nodes = TYRAN_MALLOC_TYPE(NODE, stack->alloc_size);
	return stack;
}

void tyran_mocha_parser_stack_free(tyran_mocha_parser_stack* stack)
{
	tyran_free(stack->nodes);
	tyran_free(stack);
}

NODE* tyran_mocha_parser_stack_push(tyran_mocha_parser_stack* stack, NODE node)
{
	NODE* destination = &stack->nodes[stack->length++];
	*destination = node;
	
	return destination;
}

NODE tyran_mocha_parser_stack_pop(tyran_mocha_parser_stack* stack)
{
	TYRAN_ASSERT(stack->length > 0, "You popped too much");
	return stack->nodes[--stack->length];
}

NODE tyran_mocha_parser_stack_top(tyran_mocha_parser_stack* stack)
{
	TYRAN_ASSERT(stack->length > 0, "You can not peek top on empty stack");
	return stack->nodes[stack->length - 1];
}

tyran_mocha_parser* tyran_mocha_parser_new()
{
	tyran_mocha_parser* parser = TYRAN_MALLOC_TYPE(tyran_mocha_parser, 1);
	parser->stack = tyran_mocha_parser_stack_new();
	parser->top_precedence = 999999;
	return parser;
}

void tyran_mocha_parser_debug(const char* description, tyran_mocha_parser* parser, tyran_mocha_token* operator)
{
	if (operator) {
		TYRAN_LOG_NO_LF("==== %s token:", description);
		tyran_mocha_lexer_debug_token(operator);
		TYRAN_LOG("");
	} else {
		TYRAN_LOG("===========");
	}

	tyran_mocha_parser_stack* stack = parser->stack;
	char buf[512];
	int i;
	for (i = stack->length - 1; i >= 0; --i) {
		tyran_snprintf(buf, 512,  "%d", i);
		tyran_parser_node_print(buf, stack->nodes[i]);
	}
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
	case TYRAN_MOCHA_TOKEN_PARENTHESES_LEFT:
		operand = TYRAN_PARSER_UNARY_PARENTHESES;
		break;
	case TYRAN_MOCHA_TOKEN_BLOCK_START:
		operand = TYRAN_PARSER_UNARY_BLOCK;
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
	if (node->type != TYRAN_PARSER_NODE_TYPE_OPERAND_BINARY) {
		return 0;
	} else {
		tyran_parser_node_operand_binary* binary_operator = (tyran_parser_node_operand_binary*) node;
		return binary_operator;
	}
}

NODE tyran_mocha_parser_reduce_while(tyran_mocha_parser* parser)
{
	NODE block = tyran_mocha_parser_stack_pop(parser->stack);
	NODE condition = tyran_mocha_parser_stack_pop(parser->stack);
	
	NODE result = tyran_parser_while(condition, block);
	
	return result;
}


NODE tyran_mocha_parser_reduce_if(tyran_mocha_parser* parser)
{
			NODE if_expression;
			NODE if_then;
			NODE if_else = 0;
			
			if_then = tyran_mocha_parser_stack_pop(parser->stack);
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
				if_expression = tyran_mocha_parser_stack_pop(parser->stack);
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
	NODE root = tyran_mocha_parser_stack_pop(parser->stack);
	node->right = root;
	tyran_parser_node_print("PushRootRight", (NODE) node);

	NODE* last_inserted = tyran_mocha_parser_stack_push(parser->stack, (NODE)node);
	parser->last_inserted_node = last_inserted;
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
	NODE* empty = parser->empty_node;
	if (!empty) {
		empty = tyran_mocha_parser_stack_push(parser->stack, node);
	} else {
		*empty = node;
	}
	parser->last_inserted_node = empty;
}

void tyran_mocha_parser_add_default_operator(tyran_mocha_parser* parser, tyran_mocha_token_id token_id, int precedence)
{
	if (tyran_mocha_lexer_is_unary_operator(token_id)) {
	} else {
		tyran_parser_node_operand_binary* node = tyran_parser_operand_binary(tyran_mocha_parser_convert_binary_operand(token_id), 0, 0);
		TYRAN_LOG("Compare precedence %d  %d", precedence, parser->top_precedence);
		if (precedence < parser->top_precedence) {
			tyran_mocha_parser_push_root_right(parser, node);
			parser->top_precedence = precedence;
		} else {
			tyran_mocha_parser_push_last_inserted_right(parser, node);
		}
	}
}

NODE tyran_mocha_parser_if(tyran_mocha_parser_stack* stack)
{
	NODE expression = tyran_mocha_parser_stack_pop(stack);
	NODE block = tyran_mocha_parser_stack_pop(stack);

	return tyran_parser_if(expression, block);
}

void tyran_mocha_parser_add_terminal(tyran_mocha_parser* parser, tyran_mocha_token_id token_id, int precedence)
{
	NODE node;
	switch (token_id) {
		case TYRAN_MOCHA_TOKEN_IF:
			node = tyran_mocha_parser_if(parser->stack);
			break;
		default:
			tyran_mocha_parser_add_default_operator(parser, token_id, precedence);
			return;
			break;
	}
	NODE* last_inserted = tyran_mocha_parser_stack_push(parser->stack, node);
	parser->last_inserted_node = last_inserted;
	parser->top_precedence = 99999;
	parser->empty_node = 0;
}

void tyran_mocha_parser_add_token(tyran_mocha_parser* parser, tyran_mocha_token* token)
{
	tyran_mocha_parser_debug("before", parser, 0);
	tyran_mocha_operator_info info = tyran_mocha_parser_get_operator_info(token->token_id);
	if (info.token_id != TYRAN_MOCHA_TOKEN_END) {
		tyran_mocha_parser_add_terminal(parser, token->token_id, info.precedence);
	} else {
		NODE literal = tyran_mocha_parser_token_to_literal(token);
		tyran_mocha_parser_add_to_empty(parser, literal);
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
	
	return tyran_mocha_parser_stack_top(parser->stack);
}