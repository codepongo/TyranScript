#include <tyranscript/tyran_config.h>
#include <tyranscript/tyran_value.h>
#include <tyranscript/tyran_object.h>
#include <tyranscript/tyran_object_macros.h>
#include <tyranscript/tyran_function.h>
#include <tyranscript/tyran_function_prototype.h>
#include <tyranscript/tyran_function_object.h>
#include <tyranscript/tyran_scope_stack.h>
#include <tyranscript/tyran_value_object.h>

tyran_function_object* tyran_function_object_new(const tyran_function* function)
{
	tyran_function_object* object = TYRAN_CALLOC(tyran_function_object);
	object->static_function = function;

	return object;
}

void tyran_function_object_free(tyran_function_object* function_object)
{
	tyran_scope_stack_free(function_object->scope);
	tyran_free(function_object);
}

tyran_function_object* tyran_function_object_new_callback_helper(tyran_function_callback callback)
{
	tyran_function* func = tyran_function_callback_new(callback);
	return tyran_function_object_new(func);
}

tyran_value* tyran_function_object_new_callback(const struct tyran_runtime* runtime, tyran_function_callback callback)
{
	tyran_object* object = tyran_object_new(runtime);
	tyran_object_set_function(object, tyran_function_object_new_callback_helper(callback));

	tyran_value* value = tyran_value_new();
	tyran_value_set_object(*value, object);
	

	return value;
}
