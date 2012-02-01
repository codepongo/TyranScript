#ifndef _TYRAN_FUNCTION_H
#define _TYRAN_FUNCTION_H

struct tyran_runtime;
struct tyran_value;
struct tyran_opcodes;
struct tyran_string_array;

typedef int (*tyran_function_callback)(struct tyran_runtime* runtime, struct tyran_value* function, struct tyran_value* arguments, struct tyran_value* _this, struct tyran_value* return_value, int is_new_call);

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

	const struct tyran_string_array* argument_names;
	const struct tyran_string_array* local_variable_names;
} tyran_function;

tyran_function* tyran_function_new(const struct tyran_string_array* argument_names, const struct tyran_string_array* local_variable_names, const struct tyran_opcodes* opcodes);
tyran_function* tyran_function_callback_new(tyran_function_callback callback);

#endif
