#ifndef _TYRAN_RUNTIME_STACK_H
#define _TYRAN_RUNTIME_STACK_H

struct tyran_opcodes;
struct tyran_scope_stack;
struct tyran_value;

#include <tyranscript/tyran_opcodes.h>
#include <tyranscript/tyran_value.h>

typedef struct tyran_runtime_stack {
	const struct tyran_opcodes* opcodes;
	const tyran_opcode* pc;

	const struct tyran_constants* constants;
	const struct tyran_value* c;

	struct tyran_value* r;
	struct tyran_value* return_register;

	int argument_count;

	struct tyran_value _this;
} tyran_runtime_stack;

tyran_runtime_stack* tyran_runtime_stack_new(tyran_memory_pool* runtime_stack_pool);

#endif
