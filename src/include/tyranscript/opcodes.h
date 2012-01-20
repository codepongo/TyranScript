#ifndef TYRAN_OPCODES_H
#define TYRAN_OPCODES_H

#include <tyranscript/opcode_ids.h>
#include <tyranscript/opcode_enums.h>

typedef struct tyran_opcode {
	tyran_opcode_id opcode;
	union dd
	{
		void *data;
		int idata;
	} dd;
} tyran_opcode;

typedef struct tyran_opcodes {
	tyran_opcode* codes;
	int code_len;
	int code_size;

	int expression_count;
	enum tyran_assign_mode lvalue_flag;
	const unicode_char *lvalue_name;
} tyran_opcodes;

typedef struct tyran_jump_pop_info
{
	int offset;
	int pop_count;
} tyran_jump_pop_info;

typedef struct tyran_variable_name_info {
	struct {
		const unicode_char* varname;
		struct tyran_value* lval;
	} var;
} tyran_variable_name_info;

#endif
