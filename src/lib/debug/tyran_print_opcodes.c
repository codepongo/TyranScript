#include <tyranscript/tyran_opcode_ids.h>
#include <tyranscript/tyran_opcodes.h>
#include <tyranscript/tyran_opcode.h>
#include <tyranscript/tyran_config.h>
#include <tyranscript/tyran_function.h>
#include <tyranscript/debug/tyran_print_opcodes.h>

const char* tyran_opcode_names[TYRAN_OPCODE_MAX_ID] = {
	"NOP",
	"LD",
	"LDC",
	"LDB",
	"LDN",
	"ADD",
	"DIV",
	"MOD",
	"MUL",
	"NEG",
	"NOT",
	"POW",
	"SUB",
	"JB",
	"JBLD",
	"JEQ",
	"JLT",
	"JLE",
	"JMP",
	"RET",
	"CALL",
	"NEW",
	"SET",
	"GET",
	"DEBUG"
};


#define TYRAN_OPCODE_INSTRUCTION(code) \
	(code & 0x3f)

#define TYRAN_OPCODE_ARG_A(code) \
	((code >> 6) & 0xff)

#define TYRAN_OPCODE_ARG_X(code) \
	((code >> 14) & 0x1ff)

#define TYRAN_OPCODE_ARG_Y(code) \
	((code >> 23) & 0x1ff)

#define TYRAN_OPCODE_ARG_BR(code) \
	((code >> 6) & 0xffff) - 0x8000;


void print_r_rc_rc(tyran_opcode code, char* buf, int size)
{
	tyran_reg_index a = TYRAN_OPCODE_ARG_A(code);
	tyran_reg_or_constant_index x = TYRAN_OPCODE_ARG_X(code);
	tyran_reg_or_constant_index y = TYRAN_OPCODE_ARG_Y(code);

	tyran_snprintf(buf, size, "@%d @%d @%d", a, x, y);
}

void print_r_r_rc(tyran_opcode code, char* buf, int size)
{
	tyran_reg_index a = TYRAN_OPCODE_ARG_A(code);
	tyran_reg_index r = TYRAN_OPCODE_ARG_X(code);
	tyran_reg_or_constant_index y = TYRAN_OPCODE_ARG_Y(code);

	tyran_snprintf(buf, size, "@%d @%d @%d", a, r, y);
}

void print_r_rc(tyran_opcode code, char* buf, int size)
{
	tyran_reg_index a = TYRAN_OPCODE_ARG_A(code);
	tyran_reg_or_constant_index x = TYRAN_OPCODE_ARG_X(code);

	tyran_snprintf(buf, size, "@%d @%d", a, x);
}

void print_r_c(tyran_opcode code, char* buf, int size)
{
	tyran_reg_index a = TYRAN_OPCODE_ARG_A(code);
	tyran_constant_index x = TYRAN_OPCODE_ARG_X(code);

	tyran_snprintf(buf, size, "@%d #%d", a, x);
}

void print_r_b(tyran_opcode code, char* buf, int size)
{
	tyran_reg_index a = TYRAN_OPCODE_ARG_A(code);
	tyran_boolean b = TYRAN_OPCODE_ARG_X(code);

	tyran_snprintf(buf, size, "@%d %s", a, b ? "true" : "false");
}

void print_rc_b(tyran_opcode code, char* buf, int size)
{
	tyran_reg_or_constant_index a = TYRAN_OPCODE_ARG_X(code);
	tyran_boolean b = TYRAN_OPCODE_ARG_A(code);

	tyran_snprintf(buf, size, "@%d %s", a, b ? "true" : "false");
}

void print_r_rc_b(tyran_opcode code, char* buf, int size)
{
	tyran_reg_index a = TYRAN_OPCODE_ARG_A(code);
	tyran_reg_or_constant_index y = TYRAN_OPCODE_ARG_Y(code);
	tyran_boolean b = TYRAN_OPCODE_ARG_Y(code);

	tyran_snprintf(buf, size, "@%d = @%d %s", a, y, b ? "true" : "false");
}

