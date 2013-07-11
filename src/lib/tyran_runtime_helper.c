#include <tyranscript/tyran_value.h>
#include <tyranscript/tyran_value_object.h>
#include <tyranscript/tyran_object.h>
#include <tyranscript/tyran_runtime.h>

#include <tyranscript/tyran_runtime_stack.h>
#include <tyranscript/tyran_opcodes.h>
#include <tyranscript/tyran_opcode.h>
#include <tyranscript/tyran_prototypes.h>

#include <tyranscript/debug/tyran_print_value.h>
#include <tyranscript/debug/tyran_print_opcodes.h>
#include <tyranscript/tyran_constants.h>
#include <tyranscript/tyran_string.h>
#include <tyranscript/tyran_object_macros.h>
#include <tyranscript/tyran_symbol_table.h>
#include <tyranscript/tyran_function.h>


void tyran_runtime_setup_binary_operators(tyran_runtime* rt)
{
	const char* binary_strings[] = {"+", "-", "%", "*", "^", "-", "[]", "[]=", "==", "<", "<=", "iter", "++"};

	for (size_t i=0; i<sizeof(binary_strings) / sizeof(char*); ++i) {
		tyran_symbol_table_add(rt->symbol_table, &rt->binary_operator_symbols[i], binary_strings[i]);
	}
}

tyran_runtime* tyran_runtime_new(tyran_memory_pool* runtime_pool, tyran_memory* memory, tyran_memory_pool* string_pool, tyran_memory_pool* object_key_pool, tyran_memory_pool* object_iterator_pool, tyran_memory_pool* function_pool, tyran_memory_pool* function_object_pool, tyran_memory_pool* runtime_stack_pool, tyran_memory_pool* object_pool, tyran_memory_pool* registers_value_pool, tyran_memory_pool* value_pool, tyran_memory_pool* array_node_pool)
{
	tyran_runtime* rt = TYRAN_CALLOC_TYPE(runtime_pool, tyran_runtime);

	rt->stack = TYRAN_MALLOC_NO_POOL_TYPE_COUNT(memory, tyran_runtime_stack, 128);
	rt->registers = TYRAN_MALLOC_NO_POOL_TYPE_COUNT(memory, tyran_value, 1024);
	rt->object_key_pool = object_key_pool;
	rt->function_pool = function_pool;
	rt->function_object_pool = function_object_pool;
	rt->iterator_pool = object_iterator_pool;
	rt->object_pool = object_pool;
	rt->string_pool = string_pool;
	rt->memory = memory;
	rt->symbol_table = tyran_symbol_table_new(memory);
	rt->value_pool = value_pool;
	rt->array_node_pool = array_node_pool;
	rt->runtime_stack_pool = runtime_stack_pool;
	rt->global = TYRAN_CALLOC_TYPE(value_pool, tyran_value);
	rt->delete_callback = 0;

	tyran_runtime_setup_binary_operators(rt);

	tyran_object* global_object = tyran_object_new(rt);
	tyran_value_set_object(*rt->global, global_object);

	tyran_prototypes_init(rt, rt->global);

	// rt->length_key = tyran_object_key_new(object_pool, tyran_string_from_c_str("length"), tyran_object_key_flag_normal);
	// rt->prototype_key = tyran_object_key_new(object_pool, tyran_string_from_c_str("prototype"), tyran_object_key_flag_normal);

	return rt;
}



void tyran_runtime_free(tyran_runtime* rt)
{
	tyran_free(rt);
}

void tyran_runtime_push_call(tyran_runtime* rt, const struct tyran_opcodes* opcodes, const struct tyran_constants* constants, const struct tyran_value* _this)
{
	/* Save return state */
	tyran_runtime_stack* runtime_info = tyran_runtime_stack_new(rt->runtime_stack_pool);
	tyran_value_copy(runtime_info->_this, *_this);
	// tyran_value_copy(runtime_info->function_scope, *function_scope);
	// runtime_info->scope = scope;
	runtime_info->constants = constants;
	runtime_info->c = constants->values;
	runtime_info->opcodes = opcodes;
	runtime_info->pc = opcodes->codes;
	runtime_info->r = rt->registers;
	runtime_info->argument_count = 0;
	rt->stack[rt->stack_pointer] = *runtime_info;
	rt->stack_pointer++;
}

void tyran_runtime_push_call_ex(tyran_runtime* rt, const tyran_function* func, const struct tyran_value* _this)
{
	tyran_runtime_push_call(rt, func->data.opcodes, func->constants, _this);
}

