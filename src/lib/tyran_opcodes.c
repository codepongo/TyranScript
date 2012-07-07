#include <tyranscript/tyran_opcodes.h>
#include <tyranscript/tyran_opcode_ids.h>

/* Opcodes */
struct tyran_opcodes* tyran_opcodes_new(int size)
{
	tyran_opcodes* codes = TYRAN_CALLOC(tyran_opcodes);
	codes->codes = TYRAN_MALLOC_TYPE(tyran_opcode, size);
	return codes;
}

void tyran_opcodes_free(struct tyran_opcodes* codes)
{
	tyran_free((void*)codes->codes);
	tyran_free(codes);
}

void tyran_opcodes_add_code(tyran_opcodes* codes, int code, int a, tyran_reg_or_constant_index x, tyran_reg_or_constant_index y)
{
	u32t raw = 0;

	raw |= y & 0x1ff;
	raw <<= 9;

	raw |= x & 0x1ff;
	raw <<= 8;

	raw |= a & 0xff;
	raw <<= 6;

	raw |= code & 0x3f;

	codes->codes[codes->code_len] = raw;
	codes->code_len++;
}


void tyran_opcodes_add_code_a_c(tyran_opcodes* codes, int code, tyran_reg_index a, tyran_constant_index c)
{
	tyran_opcodes_add_code(codes, code, a, c, 0);
}

void tyran_opcodes_add_code_a_x(tyran_opcodes* codes, int code, tyran_reg_index a, tyran_reg_index x)
{
	tyran_opcodes_add_code(codes, code, a, (tyran_reg_or_constant_index)x, (tyran_reg_or_constant_index)0);
}

void tyran_opcodes_add_code_a_x_y(tyran_opcodes* codes, int code, tyran_reg_index a, tyran_reg_or_constant_index x, tyran_reg_or_constant_index y)
{
	tyran_opcodes_add_code(codes, code, a, x, y);
}

/* Load values */
void tyran_opcodes_op_ld(tyran_opcodes* codes, tyran_reg_index a, tyran_reg_index x)
{
	tyran_opcodes_add_code_a_x(codes, TYRAN_OPCODE_LD, a, x);
}

void tyran_opcodes_op_ldc(tyran_opcodes* codes, tyran_reg_index a, tyran_constant_index c)
{
	tyran_opcodes_add_code_a_c(codes, TYRAN_OPCODE_LDC, a, c);
}

void tyran_opcodes_op_ldb(tyran_opcodes* codes, tyran_reg_index a, tyran_boolean boolean)
{
	tyran_opcodes_add_code_a_x(codes, TYRAN_OPCODE_LDB, a, (tyran_reg_or_constant_index) boolean);
}

void tyran_opcodes_op_ldn(tyran_opcodes* codes, tyran_reg_index a, int count)
{
	tyran_opcodes_add_code_a_x(codes, TYRAN_OPCODE_LDN, a, (tyran_reg_or_constant_index) count);
}

/* Arithmetic */
void tyran_opcodes_op_add(tyran_opcodes* codes, tyran_reg_index a, tyran_reg_or_constant_index x, tyran_reg_or_constant_index y)
{
	tyran_opcodes_add_code_a_x_y(codes, TYRAN_OPCODE_ADD, a, x, y);
}

void tyran_opcodes_op_div(tyran_opcodes* codes, tyran_reg_index a, tyran_reg_or_constant_index x, tyran_reg_or_constant_index y)
{
	tyran_opcodes_add_code_a_x_y(codes, TYRAN_OPCODE_DIV, a, x, y);
}

void tyran_opcodes_op_mod(tyran_opcodes* codes, tyran_reg_index a, tyran_reg_or_constant_index x, tyran_reg_or_constant_index y)
{
	tyran_opcodes_add_code_a_x_y(codes, TYRAN_OPCODE_MOD, a, x, y);
}

void tyran_opcodes_op_mul(tyran_opcodes* codes, tyran_reg_index a, tyran_reg_or_constant_index x, tyran_reg_or_constant_index y)
{
	tyran_opcodes_add_code_a_x_y(codes, TYRAN_OPCODE_MUL, a, x, y);
}

