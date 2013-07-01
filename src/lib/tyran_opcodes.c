#include <tyranscript/tyran_opcodes.h>
#include <tyranscript/tyran_opcode_ids.h>

int tyran_opcodes_is_constant(tyran_reg_or_constant_index index)
{
	return index >= TYRAN_OPCODE_CONSTANT_BIT;
}

/* Opcodes */
struct tyran_opcodes* tyran_opcodes_new(tyran_memory_pool* opcodes_pool, tyran_memory* memory, int size) {
	tyran_opcodes* codes = TYRAN_CALLOC_TYPE(opcodes_pool, tyran_opcodes);
	codes->codes = TYRAN_MALLOC_NO_POOL_TYPE_COUNT(memory, tyran_opcode, size);
	return codes;
}

void tyran_opcodes_free(struct tyran_opcodes* codes)
{
	TYRAN_MALLOC_FREE((void*)codes->codes);
	TYRAN_MALLOC_FREE(codes);
}

void tyran_opcodes_add_code(tyran_opcodes* codes, int code, int a, tyran_reg_or_constant_index x, tyran_reg_or_constant_index y, int b)
{
	u32t raw = 0;

	raw |= (b ? 0x01 : 0);

	raw <<= 9;
	raw |= y & 0x1ff;

	raw <<= 9;
	raw |= x & 0x1ff;

	raw <<= 8;
	raw |= a & 0xff;

	raw <<= 5;
	raw |= code & 0x1f;

	codes->codes[codes->code_len] = raw;
	codes->code_len++;
}


void tyran_opcodes_add_code_a_c(tyran_opcodes* codes, int code, tyran_reg_index a, tyran_constant_index c)
{
	TYRAN_ASSERT(a != TYRAN_OPCODE_REGISTER_ILLEGAL, "Illegal register in a");
	TYRAN_ASSERT(c != TYRAN_OPCODE_REGISTER_ILLEGAL, "Illegal register in a");
	tyran_opcodes_add_code(codes, code, a, c, 0, 0);
}

void tyran_opcodes_add_code_a_x(tyran_opcodes* codes, int code, tyran_reg_index a, tyran_reg_or_constant_index x)
{
	TYRAN_ASSERT(a != TYRAN_OPCODE_REGISTER_ILLEGAL, "Illegal register in a");
	TYRAN_ASSERT(x != TYRAN_OPCODE_REGISTER_ILLEGAL, "Illegal register in x");
	tyran_opcodes_add_code(codes, code, a, x, (tyran_reg_or_constant_index)0, 0);
}

void tyran_opcodes_add_code_a_x_y(tyran_opcodes* codes, int code, tyran_reg_index a, tyran_reg_or_constant_index x, tyran_reg_or_constant_index y)
{
	TYRAN_ASSERT(a != TYRAN_OPCODE_REGISTER_ILLEGAL, "Illegal register in a");
	TYRAN_ASSERT(x != TYRAN_OPCODE_REGISTER_ILLEGAL, "Illegal register in x");
	TYRAN_ASSERT(x != TYRAN_OPCODE_REGISTER_ILLEGAL, "Illegal register in y");
	tyran_opcodes_add_code(codes, code, a, x, y, 0);
}

/* Load values */
void tyran_opcodes_op_ld(tyran_opcodes* codes, tyran_reg_index a, tyran_reg_index x)
{
	if (a == x) {
		return;
	}
	tyran_opcodes_add_code_a_x(codes, TYRAN_OPCODE_LD, a, x);
}

void tyran_opcodes_modify_branch(tyran_opcode* code, int position)
{
	u16t br = (position + 0x8000);
	u32t mask = ~(0xffff << 5);
	*code = (*code & mask) | (br << 5);
}

void tyran_opcodes_op_ldc(tyran_opcodes* codes, tyran_reg_index a, tyran_constant_index c)
{
	tyran_opcodes_add_code_a_c(codes, TYRAN_OPCODE_LDC, a, c);
}

