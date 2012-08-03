#include <tyranscript/parser/mocha/tyran_mocha_lexer_debug.h>
#include <tyranscript/parser/mocha/tyran_mocha_lexer.h>
#include <tyranscript/tyran_config.h>

void tyran_mocha_lexer_debug(tyran_mocha_lexer* lexer)
{
	int i;
	
	for (i=0; i<lexer->token_count; ++i)
	{
		tyran_mocha_token* token = &lexer->tokens[i];
		tyran_mocha_lexer_debug_token(token);
	}
}

void tyran_mocha_lexer_debug_tokens(const char* description, tyran_mocha_token* first, tyran_mocha_token* last)
{
	TYRAN_LOG("== %s ==", description);
	tyran_mocha_token* token = first;
	
	for (token = first; token; token = tyran_mocha_lexer_next(token, last)) {
		tyran_mocha_lexer_debug_token(token);
		if (token == last) {
			break;
		}
	}

	TYRAN_LOG("========");
}

void tyran_mocha_lexer_debug_token(tyran_mocha_token* token)
{
	switch (token->token_id)
	{
	case TYRAN_MOCHA_TOKEN_ADD:
		TYRAN_LOG("add");
	break;
	case TYRAN_MOCHA_TOKEN_BRACKET_LEFT:
		TYRAN_LOG("bracket_left");
	break;
	case TYRAN_MOCHA_TOKEN_BRACKET_RIGHT:
		TYRAN_LOG("bracket_right");
	break;
	case TYRAN_MOCHA_TOKEN_CLASS:
		TYRAN_LOG("class");
	break;
	case TYRAN_MOCHA_TOKEN_COLON:
		TYRAN_LOG("colon");
	break;
	case TYRAN_MOCHA_TOKEN_COMMA:
		TYRAN_LOG("comma");
	break;
	case TYRAN_MOCHA_TOKEN_DECREMENT:
		TYRAN_LOG("decrement");
	break;
	case TYRAN_MOCHA_TOKEN_DIVIDE:
		TYRAN_LOG("divide");
	break;
	case TYRAN_MOCHA_TOKEN_ELSE:
		TYRAN_LOG("else");
	break;
	case TYRAN_MOCHA_TOKEN_END:
		TYRAN_LOG("end");
	break;
	case TYRAN_MOCHA_TOKEN_EQUAL:
		TYRAN_LOG("equal");
	break;
	case TYRAN_MOCHA_TOKEN_FALSE:
		TYRAN_LOG("false");
	break;
	case TYRAN_MOCHA_TOKEN_FOR:
		TYRAN_LOG("for");
	break;
	case TYRAN_MOCHA_TOKEN_IDENTIFIER:
		TYRAN_LOG("identifier '%s'", (const char*)(token->token_data));
	break;
	case TYRAN_MOCHA_TOKEN_IF:
		TYRAN_LOG("if");
	break;
	case TYRAN_MOCHA_TOKEN_INCREMENT:
		TYRAN_LOG("increment");
	break;
	case TYRAN_MOCHA_TOKEN_INVOKE:
		TYRAN_LOG("invoke");
	break;
	case TYRAN_MOCHA_TOKEN_MEMBER:
		TYRAN_LOG("member");
	break;
	case TYRAN_MOCHA_TOKEN_MODULUS:
		TYRAN_LOG("modulus");
	break;
	case TYRAN_MOCHA_TOKEN_MULTIPLY:
		TYRAN_LOG("multiply");
	break;
	case TYRAN_MOCHA_TOKEN_NOT:
		TYRAN_LOG("not");
	break;
	case TYRAN_MOCHA_TOKEN_NUMBER:
		TYRAN_LOG("number %f", *(float*)(token->token_data));
	break;
	case TYRAN_MOCHA_TOKEN_OBJECT_END:
		TYRAN_LOG("end");
	break;
	case TYRAN_MOCHA_TOKEN_OBJECT_START:
		TYRAN_LOG("start");
	break;
	case TYRAN_MOCHA_TOKEN_OWN:
		TYRAN_LOG("own");
	break;
	case TYRAN_MOCHA_TOKEN_PARENTHESES_LEFT:
		TYRAN_LOG("par left");
	break;
	case TYRAN_MOCHA_TOKEN_PARENTHESES_RIGHT:
		TYRAN_LOG("par right");
	break;
	case TYRAN_MOCHA_TOKEN_RETURN:
		TYRAN_LOG("return");
	break;
	case TYRAN_MOCHA_TOKEN_STRING:
		TYRAN_LOG("string '%s'", (const char*)(token->token_data));
	break;
	case TYRAN_MOCHA_TOKEN_SUBTRACT:
		TYRAN_LOG("subtract");
	break;
	case TYRAN_MOCHA_TOKEN_SUPER:
		TYRAN_LOG("super");
	break;
	case TYRAN_MOCHA_TOKEN_SWITCH:
		TYRAN_LOG("switch");
	break;
	case TYRAN_MOCHA_TOKEN_TERMINATOR:
		TYRAN_LOG("terminator");
	break;
	case TYRAN_MOCHA_TOKEN_TRUE:
		TYRAN_LOG("true");
	break;
	case TYRAN_MOCHA_TOKEN_UNTIL:
		TYRAN_LOG("until");
	break;
	case TYRAN_MOCHA_TOKEN_WHEN:
		TYRAN_LOG("when");
	break;
	case TYRAN_MOCHA_TOKEN_WHILE:
		TYRAN_LOG("while");
	break;
	case TYRAN_MOCHA_TOKEN_FUNCTION_GLYPH:
		TYRAN_LOG("func");
	break;
	case TYRAN_MOCHA_TOKEN_FUNCTION_GLYPH_BOUND:
		TYRAN_LOG("func_bound");
	break;
	}
}