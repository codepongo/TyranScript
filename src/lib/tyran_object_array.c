#include <tyranscript/tyran_object_array.h>
#include <tyranscript/tyran_object.h>
#include <tyranscript/tyran_object_macros.h>
#include <tyranscript/tyran_object_key.h>
#include <tyranscript/tyran_string.h>
#include <tyranscript/tyran_value.h>
#include <tyranscript/tyran_array_prototype.h>

#include "tyran_number_to_string.h"

struct tyran_object* tyran_object_new_array(tyran_memory_pool* object_pool, tyran_memory_pool* object_key_pool, tyran_memory_pool* value_pool, tyran_memory_pool* rb_node_pool, tyran_memory_pool* string_pool, tyran_memory* string_memory, const struct tyran_runtime* runtime, const tyran_value* items, int count)
{
	const tyran_string* number_string;
	int i;
	const struct tyran_object_key* ok;
	tyran_value* v;
	tyran_object* object = tyran_object_new(object_pool, runtime);

	for (i = 0; i < count; ++i) {
		tyran_number_integer_to_string(string_pool, string_memory, i, &number_string);
		ok = tyran_object_key_new(object_key_pool, number_string, tyran_object_key_flag_normal);
		v = tyran_value_new(value_pool);
		tyran_value_copy(*v, items[i]);
		tyran_object_insert_key(rb_node_pool, object, ok, v);
	}
	
	// tyran_object_set_length(object, count);
	
	tyran_object_set_prototype(object, tyran_array_prototype);
	
	return object;
}