void tyran_opcodes_op_ldcn(tyran_opcodes* codes, tyran_reg_index a, tyran_constant_index c)
{
	tyran_opcodes_add_code_a_c(codes, TYRAN_OPCODE_LDCU, a, c);
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

void tyran_opcodes_op_index(tyran_opcodes* codes, tyran_reg_index a, tyran_reg_or_constant_index x, tyran_reg_or_constant_index y)
{
	tyran_opcodes_add_code_a_x_y(codes, TYRAN_OPCODE_INDEX, a, x, y);
}

void tyran_opcodes_op_index_set(tyran_opcodes* codes, tyran_reg_index a, tyran_reg_or_constant_index x, tyran_reg_or_constant_index y)
{
	tyran_opcodes_add_code_a_x_y(codes, TYRAN_OPCODE_INDEX_SET, a, x, y);
}

void tyran_opcodes_op_iter(tyran_opcodes* codes, tyran_reg_index a, tyran_reg_or_constant_index x)
{
	tyran_opcodes_add_code_a_x_y(codes, TYRAN_OPCODE_ITER, a, x, 0);
}

void tyran_opcodes_op_next(tyran_opcodes* codes, tyran_reg_index a, tyran_reg_or_constant_index x)
{
	tyran_opcodes_add_code_a_x_y(codes, TYRAN_OPCODE_NEXT, a, x, 0);
}

/* Branch */

void tyran_opcodes_op_eq(tyran_opcodes* codes, tyran_reg_index a, tyran_reg_or_constant_index x, tyran_reg_or_constant_index y, int b)
{
	TYRAN_LOG("jeq. b:%d", b);
	tyran_opcodes_add_code(codes, TYRAN_OPCODE_EQ, a, x, y, b);
}

void tyran_opcodes_op_lt(tyran_opcodes* codes, tyran_reg_index a, tyran_reg_or_constant_index x, tyran_reg_or_constant_index y, int b)
{
	tyran_opcodes_add_code(codes, TYRAN_OPCODE_LT, a, x, y, b);
}

void tyran_opcodes_op_le(tyran_opcodes* codes, tyran_reg_index a, tyran_reg_or_constant_index x, tyran_reg_or_constant_index y, int b)
{
	tyran_opcodes_add_code(codes, TYRAN_OPCODE_LE, a, x, y, b);
}

void tyran_opcodes_op_jb(tyran_opcodes* codes, tyran_reg_or_constant_index x, int b)
{
	tyran_opcodes_add_code_a_x_y(codes, TYRAN_OPCODE_JB, b, x, 0);
}

void tyran_opcodes_op_jbld(tyran_opcodes* codes, tyran_reg_index a, tyran_reg_or_constant_index x, int b)
{
	tyran_opcodes_add_code_a_x_y(codes, TYRAN_OPCODE_JBLD, a, x, b);
}

void tyran_opcodes_op_jmp(tyran_opcodes* codes, int pc)
{
	TYRAN_ASSERT(pc >= 0, "Wrong pc:%d", pc);
	tyran_opcodes_add_code_a_x_y(codes, TYRAN_OPCODE_JMP, 0, 0, 0);
	tyran_opcodes_modify_branch(&codes->codes[codes->code_len-1], pc);
}

/* Call stack */
void tyran_opcodes_op_ret(tyran_opcodes* codes, tyran_reg_index a, int s)
{
	tyran_opcodes_add_code_a_x_y(codes, TYRAN_OPCODE_RET, a, s, 0);
}

void tyran_opcodes_op_call(tyran_opcodes* codes, tyran_reg_index a, int argument_count, int return_value_count)
{
	tyran_opcodes_add_code_a_x_y(codes, TYRAN_OPCODE_CALL, a, argument_count, return_value_count);
}

/* Object */
void tyran_opcodes_op_func(tyran_opcodes* codes, tyran_reg_index a, tyran_reg_or_constant_index x)
{
	tyran_opcodes_add_code_a_x_y(codes, TYRAN_OPCODE_FUNC, a, x, 0);
}

void tyran_opcodes_op_new(tyran_opcodes* codes, tyran_reg_index a, int argument_count, int return_value_count)
{
	tyran_opcodes_add_code_a_x_y(codes, TYRAN_OPCODE_NEW, a, argument_count, return_value_count);
}

void tyran_opcodes_op_set(tyran_opcodes* codes, tyran_reg_index a, tyran_reg_or_constant_index x, tyran_reg_or_constant_index y)
{
	tyran_opcodes_add_code_a_x_y(codes, TYRAN_OPCODE_SET, a, x, y);
}

void tyran_opcodes_op_get(tyran_opcodes* codes, tyran_reg_index a, tyran_reg_index r, tyran_reg_or_constant_index y)
{
	tyran_opcodes_add_code_a_x_y(codes, TYRAN_OPCODE_GET, a, r, y);
}
