#ifndef _TYRAN_MOCHA_LEXER_H
#define _TYRAN_MOCHA_LEXER_H


typedef enum tyran_mocha_token_id {
	TYRAN_MOCHA_TOKEN_END,
	TYRAN_MOCHA_TOKEN_INCREMENT,
	TYRAN_MOCHA_TOKEN_DECREMENT,
	TYRAN_MOCHA_TOKEN_DIVIDE,
	TYRAN_MOCHA_TOKEN_MULTIPLY,
	TYRAN_MOCHA_TOKEN_MODULUS,
	TYRAN_MOCHA_TOKEN_EQUAL,
	TYRAN_MOCHA_TOKEN_ADD,
	TYRAN_MOCHA_TOKEN_SUBTRACT,
	TYRAN_MOCHA_TOKEN_NOT,
	TYRAN_MOCHA_TOKEN_MEMBER,
	TYRAN_MOCHA_TOKEN_PARENTHESES_LEFT,
	TYRAN_MOCHA_TOKEN_PARENTHESES_RIGHT,
	TYRAN_MOCHA_TOKEN_BRACKET_LEFT,
	TYRAN_MOCHA_TOKEN_BRACKET_RIGHT,
	TYRAN_MOCHA_TOKEN_TERMINATOR,
	TYRAN_MOCHA_TOKEN_OBJECT_START,
	TYRAN_MOCHA_TOKEN_OBJECT_END,
	TYRAN_MOCHA_TOKEN_COLON,
	TYRAN_MOCHA_TOKEN_COMMA,
	TYRAN_MOCHA_TOKEN_IF,
	TYRAN_MOCHA_TOKEN_ELSE,
	TYRAN_MOCHA_TOKEN_TRUE,
	TYRAN_MOCHA_TOKEN_FALSE,
	TYRAN_MOCHA_TOKEN_CLASS,
	TYRAN_MOCHA_TOKEN_RETURN,
	TYRAN_MOCHA_TOKEN_WHILE,
	TYRAN_MOCHA_TOKEN_SWITCH,
	TYRAN_MOCHA_TOKEN_WHEN,
	TYRAN_MOCHA_TOKEN_FOR,
	TYRAN_MOCHA_TOKEN_SUPER,
	TYRAN_MOCHA_TOKEN_UNTIL,
	TYRAN_MOCHA_TOKEN_OWN,
	TYRAN_MOCHA_TOKEN_NUMBER,
	TYRAN_MOCHA_TOKEN_STRING,
	TYRAN_MOCHA_TOKEN_IDENTIFIER,
	TYRAN_MOCHA_TOKEN_FUNCTION_GLYPH,
	TYRAN_MOCHA_TOKEN_FUNCTION_GLYPH_BOUND,
} tyran_mocha_token_id;

typedef struct tyran_mocha_token {
	enum tyran_mocha_token_id token_id;
	void* token_data;
} tyran_mocha_token;

struct tyran_lexer;

typedef struct tyran_mocha_lexer {
	tyran_mocha_token* tokens;
	struct tyran_lexer* lexer;
	int token_count;
} tyran_mocha_lexer;

tyran_mocha_lexer* tyran_mocha_lexer_new();
void tyran_mocha_lexer_destroy(tyran_mocha_lexer* lexer);
tyran_mocha_lexer* tyran_mocha_lexer_lex(const char* buf, int length);

tyran_mocha_token* tyran_mocha_lexer_find(tyran_mocha_token* first, tyran_mocha_token* last, tyran_mocha_token_id id);
tyran_mocha_token* tyran_mocha_lexer_find_terminator(tyran_mocha_token* first, tyran_mocha_token* last);
tyran_mocha_token* tyran_mocha_lexer_find_ignore_parentheses(tyran_mocha_token* first, tyran_mocha_token* last, tyran_mocha_token_id id, int reverse);
tyran_mocha_token* tyran_mocha_lexer_first(tyran_mocha_lexer* lexer);
tyran_mocha_token* tyran_mocha_lexer_last(tyran_mocha_lexer* lexer);

tyran_mocha_token* tyran_mocha_lexer_next(tyran_mocha_token* first, tyran_mocha_token* last);
tyran_mocha_token* tyran_mocha_lexer_previous(tyran_mocha_token* token, tyran_mocha_token* first);
tyran_mocha_token_id tyran_mocha_enclosing_start_token(tyran_mocha_token_id token_id);

#endif
