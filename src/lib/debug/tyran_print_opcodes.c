#include <tyranscript/tyran_configuration.h>
#include <tyranscript/tyran_opcode_ids.h>
#include <tyranscript/tyran_opcodes.h>
#include <tyranscript/tyran_opcode.h>
#include <tyranscript/tyran_config.h>
#include <tyranscript/tyran_function.h>
#include <tyranscript/tyran_constants.h>
#include <tyranscript/debug/tyran_print_opcodes.h>
#include <tyranscript/debug/tyran_print_value.h>
#include <tyranscript/tyran_value.h>

const char* tyran_opcode_names[TYRAN_OPCODE_MAX_ID] = {
	"NOP",
	"LD",
	"LDC",
	"LDCU",
	"ADD",
	"DIV",
	"MOD",
	"MUL",
	"POW",
	"SUB",
	"INDEX",
	"INDEX_SET",
	"ITER",
	"NEXT",
	"NEG",
	"NOT",
	"EQ",
	"LT",
	"LE",
	"JB",
	"JBLD",
	"JMP",
	"RET",
	"CALL",
	"NEW",
	"SET",
	"GET",
	"FUNC",
	"DEBUG"
};


#define TYRAN_OPCODE_INSTRUCTION(code) \
	(code & 0x1f)


#define TYRAN_OPCODE_ARG_B(code) \
	((code >> 31) & 0x1)

#define TYRAN_OPCODE_ARG_A(code) \
	((code >> 5) & 0xff)

#define TYRAN_OPCODE_ARG_X(code) \
	((code >> 13) & 0x1ff)

#define TYRAN_OPCODE_ARG_Y(code) \
	((code >> 22) & 0x1ff)

#define TYRAN_OPCODE_ARG_BR(code) \
	((code >> 5) & 0xffff) - 0x8000;


void print_s(int v, char* buf, int size)
{
	const int tmp_size = 512;
	char tmp[tmp_size];

	tyran_snprintf(tmp, tmp_size, " %d", v);
	tyran_strncat(buf, tmp, size);
}

void print_b(tyran_boolean b, char* buf, int size)
{
	strncat(buf, b ? " true" : " false", size);
}

void print_r(tyran_reg_index index, char* buf, int size)
{
	const int tmp_size = 512;
	char tmp[tmp_size];

	tyran_snprintf(tmp, tmp_size, " @%d", index);
	tyran_strncat(buf, tmp, size);
}

void print_rc(tyran_reg_or_constant_index index, const tyran_constants* constants, char* buf, int size)
{
	if (index & TYRAN_OPCODE_CONSTANT_BIT) {
		const int tmp_size = 512;
		char tmp[tmp_size];
		char value_buf[tmp_size];
		int constant_index = index & TYRAN_OPCODE_REGISTER_MASK;
		tyran_value_to_c_string(constants->symbol_table, &constants->values[constant_index], value_buf, tmp_size, 1);
		tyran_snprintf(tmp, tmp_size, " %s (#%d)", value_buf, constant_index);
		tyran_strncat(buf, tmp, size);
	} else {
		print_r(index, buf, size);
	}
}


void print_r_rc_rc(tyran_opcode code, const tyran_constants* constants, char* buf, int size)
{
	print_r(TYRAN_OPCODE_ARG_A(code), buf, size);
	print_rc(TYRAN_OPCODE_ARG_X(code), constants, buf, size);
	print_rc(TYRAN_OPCODE_ARG_Y(code), constants, buf, size);
}

void print_r_rc_rc_b(tyran_opcode code, const tyran_constants* constants, char* buf, int size)
{
	print_r_rc_rc(code, constants, buf, size);
	print_b(TYRAN_OPCODE_ARG_B(code), buf, size);
}

void print_r_r_rc(tyran_opcode code, const tyran_constants* constants, char* buf, int size)
{
	print_r(TYRAN_OPCODE_ARG_A(code), buf, size);
	print_r(TYRAN_OPCODE_ARG_X(code), buf, size);
	print_rc(TYRAN_OPCODE_ARG_Y(code), constants, buf, size);
}

void print_r_r(tyran_opcode code, char* buf, int size)
{
	print_r(TYRAN_OPCODE_ARG_A(code), buf, size);
	print_r(TYRAN_OPCODE_ARG_X(code), buf, size);
}

void print_r_rc(tyran_opcode code, const tyran_constants* constants, char* buf, int size)
{
	print_r(TYRAN_OPCODE_ARG_A(code), buf, size);
	print_rc(TYRAN_OPCODE_ARG_X(code), constants, buf, size);
}

void print_r_c(tyran_opcode code, const tyran_constants* constants, char* buf, int size)
{
	print_r(TYRAN_OPCODE_ARG_A(code), buf, size);
	print_rc(TYRAN_OPCODE_ARG_X(code), constants, buf, size);
}

void print_r_b(tyran_opcode code, char* buf, int size)
{
	print_r(TYRAN_OPCODE_ARG_A(code), buf, size);
	print_b(TYRAN_OPCODE_ARG_X(code), buf, size);
}

void print_rc_b(tyran_opcode code, const tyran_constants* constants, char* buf, int size)
{
	print_rc(TYRAN_OPCODE_ARG_X(code), constants, buf, size);
	print_b(TYRAN_OPCODE_ARG_A(code), buf, size);
}

