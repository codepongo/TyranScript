#ifndef _TYRAN_LEXER_H
#define _TYRAN_LEXER_H

#include <tyranscript/tyran_string.h>

typedef struct tyran_lexer {
	char* buffer;
	int index;
	int line;
	int column;
	int indentation;
	int tab_count;
	int last_token;
} tyran_lexer;

typedef struct tyran_lexer_position_info {
	int first_line;
	int last_line;
	int first_column;
	int last_column;
} tyran_lexer_position_info;

typedef void* tyran_lexer_token_data;

tyran_lexer* tyran_lexer_new(const char* buf);
int tyran_lexer_is_alpha(int c);
int tyran_lexer_parse_identifier(tyran_lexer* lexer, char c, char* buf, int* max_length);
void tyran_lexer_set_begin(tyran_lexer_position_info* lexer_position_info, const tyran_lexer* lexer);
char tyran_lexer_next_character_skip_whitespace(tyran_lexer* lexer);
char tyran_lexer_next_character_skip_whitespace_except_newline(tyran_lexer* lexer);
void tyran_lexer_set_end(tyran_lexer_position_info* lexer_position_info, const tyran_lexer* lexer);
int tyran_lexer_is_digit(int c);
int tyran_lexer_parse_number(tyran_lexer* lexer, char c, tyran_lexer_position_info* lexer_position_info, tyran_lexer_token_data* token);
int tyran_lexer_parse_whole_string(tyran_lexer* lexer, char c, tyran_lexer_position_info* lexer_position_info, tyran_lexer_token_data* token);
int tyran_lexer_parse_to_eol(tyran_lexer* lexer);
void tyran_lexer_push_character(char c, tyran_lexer* lexer);
char tyran_lexer_pop_character(tyran_lexer* lexer);
int tyran_lexer_parse_string(tyran_lexer* lexer, char* buf, int* length);
int tyran_lexer_parse_to_eol(tyran_lexer* lexer);

#endif


