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

void tyran_opcodes_add_code(tyran_opcodes* codes, int code)
{
	code = code & 0x3f;
	codes->codes[codes->code_len] = code;
	codes->code_len++;
}

/* Load values */
void tyran_opcodes_op_ld(tyran_opcodes* codes, tyran_reg_index a, tyran_reg_index x)
{
	tyran_opcodes_add_code(codes, TYRAN_OPCODE_LD);
}

void tyran_opcodes_op_ldc_string(tyran_opcodes* codes, tyran_reg_index a, tyran_string* str)
{

}

void tyran_opcodes_op_ldc_number(tyran_opcodes* codes, tyran_reg_index a, tyran_number v)
{

}

void tyran_opcodes_op_ldc_boolean(tyran_opcodes* codes, tyran_reg_index a, int boolean)
{

}

void tyran_opcodes_op_ldc_null(tyran_opcodes* codes, tyran_reg_index a)
{

}

void tyran_opcodes_op_ldb(tyran_opcodes* codes, tyran_reg_index a, int boolean)
{

}

void tyran_opcodes_op_ldn(tyran_opcodes* codes, tyran_reg_index a, int count)
{

}

/* Arithmetic */
void tyran_opcodes_op_add(tyran_opcodes* codes, tyran_reg_index a, tyran_reg_or_constant_index x, tyran_reg_or_constant_index y)
{

}

void tyran_opcodes_op_div(tyran_opcodes* codes, tyran_reg_index a, tyran_reg_or_constant_index x, tyran_reg_or_constant_index y)
{

}

void tyran_opcodes_op_mod(tyran_opcodes* codes, tyran_reg_index a, tyran_reg_or_constant_index x, tyran_reg_or_constant_index y)
{

}

void tyran_opcodes_op_mul(tyran_opcodes* codes, tyran_reg_index a, tyran_reg_or_constant_index x, tyran_reg_or_constant_index y)
{

}

void tyran_opcodes_op_neg(tyran_opcodes* codes, tyran_reg_index a, tyran_reg_or_constant_index x)
{

}

void tyran_opcodes_op_not(tyran_opcodes* codes, tyran_reg_index a, tyran_reg_or_constant_index x)
{

}

void tyran_opcodes_op_pow(tyran_opcodes* codes, tyran_reg_index a, tyran_reg_or_constant_index x, tyran_reg_or_constant_index y)
{
}

void tyran_opcodes_op_sub(tyran_opcodes* codes, tyran_reg_index a, tyran_reg_or_constant_index x, tyran_reg_or_constant_index y)
{

}

/* Branch */
void tyran_opcodes_op_jb(tyran_opcodes* codes, tyran_reg_index y, int boolean)
{

}

void tyran_opcodes_op_jbld(tyran_opcodes* codes, tyran_reg_index a, tyran_reg_index y, int boolean)
{

}

void tyran_opcodes_op_jeq(tyran_opcodes* codes, tyran_reg_or_constant_index x, tyran_reg_or_constant_index y, int boolean)
{

}

void tyran_opcodes_op_jlt(tyran_opcodes* codes, tyran_reg_or_constant_index x, tyran_reg_or_constant_index y, int boolean)
{

}

void tyran_opcodes_op_jle(tyran_opcodes* codes, tyran_reg_or_constant_index x, tyran_reg_or_constant_index y, int boolean)
{

}

void tyran_opcodes_op_jmp(tyran_opcodes* codes, int pc)
{

}

/* Call stack */
void tyran_opcodes_op_ret(tyran_opcodes* codes)
{

}

void tyran_opcdoes_op_call(tyran_opcodes* codes)
{

}

/* Object */
void tyran_opcodes_op_new(tyran_opcodes* codes)
{

}

void tyran_opcodes_op_set(tyran_opcodes* codes)
{

}

void tyran_opcodes_op_get(tyran_opcodes* codes)
{

}
