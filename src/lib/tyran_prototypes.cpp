#include <tyranscript/tyran_prototypes.h>
#include <tyranscript/tyran_object_prototype.h>
#include <tyranscript/tyran_function_prototype.h>
#include <tyranscript/tyran_array_prototype.h>
#include <tyranscript/tyran_string.h>
#include <tyranscript/tyran_value_object.h>
#include <tyranscript/tyran_value.h>
#include <tyranscript/tyran_function_object.h>

#define TYRAN_INITIALIZE_PROTOTYPE(TYPE, name) tyran_ ## TYPE ## _prototype_init(); { \
	tyran_value* p = tyran_function_object_new_callback(tyran_ ## TYPE ## _prototype_constructor); \
	tyran_value_object_insert_string_key(p, tyran_string_from_c_str("prototype"), tyran_ ## TYPE ## _prototype); \
	tyran_value_object_set_prototype(p, tyran_function_prototype); \
	tyran_value_object_insert_string_key(global, tyran_string_from_c_str(name), p); \
}

void tyran_prototypes_init(tyran_value* global)
{
	TYRAN_INITIALIZE_PROTOTYPE(object, "Object");
	TYRAN_INITIALIZE_PROTOTYPE(function, "Function");
	TYRAN_INITIALIZE_PROTOTYPE(array, "Array");
}
