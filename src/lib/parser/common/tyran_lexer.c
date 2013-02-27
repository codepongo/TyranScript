#include <tyranscript/parser/tyran_lexer.h>
#include <tyranscript/tyran_string.h>
#include <tyranscript/parser/common/tyran_parser_tree.h>
#include <tyranscript/parser/tyran_parser_state.h>
#include <tyranscript/parser/common/tyran_errors.h>

#include <tyranscript/tyran_config.h>
#include <tyranscript/tyran_number.h>

#include <tyranscript/tyran_string.h>


const int TYRAN_TOKEN_COMMENT = -1;

tyran_lexer* tyran_lexer_new(tyran_memory_pool* lexer_pool, tyran_memory* memory, const char* buf)
{
	int length = tyran_strlen(buf);
	tyran_lexer* lexer = TYRAN_CALLOC_TYPE(lexer_pool, tyran_lexer);
	lexer->size = length + 1;
	lexer->buffer = TYRAN_MALLOC_NO_POOL_TYPE_COUNT(memory, char, lexer->size);
	lexer->string_buffer_max_size = 4096;
	lexer->string_buffer = TYRAN_MALLOC_NO_POOL_TYPE_COUNT(memory, char, lexer->string_buffer_max_size);
	lexer->errors = tyran_errors_new(memory);
	lexer->memory = memory;
	lexer->target_indentation = 0;
	lexer->current_indentation = 0;
	lexer->last_was_whitespace = TYRAN_TRUE;

	tyran_memcpy_type(char, lexer->buffer, buf, lexer->size);
	return lexer;
}

char tyran_lexer_pop_character(tyran_lexer* lexer)
{
	char c = 0;
	TYRAN_ASSERT(lexer->index < lexer->size, "you popped too far");

	c = lexer->buffer[lexer->index];
	lexer->index++;

	if (c == '\n') {
		lexer->line++;
		lexer->column = 0;
		lexer->tab_count = 0;
		lexer->indentation = 0;
	} else if (c == '\t') {
		lexer->tab_count++;
		lexer->column += 4;
	} else {
		lexer->indentation = lexer->tab_count;
	}
	lexer->column++;

	return c;
}

void tyran_lexer_push_character(char c, tyran_lexer* lexer)
{
	if (c == '\n') {
		lexer->line--;
		lexer->column = -1;
		lexer->tab_count = 0;
		lexer->indentation = 0;
	} else if (c == '\t') {
		lexer->tab_count--;
		lexer->column -= 3;
	}
	lexer->column++;
	// TYRAN_ASSERT(c != 0, "Must be a real character");
	TYRAN_ASSERT(lexer->index > 0, "You pushed too much");
	lexer->index--;
	lexer->buffer[lexer->index] = c;
}

int tyran_lexer_is_digit(int c)
{
	return (c >= '0' && c <='9');
}

int tyran_lexer_is_alpha(int c)
{
	return ((c >= 'a' && c <='z') || (c >= 'A' && c <= 'Z'));
}

int tyran_lexer_is_alpha_numeric(int c)
{
	return tyran_lexer_is_alpha(c) || tyran_lexer_is_digit(c);
}

tyran_boolean tyran_lexer_is_whitespace(int c)
{
	return c == ' ' || c == '\t' || c == '\n' || c == '\r';
}

int tyran_lexer_parse_string(tyran_lexer* lexer, char* buf, int* length)
{
	char c = tyran_lexer_pop_character(lexer);
	char endchar = c;

	int index = 0;

	while (index < *length) {
		c = tyran_lexer_pop_character(lexer);
		if (c == 0) {
			return tyran_errors_add(lexer->errors, TYRAN_ERROR_NO_END_STRING, lexer);
		}
		if (c == '\\') {
			char n = tyran_lexer_pop_character(lexer);
			switch(n) {
				case 'b':
					buf[index++] = '\b';
					break;
				case 'f':
					buf[index++] = '\f';
					break;
				case 'n':
					buf[index++] = '\n';
					break;
				case 'r':
					buf[index++] = '\r';
					break;
				case 't':
					buf[index++] = '\t';
					break;
				case 0:
					TYRAN_SOFT_ERROR("Unexpected EOF parsing string.");
				default:
					buf[index++] = n;
			}
		} else {
			if (c == '\n') {
				c = tyran_lexer_next_character_skip_whitespace(lexer);
			}
			buf[index++] = c;
		}
		if (c == endchar) {
			index --;
			break;
		}
	}

	buf[index] = 0;
	*length = index;
	return 1;
}

