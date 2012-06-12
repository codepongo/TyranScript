/*
#include "tyranscript/parser/tyran_lexer.h"

void tyran_parse_assembler(tyran_lexer* lexer, char c)
{
	TYRAN_UNICODE_STRING(1024) string_buffer;
	tyran_string* temp_string_buffer = string_buffer.string;

	if (tyran_lexer_is_alpha(c) || c == '_' || c == '$') {
		int length = tyran_lexer_parse_identifier(lexer, c, temp_string_buffer);
	}
}

enum {
	TYRAN_TOKEN_ASSEMBLER_LD,
	TYRAN_TOKEN_ASSEMBLER_LDB,
	TYRAN_TOKEN_ASSEMBLER_LDC,
	TYRAN_TOKEN_ASSEMBLER_LDN,
	TYRAN_TOKEN_ASSEMBLER_ADD,
	TYRAN_TOKEN_ASSEMBLER_DIV,
	TYRAN_TOKEN_ASSEMBLER_MOD,
	TYRAN_TOKEN_ASSEMBLER_MUL,
	TYRAN_TOKEN_ASSEMBLER_NEG,
	TYRAN_TOKEN_ASSEMBLER_NOT,
	TYRAN_TOKEN_ASSEMBLER_POW,
	TYRAN_TOKEN_ASSEMBLER_SUB,
	TYRAN_TOKEN_ASSEMBLER_JB,
	TYRAN_TOKEN_ASSEMBLER_JBLD,
	TYRAN_TOKEN_ASSEMBLER_JEQ,
	TYRAN_TOKEN_ASSEMBLER_JLT,
	TYRAN_TOKEN_ASSEMBLER_JLE,
	TYRAN_TOKEN_ASSEMBLER_JMP,
	TYRAN_TOKEN_ASSEMBLER_RET,
	TYRAN_TOKEN_ASSEMBLER_CALL,
	TYRAN_TOKEN_ASSEMBLER_SET,
	TYRAN_TOKEN_ASSEMBLER_GET,
	TYRAN_TOKEN_ASSEMBLER_NEW,
} tyran_assembler_token;


static int tyran_lexer_assembler_get_keyword_token(const char* temp_string_buffer)
{
	typedef struct tyran_lexer_keyword {
		const char* name;
		int token_value;
	} tyran_lexer_keyword;

	static tyran_lexer_keyword keywords[] = {
		{ "ld", TYRAN_TOKEN_ASSEMBLER_LD },
		{ "lda", TYRAN_TOKEN_ASSEMBLER_LDA },
		{ "ldc", TYRAN_TOKEN_ASSEMBLER_LDC },
		{ "ldn", TYRAN_TOKEN_ASSEMBLER_LDN },
		{ "add", TYRAN_TOKEN_ASSEMBLER_ADD },
		{ "div", TYRAN_TOKEN_ASSEMBLER_DIV },
		{ "mod", TYRAN_TOKEN_ASSEMBLER_MOD },
		{ "mul", TYRAN_TOKEN_ASSEMBLER_MUL },
		{ "neg", TYRAN_TOKEN_ASSEMBLER_NEG },
		{ "not", TYRAN_TOKEN_ASSEMBLER_NOT },
		{ "pow", TYRAN_TOKEN_ASSEMBLER_POW },
		{ "sub", TYRAN_TOKEN_ASSEMBLER_SUB },
		{ "jb", TYRAN_TOKEN_ASSEMBLER_JB },
		{ "jbld", TYRAN_TOKEN_ASSEMBLER_JBLD },
		{ "jeq", TYRAN_TOKEN_ASSEMBLER_JEQ },
		{ "jlt", TYRAN_TOKEN_ASSEMBLER_JLT },
		{ "jlte", TYRAN_TOKEN_ASSEMBLER_JLE },
		{ "jmp", TYRAN_TOKEN_ASSEMBLER_JMP },
		{ "ret", TYRAN_TOKEN_ASSEMBLER_RET },
		{ "call", TYRAN_TOKEN_ASSEMBLER_CALL },
		{ "set", TYRAN_TOKEN_ASSEMBLER_SET },
		{ "get", TYRAN_TOKEN_ASSEMBLER_GET },
		{ "new", TYRAN_TOKEN_ASSEMBLER_NEW }
	};

	size_t i;

	for (i = 0; i < sizeof(keywords) / sizeof(tyran_lexer_keyword); ++i) {
		if (tyran_strcmp(temp_string_buffer, keywords[i].name) == 0)
			return keywords[i].token_value;
	}
	return 0;
}

static int tyran_lexer_assembler_next_token(YYSTYPE* token, YYLTYPE* lexer_position_info, tyran_lexer* lexer)
{
	TYRAN_UNICODE_STRING(1024) string_buffer;
	tyran_string* temp_string_buffer = string_buffer.string;

	tyran_lexer_set_begin(lexer_position_info, lexer);

	char c = tyran_lexer_next_character_skip_whitespace(lexer);
	if (!c) {
		return 0;
	}

	if (tyran_lexer_is_alpha(c) || c == '_' || c == '$') {
		return tyran_lexer_assembler_get_keyword_token(lexer, c, temp_string_buffer, &string_buffer.len, lexer_position_info, token);
	} else if (tyran_lexer_is_digit(c)) {
		return tyran_lexer_parse_number(lexer, c, temp_string_buffer, &string_buffer.len, lexer_position_info, token);
	} else if (c == '"' || c == '\'') {
		return tyran_lexer_parse_whole_string(lexer, c, lexer_position_info, token);
	} else if (c == '/') {
		int r = tyran_lexer_parse_comment(lexer);
		if (r) {
			return r;
		}
	}

	tyran_lexer_push_character(c, lexer);
	int r = tyran_lexer_parse_operand(lexer);

	tyran_lexer_set_end(lexer_position_info, lexer);

	return r;
}


int yylex(YYSTYPE* token, YYLTYPE* lexer_position_info, tyran_parser_state* parser_state)
{
	int ret;
	do {
		ret = tyran_lexer_next_token(token, lexer_position_info, parser_state->lexer);
	} while (ret == TYRAN_TOKEN_COMMENT);

	parser_state->lexer->last_token = ret;
	return ret;
}

*/