void tyran_opcodes_op_neg(tyran_opcodes* codes, tyran_reg_index a, tyran_reg_or_constant_index x)
{
	tyran_opcodes_add_code_a_x(codes, TYRAN_OPCODE_NEG, a, x);
}

void tyran_opcodes_op_not(tyran_opcodes* codes, tyran_reg_index a, tyran_reg_or_constant_index x)
{
	tyran_opcodes_add_code_a_x(codes, TYRAN_OPCODE_NOT, a, x);
}

void tyran_opcodes_op_pow(tyran_opcodes* codes, tyran_reg_index a, tyran_reg_or_constant_index x, tyran_reg_or_constant_index y)
{
	tyran_opcodes_add_code_a_x_y(codes, TYRAN_OPCODE_POW, a, x, y);
}

void tyran_opcodes_op_sub(tyran_opcodes* codes, tyran_reg_index a, tyran_reg_or_constant_index x, tyran_reg_or_constant_index y)
{
	tyran_opcodes_add_code_a_x_y(codes, TYRAN_OPCODE_SUB, a, x, y);
}

/* Branch */
void tyran_opcodes_op_jb(tyran_opcodes* codes, tyran_reg_index a, tyran_boolean boolean)
{
	tyran_opcodes_add_code_a_x(codes, TYRAN_OPCODE_JB, a, boolean);
}

void tyran_opcodes_op_jbld(tyran_opcodes* codes, tyran_reg_index a, tyran_reg_or_constant_index x, tyran_boolean boolean)
{
	tyran_opcodes_add_code_a_x_y(codes, TYRAN_OPCODE_JBLD, a, x, boolean);
}

void tyran_opcodes_op_jeq(tyran_opcodes* codes, tyran_reg_or_constant_index x, tyran_reg_or_constant_index y, tyran_boolean boolean)
{
	tyran_opcodes_add_code_a_x_y(codes, TYRAN_OPCODE_JEQ, boolean, x, y);
}

void tyran_opcodes_op_jlt(tyran_opcodes* codes, tyran_reg_or_constant_index x, tyran_reg_or_constant_index y, tyran_boolean boolean)
{
	tyran_opcodes_add_code_a_x_y(codes, TYRAN_OPCODE_JLT, boolean, x, y);
}

void tyran_opcodes_op_jle(tyran_opcodes* codes, tyran_reg_or_constant_index x, tyran_reg_or_constant_index y, tyran_boolean boolean)
{
	tyran_opcodes_add_code_a_x_y(codes, TYRAN_OPCODE_JLE, boolean, x, y);
}

void tyran_opcodes_op_jmp(tyran_opcodes* codes, int pc)
{
	tyran_opcodes_add_code_a_x_y(codes, TYRAN_OPCODE_JMP, pc, 0, 0);
}

/* Call stack */
void tyran_opcodes_op_ret(tyran_opcodes* codes)
{
	tyran_opcodes_add_code_a_x_y(codes, TYRAN_OPCODE_RET, 0, 0, 0);
}

void tyran_opcodes_op_call(tyran_opcodes* codes, tyran_reg_index a, int s, int s2)
{
	tyran_opcodes_add_code_a_x_y(codes, TYRAN_OPCODE_CALL, a, s, s2);
}

/* Object */
void tyran_opcodes_op_new(tyran_opcodes* codes, tyran_reg_index a)
{
	tyran_opcodes_add_code_a_x_y(codes, TYRAN_OPCODE_NEW, a, 0, 0);
}

void tyran_opcodes_op_set(tyran_opcodes* codes, tyran_reg_index a, tyran_reg_or_constant_index x, tyran_reg_or_constant_index y)
{
	tyran_opcodes_add_code_a_x_y(codes, TYRAN_OPCODE_SET, a, x, y);
}

void tyran_opcodes_op_get(tyran_opcodes* codes, tyran_reg_index a, tyran_reg_index r, tyran_reg_or_constant_index y)
{
	tyran_opcodes_add_code_a_x_y(codes, TYRAN_OPCODE_GET, a, r, y);
}
