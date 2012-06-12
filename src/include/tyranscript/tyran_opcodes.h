#ifndef _TYRAN_OPCODES_H
#define _TYRAN_OPCODES_H

#include <tyranscript/tyran_opcode_enums.h>
#include <tyranscript/tyran_string.h>

struct tyran_function;
typedef u32t tyran_opcode;
typedef u8t tyran_reg_index;

typedef struct tyran_opcodes {
	const tyran_opcode* codes;
	int code_len;
	int code_size;

	int expression_count;
	enum tyran_assign_mode lvalue_flag;
	const tyran_string* lvalue_name;
} tyran_opcodes;

/* Opcodes */
struct tyran_opcodes* tyran_opcodes_new(int size);
void tyran_opcodes_free(struct tyran_opcodes* codes);

/* Load values */
void tyran_opcodes_op_ld(tyran_reg_index a, tyran_reg_index x);
void tyran_opcodes_op_ldc_string(tyran_reg_index a, tyran_string* str);
void tyran_opcodes_op_ldc_number(tyran_reg_index a, tyran_number v);
void tyran_opcodes_op_ldc_boolean(tyran_reg_index a, int boolean);
void tyran_opcodes_op_ldc_null(tyran_reg_index a);
void tyran_opcodes_op_ldb(tyran_reg_index a, int boolean);
void tyran_opcodes_op_ldn(tyran_reg_index);

/* Arithmetic */
void tyran_opcodes_op_add(tyran_reg_index a, tyran_reg_index x, int x_constant, tyran_reg_index y, int y_constant);
void tyran_opcodes_op_div(tyran_reg_index a, tyran_reg_index x, int x_constant, tyran_reg_index y, int y_constant);
void tyran_opcodes_op_mod(tyran_reg_index a, tyran_reg_index x, int x_constant, tyran_reg_index y, int y_constant);
void tyran_opcodes_op_mul(tyran_reg_index a, tyran_reg_index x, int x_constant, tyran_reg_index y, int y_constant);
void tyran_opcodes_op_neg(tyran_reg_index a, tyran_reg_index x, int x_constant, tyran_reg_index y, int y_constant);
void tyran_opcodes_op_not(tyran_reg_index a, tyran_reg_index x, int x_constant);
void tyran_opcodes_op_pow(tyran_reg_index a, tyran_reg_index x, int x_constant, tyran_reg_index y, int y_constant);
void tyran_opcodes_op_sub(tyran_reg_index a, tyran_reg_index x, int x_constant, tyran_reg_index y, int y_constant);

/* Branch */
void tyran_opcodes_op_jb(tyran_reg_index y, int boolean);
void tyran_opcodes_op_jbld(tyran_reg_index a, tyran_reg_index y, int boolean);
void tyran_opcodes_op_jeq(tyran_reg_index x, int x_constant, tyran_reg_index y, int y_constant, int boolean, int pc);
void tyran_opcodes_op_jlt(tyran_reg_index x, int x_constant, tyran_reg_index y, int y_constant, int boolean, int pc);
void tyran_opcodes_op_jle(tyran_reg_index x, int x_constant, tyran_reg_index y, int y_constant, int boolean, int pc);
void tyran_opcodes_op_jmp(int pc);

/* Call stack */
void tyran_opcodes_op_ret();
void tyran_opcdoes_op_call();

/* Object */
void tyran_opcodes_op_new();
void tyran_opcodes_op_set();
void tyran_opcodes_op_get();


#endif
