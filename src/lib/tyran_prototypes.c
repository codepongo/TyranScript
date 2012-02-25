#include <tyranscript/tyran_prototypes.h>
#include <tyranscript/tyran_object_prototype.h>
#include <tyranscript/tyran_function_prototype.h>
#include <tyranscript/tyran_array_prototype.h>
#include <tyranscript/tyran_string_prototype.h>

#include <tyranscript/tyran_string.h>
#include <tyranscript/tyran_value_object.h>
#include <tyranscript/tyran_value.h>
#include <tyranscript/tyran_function_object.h>

#include <tyranscript/debug/tyran_print_value.h>

#define TYRAN_INITIALIZE_PROTOTYPE(RUNTIME, TYPE, name)  { \
	tyran_value* constructor_function = tyran_function_object_new_callback(RUNTIME, tyran_ ## TYPE ## _prototype_constructor); \
	{ tyran_value_object_set_prototype(constructor_function, tyran_value_object_new(RUNTIME)); } \
	tyran_value_object_insert_string_key(global, tyran_string_from_c_str(name), constructor_function); \
	tyran_ ## TYPE ## _prototype_init(RUNTIME, tyran_object_get_prototype(constructor_function->data.object)); \
}

void tyran_prototypes_init(const struct tyran_runtime* runtime, tyran_value* global)
{
	TYRAN_INITIALIZE_PROTOTYPE(runtime, object, "Object");
	TYRAN_INITIALIZE_PROTOTYPE(runtime, function, "Function");
	TYRAN_INITIALIZE_PROTOTYPE(runtime, array, "Array");
	TYRAN_INITIALIZE_PROTOTYPE(runtime, string, "String");
}
