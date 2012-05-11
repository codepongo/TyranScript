#ifndef _TYRAN_OPCODE_H
#define _TYRAN_OPCODE_H

#include <tyranscript/tyran_opcode_ids.h>
#include <tyranscript/tyran_string.h>

typedef struct tyran_jump_pop_info {
	int offset;
	int pop_count;
} tyran_jump_pop_info;

typedef struct tyran_variable_name_info {
	struct {
		const tyran_string* variable_name;
		struct tyran_value* variable;
	} data;
} tyran_variable_name_info;

#endif

