#include <tyranscript/tyran_function.h>
#include <tyranscript/tyran_config.h>

tyran_function* tyran_function_new(tyran_memory_pool* function_pool, const struct tyran_opcodes* opcodes, const struct tyran_constants* constants)
{
	tyran_function* func = TYRAN_CALLOC_TYPE(function_pool, tyran_function);
	func->type = tyran_function_type_normal;
	func->data.opcodes = opcodes;
	func->constants = constants;

	return func;
}

tyran_function* tyran_function_callback_new(tyran_memory_pool* function_pool, tyran_function_callback callback)
{
	tyran_function* func = TYRAN_CALLOC_TYPE(function_pool, tyran_function);
	func->type = tyran_function_type_callback;
	func->data.callback = callback;

	return func;
}
