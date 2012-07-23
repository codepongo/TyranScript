#include <tyranscript/parser/tyran_lexer.h>
#include <tyranscript/tyran_string.h>
#include <tyranscript/parser/mocha/tyran_parser.h>
#include <tyranscript/parser/tyran_parser_state.h>

#include <tyranscript/tyran_config.h>
#include <tyranscript/tyran_number.h>

#include <tyranscript/tyran_string.h>


const int TYRAN_TOKEN_COMMENT = -1;

void yyerror(tyran_lexer_position_info* lexer_position_info, tyran_parser_state* ps, const char *msg)
{
	TYRAN_SOFT_ERROR("%d[%d-%d]:%s", lexer_position_info->first_line, lexer_position_info->first_column, lexer_position_info->last_column, msg);
	ps->error_count++;
}

tyran_lexer* tyran_lexer_new(const char* buf)
{
	int length = tyran_strlen(buf);
	tyran_lexer* lexer = TYRAN_MALLOC_TYPE(tyran_lexer, 1);
	lexer->buffer = TYRAN_MALLOC_TYPE(char, length + 1);
	tyran_memcpy(lexer->buffer, buf, length);
	lexer->buffer[length] = 0;
	return lexer;
}

static char tyran_lexer_pop_character(tyran_lexer* lexer)
{
	char c = 0;

	c = lexer->buffer[lexer->index];
	if (c != 0) {
		lexer->index++;
	}

	if (c == '\n') {
		lexer->line++;
		lexer->column = 0;
	}
	lexer->column++;

	return c;
}

void tyran_lexer_push_character(char c, tyran_lexer* lexer)
{
	// TYRAN_ASSERT(c != 0, "Must be a real character");
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

const tyran_string* tyran_lexer_parse_string(tyran_lexer* lexer)
{
	char c = tyran_lexer_pop_character(lexer);
	char endchar = c;

	#define max_string_length 4096
	tyran_string_char buf[max_string_length];

	int index = 0;

	while (index < max_string_length) {
		c = tyran_lexer_pop_character(lexer);
		if (c == 0) {
			TYRAN_SOFT_ERROR("Unexpected End of File");
			return 0;
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
			buf[index++] = c;
		}
		if (c == endchar) {
			index --;
			break;
		}
	}

	return tyran_string_from_characters(buf, index);;
}

static void tyran_lexer_skip_comment(tyran_lexer *lexer)
{
	char c;
	do {
		c = tyran_lexer_pop_character(lexer);
		if (c == '*') {
			c = tyran_lexer_pop_character(lexer);
			if (c == '/') {
				return;
			}
			tyran_lexer_push_character(c, lexer);
		}
	} while (c);
	TYRAN_SOFT_ERROR("Unexpected end of file");
}


char tyran_lexer_next_character_skip_whitespace(tyran_lexer* lexer)
{
	char c;
	
	while ((c = tyran_lexer_pop_character(lexer)) == ' ' || c == '\t' || c == '\n' || c == '\r')
		;

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

int tyran_lexer_parse_identifier(tyran_lexer* lexer, char c, char* buf, int* max_length)
{
	int string_index = 0;

	tyran_lexer_push_character(c, lexer);
	while (string_index < 1020) {
		c = tyran_lexer_pop_character(lexer);
		if (!tyran_lexer_is_alpha_numeric(c) && c != '_' && c != '$') {
			break;
		}
		buf[string_index++] = c;
	}
	tyran_lexer_push_character(c, lexer);

	buf[string_index] = 0;
	*max_length = string_index;
	
	return 0;
}

int tyran_lexer_parse_number(tyran_lexer* lexer, char c, tyran_lexer_position_info* lexer_position_info, tyran_lexer_token_data* token)
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
			if (decimal_point_detected || hex_number_detected) {
				TYRAN_SOFT_ERROR("Number format error");
				return 0;
			}
			decimal_point_detected = 1;
			buf[string_index++] = (int) c;
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

	tyran_number* number_pointer = TYRAN_MALLOC_TYPE(tyran_number, 1);
	if (hex_number_detected) {
		unsigned int temp_value;
		tyran_sscanf(buf, "%X", &temp_value);
		*number_pointer = temp_value;

	} else {
		tyran_sscanf(buf, "%f", number_pointer);
	}

	*token = number_pointer;
	return 1;
}

int tyran_lexer_parse_comment(tyran_lexer* lexer)
{
	char d = tyran_lexer_pop_character(lexer);
	if (d == '/') {
		while ((d = tyran_lexer_pop_character(lexer)) != '\n' && d != '\n' && d != 0)
			;
		return TYRAN_TOKEN_COMMENT;
	} else if (d == '*') {
		tyran_lexer_skip_comment(lexer);
		return TYRAN_TOKEN_COMMENT;
	}

	tyran_lexer_push_character(d, lexer);
	return 0;
}

int tyran_lexer_parse_whole_string(tyran_lexer* lexer, char c, tyran_lexer_position_info* lexer_position_info, tyran_lexer_token_data* token)
{
	tyran_lexer_push_character(c, lexer);
	*token = (void *) tyran_lexer_parse_string(lexer);

	tyran_lexer_set_end(lexer_position_info, lexer);
	return 1;
}
