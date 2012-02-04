#include <tyranscript/tyran_runtime_stack.h>
#include <tyranscript/tyran_config.h>

tyran_runtime_stack* tyran_runtime_stack_new()
{
	return TYRAN_CALLOC(tyran_runtime_stack);
}
