#ifndef _TYRAN_RUNTIME_STACK_H
#define _TYRAN_RUNTIME_STACK_H

#include <tyranscript/tyran_value.h>
#include <tyranscript/tyran_opcodes.h>
#include <tyranscript/tyran_constants.h>

struct tyran_opcodes;
struct tyran_scope_stack;

typedef struct tyran_runtime_stack {
	const tyran_opcodes* opcodes;
	const tyran_opcode* pc;

	const tyran_constants* constants;
	const tyran_value* c;

	tyran_value* r;

	tyran_value* return_register;

	tyran_value _this;
} tyran_runtime_stack;

tyran_runtime_stack* tyran_runtime_stack_new();

#endif
