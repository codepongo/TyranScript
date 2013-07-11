#include <tyranscript/parser/mocha/tyran_mocha_lexer.h>
#include <tyranscript/parser/tyran_lexer.h>

tyran_mocha_lexer* tyran_mocha_lexer_new(tyran_memory_pool* mocha_lexer_pool, tyran_memory* memory, tyran_memory_pool* mocha_token_pool, const tyran_mocha_token* tokens, int token_count)
{
	tyran_mocha_lexer* lexer = TYRAN_MALLOC_TYPE(mocha_lexer_pool, tyran_mocha_lexer);

	lexer->tokens = TYRAN_MALLOC_NO_POOL_TYPE_COUNT(memory, tyran_mocha_token, token_count);
	tyran_memcpy_type(tyran_mocha_token, lexer->tokens, tokens, token_count);
	lexer->token_count = token_count;
	return lexer;
}

void tyran_mocha_lexer_destroy(tyran_mocha_lexer* lexer)
{
	TYRAN_MALLOC_FREE(lexer->tokens);
	TYRAN_MALLOC_FREE(lexer);
}

tyran_mocha_token_id tyran_mocha_lexer_operand(tyran_lexer* lexer, int c)
{
	tyran_lexer_push_character(c, lexer);

	typedef struct tyran_operand_info {
		const char* name;
		int len;
		tyran_mocha_token_id value;
	} tyran_operand_info;

	static tyran_operand_info operands[] = {
		{ "++", 2, TYRAN_MOCHA_TOKEN_INCREMENT },
		{ "--", 2, TYRAN_MOCHA_TOKEN_DECREMENT },
		{ "+=", 2, TYRAN_MOCHA_TOKEN_ASSIGNMENT_ADD },
		{ "-=", 2, TYRAN_MOCHA_TOKEN_ASSIGNMENT_SUBTRACT },
		{ "*=", 2, TYRAN_MOCHA_TOKEN_ASSIGNMENT_MULTIPLY },
		{ "/=", 2, TYRAN_MOCHA_TOKEN_ASSIGNMENT_DIVIDE },
		{ "%=", 2, TYRAN_MOCHA_TOKEN_ASSIGNMENT_MODULUS },
		{ "->", 2, TYRAN_MOCHA_TOKEN_FUNCTION_GLYPH },
		{ "=>", 2, TYRAN_MOCHA_TOKEN_FUNCTION_GLYPH_BOUND },
		{ "<=", 2, TYRAN_MOCHA_TOKEN_LESS_EQUAL },
		{ ">=", 2, TYRAN_MOCHA_TOKEN_GREATER_EQUAL },
		{ "<", 1, TYRAN_MOCHA_TOKEN_LESS },
		{ ">", 1, TYRAN_MOCHA_TOKEN_GREATER },
		{ "&", 1, TYRAN_MOCHA_TOKEN_END },
		{ "|", 1, TYRAN_MOCHA_TOKEN_END },
		{ "^", 1, TYRAN_MOCHA_TOKEN_END },
		{ "/", 1, TYRAN_MOCHA_TOKEN_DIVIDE },
		{ "*", 1, TYRAN_MOCHA_TOKEN_MULTIPLY },
		{ "%", 1, TYRAN_MOCHA_TOKEN_MODULUS },
		{ "=", 1, TYRAN_MOCHA_TOKEN_ASSIGNMENT },
		{ "+", 1, TYRAN_MOCHA_TOKEN_ADD },
		{ "-", 1, TYRAN_MOCHA_TOKEN_SUBTRACT },
		{ "~", 1, TYRAN_MOCHA_TOKEN_END },
		{ "...", 3, TYRAN_MOCHA_TOKEN_RANGE_EXCLUSIVE },
		{ "..", 2, TYRAN_MOCHA_TOKEN_RANGE_INCLUSIVE },
		{ ".", 1, TYRAN_MOCHA_TOKEN_MEMBER },
		{ "(", 1, TYRAN_MOCHA_TOKEN_PARENTHESES_LEFT },
		{ ")", 1, TYRAN_MOCHA_TOKEN_PARENTHESES_RIGHT },
		{ "[", 1, TYRAN_MOCHA_TOKEN_BRACKET_LEFT },
		{ "]", 1, TYRAN_MOCHA_TOKEN_BRACKET_RIGHT },
		{ "{", 1, TYRAN_MOCHA_TOKEN_OBJECT_START },
		{ "}", 1, TYRAN_MOCHA_TOKEN_OBJECT_END },
		{ ":", 1, TYRAN_MOCHA_TOKEN_COLON },
		{ ",", 1, TYRAN_MOCHA_TOKEN_COMMA },
		{ "?", 1, TYRAN_MOCHA_TOKEN_END },
	};
	int index;
	char buf[5];
	size_t operand_index;
	char popped_character = 1;
	for (index = 0; index < 4 && (popped_character != 0); ++index) {
		popped_character = tyran_lexer_pop_character(lexer);
		buf[index] = popped_character;
	}

	for (operand_index = 0; operand_index < sizeof(operands)/sizeof(tyran_operand_info); ++operand_index) {
		if (index < operands[operand_index].len) {
			continue;
		}

		if (tyran_strncmp(buf, operands[operand_index].name, operands[operand_index].len) == 0) {
			int j;
			for (j = index - 1; j >= operands[operand_index].len; --j) {
				tyran_lexer_push_character(buf[j], lexer);
			}
			return operands[operand_index].value;
		}
	}

	int i;
	for (i = index - 1; i >= 0; --i) {
		tyran_lexer_push_character(buf[i], lexer);
	}
	return TYRAN_MOCHA_TOKEN_END;
}


