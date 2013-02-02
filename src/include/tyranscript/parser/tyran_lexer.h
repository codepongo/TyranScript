#ifndef _TYRAN_LEXER_H
#define _TYRAN_LEXER_H

#include <tyranscript/tyran_string.h>

struct tyran_errors;

typedef struct tyran_lexer {
	char* buffer;
	int size;
	int index;
	int line;
	int column;
	int indentation;
	int tab_count;
	int last_token;

	int target_indentation;
	int current_indentation;

	char* string_buffer;
	int string_buffer_max_size;
	tyran_number number;

	tyran_memory* memory;
	struct tyran_errors* errors;
	tyran_boolean last_was_whitespace;
	int next_is_member;

} tyran_lexer;

typedef struct tyran_lexer_position_info {
	int first_line;
	int last_line;
	int first_column;
	int last_column;
} tyran_lexer_position_info;

typedef void* tyran_lexer_token_data;

tyran_lexer* tyran_lexer_new(tyran_memory_pool* lexer_pool, tyran_memory* memory, const char* buf);
int tyran_lexer_is_alpha(int c);
int tyran_lexer_parse_identifier(tyran_lexer* lexer, char c, char* buf, int* max_length, tyran_boolean* last_was_whitespace);
void tyran_lexer_set_begin(tyran_lexer_position_info* lexer_position_info, const tyran_lexer* lexer);
char tyran_lexer_next_character_skip_whitespace(tyran_lexer* lexer);
char tyran_lexer_next_character_skip_whitespace_except_newline(tyran_lexer* lexer, tyran_boolean* last_was_whitespace);
void tyran_lexer_set_end(tyran_lexer_position_info* lexer_position_info, const tyran_lexer* lexer);
int tyran_lexer_is_digit(int c);
int tyran_lexer_parse_number(tyran_lexer* lexer, char c, tyran_lexer_position_info* lexer_position_info, tyran_number* token);
int tyran_lexer_parse_whole_string(tyran_lexer* lexer, char c, tyran_lexer_position_info* lexer_position_info, char* token, int length);
int tyran_lexer_parse_to_eol(tyran_lexer* lexer);
void tyran_lexer_push_character(char c, tyran_lexer* lexer);
char tyran_lexer_pop_character(tyran_lexer* lexer);
int tyran_lexer_parse_string(tyran_lexer* lexer, char* buf, int* length);
int tyran_lexer_parse_to_eol(tyran_lexer* lexer);

#endif


