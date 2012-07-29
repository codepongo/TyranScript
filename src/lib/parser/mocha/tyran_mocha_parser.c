#include <tyranscript/parser/mocha/tyran_mocha_lexer.h>
#include <tyranscript/parser/mocha/tyran_mocha_lexer_debug.h>
#include <tyranscript/parser/mocha/tyran_parser_tree.h>

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

NODE tyran_mocha_parser_expression(tyran_mocha_token* first, tyran_mocha_token* last);


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
	default:
		TYRAN_ERROR("unknown token to convert");
	}
	
	return operand;
}


NODE tyran_mocha_parser_expression_operands(tyran_mocha_token* first, tyran_mocha_token* last)
{
	tyran_mocha_lexer_debug_tokens("operand check", first, last);
	if (first == last) {
		return 0;
	}
	
	typedef struct operands {
		tyran_mocha_token_id token_id;
	} operands;

	operands operands_to_match[] = {TYRAN_MOCHA_TOKEN_ADD, TYRAN_MOCHA_TOKEN_SUBTRACT, TYRAN_MOCHA_TOKEN_MULTIPLY, TYRAN_MOCHA_TOKEN_MULTIPLY};
	
	int i;
	
	for (i=0; i < sizeof(operands_to_match)/sizeof(operands); ++i)
	{
		tyran_mocha_token* found_operand = tyran_mocha_lexer_find(first, last, operands_to_match[i].token_id);
		if (found_operand) {
		
			NODE left = tyran_mocha_parser_expression(first, tyran_mocha_lexer_previous(found_operand, first));
			NODE right = tyran_mocha_parser_expression(tyran_mocha_lexer_next(found_operand, last), last);
			
			if (left && right) {
				return tyran_parser_operand_binary(tyran_mocha_parser_convert_binary_operand(found_operand->token_id), left, right);
			}
		}
	}
	
	return 0;
}

NODE tyran_mocha_parser_expression(tyran_mocha_token* first, tyran_mocha_token* last)
{
	if (first == last) {
		if (first->token_id == TYRAN_MOCHA_TOKEN_IDENTIFIER) {
			return tyran_parser_literal_identifier(first->token_data);
		} else if (first->token_id == TYRAN_MOCHA_TOKEN_STRING) {
			return tyran_parser_literal_string(first->token_data);
		} else if (first->token_id == TYRAN_MOCHA_TOKEN_NUMBER) {
			return tyran_parser_literal_number(first->token_data);
		}
	}
	
	tyran_mocha_lexer_debug_tokens("expression check", first, last);
	typedef struct matching_operands {
		tyran_mocha_token_id left;
		tyran_mocha_token_id right;
	} matching_operands;

	matching_operands operands_to_match[] = {{TYRAN_MOCHA_TOKEN_PARENTHESES_LEFT, TYRAN_MOCHA_TOKEN_PARENTHESES_RIGHT}, {TYRAN_MOCHA_TOKEN_BRACKET_LEFT, TYRAN_MOCHA_TOKEN_BRACKET_RIGHT}};
	
	int i;
	
	for (i=0; i < sizeof(operands_to_match)/sizeof(matching_operands); ++i)
	{
		tyran_mocha_token* found = tyran_mocha_lexer_find(first, last, operands_to_match[i].left);
		if (found) {
			tyran_mocha_token* last_operand = tyran_mocha_parser_find_matching_operand(operands_to_match[i].left, operands_to_match[i].right, found, last);
			tyran_mocha_lexer_debug_tokens("expression match", found, last_operand);
			NODE result = tyran_mocha_parser_expression(tyran_mocha_lexer_next(found, last), tyran_mocha_lexer_previous(last_operand, last));
			NODE left = 0;
			NODE right = 0;
			if (first != found) {
				left = tyran_mocha_parser_expression(first, tyran_mocha_lexer_previous(found, last));
			}
			if (last != last_operand) {
				right = tyran_mocha_parser_expression(tyran_mocha_lexer_next(last_operand, last), last);
			}
			if (left) {
				result = tyran_parser_concat(left, result);
			}
			if (right) {
				result = tyran_parser_concat(result, right);
			}
			
			return result;
		}
	}
	
	return tyran_mocha_parser_expression_operands(first, last);
}

NODE tyran_mocha_parser_return(tyran_mocha_token* first, tyran_mocha_token* last)
{
	NODE expression;
	if (first->token_id == TYRAN_MOCHA_TOKEN_TERMINATOR) {
		expression = 0;
	} else {
		tyran_mocha_token* terminator = tyran_mocha_lexer_find_terminator(first, last);
		expression = tyran_mocha_parser_expression(first, tyran_mocha_lexer_previous(terminator, first));
	}
	return tyran_parser_return(expression);
}

NODE tyran_mocha_parser_body(tyran_mocha_token* first, tyran_mocha_token* last)
{
	NODE node;
	
	switch (first->token_id) {
	case TYRAN_MOCHA_TOKEN_IF:
		node = tyran_mocha_parser_if(tyran_mocha_lexer_next(first, last), last);
		break;
	case TYRAN_MOCHA_TOKEN_RETURN:
		node = tyran_mocha_parser_return(tyran_mocha_lexer_next(first, last), last);
		break;
	default:
		node = tyran_mocha_parser_expression(first, last);
	}
	return node;
}

NODE tyran_mocha_parser_parse(tyran_mocha_lexer* lexer)
{
	tyran_mocha_token* first = tyran_mocha_lexer_first(lexer);
	tyran_mocha_token* last = tyran_mocha_lexer_last(lexer);
	
	return tyran_mocha_parser_body(first, tyran_mocha_lexer_previous(last, first));
}
