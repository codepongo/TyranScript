#ifndef _TYRAN_LEXER_H
#define _TYRAN_LEXER_H

#include "tyran_parser.h"
#include <tyranscript/tyran_string.h>

struct tyran_parser_state;

typedef struct tyran_lexer {
	char* buffer;
	int index;
	int line;
	int column;
	int last_token;
} tyran_lexer;

int yylex(tyran_lexer_token_data* token, tyran_lexer_position_info* lexer_position_info, struct tyran_parser_state* parser_state);
void yyerror(tyran_lexer_position_info* lexer_position_info, struct tyran_parser_state* ps, const char* error_message);

int tyran_lexer_is_alpha(int c);
int tyran_lexer_parse_identifier(tyran_lexer* lexer, char c, tyran_string* temp_string_buffer);
void tyran_lexer_set_begin(tyran_lexer_position_info* lexer_position_info, const tyran_lexer* lexer);
static char tyran_lexer_next_character_skip_whitespace(tyran_lexer* lexer);
void tyran_lexer_set_end(tyran_lexer_position_info* lexer_position_info, const tyran_lexer* lexer);
int tyran_lexer_is_digit(int c);
int tyran_lexer_parse_number(tyran_lexer* lexer, char c, tyran_string* number_string, tyran_string_length_type* string_length, tyran_lexer_position_info* lexer_position_info, tyran_lexer_token_data* token);
int tyran_lexer_parse_whole_string(tyran_lexer* lexer, char c, tyran_lexer_position_info* lexer_position_info, tyran_lexer_token_data* token);
int tyran_lexer_parse_comment(tyran_lexer* lexer);
static void tyran_lexer_push_character(char c, tyran_lexer* lexer);

#endif
