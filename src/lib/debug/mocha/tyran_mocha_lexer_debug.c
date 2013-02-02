#include <tyranscript/tyran_configuration.h>
#include <tyranscript/debug/mocha/tyran_mocha_lexer_debug.h>
#include <tyranscript/parser/mocha/tyran_mocha_lexer.h>
#include <tyranscript/tyran_config.h>

void tyran_mocha_lexer_debug(tyran_mocha_lexer* lexer)
{
	int i;

	for (i=0; i<lexer->token_count; ++i) {
		tyran_mocha_token* token = &lexer->tokens[i];
		tyran_mocha_lexer_debug_token(token);
	}
}

void tyran_mocha_lexer_debug_tokens(const char* description, tyran_mocha_token* first, tyran_mocha_token* last)
{
	tyran_mocha_token* token = first;
	TYRAN_LOG("== %s ==", description);

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
#if defined TYRAN_CONFIGURATION_DEBUG
	const char* token_id_to_string[TYRAN_MOCHA_TOKEN_MAX] = {
		"END",
		"INCREMENT",
		"DECREMENT",
		"DIVIDE",
		"MULTIPLY",
		"MODULUS",
		"ASSIGNMENT",
		"ASSIGNMENT_ADD",
		"ASSIGNMENT_SUBTRACT",
		"ASSIGNMENT_MULTIPLY",
		"ASSIGNMENT_DIVIDE",
		"ASSIGNMENT_MODULUS",
		"ADD",
		"SUBTRACT",
		"EQUAL",
		"NOT_EQUAL",
		"LESS_EQUAL",
		"LESS",
		"GREATER_EQUAL",
		"GREATER",
		"NOT",
		"AND",
		"OR",
		"MEMBER",
		"INDEX",
		"IN",
		"PARENTHESES_LEFT",
		"PARENTHESES_RIGHT",
		"BRACKET_LEFT",
		"BRACKET_RIGHT",
		"OBJECT_START",
		"OBJECT_END",
		"COLON",
		"COMMA",
		"IF",
		"UNLESS",
		"THEN",
		"ELSE",
		"TRUE",
		"FALSE",
		"UNDEFINED",
		"SELF",
		"CLASS",
		"EXTENDS",
		"RETURN",
		"WHILE",
		"CASE",
		"WHEN",
		"FOR",
		"SUPER",
		"UNTIL",
		"BREAK",
		"CONTINUE",
		"NUMBER",
		"STRING",
		"IDENTIFIER",
		"CALL",
		"FUNC_GLYPH",
		"FUNC_GLYPH_BOUND",
		"BLOCK_START",
		"BLOCK_END",
		"LINE_START",
		"RANGE_INCLUSIVE",
		"RANGE"
	};

	TYRAN_LOG_NO_LF(" %s", token_id_to_string[token->token_id]);

	if (token->token_id == TYRAN_MOCHA_TOKEN_IDENTIFIER || token->token_id == TYRAN_MOCHA_TOKEN_STRING) {
		TYRAN_LOG_NO_LF("(%s)", (const char*) token->token_data);
	}

#endif
}

