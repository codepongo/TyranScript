#ifndef _TYRAN_OPCODES_H
#define _TYRAN_OPCODES_H

#include <tyranscript/tyran_config.h>

static const u16t TYRAN_OPCODE_CONSTANT_BIT = 0x100;
static const u16t TYRAN_OPCODE_REGISTER_MASK = 0xff;
static const u8t TYRAN_OPCODE_REGISTER_ILLEGAL = 0xff;

typedef u32t tyran_opcode;
typedef u8t tyran_reg_index;
typedef u16t tyran_reg_or_constant_index;
typedef u16t tyran_constant_index;

int tyran_opcodes_is_constant(tyran_reg_or_constant_index index);

struct tyran_function;

typedef struct tyran_opcodes {
	tyran_opcode* codes;
	int code_len;
	int code_size;
} tyran_opcodes;

/* Opcodes */
struct tyran_opcodes* tyran_opcodes_new(tyran_memory_pool* opcode_pool, tyran_memory* memory, int size);
void tyran_opcodes_free(struct tyran_opcodes* codes);

void tyran_opcodes_modify_branch(tyran_opcode* code, int position);

/* Load values */
void tyran_opcodes_op_ld(tyran_opcodes* codes, tyran_reg_index a, tyran_reg_index x);
void tyran_opcodes_op_ldc(tyran_opcodes* codes, tyran_reg_index a, tyran_constant_index c);
void tyran_opcodes_op_ldcn(tyran_opcodes* codes, tyran_reg_index a, tyran_constant_index c);

/* Arithmetic */
void tyran_opcodes_op_add(tyran_opcodes* codes, tyran_reg_index a, tyran_reg_or_constant_index x, tyran_reg_or_constant_index y);
void tyran_opcodes_op_div(tyran_opcodes* codes, tyran_reg_index a, tyran_reg_or_constant_index x, tyran_reg_or_constant_index y);
void tyran_opcodes_op_mod(tyran_opcodes* codes, tyran_reg_index a, tyran_reg_or_constant_index x, tyran_reg_or_constant_index y);
void tyran_opcodes_op_mul(tyran_opcodes* codes, tyran_reg_index a, tyran_reg_or_constant_index x, tyran_reg_or_constant_index y);
void tyran_opcodes_op_neg(tyran_opcodes* codes, tyran_reg_index a, tyran_reg_or_constant_index x);
void tyran_opcodes_op_not(tyran_opcodes* codes, tyran_reg_index a, tyran_reg_or_constant_index x);
void tyran_opcodes_op_pow(tyran_opcodes* codes, tyran_reg_index a, tyran_reg_or_constant_index x, tyran_reg_or_constant_index y);
void tyran_opcodes_op_sub(tyran_opcodes* codes, tyran_reg_index a, tyran_reg_or_constant_index x, tyran_reg_or_constant_index y);
void tyran_opcodes_op_index(tyran_opcodes* codes, tyran_reg_index a, tyran_reg_or_constant_index x, tyran_reg_or_constant_index y);
void tyran_opcodes_op_index_set(tyran_opcodes* codes, tyran_reg_index a, tyran_reg_or_constant_index x, tyran_reg_or_constant_index y);
void tyran_opcodes_op_iter(tyran_opcodes* codes, tyran_reg_index a, tyran_reg_or_constant_index x);
void tyran_opcodes_op_next(tyran_opcodes* codes, tyran_reg_index a, tyran_reg_or_constant_index x);

void tyran_opcodes_op_eq(tyran_opcodes* codes, tyran_reg_index a, tyran_reg_or_constant_index x, tyran_reg_or_constant_index y, int boolean);
void tyran_opcodes_op_lt(tyran_opcodes* codes, tyran_reg_index a, tyran_reg_or_constant_index x, tyran_reg_or_constant_index y, int boolean);
void tyran_opcodes_op_le(tyran_opcodes* codes, tyran_reg_index a, tyran_reg_or_constant_index x, tyran_reg_or_constant_index y, int boolean);

/* Branch */
void tyran_opcodes_op_jbld(tyran_opcodes* codes, tyran_reg_index a, tyran_reg_or_constant_index x, int b);
void tyran_opcodes_op_jb(tyran_opcodes* codes, tyran_reg_or_constant_index x, int b);
void tyran_opcodes_op_jmp(tyran_opcodes* codes, int pc);

/* Call stack */
void tyran_opcodes_op_ret(tyran_opcodes* codes, tyran_reg_index, int s);
void tyran_opcodes_op_call(tyran_opcodes* codes, tyran_reg_index, int s, int s2);
void tyran_opcodes_op_new(tyran_opcodes* codes, tyran_reg_index a, int argument_count, int return_value_count);

/* Object */
void tyran_opcodes_op_func(tyran_opcodes* codes, tyran_reg_index a, tyran_reg_or_constant_index x);

void tyran_opcodes_op_set(tyran_opcodes* codes, tyran_reg_index a, tyran_reg_or_constant_index x, tyran_reg_or_constant_index y);
void tyran_opcodes_op_get(tyran_opcodes* codes, tyran_reg_index a, tyran_reg_index r, tyran_reg_or_constant_index y);

#endif
