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

#define TYRAN_INITIALIZE_PROTOTYPE(TYPE, name)  { \
	tyran_value* constructor_function = tyran_function_object_new_callback(tyran_ ## TYPE ## _prototype_constructor); \
	if (tyran_strcmp(name, "Object") != 0) { tyran_value_object_set_prototype(constructor_function, tyran_value_object_new()); } \
	tyran_value_object_insert_string_key(global, tyran_string_from_c_str(name), constructor_function); \
	tyran_ ## TYPE ## _prototype_init(tyran_object_get_prototype(constructor_function->data.object)); \
	tyran_print_value(name, constructor_function, 1); \
}

void tyran_prototypes_init(tyran_value* global)
{
	TYRAN_INITIALIZE_PROTOTYPE(object, "Object");
	TYRAN_INITIALIZE_PROTOTYPE(function, "Function");
	TYRAN_INITIALIZE_PROTOTYPE(array, "Array");
	TYRAN_INITIALIZE_PROTOTYPE(string, "String");
}
