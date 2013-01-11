#include <tyranscript/tyran_prototypes.h>
#include <tyranscript/tyran_object_prototype.h>
#include <tyranscript/tyran_function_prototype.h>
#include <tyranscript/tyran_array_prototype.h>
#include <tyranscript/tyran_string_prototype.h>

#include <tyranscript/tyran_string.h>
#include <tyranscript/tyran_value_object.h>
#include <tyranscript/tyran_value.h>
#include <tyranscript/tyran_object.h>
#include <tyranscript/tyran_function_object.h>

#include <tyranscript/tyran_range_prototype.h>
#include <tyranscript/tyran_range_iterator_prototype.h>

#include <tyranscript/tyran_array_iterator_prototype.h>

#include <tyranscript/debug/tyran_print_value.h>

#include <tyranscript/tyran_runtime.h>

#define TYRAN_INITIALIZE_PROTOTYPE(RUNTIME, TYPE, name)  { \
	tyran_value* klass = tyran_value_object_new(RUNTIME); \
	tyran_value_object_insert_c_string_key(RUNTIME, global, name, klass); \
	tyran_ ## TYPE ## _prototype_init(RUNTIME, klass); \
	RUNTIME->_## TYPE ## _class = klass->data.object; \
}

void tyran_prototypes_init(struct tyran_runtime* runtime, tyran_value* global)
{
	TYRAN_INITIALIZE_PROTOTYPE(runtime, object, "Object");
	TYRAN_INITIALIZE_PROTOTYPE(runtime, array, "Array");
	TYRAN_INITIALIZE_PROTOTYPE(runtime, array_iterator, "ArrayIterator");
	TYRAN_INITIALIZE_PROTOTYPE(runtime, string, "String");
	TYRAN_INITIALIZE_PROTOTYPE(runtime, range, "Range");
	TYRAN_INITIALIZE_PROTOTYPE(runtime, range_iterator, "RangeIterator");
}
