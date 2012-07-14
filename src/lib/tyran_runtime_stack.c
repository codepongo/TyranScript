#include <tyranscript/tyran_runtime_stack.h>
#include <tyranscript/tyran_config.h>
#include <tyranscript/tyran_value.h>

tyran_runtime_stack* tyran_runtime_stack_new()
{
	tyran_runtime_stack* stack = TYRAN_CALLOC(tyran_runtime_stack);
	stack->_this = tyran_value_new();
	
	return stack;
}