tyran_mocha_token_id tyran_mocha_lexer_keyword(const char* identifier)
{
	typedef struct tyran_mocha_keyword_info {
		const char* name;
		tyran_mocha_token_id value;
	} tyran_mocha_keyword_info;

	static tyran_mocha_keyword_info keywords[] = {
		{ "if", TYRAN_MOCHA_TOKEN_IF },
		{ "unless", TYRAN_MOCHA_TOKEN_UNLESS },
		{ "then", TYRAN_MOCHA_TOKEN_THEN },
		{ "else", TYRAN_MOCHA_TOKEN_ELSE },
		{ "true", TYRAN_MOCHA_TOKEN_TRUE },
		{ "false", TYRAN_MOCHA_TOKEN_FALSE },
		{ "nil", TYRAN_MOCHA_TOKEN_NIL },
		{ "self", TYRAN_MOCHA_TOKEN_SELF },
		{ "class", TYRAN_MOCHA_TOKEN_CLASS },
		{ "extends", TYRAN_MOCHA_TOKEN_EXTENDS },
		{ "return", TYRAN_MOCHA_TOKEN_RETURN },
		{ "while", TYRAN_MOCHA_TOKEN_WHILE },
		{ "until", TYRAN_MOCHA_TOKEN_UNTIL },
		{ "case", TYRAN_MOCHA_TOKEN_CASE },
		{ "when", TYRAN_MOCHA_TOKEN_WHEN },
		{ "for", TYRAN_MOCHA_TOKEN_FOR },
		{ "break", TYRAN_MOCHA_TOKEN_BREAK },
		{ "continue", TYRAN_MOCHA_TOKEN_CONTINUE },
		{ "super", TYRAN_MOCHA_TOKEN_SUPER },
		{ "isnt", TYRAN_MOCHA_TOKEN_NOT_EQUAL },
		{ "is", TYRAN_MOCHA_TOKEN_EQUAL },
		{ "in", TYRAN_MOCHA_TOKEN_IN },
		{ "and", TYRAN_MOCHA_TOKEN_AND },
		{ "or", TYRAN_MOCHA_TOKEN_OR },
		{ "not", TYRAN_MOCHA_TOKEN_NOT },
	};

	size_t i;
	for (i = 0; i < sizeof(keywords) / sizeof(tyran_mocha_keyword_info); ++i) {
		if (tyran_strcmp(identifier, keywords[i].name) == 0) {
			return keywords[i].value;
		}
	}

	return TYRAN_MOCHA_TOKEN_END;
}


