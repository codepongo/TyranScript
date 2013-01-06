#include <tyranscript/tyran_function_prototype.h>
#include <tyranscript/tyran_object_prototype.h>
#include <tyranscript/tyran_runtime.h>
#include <tyranscript/tyran_function_object.h>
#include <tyranscript/tyran_function.h>
#include <tyranscript/tyran_object.h>
#include <tyranscript/tyran_value.h>
#include <tyranscript/tyran_string.h>
#include <tyranscript/tyran_object_array.h>
#include <tyranscript/tyran_value_object.h>
#include <tyranscript/debug/tyran_print_value.h>

int tyran_function_prototype_constructor(tyran_runtime* runtime, tyran_value* a, tyran_value* b, int argument_count, tyran_value* c, tyran_value* d, int is_constructor)
{
	return 0;
}

int tyran_function_prototype_call(tyran_runtime* runtime,  tyran_value* a, tyran_value* b, int argument_count, tyran_value* c, tyran_value* d, int is_constructor)
{
	return 0;
}

int tyran_function_prototype_apply(tyran_runtime* runtime, tyran_value* function_object_value, tyran_value* function_scope, int argument_count, tyran_value* _this, tyran_value* return_value, int is_constructor)
{
	/* tyran_object_key_flag_type flag;
	
	tyran_value* this_to_use = tyran_value_object_lookup_array(function_scope, 0, &flag);
	
	const tyran_function* function_to_call = _this->data.object->data.function->static_function;
	
	
	tyran_runtime_push_call(runtime, function_to_call->data.opcodes, 0, this_to_use);
	*/
	return -1;
}

void tyran_function_prototype_init(tyran_memory_pool* function_pool, tyran_memory_pool* function_object_pool, tyran_memory_pool* object_pool, tyran_memory_pool* value_pool, const struct tyran_runtime* runtime, tyran_value* constructor_protoype)
{
	// tyran_value* function_call = tyran_function_object_new_callback(runtime, tyran_function_prototype_call);
	// tyran_value_object_insert_string_key(constructor_protoype, tyran_string_from_c_str("call"), function_call);
	// tyran_value_object_set_prototype(function_call, runtime->_object_class);

	// tyran_value* function_apply = tyran_function_object_new_callback(runtime, tyran_function_prototype_apply);
	// tyran_value_object_insert_string_key(constructor_protoype, tyran_string_from_c_str("apply"), function_apply);
	// tyran_value_object_set_prototype(function_apply, runtime->_object_class);
}
