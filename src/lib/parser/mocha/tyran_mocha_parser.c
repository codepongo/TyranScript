#include <tyranscript/parser/mocha/tyran_mocha_lexer.h>
#include <tyranscript/parser/mocha/tyran_parser_tree.h>

NODE tyran_mocha_parser_if(tyran_mocha_token* first, tyran_mocha_token* last)
{
	return 0;
}

NODE tyran_mocha_parser_expression(tyran_mocha_token* first, tyran_mocha_token* last)
{
	tyran_mocha_lexer_debug_tokens("expression", first, last);
	return 0;
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
	
	return tyran_mocha_parser_body(first, last);
}