tyran_mocha_token tyran_mocha_lexer_next_token(tyran_lexer_position_info* lexer_position_info, tyran_lexer* lexer)
{
	tyran_mocha_token token;
	token.token_data = 0;

	if (lexer->next_is_member) {
		lexer->next_is_member = TYRAN_FALSE;
		token.token_id = TYRAN_MOCHA_TOKEN_MEMBER;
		token.token_data = 0;

		return token;
	}

	token.token_id = TYRAN_MOCHA_TOKEN_END;

	tyran_lexer_set_begin(lexer_position_info, lexer);

	if (lexer->current_indentation < lexer->target_indentation) {
		token.token_id = TYRAN_MOCHA_TOKEN_BLOCK_START;
		lexer->current_indentation++;
		return token;
	} else if (lexer->current_indentation > lexer->target_indentation) {
		token.token_id = TYRAN_MOCHA_TOKEN_BLOCK_END;
		lexer->current_indentation--;
		return token;
	}
	tyran_boolean last_was_whitespace;
	char c = tyran_lexer_next_character_skip_whitespace_except_newline(lexer, &last_was_whitespace);
	lexer->last_was_whitespace |= last_was_whitespace;

	if (c == '\n') {
		if (token.token_id != TYRAN_MOCHA_TOKEN_LINE_START && token.token_id != TYRAN_MOCHA_TOKEN_BLOCK_END) {
			c = tyran_lexer_next_character_skip_whitespace_except_newline(lexer, &last_was_whitespace);
			tyran_lexer_push_character(c, lexer);
			if (c != '\n') {
				lexer->target_indentation = lexer->indentation;
			}
			if (lexer->indentation != lexer->current_indentation) {
				return tyran_mocha_lexer_next_token(lexer_position_info, lexer);
			} else {
				token.token_id = TYRAN_MOCHA_TOKEN_LINE_START;
			}
		} else {
			return tyran_mocha_lexer_next_token(lexer_position_info, lexer);
		}
	} else if (!c) {
		if (lexer->current_indentation > 0) {
			tyran_lexer_push_character(c, lexer);
			lexer->target_indentation = 0;
			return tyran_mocha_lexer_next_token(lexer_position_info, lexer);
		} else {
			token.token_id = TYRAN_MOCHA_TOKEN_END;
		}
	} else if (c=='@') {
		token.token_id = TYRAN_MOCHA_TOKEN_SELF;
		token.token_data = 0;
		lexer->next_is_member = TYRAN_TRUE;
	} else if (tyran_lexer_is_alpha(c) || c == '_' || c == '$') {
		int len = 100;
		char identifier[100];
		tyran_boolean ended_with_whitespace;

		tyran_lexer_parse_identifier(lexer, c, identifier, &len, &ended_with_whitespace);
		tyran_mocha_token_id token_id = TYRAN_MOCHA_TOKEN_IDENTIFIER;

		if (lexer->last_was_whitespace && ended_with_whitespace) {
			tyran_mocha_token_id found_id = tyran_mocha_lexer_keyword(identifier);
			if (found_id != TYRAN_MOCHA_TOKEN_END) {
				token_id = found_id;
			}
		}

		token.token_id = token_id;

		if (token_id != TYRAN_MOCHA_TOKEN_IDENTIFIER) {
			token.token_data = 0;
		} else {
			token.token_data = tyran_strdup(lexer->memory, identifier);
		}
		lexer->last_was_whitespace = ended_with_whitespace;
	} else if (tyran_lexer_is_digit(c)) {
		int worked = tyran_lexer_parse_number(lexer, c, lexer_position_info, &lexer->number);
		if (!worked) {
			return tyran_mocha_lexer_next_token(lexer_position_info, lexer);
		}

		token.token_data = TYRAN_MALLOC_NO_POOL_TYPE(lexer->memory, tyran_number);
		tyran_memcpy_type(tyran_number, token.token_data, &lexer->number, 1);
		token.token_id = TYRAN_MOCHA_TOKEN_NUMBER;
	} else if (c == '"' || c == '\'') {
		tyran_lexer_parse_whole_string(lexer, c, lexer_position_info, lexer->string_buffer, lexer->string_buffer_max_size);
		token.token_data = tyran_strdup(lexer->memory, lexer->string_buffer);
		token.token_id = TYRAN_MOCHA_TOKEN_STRING;
	} else if (c == '#') {
		tyran_lexer_parse_to_eol(lexer);
		token = tyran_mocha_lexer_next_token(lexer_position_info, lexer);
	} else {
		tyran_mocha_token_id found = tyran_mocha_lexer_operand(lexer, c);
		if (found) {
			token.token_id = found;
		} else {
			token = tyran_mocha_lexer_next_token(lexer_position_info, lexer);
		}
	}

	tyran_lexer_set_end(lexer_position_info, lexer);

	return token;
}

