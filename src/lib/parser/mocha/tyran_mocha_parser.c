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


typedef struct tyran_mocha_operator_stack {
	tyran_mocha_token** tokens;
	int length;
	int alloc_size;
} tyran_mocha_operator_stack;

typedef struct tyran_mocha_parser_stack {
	NODE* nodes;
	int alloc_size;
	int length;
} tyran_mocha_parser_stack;

typedef struct tyran_mocha_parser {
	tyran_mocha_operator_stack* operator_stack;
	tyran_mocha_parser_stack* stack;
} tyran_mocha_parser;


tyran_mocha_operator_stack* tyran_mocha_operator_stack_new()
{
	tyran_mocha_operator_stack* stack = TYRAN_MALLOC_TYPE(tyran_mocha_operator_stack, 1);
	stack->length = 0;
	stack->alloc_size = 100;
	stack->tokens = TYRAN_MALLOC_TYPE(tyran_mocha_token*, stack->alloc_size);
	return stack;
}

void tyran_mocha_operator_stack_push(tyran_mocha_operator_stack* stack, tyran_mocha_token* token)
{
	TYRAN_ASSERT(stack->length < stack->alloc_size, "Stack overflow");
	stack->tokens[stack->length++] = token;
}

tyran_mocha_token* tyran_mocha_operator_stack_pop(tyran_mocha_operator_stack* stack)
{
	if (!stack->length) {
		return 0;
	}
	return stack->tokens[--stack->length];
}


tyran_mocha_token* tyran_mocha_operator_stack_top(tyran_mocha_operator_stack* stack)
{
	if (!stack->length) {
		return 0;
	}
	return stack->tokens[stack->length - 1];
}

void tyran_mocha_operator_stack_free(tyran_mocha_operator_stack* stack)
{
	tyran_free(stack->tokens);
	tyran_free(stack);
}

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

void tyran_mocha_parser_stack_push(tyran_mocha_parser_stack* stack, NODE node)
{
	stack->nodes[stack->length++] = node;
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
	parser->operator_stack = tyran_mocha_operator_stack_new();
	parser->stack = tyran_mocha_parser_stack_new();
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

	TYRAN_LOG("---------------");
	tyran_mocha_operator_stack* operator_stack = parser->operator_stack;
	for (i=operator_stack->length-1; i>= 0; --i) {
		TYRAN_LOG_NO_LF("#%d operator:", i);
		tyran_mocha_lexer_debug_token(operator_stack->tokens[i]);
		TYRAN_LOG("");
	}
	TYRAN_LOG("==============");
}

tyran_mocha_operator_info tyran_mocha_parser_get_top_operator_info(tyran_mocha_operator_stack* stack)
{
	tyran_mocha_token_id token_id;
	if (!stack->length) {
		token_id = TYRAN_MOCHA_TOKEN_END;
	} else {
		token_id = stack->tokens[stack->length - 1]->token_id;
	}
	return tyran_mocha_parser_get_operator_info(token_id);
}


tyran_mocha_token* tyran_mocha_parser_find_matching_operand(tyran_mocha_token_id left, tyran_mocha_token_id right, tyran_mocha_token* first, tyran_mocha_token* last)
{
	tyran_mocha_token* token = tyran_mocha_lexer_next(first, last);
	int count = 0;

	for ( ; ; token = tyran_mocha_lexer_next(token, last))
	{
		if (token->token_id == right) {
			if (!count) {
				return token;
			}
			count--;
		} else if (token->token_id == left) {
			count++;
		}
	}
	
	return 0;
}

NODE tyran_mocha_parser_expression(tyran_mocha_parser* parser, tyran_mocha_token* first, tyran_mocha_token* last);

