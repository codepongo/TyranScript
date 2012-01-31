#include <tyranscript/tyran_function.h>
#include <tyranscript/tyran_config.h>

tyran_function* tyran_function_new(const tyran_string_array* arguments, const tyran_string_array* local_variables, const tyran_opcodes* opcodes)
{
	tyran_function* func = TYRAN_CALLOC(tyran_function);
	func->type = tyran_function_type_normal;
	func->data.opcodes = opcodes;
	func->argument_names = arguments;
	func->local_variable_names = local_variables;
	
	return func;
}

tyran_function* tyran_function_callback_new(tyran_function_callback callback)
{
	tyran_function* func = TYRAN_CALLOC(tyran_function);
	func->type = tyran_function_type_callback;
	func->data.callback = callback;

	return func;
}