void print_b_rc_rc(tyran_opcode code, char* buf, int size)
{
	tyran_boolean b = TYRAN_OPCODE_ARG_A(code);
	tyran_reg_or_constant_index x = TYRAN_OPCODE_ARG_X(code);
	tyran_reg_or_constant_index y = TYRAN_OPCODE_ARG_Y(code);

	tyran_snprintf(buf, size, "@%d @%d %s", x, y, b ? "true" : "false");
}

void print_br(tyran_opcode code, int pc, char* buf, int size)
{
	int br = TYRAN_OPCODE_ARG_BR(code);
	tyran_snprintf(buf, size, "%d (%d)", (pc + br + 1), br);
}


void print_r_s(tyran_opcode code, char* buf, int size)
{
	tyran_reg_index a = TYRAN_OPCODE_ARG_A(code);
	int s = TYRAN_OPCODE_ARG_X(code);

	tyran_snprintf(buf, size, "@%d %d", a, s);
}

void print_r_s_s(tyran_opcode code, char* buf, int size)
{
	tyran_reg_index a = TYRAN_OPCODE_ARG_A(code);
	int s = TYRAN_OPCODE_ARG_X(code);
	int s2 = TYRAN_OPCODE_ARG_Y(code);

	tyran_snprintf(buf, size, "@%d %d %d", a, s, s2);
}

void tyran_print_arguments(tyran_opcode code, int ip, char* buf, int size)
{
	int instruction = TYRAN_OPCODE_INSTRUCTION(code);
	switch (instruction)
	{
		case TYRAN_OPCODE_ADD:
		case TYRAN_OPCODE_DIV:
		case TYRAN_OPCODE_MOD:
		case TYRAN_OPCODE_MUL:
		case TYRAN_OPCODE_POW:
		case TYRAN_OPCODE_SUB:
			print_r_rc_rc(code, buf, size);
			break;
		case TYRAN_OPCODE_NEG:
		case TYRAN_OPCODE_NOT:
			print_r_rc(code, buf, size);
			break;
		case TYRAN_OPCODE_LDC:
			print_r_c(code, buf, size);
			break;
		case TYRAN_OPCODE_LDB:
			print_r_b(code, buf, size);
			break;
		case TYRAN_OPCODE_LDN:
			print_r_s(code, buf, size);
			break;
		case TYRAN_OPCODE_JEQ:
		case TYRAN_OPCODE_JLT:
		case TYRAN_OPCODE_JLE:
			print_b_rc_rc(code, buf, size);
			break;
		case TYRAN_OPCODE_JB:
			print_rc_b(code, buf, size);
			break;
		case TYRAN_OPCODE_JBLD:
			print_r_rc_b(code, buf, size);
			break;
		case TYRAN_OPCODE_JMP:
			print_br(code, ip, buf, size);
			break;
		case TYRAN_OPCODE_RET:
			buf[0] = 0;
			break;
		case TYRAN_OPCODE_CALL:
			print_r_s_s(code, buf, size);
			break;
		case TYRAN_OPCODE_NEW:
		case TYRAN_OPCODE_SET:
		case TYRAN_OPCODE_GET:
			print_r_r_rc(code, buf, size);
			break;
		case TYRAN_OPCODE_DEBUG:
			buf[0] = 0;
			break;
	}
}

void tyran_print_opcode(const tyran_opcode* opcode, int ip, int highlight)
{
	tyran_opcode code = *opcode;
	int instruction = TYRAN_OPCODE_INSTRUCTION(code);

	char args[512];
	tyran_print_arguments(code, ip, args, 512);
	
	TYRAN_LOG("%d %s %s", ip, tyran_opcode_names[instruction], args);
}

void tyran_print_opcodes(const struct tyran_opcodes* ops, const tyran_opcode* ip)
{
	int i = 0;
	const tyran_opcode* tyran_opcodes = ops->codes;
	int octet_length = ops->code_len;

	TYRAN_LOG("opcode octets:%d", octet_length);

	for (i = 0; i < octet_length; ++i) {
		tyran_print_opcode(&tyran_opcodes[i], i, ip == &tyran_opcodes[i]);
	}
}
