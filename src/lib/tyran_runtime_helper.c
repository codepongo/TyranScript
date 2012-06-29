#include <tyranscript/tyran_value.h>
#include <tyranscript/tyran_value_object.h>
#include <tyranscript/tyran_runtime.h>

#include <tyranscript/tyran_runtime_stack.h>
#include <tyranscript/tyran_opcodes.h>
#include <tyranscript/tyran_opcode.h>
#include "tyran_runtime_helper.h"
#include "tyran_value_convert.h"

#include <tyranscript/debug/tyran_print_value.h>
#include <tyranscript/debug/tyran_print_opcodes.h>

tyran_runtime* tyran_runtime_new()
{
	tyran_runtime* rt = TYRAN_CALLOC(tyran_runtime);
	rt->stack = TYRAN_MALLOC_TYPE(tyran_runtime_stack, 128);
	return rt;
}

void tyran_runtime_free(tyran_runtime* rt)
{
	tyran_free(rt);
}

void tyran_runtime_push_call(tyran_runtime* rt, const struct tyran_opcodes* opcodes, struct tyran_scope_stack* scope, struct tyran_value* function_scope, const struct tyran_value* _this)
{
	/* Save return state */
	tyran_runtime_stack* runtime_info = tyran_runtime_stack_new();
	// tyran_value_copy(runtime_info->_this, *_this);
	// tyran_value_copy(runtime_info->function_scope, *function_scope);
	runtime_info->scope = scope;
	runtime_info->opcodes = opcodes;
	runtime_info->pc = opcodes->codes;

	rt->stack[rt->stack_pointer] = *runtime_info;
	rt->stack_pointer++;
}

