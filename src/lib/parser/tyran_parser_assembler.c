#include "tyranscript/parser/tyran_lexer.h"
#include "tyranscript/parser/tyran_parser_state.h"
#include <tyranscript/parser/tyran_label.h>
#include <tyranscript/parser/tyran_label_reference.h>

#include "tyranscript/tyran_opcodes.h"
#include <tyranscript/tyran_string.h>
#include <tyranscript/tyran_opcodes.h>
#include <tyranscript/tyran_constants.h>

void tyran_parse_assembler(tyran_lexer* lexer, char c)
{
	TYRAN_UNICODE_STRING(1024) string_buffer;
	tyran_string* temp_string_buffer = string_buffer.string;

	if (tyran_lexer_is_alpha(c) || c == '_' || c == '$') {
		int length = tyran_lexer_parse_identifier(lexer, c, temp_string_buffer);
	}
}

enum {
	TYRN_TOKEN_NOTHING,
	TYRAN_TOKEN_ASSEMBLER_LD,
	TYRAN_TOKEN_ASSEMBLER_LDA,
	TYRAN_TOKEN_ASSEMBLER_LDB,
	TYRAN_TOKEN_ASSEMBLER_LDC,
	TYRAN_TOKEN_ASSEMBLER_LDN,
	TYRAN_TOKEN_ASSEMBLER_ADD,
	TYRAN_TOKEN_ASSEMBLER_DIV,
	TYRAN_TOKEN_ASSEMBLER_MOD,
	TYRAN_TOKEN_ASSEMBLER_MUL,
	TYRAN_TOKEN_ASSEMBLER_NEG,
	TYRAN_TOKEN_ASSEMBLER_NOT,
	TYRAN_TOKEN_ASSEMBLER_POW,
	TYRAN_TOKEN_ASSEMBLER_SUB,
	TYRAN_TOKEN_ASSEMBLER_JB,
	TYRAN_TOKEN_ASSEMBLER_JBLD,
	TYRAN_TOKEN_ASSEMBLER_JEQ,
	TYRAN_TOKEN_ASSEMBLER_JLT,
	TYRAN_TOKEN_ASSEMBLER_JLE,
	TYRAN_TOKEN_ASSEMBLER_JMP,
	TYRAN_TOKEN_ASSEMBLER_RET,
	TYRAN_TOKEN_ASSEMBLER_CALL,
	TYRAN_TOKEN_ASSEMBLER_SET,
	TYRAN_TOKEN_ASSEMBLER_GET,
	TYRAN_TOKEN_ASSEMBLER_NEW,
	TYRAN_TOKEN_ASSEMBLER_COLON,
} tyran_assembler_token;


static int tyran_lexer_assembler_get_keyword_token(const char* temp_string_buffer)
{
	typedef struct tyran_lexer_keyword {
		const char* name;
		int token_value;
	} tyran_lexer_keyword;

	static tyran_lexer_keyword keywords[] = {
		{ "ld", TYRAN_TOKEN_ASSEMBLER_LD },
		{ "lda", TYRAN_TOKEN_ASSEMBLER_LDA },
		{ "ldc", TYRAN_TOKEN_ASSEMBLER_LDC },
		{ "ldn", TYRAN_TOKEN_ASSEMBLER_LDN },
		{ "add", TYRAN_TOKEN_ASSEMBLER_ADD },
		{ "div", TYRAN_TOKEN_ASSEMBLER_DIV },
		{ "mod", TYRAN_TOKEN_ASSEMBLER_MOD },
		{ "mul", TYRAN_TOKEN_ASSEMBLER_MUL },
		{ "neg", TYRAN_TOKEN_ASSEMBLER_NEG },
		{ "not", TYRAN_TOKEN_ASSEMBLER_NOT },
		{ "pow", TYRAN_TOKEN_ASSEMBLER_POW },
		{ "sub", TYRAN_TOKEN_ASSEMBLER_SUB },
		{ "jb", TYRAN_TOKEN_ASSEMBLER_JB },
		{ "jbld", TYRAN_TOKEN_ASSEMBLER_JBLD },
		{ "jeq", TYRAN_TOKEN_ASSEMBLER_JEQ },
		{ "jlt", TYRAN_TOKEN_ASSEMBLER_JLT },
		{ "jlte", TYRAN_TOKEN_ASSEMBLER_JLE },
		{ "jmp", TYRAN_TOKEN_ASSEMBLER_JMP },
		{ "ret", TYRAN_TOKEN_ASSEMBLER_RET },
		{ "call", TYRAN_TOKEN_ASSEMBLER_CALL },
		{ "set", TYRAN_TOKEN_ASSEMBLER_SET },
		{ "get", TYRAN_TOKEN_ASSEMBLER_GET },
		{ "new", TYRAN_TOKEN_ASSEMBLER_NEW },
	};

	size_t i;

	for (i = 0; i < sizeof(keywords) / sizeof(tyran_lexer_keyword); ++i) {
		if (tyran_strcmp(temp_string_buffer, keywords[i].name) == 0) {
			TYRAN_LOG("Found match:%d (%s) (%s)", keywords[i].token_value, temp_string_buffer, keywords[i].name);
			return keywords[i].token_value;
		}
	}
	return 0;
}

