#ifndef _TYRAN_RUNTIME_H
#define _TYRAN_RUNTIME_H

#include <tyranscript/tyran_symbol.h>

struct tyran_opcodes;
struct tyran_scope_stack;
struct tyran_runtime;
struct tyran_runtime_stack;
struct tyran_constants;
struct tyran_value;
struct tyran_object;
struct tyran_memory_pool;
struct tyran_symbol_table;
struct tyran_function;

#define TYRAN_RUNTIME_CALL_FUNC(NAME) static int NAME(struct tyran_runtime* runtime, tyran_value* func, tyran_value* arguments, int argument_count, tyran_value* self, tyran_value* return_value, int is_constructor)

typedef void (*tyran_value_delete_callback)(const struct tyran_runtime* program_specific_context, struct tyran_object* program_specific);

typedef struct tyran_runtime {
	struct tyran_runtime_stack* stack;
	tyran_value_delete_callback delete_callback;
	int stack_pointer;
	void* program_specific_context;

	const struct tyran_object_key* length_key;
	const struct tyran_object_key* prototype_key;


	struct tyran_object* _string_class;
	struct tyran_object* _array_class;
	struct tyran_object* _object_class;
	struct tyran_object* _range_class;
	struct tyran_object* _range_iterator_class;
	struct tyran_object* _array_iterator_class;

	struct tyran_value* registers;

	struct tyran_value* global;

	struct tyran_memory* memory;
	struct tyran_memory_pool* string_pool;
	struct tyran_memory_pool* object_key_pool;
	struct tyran_memory_pool* function_pool;
	struct tyran_memory_pool* function_object_pool;
	struct tyran_memory_pool* iterator_pool;
	struct tyran_memory_pool* object_pool;
	struct tyran_memory_pool* value_pool;
	struct tyran_memory_pool* array_node_pool;
	struct tyran_memory_pool* runtime_stack_pool;

	struct tyran_symbol_table* symbol_table;

	tyran_symbol binary_operator_symbols[32];

} tyran_runtime;

struct tyran_runtime_callbacks;

tyran_runtime* tyran_runtime_new(struct tyran_memory_pool* runtime_pool, struct tyran_memory* memory, struct tyran_memory_pool* string_pool, struct tyran_memory_pool* object_key_pool, struct tyran_memory_pool* object_iterator_pool, struct tyran_memory_pool* function_pool, struct tyran_memory_pool* function_object_pool, struct tyran_memory_pool* runtime_stack_pool, struct tyran_memory_pool* object_pool, struct tyran_memory_pool* value_registers_pool, struct tyran_memory_pool* value_pool, struct tyran_memory_pool* array_node_pool);
void tyran_runtime_free(tyran_runtime* rt);
void tyran_runtime_execute(tyran_runtime* runtime, struct tyran_value* return_value, const struct tyran_runtime_callbacks* callbacks);
void tyran_runtime_push_call(tyran_runtime* rt, const struct tyran_opcodes* opcodes, const struct tyran_constants* constants, const struct tyran_value* _this);
void tyran_runtime_push_call_ex(tyran_runtime* rt, const struct tyran_function* func, const struct tyran_value* _this);

#define tyran_runtime_context(RUNTIME) (RUNTIME->global)

#endif