void print_r_rc_b(tyran_opcode code, const tyran_constants* constants, char* buf, int size)
{
	print_r(TYRAN_OPCODE_ARG_A(code), buf, size);
	print_rc(TYRAN_OPCODE_ARG_X(code), constants, buf, size);
	print_b(TYRAN_OPCODE_ARG_Y(code), buf, size);
}

void print_b_rc_rc(tyran_opcode code, const tyran_constants* constants, char* buf, int size)
{
	print_b(TYRAN_OPCODE_ARG_A(code), buf, size);
	print_rc(TYRAN_OPCODE_ARG_X(code), constants, buf, size);
	print_rc(TYRAN_OPCODE_ARG_Y(code), constants, buf, size);
}

void print_br(tyran_opcode code, int pc, char* buf, int size)
{
	int br = TYRAN_OPCODE_ARG_BR(code);
	tyran_snprintf(buf, size, " %d (%d)", (pc + br + 1), br);
}

void print_br_b(tyran_opcode code, int pc, char* buf, int size)
{
	print_br(code, pc, buf, size);
	print_b(TYRAN_OPCODE_ARG_A(code), buf, size);
}

void print_r_s(tyran_opcode code, char* buf, int size)
{
	print_r(TYRAN_OPCODE_ARG_A(code), buf, size);
	print_s(TYRAN_OPCODE_ARG_X(code), buf, size);
}

void print_r_s_s(tyran_opcode code, char* buf, int size)
{
	print_r(TYRAN_OPCODE_ARG_A(code), buf, size);
	print_s(TYRAN_OPCODE_ARG_X(code), buf, size);
	print_s(TYRAN_OPCODE_ARG_Y(code), buf, size);
}

void tyran_print_arguments(tyran_opcode code, int ip, const tyran_constants* constants, char* buf, int size)
{
	int instruction = TYRAN_OPCODE_INSTRUCTION(code);
	switch (instruction) {
		case TYRAN_OPCODE_ADD:
		case TYRAN_OPCODE_DIV:
		case TYRAN_OPCODE_MOD:
		case TYRAN_OPCODE_MUL:
		case TYRAN_OPCODE_POW:
		case TYRAN_OPCODE_SUB:
			print_r_rc_rc(code, constants, buf, size);
			break;
		case TYRAN_OPCODE_NEG:
		case TYRAN_OPCODE_NOT:
			print_r_rc(code, constants, buf, size);
			break;
		case TYRAN_OPCODE_LD:
			print_r_r(code, buf, size);
			break;
		case TYRAN_OPCODE_LDC:
		case TYRAN_OPCODE_LDCU:
		case TYRAN_OPCODE_NEXT:
		case TYRAN_OPCODE_ITER:
			print_r_c(code, constants, buf, size);
			break;
		case TYRAN_OPCODE_EQ:
		case TYRAN_OPCODE_LT:
		case TYRAN_OPCODE_LE:
			print_r_rc_rc_b(code, constants, buf, size);
			break;
		case TYRAN_OPCODE_JBLD:
			print_r_rc_b(code, constants, buf, size);
			break;
		case TYRAN_OPCODE_JB:
			print_rc_b(code, constants, buf, size);
			break;
		case TYRAN_OPCODE_JMP:
			print_br(code, ip, buf, size);
			break;
		case TYRAN_OPCODE_RET:
			print_r_s(code, buf, size);
			break;
		case TYRAN_OPCODE_CALL:
			print_r_s_s(code, buf, size);
			break;
		case TYRAN_OPCODE_FUNC:
			print_r_rc(code, constants, buf, size);
			break;
		case TYRAN_OPCODE_NEW:
			print_r(TYRAN_OPCODE_ARG_A(code), buf, size);
			break;
		case TYRAN_OPCODE_SET:
		case TYRAN_OPCODE_INDEX_SET:
			print_r_rc_rc(code, constants, buf, size);
			break;
		case TYRAN_OPCODE_GET:
		case TYRAN_OPCODE_INDEX:
			print_r_rc_rc(code, constants, buf, size);
			break;
		case TYRAN_OPCODE_DEBUG:
			break;
	}
}

void tyran_print_opcode(const tyran_opcode* opcode, const tyran_constants* constants, int ip, int highlight)
{
#if defined TYRAN_CONFIGURATION_DEBUG
	tyran_opcode code = *opcode;
	int instruction = TYRAN_OPCODE_INSTRUCTION(code);

	char args[512];
	args[0] = 0;
	tyran_print_arguments(code, ip, constants, args, 512);

	TYRAN_LOG("%d %s%s", ip, tyran_opcode_names[instruction], args);
#endif
}

void tyran_print_opcodes(const struct tyran_opcodes* ops, const tyran_opcode* ip, const tyran_constants* constants)
{
#if defined TYRAN_CONFIGURATION_DEBUG
	int i = 0;
	const tyran_opcode* tyran_opcodes = ops->codes;
	int octet_length = ops->code_len;

	TYRAN_LOG("opcode octets:%d", octet_length);

	for (i = 0; i < octet_length; ++i) {
		tyran_print_opcode(&tyran_opcodes[i], constants, i, ip == &tyran_opcodes[i]);
	}
#endif
}
