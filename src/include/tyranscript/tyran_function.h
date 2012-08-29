#ifndef _TYRAN_FUNCTION_H
#define _TYRAN_FUNCTION_H

#include <tyranscript/tyran_function_callback.h>

struct tyran_runtime;
struct tyran_value;
struct tyran_opcodes;
struct tyran_string_array;
struct tyran_constants;
struct tyran_memory_pool;

typedef enum {
	tyran_function_type_normal,
	tyran_function_type_callback
} tyran_function_type;

typedef struct tyran_function {
	tyran_function_type type;

	union {
		const struct tyran_opcodes* opcodes;
		tyran_function_callback callback;
	} data;

	const struct tyran_constants* constants;
} tyran_function;

tyran_function* tyran_function_new(struct tyran_memory_pool* function_pool, const struct tyran_opcodes* opcodes, const struct tyran_constants* constants);
tyran_function* tyran_function_callback_new(struct tyran_memory_pool* function_pool, tyran_function_callback callback);

#endif
