#ifndef _TYRAN_LEXER_H
#define _TYRAN_LEXER_H

#include "tyran_parser.h"

struct tyran_parser_state;

typedef struct tyran_lexer {
	char* buffer;
	int index;
	int line;
	int column;
	int last_token;
} tyran_lexer;

int yylex(YYSTYPE* token, YYLTYPE* lexer_position_info, struct tyran_parser_state* parser_state);
void yyerror(YYLTYPE* lexer_position_info, struct tyran_parser_state* ps, const char* error_message);

#endif
