#include <tyranscript/tyran_value.h>
#include <tyranscript/tyran_value_object.h>
#include <tyranscript/tyran_runtime.h>

#include <tyranscript/tyran_runtime_stack.h>
#include <tyranscript/tyran_opcodes.h>
#include <tyranscript/tyran_opcode.h>
#include "tyran_value_convert.h"

#include <tyranscript/debug/tyran_print_value.h>
#include <tyranscript/debug/tyran_print_opcodes.h>
#include <tyranscript/tyran_constants.h>
#include <tyranscript/tyran_string.h>
#include <tyranscript/tyran_object_macros.h>
#include <tyranscript/tyran_object_key.h>

tyran_runtime* tyran_runtime_new(tyran_memory_pool* runtime_pool, tyran_memory_pool* runtime_stack_pool, tyran_memory_pool* object_pool, tyran_memory_pool* value_pool)
{
	tyran_runtime* rt = TYRAN_CALLOC_TYPE(runtime_pool, tyran_runtime);
	rt->stack = TYRAN_MALLOC_TYPE_COUNT(runtime_stack_pool, tyran_runtime_stack, 128);
	
	rt->registers = TYRAN_MALLOC_TYPE_COUNT(value_pool, tyran_value, 128);
	
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
	tyran_runtime_stack* runtime_info = tyran_runtime_stack_new();
	// tyran_value_copy(runtime_info->_this, *_this);
	// tyran_value_copy(runtime_info->function_scope, *function_scope);
	// runtime_info->scope = scope;
	runtime_info->constants = constants;
	runtime_info->c = constants->values;
	runtime_info->opcodes = opcodes;
	runtime_info->pc = opcodes->codes;
	if (_this) {
		tyran_value_copy(*runtime_info->_this, *_this);
	}

	rt->stack[rt->stack_pointer] = *runtime_info;
	rt->stack_pointer++;
}