int tyran_lexer_assembler_parse_identifier_or_keyword(tyran_lexer* lexer, char c, tyran_string* temp_string_buffer, tyran_string_length_type* string_length, tyran_lexer_position_info* lexer_position_info, tyran_lexer_token_data* token)
{
	int identifier_length = tyran_lexer_parse_identifier(lexer, c, temp_string_buffer);
	*string_length = (tyran_string_length_type) identifier_length;
	char temp_buffer[512];
	tyran_string_to_c_str(temp_buffer, 512, temp_string_buffer);
	int r = tyran_lexer_assembler_get_keyword_token(temp_buffer);
	if (r) {
		return r;
	}

	int len = tyran_strlen(temp_buffer);
	if (len == 0) {
		return 0;
	}

	if (tyran_strcmp(temp_buffer, "true") == 0) {
		return TYRAN_TOKEN_TRUE;
	} else if (tyran_strcmp(temp_buffer, "false") == 0) {
		return TYRAN_TOKEN_FALSE;
	}

	*token = (void*) tyran_string_strdup(temp_string_buffer);
	tyran_lexer_set_end(lexer_position_info, lexer);
	return TYRAN_TOKEN_IDENTIFIER;
}


static int tyran_lexer_assembler_next_token(tyran_lexer_token_data token, tyran_lexer_position_info* lexer_position_info, tyran_lexer* lexer)
{
	TYRAN_UNICODE_STRING(1024) string_buffer;
	tyran_string* temp_string_buffer = string_buffer.string;

	tyran_lexer_set_begin(lexer_position_info, lexer);

	char c = tyran_lexer_next_character_skip_whitespace(lexer);
	if (!c) {
		return 0;
	}

	if (c=='@') {
		return TYRAN_TOKEN_REGISTER;
	}

	if (c==':') {
		return TYRAN_TOKEN_COLON;
	}
	if (tyran_lexer_is_alpha(c) || c == '_' || c == '$') {
		return tyran_lexer_assembler_parse_identifier_or_keyword(lexer, c, temp_string_buffer, &string_buffer.len, lexer_position_info, token);
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
	tyran_lexer_set_end(lexer_position_info, lexer);

	return 0;
}

void error()
{
	TYRAN_LOG("ERROR!!");
}

void add_label(tyran_parser_state* state, tyran_string* name)
{
	struct tyran_label* label = &state->labels[state->label_count++];
	label->name = tyran_string_strdup(name);
	label->position = state->opcodes->code_len + 1;
	TYRAN_LOG("Adding label at pos:%d", label->position);
}

void add_label_reference(tyran_parser_state* state, tyran_string* name)
{
	TYRAN_LOG("Adding label reference");
	struct tyran_label_reference* label_reference = &state->label_references[state->label_reference_count++];
	label_reference->name = tyran_string_strdup(name);
	label_reference->opcode = &state->opcodes->codes[state->opcodes->code_len];
}


tyran_reg_or_constant_index add_constant_number(tyran_parser_state* state, tyran_number v)
{
	return 1;
}

void parse_r_index(tyran_parser_state* state, tyran_reg_index* a)
{
	tyran_number* number;
	tyran_lexer_position_info position;
	int token = tyran_lexer_assembler_next_token(&number, &position, state->lexer);
	if (token != TYRAN_TOKEN_NUMBER) {
		return error();
	}

	*a = (int) *number;
}

void parse_rc(tyran_parser_state* state, tyran_reg_or_constant_index* a)
{
	tyran_number* number;
	tyran_lexer_position_info position;

	int token = tyran_lexer_assembler_next_token(&number, &position, state->lexer);
	switch (token) {
		case TYRAN_TOKEN_NUMBER:
			*a = add_constant_number(state, *number);
			break;
		case TYRAN_TOKEN_REGISTER:
			parse_r_index(state, (tyran_reg_index*)a);
			break;
	}
}

void parse_r(tyran_parser_state* state, tyran_reg_index* a)
{
	tyran_number* number;
	tyran_lexer_position_info position;

	int token = tyran_lexer_assembler_next_token((tyran_lexer_token_data*)0, &position, state->lexer);
	if (token != TYRAN_TOKEN_REGISTER) {
		return error();
	}
	parse_r_index(state, a);
}

void parse_identifier(tyran_parser_state* state)
{
	tyran_string* name;
	tyran_lexer_position_info position;

	int token = tyran_lexer_assembler_next_token((tyran_lexer_token_data*)&name, &position, state->lexer);
	if (token != TYRAN_TOKEN_IDENTIFIER) {
		return error();
	}
	add_label_reference(state, name);
}

void parse_b(tyran_parser_state* state, tyran_boolean* b)
{
	tyran_number* number;
	tyran_lexer_position_info position;

	int token = tyran_lexer_assembler_next_token((tyran_lexer_token_data*)0, &position, state->lexer);
	if (token != TYRAN_TOKEN_TRUE && token != TYRAN_TOKEN_FALSE) {
		return error();
	}

	*b = (token == TYRAN_TOKEN_TRUE);
}

void parse_r_rc(tyran_parser_state* state, tyran_reg_index* a, tyran_reg_or_constant_index* c)
{
	parse_r(state, a);
	parse_rc(state, c);
}

void parse_r_rc_rc(tyran_parser_state* state, tyran_reg_index* a, tyran_reg_or_constant_index* x, tyran_reg_or_constant_index* y)
{
	parse_r(state, a);
	parse_rc(state, x);
	parse_rc(state, y);
}


void parse_r_b(tyran_parser_state* state, tyran_reg_index* a, int* b)
{
}

void parse_b_rc(tyran_parser_state* state, int* b, tyran_reg_or_constant_index* a)
{
}

void parse_b_rc_rc(tyran_parser_state* state, tyran_boolean* b, tyran_reg_or_constant_index* a, tyran_reg_or_constant_index* y)
{
	parse_b(state, b);
	parse_rc(state, a);
	parse_rc(state, y);
}

void parse_r_b_rc(tyran_parser_state* state, tyran_reg_index* a, int* b, tyran_reg_or_constant_index* x)
{
}


void parse_r_s(tyran_parser_state* state, tyran_reg_index* a, int* b)
{
}


void change_opcode_branch(tyran_opcode* code, int position)
{
	u16t br = (position + 0x8000);
	*code = (*code & 0x3f) | (br << 6);
}

tyran_label* get_label(tyran_label* labels, int count, const tyran_string* name)
{
	for (int i=0; i<count; ++i)
	{
		if (tyran_string_strcmp(labels[i].name, name) == 0) {
			return &labels[i];
		}
	}

	return 0;
}

void fixup_label_references(tyran_parser_state* state)
{
	for (int i=0; i<state->label_reference_count;++i)
	{
		tyran_label_reference* ref = &state->label_references[i];
		tyran_label* label = get_label(state->labels, state->label_count, ref->name);
		if (!label) {
			error();
			return;
		}
		int delta = label->position - (ref->opcode - state->opcodes->codes) - 2; 
		change_opcode_branch(ref->opcode, delta);
	}
}


int tyran_lexer_assembler_parse_one(tyran_lexer_position_info* lexer_position, tyran_parser_state* parser_state)
{
	tyran_lexer_token_data data;
	int token = tyran_lexer_assembler_next_token(&data, lexer_position, parser_state->lexer);
	if (token == 0) {
		TYRAN_LOG("END OF FILE!");
		return 0;
	}


	tyran_reg_index a;
	int b;
	int s;
	tyran_reg_or_constant_index x, y;
	tyran_opcodes* opcodes = parser_state->opcodes;
	tyran_constant_index c;

	switch (token) {
		case TYRAN_TOKEN_IDENTIFIER:
			token = tyran_lexer_assembler_next_token(&data, lexer_position, parser_state->lexer);
			if (token == TYRAN_TOKEN_COLON) {
				add_label(parser_state, (tyran_string*)data);
			} else {
				TYRAN_LOG("error token:%d", token);
				error();
			}
			break;
		case TYRAN_TOKEN_ASSEMBLER_LD:
			parse_r_rc(parser_state, &a, &x);
			tyran_opcodes_op_ld(opcodes, a, x);
			break;
		case TYRAN_TOKEN_ASSEMBLER_LDC:
			parse_r(parser_state, &a);
			token = tyran_lexer_assembler_next_token(&data, lexer_position, parser_state->lexer);
			switch (token) {
				case TYRAN_TOKEN_NUMBER:
					c = tyran_constants_add_number(parser_state->constants, *(tyran_number*)data);
					break;
				case TYRAN_TOKEN_STRING:
					c = tyran_constants_add_string(parser_state->constants, (tyran_string*)data);
					break;
				case TYRAN_TOKEN_TRUE:
				case TYRAN_TOKEN_FALSE:
					c = tyran_constants_add_boolean(parser_state->constants, *(tyran_boolean*)data);
					break;
				default:
					error();
					return -1;
			}
			tyran_opcodes_op_ldc(opcodes, a, c);
			break;
		case TYRAN_TOKEN_ASSEMBLER_LDB:
			parse_r_b(parser_state, &a, &b);
			tyran_opcodes_op_ldb(opcodes, a, *(int *)data);
			break;
		case TYRAN_TOKEN_ASSEMBLER_LDN:
			parse_r_s(parser_state, &a, &s);
			tyran_opcodes_op_ldn(opcodes, a, x);
			break;
		case TYRAN_TOKEN_ASSEMBLER_ADD:
			parse_r_rc_rc(parser_state, &a, &x, &y);
			tyran_opcodes_op_add(opcodes, a, x, y);
			break;
		case TYRAN_TOKEN_ASSEMBLER_DIV:
			parse_r_rc_rc(parser_state, &a, &x, &y);
			tyran_opcodes_op_div(opcodes, a, x, y);
			break;
		case TYRAN_TOKEN_ASSEMBLER_MOD:
			parse_r_rc_rc(parser_state, &a, &x, &y);
			tyran_opcodes_op_mod(opcodes, a, x, y);
			break;
		case TYRAN_TOKEN_ASSEMBLER_MUL:
			parse_r_rc_rc(parser_state, &a, &x, &y);
			tyran_opcodes_op_mul(opcodes, a, x, y);
			break;
		case TYRAN_TOKEN_ASSEMBLER_NEG:
			parse_r_rc(parser_state, &a, &x);
			tyran_opcodes_op_neg(opcodes, a, x);
			break;
		case TYRAN_TOKEN_ASSEMBLER_NOT:
			parse_r_rc(parser_state, &a, &x);
			tyran_opcodes_op_not(opcodes, a, x);
			break;
		case TYRAN_TOKEN_ASSEMBLER_POW:
			parse_r_rc_rc(parser_state, &a, &x, &y);
			tyran_opcodes_op_pow(opcodes, a, x, y);
			break;
		case TYRAN_TOKEN_ASSEMBLER_SUB:
			parse_r_rc_rc(parser_state, &a, &x, &y);
			tyran_opcodes_op_sub(opcodes, a, x, y);
			break;
		case TYRAN_TOKEN_ASSEMBLER_JB:
			parse_b_rc(parser_state, &b, &x);
			tyran_opcodes_op_jb(opcodes, a, b);
			break;
		case TYRAN_TOKEN_ASSEMBLER_JBLD:
			parse_r_b_rc(parser_state, &a, &b, &y);
			tyran_opcodes_op_jbld(opcodes, a, x, y);
			break;
		case TYRAN_TOKEN_ASSEMBLER_JEQ:
			parse_b_rc_rc(parser_state, &b, &x, &y);
			tyran_opcodes_op_jeq(opcodes, a, x, y);
			break;
		case TYRAN_TOKEN_ASSEMBLER_JLT:
			parse_b_rc_rc(parser_state, &b, &x, &y);
			tyran_opcodes_op_jlt(opcodes, a, x, y);
			break;
		case TYRAN_TOKEN_ASSEMBLER_JLE:
			parse_b_rc_rc(parser_state, &b, &x, &y);
			tyran_opcodes_op_jle(opcodes, b, x, y);
			break;
		case TYRAN_TOKEN_ASSEMBLER_JMP:
			parse_identifier(parser_state);
			tyran_opcodes_op_jmp(opcodes, 0);
			break;
		case TYRAN_TOKEN_ASSEMBLER_RET:
			tyran_opcodes_op_ret(opcodes);
			break;
	}

	return token;
}

int tyran_lexer_assembler_parse(tyran_lexer_position_info* lexer_position, tyran_parser_state* parser_state)
{
	int token;
	do {
		token = tyran_lexer_assembler_parse_one(lexer_position, parser_state);
	} while (token != 0);
	
	fixup_label_references(parser_state);
	
	return 0;
}