tyran_mocha_lexer* tyran_mocha_lexer_lex(tyran_memory_pool* mocha_lexer_pool, tyran_memory_pool* mocha_token_pool, tyran_memory_pool* lexer_pool, tyran_memory* memory, const char* buf)
{
	tyran_lexer_position_info position_info;
	tyran_mocha_token* temp_buffer = TYRAN_MALLOC_NO_POOL_TYPE_COUNT(memory, tyran_mocha_token, 8192);
	int count = 0;

	tyran_lexer* lexer = tyran_lexer_new(lexer_pool, memory, buf);
	tyran_mocha_token start_token;
	start_token.token_data = 0;
	start_token.token_id = TYRAN_MOCHA_TOKEN_LINE_START;

	temp_buffer[count++] = start_token;
	while (1) {
		tyran_mocha_token token = tyran_mocha_lexer_next_token(&position_info, lexer);
		temp_buffer[count++] = token;
		if (token.token_id == TYRAN_MOCHA_TOKEN_END) {
			break;
		}
	}

	tyran_mocha_lexer* mocha_lexer = tyran_mocha_lexer_new(mocha_lexer_pool, memory, mocha_token_pool, temp_buffer, count);
	tyran_free(temp_buffer);

	return mocha_lexer;
}

tyran_mocha_token* tyran_mocha_lexer_previous(tyran_mocha_token* token, tyran_mocha_token* first)
{
	if (token == first) {
		return 0;
	}
	tyran_mocha_token* previous = token - 1;
	return previous;
}


int tyran_mocha_lexer_is_literal(tyran_mocha_token* token)
{
	tyran_mocha_token_id token_id = token->token_id;

	return (token_id == TYRAN_MOCHA_TOKEN_STRING || token_id == TYRAN_MOCHA_TOKEN_NUMBER || token_id == TYRAN_MOCHA_TOKEN_IDENTIFIER);
}

tyran_mocha_token* tyran_mocha_lexer_next(tyran_mocha_token* first, tyran_mocha_token* last)
{
	if (first == last) {
		return 0;
	}
	if (first->token_id == TYRAN_MOCHA_TOKEN_END) {
		return 0;
	}
	tyran_mocha_token* next = first + 1;
	return next;
}


tyran_mocha_token* tyran_mocha_lexer_first(tyran_mocha_lexer* lexer)
{
	return &lexer->tokens[0];
}

tyran_mocha_token* tyran_mocha_lexer_last(tyran_mocha_lexer* lexer)
{
	return &lexer->tokens[lexer->token_count - 1];
}

int tyran_mocha_lexer_is_unary_operator(tyran_mocha_token_id token_id)
{
	return (token_id == TYRAN_MOCHA_TOKEN_NOT || token_id == TYRAN_MOCHA_TOKEN_RETURN || token_id == TYRAN_MOCHA_TOKEN_IF || token_id == TYRAN_MOCHA_TOKEN_UNLESS || token_id == TYRAN_MOCHA_TOKEN_PARENTHESES_RIGHT || token_id == TYRAN_MOCHA_TOKEN_BLOCK_END || token_id == TYRAN_MOCHA_TOKEN_BRACKET_RIGHT || token_id == TYRAN_MOCHA_TOKEN_OBJECT_END);
}

tyran_mocha_token_id tyran_mocha_enclosing_start_token(tyran_mocha_token_id token_id)
{
	typedef struct tyran_mocha_matching_tokens {
		tyran_mocha_token_id start;
		tyran_mocha_token_id end;
	} tyran_mocha_matching_tokens;

	tyran_mocha_matching_tokens enclosing_tokens[] = {
		{TYRAN_MOCHA_TOKEN_BRACKET_LEFT, TYRAN_MOCHA_TOKEN_BRACKET_RIGHT},
		{TYRAN_MOCHA_TOKEN_PARENTHESES_LEFT, TYRAN_MOCHA_TOKEN_PARENTHESES_RIGHT},
		{TYRAN_MOCHA_TOKEN_OBJECT_START, TYRAN_MOCHA_TOKEN_OBJECT_END},
		{TYRAN_MOCHA_TOKEN_BLOCK_START, TYRAN_MOCHA_TOKEN_BLOCK_END},
	};

	size_t i;
	for (i=0; i<sizeof(enclosing_tokens) / sizeof(tyran_mocha_matching_tokens); ++i) {
		if (token_id == enclosing_tokens[i].end) {
			return enclosing_tokens[i].start;
		}
	}
	return TYRAN_MOCHA_TOKEN_END;
}



tyran_mocha_token* tyran_mocha_lexer_find(tyran_mocha_token* first, tyran_mocha_token* last, tyran_mocha_token_id id)
{
	if (first->token_id == TYRAN_MOCHA_TOKEN_END) {
		return 0;
	}

	tyran_mocha_token* token = first;
	while (token->token_id != id) {
		token = tyran_mocha_lexer_next(token, last);
		if (!token) {
			break;
		}
	}

	return token;
}