NODE tyran_mocha_parser_expression(tyran_mocha_parser* parser, tyran_mocha_token* first, tyran_mocha_token* last)
{
	return 0;
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

void tyran_mocha_parser_reduce(tyran_mocha_parser* parser, tyran_mocha_token* operator)
{
	tyran_mocha_parser_debug("reduce", parser, operator);
	
	NODE result;
	switch (operator->token_id)
	{
		case TYRAN_MOCHA_TOKEN_IF:
			result = tyran_mocha_parser_reduce_if(parser);
		break;
		case TYRAN_MOCHA_TOKEN_WHILE:
			result = tyran_mocha_parser_reduce_while(parser);
		break;
		default: {
		NODE right = 0;
		if (!tyran_mocha_lexer_is_unary_operator(operator->token_id)) {
			right = tyran_mocha_parser_stack_pop(parser->stack);
			// tyran_parser_node_print("right", right);
		}
		NODE left = tyran_mocha_parser_stack_pop(parser->stack);
		if (!left) {
			return;
		}
			// tyran_parser_node_print("left", left);
		if (!right) {
			result = tyran_parser_operand_unary(tyran_mocha_parser_convert_unary_operand(operator->token_id), left, 0);
		} else {
			result = tyran_parser_operand_binary(tyran_mocha_parser_convert_binary_operand(operator->token_id), left, right);
		}
	}
	break;
		
	}
	
	tyran_mocha_parser_stack_push(parser->stack, result);
}

int tyran_mocha_parser_reduce_once(tyran_mocha_parser* parser)
{
		tyran_mocha_token* operator = tyran_mocha_operator_stack_pop(parser->operator_stack);
		if (operator == 0) {
			return 0;
		}
		
		tyran_mocha_parser_reduce(parser, operator);
		return 1;
}

void tyran_mocha_parser_reduce_all_to(tyran_mocha_parser* parser, tyran_mocha_token_id encloser_id)
{
	tyran_mocha_token token;
	token.token_id = encloser_id;
	tyran_mocha_parser_debug("reduce enclosing", parser, &token);

	for ( ; ; ) {
		tyran_mocha_token* token = tyran_mocha_operator_stack_top(parser->operator_stack);
		int worked = tyran_mocha_parser_reduce_once(parser);
		if (!worked) {
			break;
		}
		if (token->token_id == encloser_id) {
			break;
		}
	}
}

void tyran_mocha_parser_reduce_all(tyran_mocha_parser* parser)
{
	tyran_mocha_parser_debug("reduce all", parser, 0);

	for ( ; ; ) {
		int worked = tyran_mocha_parser_reduce_once(parser);
		if (!worked) {
			break;
		}
	}
}

void tyran_mocha_parser_operator_stack_push_and_reduce(tyran_mocha_parser* parser, tyran_mocha_token* token)
{
	tyran_mocha_operator_stack* stack = parser->operator_stack;
	if (stack->length > 0) {
		tyran_mocha_token* top = stack->tokens[stack->length - 1];
		tyran_mocha_operator_info top_info = tyran_mocha_parser_get_operator_info(top->token_id);
		tyran_mocha_operator_info add_info = tyran_mocha_parser_get_operator_info(token->token_id);
		if (!top_info.is_enclosing && add_info.precedence <= top_info.precedence) {
			tyran_mocha_parser_reduce_once(parser);
		}
	}
	tyran_mocha_operator_stack_push(parser->operator_stack, token);
}

void tyran_mocha_parser_stack_push_and_check_enclosing(tyran_mocha_parser* parser, tyran_mocha_token* token)
{
	tyran_mocha_token_id enclosing_token_id = tyran_mocha_enclosing_end_token(token->token_id);
	if (enclosing_token_id != TYRAN_MOCHA_TOKEN_END) {
		tyran_mocha_parser_reduce_all_to(parser, enclosing_token_id);
	} else {
		NODE literal = tyran_mocha_parser_token_to_literal(token);
		tyran_mocha_parser_stack_push(parser->stack, literal);
	}
}

void tyran_mocha_parser_postfix(tyran_mocha_parser* parser, tyran_mocha_token* first, tyran_mocha_token* last)
{
	tyran_mocha_token* token = first;
	int last_was_literal = 0;
	
	for (; ; token = tyran_mocha_lexer_next(token, last))
	{
		tyran_mocha_operator_info operator_info = tyran_mocha_parser_get_operator_info(token->token_id);
		if (operator_info.token_id != TYRAN_MOCHA_TOKEN_END) {
			tyran_mocha_parser_operator_stack_push_and_reduce(parser, token);
			last_was_literal = 0;
		} else if (token->token_id != TYRAN_MOCHA_TOKEN_END) {
			int is_literal = tyran_mocha_lexer_is_literal(token);
			if (last_was_literal  && is_literal) {
				tyran_mocha_token* call = TYRAN_CALLOC(tyran_mocha_token);
				call->token_id = TYRAN_MOCHA_TOKEN_INVOKE;
				tyran_mocha_parser_operator_stack_push_and_reduce(parser, call);
			}
			last_was_literal = is_literal;
			tyran_mocha_parser_stack_push_and_check_enclosing(parser, token);
		}
		if (token == last) {
			break;
		}
	}
}


NODE tyran_mocha_parser_parse(tyran_mocha_lexer* lexer)
{
	tyran_mocha_token* first = tyran_mocha_lexer_first(lexer);
	tyran_mocha_token* last = tyran_mocha_lexer_last(lexer);
	
	tyran_mocha_parser* parser = tyran_mocha_parser_new();
	
	tyran_mocha_parser_postfix(parser, first, last);
	// tyran_mocha_parser_debug("postfix", parser);
	tyran_mocha_parser_reduce_all(parser);
	// tyran_mocha_parser_debug("result", parser);
	return tyran_mocha_parser_stack_top(parser->stack);
}