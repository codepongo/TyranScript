#include <tyranscript/tyran_runtime_stack.h>
#include <tyranscript/tyran_config.h>
#include <tyranscript/tyran_value.h>

tyran_runtime_stack* tyran_runtime_stack_new(tyran_memory_pool* runtime_stack_pool)
{
	tyran_runtime_stack* stack = TYRAN_CALLOC_TYPE(runtime_stack_pool, tyran_runtime_stack);

	return stack;
}
