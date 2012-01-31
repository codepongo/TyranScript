#ifndef _TYRAN_FUNCTION_OBJECT_H
#define _TYRAN_FUNCTION_OBJECT_H

#include "tyran_function.h"

struct tyran_scope_stack;
struct tyran_value;

typedef struct tyran_function_object {
	const struct tyran_function* static_function;
	struct tyran_scope_stack* scope;
} tyran_function_object;

tyran_function_object* tyran_function_object_new(const tyran_function* function);
struct tyran_value* tyran_function_object_new_callback(tyran_function_callback callback);
void tyran_function_object_free(tyran_function_object* function_object);

#endif
