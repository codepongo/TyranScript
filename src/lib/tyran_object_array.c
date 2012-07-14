#include <tyranscript/tyran_object_array.h>
#include <tyranscript/tyran_object.h>
#include <tyranscript/tyran_object_macros.h>
#include <tyranscript/tyran_object_key.h>
#include <tyranscript/tyran_string.h>
#include <tyranscript/tyran_value.h>
#include <tyranscript/tyran_array_prototype.h>

#include "tyran_number_to_string.h"

struct tyran_object* tyran_object_new_array(const struct tyran_runtime* runtime, const tyran_value* items, int count)
{
	tyran_string* number_string = tyran_string_alloc(12);
	int i;
	const struct tyran_object_key* ok;
	tyran_value* v;
	tyran_object* object = tyran_object_new(runtime);

	for (i = 0; i < count; ++i) {
		tyran_number_integer_to_string(i, number_string);
		ok = tyran_object_key_new(number_string, tyran_object_key_flag_normal);
		v = tyran_value_new();
		tyran_value_copy(*v, items[i]);
		tyran_object_insert_key(object, ok, v);
	}
	
	tyran_object_set_length(object, count);
	
	tyran_object_set_prototype(object, tyran_array_prototype);
	
	return object;
}
