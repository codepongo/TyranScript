#include <tyranscript/parser/mocha/tyran_mocha_lexer.h>
#include <tyranscript/parser/mocha/tyran_mocha_lexer_debug.h>
#include <tyranscript/parser/mocha/tyran_parser_tree.h>

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
	return stack->nodes[--stack->length];
}


tyran_mocha_parser* tyran_mocha_parser_new()
{
	tyran_mocha_parser* parser = TYRAN_MALLOC_TYPE(tyran_mocha_parser, 1);
	parser->operator_stack = tyran_mocha_operator_stack_new();
	parser->stack = tyran_mocha_parser_stack_new();
	return parser;
}

void tyran_mocha_parser_debug(tyran_mocha_parser* parser)
{
	tyran_mocha_parser_stack* stack = parser->stack;
	int i;
	for (i = 0; i < stack->length; ++i) {
		TYRAN_PARSER_NODE_PRINT("%d", stack->nodes[i]);
	}

	tyran_mocha_operator_stack* operator_stack = parser->operator_stack;
	for (i=0; i< operator_stack->length; ++i) {
		tyran_mocha_lexer_debug_token(operator_stack->tokens[i]);
	}
}


NODE tyran_mocha_parser_if(tyran_mocha_token* first, tyran_mocha_token* last)
{
	return 0;
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
	case TYRAN_MOCHA_TOKEN_EQUAL:
		operand = TYRAN_PARSER_ASSIGNMENT;
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
	default:
		TYRAN_ERROR("unknown token to convert");
	}
	
	return operand;
}



NODE tyran_mocha_parser_return(tyran_mocha_parser* parser, tyran_mocha_token* first, tyran_mocha_token* last)
{
	NODE expression;
	if (first->token_id == TYRAN_MOCHA_TOKEN_TERMINATOR) {
		expression = 0;
	} else {
		tyran_mocha_token* terminator = tyran_mocha_lexer_find_terminator(first, last);
		expression = tyran_mocha_parser_expression(parser, first, tyran_mocha_lexer_previous(terminator, first));
	}
	return tyran_parser_return(expression);
}

NODE tyran_mocha_parser_body(tyran_mocha_parser* parser, tyran_mocha_token* first, tyran_mocha_token* last)
{
	NODE node;
	
	switch (first->token_id) {
	case TYRAN_MOCHA_TOKEN_IF:
		node = tyran_mocha_parser_if(tyran_mocha_lexer_next(first, last), last);
		break;
	case TYRAN_MOCHA_TOKEN_RETURN:
		node = tyran_mocha_parser_return(parser, tyran_mocha_lexer_next(first, last), last);
		break;
	default:
		node = tyran_mocha_parser_expression(parser, first, last);
	}
	return node;
}

typedef struct tyran_mocha_operator_info {
	tyran_mocha_token_id token_id;
	int direction;
	int precedence;
} tyran_mocha_operator_info;


tyran_mocha_operator_info tyran_mocha_parser_get_operator_info(tyran_mocha_token_id token_id)
{
	tyran_mocha_operator_info operands_to_match[] = {
		{TYRAN_MOCHA_TOKEN_EQUAL, 1},
		{TYRAN_MOCHA_TOKEN_MEMBER, 1},
		{TYRAN_MOCHA_TOKEN_COMMA, 1},
		{TYRAN_MOCHA_TOKEN_ADD, 1},
		{TYRAN_MOCHA_TOKEN_SUBTRACT, 1},
		{TYRAN_MOCHA_TOKEN_MULTIPLY, 1},
		{TYRAN_MOCHA_TOKEN_BRACKET_LEFT, 1},
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

NODE tyran_mocha_parser_token_to_literal(tyran_mocha_token* first)
{
	switch (first->token_id) {
		case TYRAN_MOCHA_TOKEN_IDENTIFIER:
			return tyran_parser_literal_identifier(first->token_data);
		case TYRAN_MOCHA_TOKEN_STRING:
			return tyran_parser_literal_string(first->token_data);
		case TYRAN_MOCHA_TOKEN_NUMBER:
			return tyran_parser_literal_number(first->token_data);
		default:
			TYRAN_ERROR("Illegal token:%d", first->token_id);
			return 0;
	}
}

void tyran_mocha_parser_postfix(tyran_mocha_parser* parser, tyran_mocha_token* first, tyran_mocha_token* last)
{
	tyran_mocha_token* token = first;
	
	for (; ; token = tyran_mocha_lexer_next(token, last))
	{
		tyran_mocha_operator_info operator_info = tyran_mocha_parser_get_operator_info(token->token_id);
		if (operator_info.token_id != TYRAN_MOCHA_TOKEN_END) {
			tyran_mocha_operator_stack_push(parser->operator_stack, token);
		} else if (token->token_id != TYRAN_MOCHA_TOKEN_END) {
			NODE literal = tyran_mocha_parser_token_to_literal(token);
			tyran_mocha_parser_stack_push(parser->stack, literal);
		}
		if (token == last) {
			break;
		}
	}
}

void tyran_mocha_parser_reduce(tyran_mocha_parser* parser)
{
	TYRAN_LOG("REDUCE!");

	tyran_mocha_token* operator;
	while ((operator = tyran_mocha_operator_stack_pop(parser->operator_stack)) != 0) {
		tyran_mocha_lexer_debug_token(operator);
		NODE left = tyran_mocha_parser_stack_pop(parser->stack);
		TYRAN_PARSER_NODE_PRINT("left", left);
		NODE right = tyran_mocha_parser_stack_pop(parser->stack);
		TYRAN_PARSER_NODE_PRINT("right", right);
		
		NODE result = tyran_parser_operand_binary(tyran_mocha_parser_convert_binary_operand(operator->token_id), left, right);
		tyran_mocha_parser_stack_push(parser->stack, result);
	}
}

NODE tyran_mocha_parser_parse(tyran_mocha_lexer* lexer)
{
	tyran_mocha_token* first = tyran_mocha_lexer_first(lexer);
	tyran_mocha_token* last = tyran_mocha_lexer_last(lexer);
	
	tyran_mocha_parser* parser = tyran_mocha_parser_new();
	
	tyran_mocha_parser_postfix(parser, first, last);
	tyran_mocha_parser_debug(parser);
	
	tyran_mocha_parser_reduce(parser);
	
	return tyran_mocha_parser_body(parser, first, tyran_mocha_lexer_previous(last, first));
}