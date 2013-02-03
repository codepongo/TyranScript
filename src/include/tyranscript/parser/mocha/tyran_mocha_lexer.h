#ifndef _TYRAN_MOCHA_LEXER_H
#define _TYRAN_MOCHA_LEXER_H

struct tyran_memory_pool;
struct tyran_memory;



typedef enum tyran_mocha_token_id {
	TYRAN_MOCHA_TOKEN_END,
	TYRAN_MOCHA_TOKEN_INCREMENT,
	TYRAN_MOCHA_TOKEN_DECREMENT,
	TYRAN_MOCHA_TOKEN_DIVIDE,
	TYRAN_MOCHA_TOKEN_MULTIPLY,
	TYRAN_MOCHA_TOKEN_MODULUS,
	TYRAN_MOCHA_TOKEN_ASSIGNMENT,
	TYRAN_MOCHA_TOKEN_ASSIGNMENT_ADD,
	TYRAN_MOCHA_TOKEN_ASSIGNMENT_SUBTRACT,
	TYRAN_MOCHA_TOKEN_ASSIGNMENT_MULTIPLY,
	TYRAN_MOCHA_TOKEN_ASSIGNMENT_DIVIDE,
	TYRAN_MOCHA_TOKEN_ASSIGNMENT_MODULUS,
	TYRAN_MOCHA_TOKEN_ADD,
	TYRAN_MOCHA_TOKEN_SUBTRACT,
	TYRAN_MOCHA_TOKEN_EQUAL,
	TYRAN_MOCHA_TOKEN_NOT_EQUAL,
	TYRAN_MOCHA_TOKEN_LESS_EQUAL,
	TYRAN_MOCHA_TOKEN_LESS,
	TYRAN_MOCHA_TOKEN_GREATER_EQUAL,
	TYRAN_MOCHA_TOKEN_GREATER,
	TYRAN_MOCHA_TOKEN_NOT,
	TYRAN_MOCHA_TOKEN_AND,
	TYRAN_MOCHA_TOKEN_OR,
	TYRAN_MOCHA_TOKEN_MEMBER,
	TYRAN_MOCHA_TOKEN_INDEX,
	TYRAN_MOCHA_TOKEN_IN,
	TYRAN_MOCHA_TOKEN_PARENTHESES_LEFT,
	TYRAN_MOCHA_TOKEN_PARENTHESES_RIGHT,
	TYRAN_MOCHA_TOKEN_BRACKET_LEFT,
	TYRAN_MOCHA_TOKEN_BRACKET_RIGHT,
	TYRAN_MOCHA_TOKEN_OBJECT_START,
	TYRAN_MOCHA_TOKEN_OBJECT_END,
	TYRAN_MOCHA_TOKEN_COLON,
	TYRAN_MOCHA_TOKEN_COMMA,
	TYRAN_MOCHA_TOKEN_IF,
	TYRAN_MOCHA_TOKEN_UNLESS,
	TYRAN_MOCHA_TOKEN_THEN,
	TYRAN_MOCHA_TOKEN_ELSE,
	TYRAN_MOCHA_TOKEN_TRUE,
	TYRAN_MOCHA_TOKEN_FALSE,
	TYRAN_MOCHA_TOKEN_NIL,
	TYRAN_MOCHA_TOKEN_SELF,
	TYRAN_MOCHA_TOKEN_CLASS,
	TYRAN_MOCHA_TOKEN_EXTENDS,
	TYRAN_MOCHA_TOKEN_RETURN,
	TYRAN_MOCHA_TOKEN_WHILE,
	TYRAN_MOCHA_TOKEN_CASE,
	TYRAN_MOCHA_TOKEN_WHEN,
	TYRAN_MOCHA_TOKEN_FOR,
	TYRAN_MOCHA_TOKEN_SUPER,
	TYRAN_MOCHA_TOKEN_UNTIL,
	TYRAN_MOCHA_TOKEN_BREAK,
	TYRAN_MOCHA_TOKEN_CONTINUE,
	TYRAN_MOCHA_TOKEN_NUMBER,
	TYRAN_MOCHA_TOKEN_STRING,
	TYRAN_MOCHA_TOKEN_IDENTIFIER,
	TYRAN_MOCHA_TOKEN_CALL,
	TYRAN_MOCHA_TOKEN_FUNCTION_GLYPH,
	TYRAN_MOCHA_TOKEN_FUNCTION_GLYPH_BOUND,
	TYRAN_MOCHA_TOKEN_BLOCK_START,
	TYRAN_MOCHA_TOKEN_BLOCK_END,
	TYRAN_MOCHA_TOKEN_LINE_START,
	TYRAN_MOCHA_TOKEN_RANGE_INCLUSIVE,
	TYRAN_MOCHA_TOKEN_RANGE_EXCLUSIVE,
	TYRAN_MOCHA_TOKEN_MAX
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
tyran_mocha_lexer* tyran_mocha_lexer_lex(struct tyran_memory_pool* mocha_lexer_pool, struct tyran_memory_pool* mocha_token_pool, struct tyran_memory_pool* lexer_pool, struct tyran_memory* memory, const char* buf, int length);

tyran_mocha_token* tyran_mocha_lexer_find(tyran_mocha_token* first, tyran_mocha_token* last, tyran_mocha_token_id id);
tyran_mocha_token* tyran_mocha_lexer_find_terminator(tyran_mocha_token* first, tyran_mocha_token* last);
tyran_mocha_token* tyran_mocha_lexer_find_ignore_parentheses(tyran_mocha_token* first, tyran_mocha_token* last, tyran_mocha_token_id id, int reverse);
tyran_mocha_token* tyran_mocha_lexer_first(tyran_mocha_lexer* lexer);
tyran_mocha_token* tyran_mocha_lexer_last(tyran_mocha_lexer* lexer);

tyran_mocha_token* tyran_mocha_lexer_next(tyran_mocha_token* first, tyran_mocha_token* last);
tyran_mocha_token* tyran_mocha_lexer_previous(tyran_mocha_token* token, tyran_mocha_token* first);

int tyran_mocha_lexer_is_unary_operator(tyran_mocha_token_id token_id);
tyran_mocha_token_id tyran_mocha_enclosing_start_token(tyran_mocha_token_id token_id);
int tyran_mocha_lexer_is_literal(tyran_mocha_token* token);

#endif
