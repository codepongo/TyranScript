#ifndef _TYRAN_RUNTIME_H
#define _TYRAN_RUNTIME_H

#include "tyran_value.h"

struct tyran_opcodes;
struct tyran_scope_stack;
struct tyran_runtime;

typedef void (*tyran_value_delete_callback)(void* program_specific_context, tyran_object* program_specific);

typedef struct tyran_runtime {
	tyran_value stack[8192];
	tyran_value_delete_callback delete_callback;
	int stack_pointer;
	void* program_specific_context;
} tyran_runtime;

struct tyran_runtime_callbacks;

tyran_runtime* tyran_runtime_new();
void tyran_runtime_free(tyran_runtime* rt);
void tyran_runtime_execute(tyran_runtime* runtime, struct tyran_value* return_value, const struct tyran_runtime_callbacks* callbacks);
void tyran_runtime_push_call(tyran_runtime* rt, const struct tyran_opcodes* opcodes, struct tyran_scope_stack* scope, struct tyran_value* function_scope, const struct tyran_value* _this);


#endif
