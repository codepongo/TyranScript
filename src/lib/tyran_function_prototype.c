#include <tyranscript/tyran_function_prototype.h>
#include <tyranscript/tyran_object_prototype.h>
#include <tyranscript/tyran_runtime.h>
#include <tyranscript/tyran_function_object.h>
#include <tyranscript/tyran_object.h>
#include <tyranscript/tyran_value_object.h>

tyran_value* tyran_function_prototype;

int tyran_function_prototype_constructor(tyran_runtime* runtime, tyran_value* a, tyran_value* b, tyran_value* c, tyran_value* d, int is_constructor)
{
	return 0;
}

static int tyran_function_prototype_call(tyran_runtime* runtime,  tyran_value* a, tyran_value* b, tyran_value* c, tyran_value* d, int is_constructor)
{
	return 0;
}

static int tyran_function_prototype_apply(tyran_runtime* runtime,  tyran_value* a, tyran_value* b, tyran_value* c, tyran_value* d, int is_constructor)
{
	return 0;
}

void tyran_function_prototype_init(tyran_value* constructor_protoype)
{
	tyran_value* function_call = tyran_function_object_new_callback(tyran_function_prototype_call);
	tyran_value_object_insert_string_key(constructor_protoype, tyran_string_from_c_str("call"), function_call);
	tyran_value_object_set_prototype(function_call, tyran_function_prototype);

	tyran_value* function_apply = tyran_function_object_new_callback(tyran_function_prototype_apply);
	tyran_value_object_insert_string_key(constructor_protoype, tyran_string_from_c_str("apply"), function_apply);
	tyran_value_object_set_prototype(function_apply, tyran_function_prototype);
}
