#include <tyranscript/parser/tyran_lexer.h>
#include <tyranscript/tyran_string.h>
#include <tyranscript/parser/tyran_parser.h>
#include <tyranscript/parser/tyran_parser_state.h>

#include <tyranscript/tyran_config.h>

const int TYRAN_TOKEN_COMMENT = -1;

void yyerror(YYLTYPE* lexer_position_info, tyran_parser_state* ps, const char *msg)
{
	TYRAN_SOFT_ERROR("%d[%d-%d]:%s", lexer_position_info->first_line, lexer_position_info->first_column, lexer_position_info->last_column, msg);
	ps->error_count++;
}

static int tyran_lexer_pop_character(tyran_lexer* lexer)
{
	int c = 0;

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

static void tyran_lexer_push_character(int c, tyran_lexer* lexer)
{
	TYRAN_ASSERT(c != 0, "Must be a real character");
	lexer->index--;
	lexer->buffer[lexer->index] = c;
}

static int tyran_lexer_get_keyword_token(const char* temp_string_buffer)
{
	struct tyran_lexer_keyword {
		const char* name;
		int token_value;
	};

	static struct tyran_lexer_keyword keywords[] = {
		{ "var", TYRAN_TOKEN_LOCAL },
		{ "new", TYRAN_TOKEN_NEW },
		{ "delete", TYRAN_TOKEN_DELETE },
		{ "undefined", TYRAN_TOKEN_UNDEFINED },
		{ "true", TYRAN_TOKEN_TRUE },
		{ "false", TYRAN_TOKEN_FALSE },
		{ "this", TYRAN_TOKEN_THIS },
		{ "arguments", TYRAN_TOKEN_ARGUMENTS },
		{ "if", TYRAN_TOKEN_IF },
		{ "else", TYRAN_TOKEN_ELSE },
		{ "for", TYRAN_TOKEN_FOR },
		{ "in", TYRAN_TOKEN_IN },
		{ "while", TYRAN_TOKEN_WHILE },
		{ "do", TYRAN_TOKEN_DO },
		{ "continue", TYRAN_TOKEN_CONTINUE },
		{ "switch", TYRAN_TOKEN_SWITCH },
		{ "case", TYRAN_TOKEN_CASE },
		{ "break", TYRAN_TOKEN_BREAK },
		{ "default", TYRAN_TOKEN_DEFAULT },
		{ "function", TYRAN_TOKEN_FUNCTION },
		{ "return", TYRAN_TOKEN_RETURN }
	};

	size_t i;

	for (i = 0; i < sizeof(keywords) / sizeof(struct tyran_lexer_keyword); ++i) {
		if (tyran_strcmp(temp_string_buffer, keywords[i].name) == 0)
			return keywords[i].token_value;
	}
	return 0;
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
	int c = tyran_lexer_pop_character(lexer);
	int endchar = c;

	#define max_string_length 4096
	TYRAN_UNICODE_STRING(max_string_length) string_buffer;

	int index = 0;
	tyran_string* buf = string_buffer.string;

	while (index < max_string_length) {
		c = tyran_lexer_pop_character(lexer);
		if (c == 0) {
			TYRAN_SOFT_ERROR("Unexpected End of File");
			return 0;
		}
		if (c == '\\') {
			int n = tyran_lexer_pop_character(lexer);
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
	buf[index] = 0;
	string_buffer.len = index;
	return tyran_string_strdup(buf);
}

int tyran_lexer_parse_operand(tyran_lexer* lexer)
{
	struct tyran_operand_info {
		const char* name;
		int len;
		int value;
	};
	
	static tyran_operand_info operands[] = {
		{ ">>>=", 4, TYRAN_TOKEN_UNSIGNED_SHIFT_RIGHT_ASSIGNMENT },
		{ "<<=", 3, TYRAN_TOKEN_SHIFT_LEFT_ASSIGNMENT },
		{ ">>=", 3, TYRAN_TOKEN_SHIFT_RIGHT_ASSIGNMENT },
		{ "===", 3, TYRAN_TOKEN_EQUAL },
		{ "!==", 3, TYRAN_TOKEN_NOT_EQUAL },
		{ ">>>", 3, TYRAN_TOKEN_SHIFT_RIGHT_UNSIGNED },
		{ "==", 2, TYRAN_TOKEN_EQUAL },
		{ "!=", 2, TYRAN_TOKEN_NOT_EQUAL },
		{ "<=", 2, TYRAN_TOKEN_LESS_EQUAL },
		{ ">=", 2, TYRAN_TOKEN_GREATER_EQUAL },
		{ "++", 2, TYRAN_TOKEN_INCREASE },
		{ "--", 2, TYRAN_TOKEN_DECREASE },
		{ "&&", 2, TYRAN_TOKEN_AND },
		{ "||", 2, TYRAN_TOKEN_OR },
		{ "+=", 2, TYRAN_TOKEN_ADD_ASSIGNMENT },
		{ "-=", 2, TYRAN_TOKEN_SUBTRACT_ASSIGNMENT },
		{ "*=", 2, TYRAN_TOKEN_MULTIPLY_ASSIGNMENT },
		{ "/=", 2, TYRAN_TOKEN_DIVIDE_ASSIGNMENT },
		{ "%=", 2, TYRAN_TOKEN_MODULUS_ASSIGNMENT },
		{ "&=", 2, TYRAN_TOKEN_BITWISE_AND_ASSIGNMENT },
		{ "|=", 2, TYRAN_TOKEN_BITWISE_OR_ASSIGNMENT },
		{ "^=", 2, TYRAN_TOKEN_BITWISE_XOR_ASSIGNMENT },
		{ "<<", 2, TYRAN_TOKEN_SHIFT_LEFT },
		{ ">>", 2, TYRAN_TOKEN_SHIFT_RIGHT },
		{ "=", 1, TYRAN_TOKEN_ASSIGNMENT },
		{ "<", 1, TYRAN_TOKEN_LESS },
		{ ">", 1, TYRAN_TOKEN_GREATER },
		{ "&", 1, TYRAN_TOKEN_BITWISE_AND },
		{ "|", 1, TYRAN_TOKEN_BITWISE_OR },
		{ "^", 1, TYRAN_TOKEN_BITWISE_XOR },
		{ "/", 1, TYRAN_TOKEN_DIVIDE },
		{ "*", 1, TYRAN_TOKEN_MULTIPLY },
		{ "%", 1, TYRAN_TOKEN_MODULUS },
		{ "+", 1, TYRAN_TOKEN_ADD },
		{ "-", 1, TYRAN_TOKEN_SUBTRACT },
		{ "~", 1, TYRAN_TOKEN_BITWISE_NOT },
		{ "!", 1, TYRAN_TOKEN_NOT },
		{ ".", 1, TYRAN_TOKEN_MEMBER },
		{ "(", 1, TYRAN_TOKEN_PARENTHESES_LEFT },
		{ ")", 1, TYRAN_TOKEN_PARENTHESES_RIGHT },
		{ "[", 1, TYRAN_TOKEN_BRACKET_LEFT },
		{ "]", 1, TYRAN_TOKEN_BRACKET_RIGHT },
		{ ";", 1, TYRAN_TOKEN_EOL },
		{ "{", 1, TYRAN_TOKEN_BLOCK_START },
		{ "}", 1, TYRAN_TOKEN_BLOCK_END },
		{ ":", 1, TYRAN_TOKEN_COLON },
		{ ",", 1, TYRAN_TOKEN_COMMA },
		{ "?", 1, TYRAN_TOKEN_QUESTION_MARK },
	};

	int index;
	char buf[4];
	size_t i;
	for (index = 0; index < 4; ++index) {
		int c = tyran_lexer_pop_character(lexer);
		if (c == 0 || c == '\n') {
			break;
		}
		buf[index] = c;
	}
	if (!index) {
		return 0;
	}

	for (i = 0; i < sizeof(operands)/sizeof(struct tyran_operand_info); ++i) {
		if (index < operands[i].len) {
			continue;
		}
		
		if (tyran_strncmp(buf, operands[i].name, operands[i].len) == 0) {
			int j;
			for (j = index - 1; j >= operands[i].len; --j) {
				tyran_lexer_push_character(buf[j], lexer);
			}

			return operands[i].value;
		}
	}

	for (i = index - 1; i >= 1; --i) {
		tyran_lexer_push_character(buf[i], lexer);
	}

	return 0;
}

static void tyran_lexer_skip_comment(tyran_lexer *lexer)
{
	int c;
	while((c = tyran_lexer_pop_character(lexer))) {
		if (c == '*') {
			c = tyran_lexer_pop_character(lexer);
			if (c == '/') {
				return;
			}
			tyran_lexer_push_character(c, lexer);
		}
	}
	TYRAN_SOFT_ERROR("Unexpected end of file");
}


static int tyran_lexer_next_character_skip_whitespace(tyran_lexer* lexer)
{
	int c;
	
	while ((c = tyran_lexer_pop_character(lexer)) == ' ' || c == '\t' || c == '\n' || c == '\r')
		;

	return c;
}

void tyran_lexer_set_begin(YYLTYPE* lexer_position_info, const tyran_lexer* lexer)	
{
	lexer_position_info->first_line = lexer->line;
	lexer_position_info->first_column = lexer->column;
}

void tyran_lexer_set_end(YYLTYPE* lexer_position_info, const tyran_lexer* lexer)
{
	lexer_position_info->last_line = lexer->line;
	lexer_position_info->last_column = lexer->column;
}

int tyran_lexer_parse_identifier(tyran_lexer* lexer, int c, tyran_string* temp_string_buffer)
{
	int string_index = 0;
	tyran_lexer_push_character(c, lexer);
	while (string_index < 1020) {
		c = tyran_lexer_pop_character(lexer);
		if (!tyran_lexer_is_alpha_numeric(c) && c != '_' && c != '$') {
			break;
		}
		temp_string_buffer[string_index++] = c;
	}
	tyran_lexer_push_character(c, lexer);
	temp_string_buffer[string_index] = 0;
	
	return string_index;
}

int tyran_lexer_parse_identifier_or_keyword(tyran_lexer* lexer, int c, tyran_string* temp_string_buffer, tyran_string_length_type* string_length, YYLTYPE* lexer_position_info, YYSTYPE* token)
{
	int identifier_length = tyran_lexer_parse_identifier(lexer, c, temp_string_buffer);
	*string_length = identifier_length;
	int r = tyran_lexer_get_keyword_token(tyran_string_to_c_str(temp_string_buffer));
	if (r) {
		return r;
	}
	*token = (void*) tyran_string_strdup(temp_string_buffer);
	tyran_lexer_set_end(lexer_position_info, lexer);
	return TYRAN_TOKEN_IDENTIFIER;
}

int tyran_lexer_parse_number(tyran_lexer* lexer, int c, tyran_string* number_string, tyran_string_length_type* string_length, YYLTYPE* lexer_position_info, YYSTYPE* token)
{
	int decimal_point_detected = 0;
	int hex_number_detected = 0;
	int string_index = 0;

	number_string[string_index++] = c;

	while (string_index < 128) {
		c = tyran_lexer_pop_character(lexer);
		if (tyran_lexer_is_digit(c)) {
			number_string[string_index++] = c;
		} else if (c == '.') {
			if (decimal_point_detected || hex_number_detected) {
				TYRAN_SOFT_ERROR("Number format error");
				return 0;
			}
			decimal_point_detected = 1;
			number_string[string_index++] = c;
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

	number_string[string_index] = 0;
	*string_length = string_index;

	double* number_pointer = TYRAN_MALLOC_TYPE(double, 1);
	if (hex_number_detected) {
		int temp_value;
		tyran_sscanf(tyran_string_to_c_str(number_string), "%X", &temp_value);
		*number_pointer = temp_value;

	} else {
		tyran_sscanf(tyran_string_to_c_str(number_string), "%lf", number_pointer);
	}

	*token = number_pointer;
	return TYRAN_TOKEN_NUMBER;
}

int tyran_lexer_parse_comment(tyran_lexer* lexer)
{
	int d = tyran_lexer_pop_character(lexer);
	if (d == '/') {
		while ((d = tyran_lexer_pop_character(lexer)) != '\r' && d != '\n' && d != 0)
			;
		return TYRAN_TOKEN_COMMENT;
	} else if (d == '*') {
		tyran_lexer_skip_comment(lexer);
		return TYRAN_TOKEN_COMMENT;
	}

	tyran_lexer_push_character(d, lexer);
	return 0;
}

int tyran_lexer_parse_whole_string(tyran_lexer* lexer, int c, YYLTYPE* lexer_position_info, YYSTYPE* token)
{
	tyran_lexer_push_character(c, lexer);
	*token = (void *) tyran_lexer_parse_string(lexer);
	tyran_lexer_set_end(lexer_position_info, lexer);
	return TYRAN_TOKEN_STRING;
}

static int tyran_lexer_next_token(YYSTYPE* token, YYLTYPE* lexer_position_info, tyran_lexer* lexer)
{
	TYRAN_UNICODE_STRING(1024) string_buffer;
	tyran_string* temp_string_buffer = string_buffer.string;

	tyran_lexer_set_begin(lexer_position_info, lexer);

	int c = tyran_lexer_next_character_skip_whitespace(lexer);
	if (!c) {
		return 0;
	}

	if (tyran_lexer_is_alpha(c) || c == '_' || c == '$') {
		return tyran_lexer_parse_identifier_or_keyword(lexer, c, temp_string_buffer, &string_buffer.len, lexer_position_info, token);
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
