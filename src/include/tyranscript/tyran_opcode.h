#ifndef _TYRAN_OPCODE_H
#define _TYRAN_OPCODE_H

struct tyran_string;
struct tyran_value;

typedef struct tyran_jump_pop_info {
	int offset;
	int pop_count;
} tyran_jump_pop_info;

typedef struct tyran_variable_name_info {
	struct {
		const struct tyran_string* variable_name;
		struct tyran_value* variable;
	} data;
} tyran_variable_name_info;

#endif