char tyran_lexer_next_character_skip_whitespace(tyran_lexer* lexer)
{
	char c;

	while ((c = tyran_lexer_pop_character(lexer)) == ' ' || c == '\t' || c == '\n' || c == '\r')
		;

	return c;
}

char tyran_lexer_next_character_skip_whitespace_except_newline(tyran_lexer* lexer, tyran_boolean* first_was_whitespace)
{
	char c;

	*first_was_whitespace = TYRAN_FALSE;

	while ((c = tyran_lexer_pop_character(lexer)) == ' ' || c == '\t' || c == '\r') {
		*first_was_whitespace = TYRAN_TRUE;
	}

	if ( c == '\n') {
		*first_was_whitespace = TYRAN_TRUE;
	}
	return c;
}


void tyran_lexer_set_begin(tyran_lexer_position_info* lexer_position_info, const tyran_lexer* lexer)
{
	lexer_position_info->first_line = lexer->line;
	lexer_position_info->first_column = lexer->column;
}

void tyran_lexer_set_end(tyran_lexer_position_info* lexer_position_info, const tyran_lexer* lexer)
{
	lexer_position_info->last_line = lexer->line;
	lexer_position_info->last_column = lexer->column;
}

int tyran_lexer_parse_identifier(tyran_lexer* lexer, char c, char* buf, int* max_length, tyran_boolean* last_was_whitespace)
{
	int string_index = 0;

	tyran_lexer_push_character(c, lexer);
	while (string_index < 1020) {
		c = tyran_lexer_pop_character(lexer);
		if (!tyran_lexer_is_alpha_numeric(c) && c != '_' && c != '$') {
			tyran_lexer_push_character(c, lexer);
			break;
		}
		buf[string_index++] = c;
	}

	buf[string_index] = 0;
	*last_was_whitespace = tyran_lexer_is_whitespace(c) || c == ',' || c == ']';
	*max_length = string_index;

	return 0;
}

int tyran_lexer_parse_number(tyran_lexer* lexer, char c, tyran_lexer_position_info* lexer_position_info, tyran_number* number_pointer)
{
	int decimal_point_detected = 0;
	int hex_number_detected = 0;
	int string_index = 0;

	char buf[1024];

	buf[string_index++] = (int) c;

	while (string_index < 128) {
		c = tyran_lexer_pop_character(lexer);
		if (tyran_lexer_is_digit(c)) {
			buf[string_index++] = (int) c;
		} else if (c == '.') {
			int next = tyran_lexer_pop_character(lexer);
			if (next == '.') {
				tyran_lexer_push_character(next, lexer);
				tyran_lexer_push_character(next, lexer);
				break;
			}
			if (decimal_point_detected || hex_number_detected) {
				TYRAN_SOFT_ERROR("Number format error");
				return 0;
			}
			decimal_point_detected = 1;
			buf[string_index++] = (int) c;
			buf[string_index++] = next;
		} else if ((c == 'x' || c == 'X') && string_index == 1 && string_index) {
			if (decimal_point_detected || hex_number_detected) {
				TYRAN_SOFT_ERROR("Number format error");
				return 0;
			}
			hex_number_detected = 1;
		} else {
			tyran_lexer_push_character(c, lexer);
			break;
		}
	}
	tyran_lexer_set_end(lexer_position_info, lexer);

	buf[string_index] = 0;

	if (hex_number_detected) {
		unsigned int temp_value;
		tyran_sscanf(buf, "%X", &temp_value);
		*number_pointer = temp_value;

	} else {
		tyran_sscanf(buf, "%f", number_pointer);
	}

	return 1;
}

int tyran_lexer_parse_to_eol(tyran_lexer* lexer)
{
	char d = tyran_lexer_pop_character(lexer);
	while ((d = tyran_lexer_pop_character(lexer)) != '\n' && d != '\n' && d != 0)
		;
	return TYRAN_TOKEN_COMMENT;

	return 0;
}

int tyran_lexer_parse_whole_string(tyran_lexer* lexer, char c, tyran_lexer_position_info* lexer_position_info, char* buf, int length)
{
	tyran_lexer_push_character(c, lexer);
	int error = tyran_lexer_parse_string(lexer, buf, &length);
	if (error) {
		return error;
	}
	tyran_lexer_set_end(lexer_position_info, lexer);
	return 0;
}
