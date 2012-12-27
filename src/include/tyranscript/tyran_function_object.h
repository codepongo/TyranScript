#ifndef _TYRAN_FUNCTION_OBJECT_H
#define _TYRAN_FUNCTION_OBJECT_H

#include <tyranscript/tyran_function_callback.h>

struct tyran_function;
struct tyran_scope_stack;
struct tyran_value;
struct tyran_runtime;
struct tyran_memory_pool;

typedef struct tyran_function_object {
	const struct tyran_function* static_function;
	struct tyran_scope_stack* scope;
} tyran_function_object;

#define TYRAN_MEMBER(TARGET, NAME, FUNC) { \
	tyran_value* function_object = tyran_function_object_new_callback(runtime, FUNC); \
	tyran_value_object_insert_c_string_key(runtime, TARGET, NAME, function_object); \
	}

tyran_function_object* tyran_function_object_new(struct tyran_memory_pool* function_object_pool, const struct tyran_function* function);
struct tyran_value* tyran_function_object_new_callback(const struct tyran_runtime* runtime, tyran_function_callback callback);
void tyran_function_object_free(tyran_function_object* function_object);

#endif
