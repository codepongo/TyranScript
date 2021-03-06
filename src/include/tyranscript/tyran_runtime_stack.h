#ifndef _TYRAN_RUNTIME_STACK_H
#define _TYRAN_RUNTIME_STACK_H

#include <tyranscript/tyran_value.h>

struct tyran_opcodes;
struct tyran_opcode;
struct tyran_scope_stack;

typedef struct tyran_runtime_stack {
	const struct tyran_opcodes* opcodes;
	struct tyran_scope_stack* scope;
	tyran_value function_scope;
	tyran_value _this;
	const struct tyran_opcode* ip;
} tyran_runtime_stack;

tyran_runtime_stack* tyran_runtime_stack_new();

#endif
