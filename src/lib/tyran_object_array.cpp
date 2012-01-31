#include <tyranscript/tyran_object_array.h>
#include <tyranscript/tyran_object.h>
#include <tyranscript/tyran_string.h>
#include <tyranscript/tyran_value.h>
#include <tyranscript/tyran_array_prototype.h>

#include "tyran_number_to_string.h"

struct tyran_object* tyran_object_new_array(const tyran_value* items, int count)
{
	TYRAN_UNICODE_STRING(12) number_string;
	int i;
	const tyran_object_key* ok;
	tyran_value* v;
	tyran_object* object = tyran_object_new();

	for (i = 0; i < count; ++i) {
		tyran_number_integer_to_string(i, number_string.string);
		ok = tyran_object_key_new(number_string.string, 0);
		v = tyran_value_new();
		tyran_value_copy(*v, items[i]);
		tyran_object_insert_key(object, ok, v);
	}
	
	tyran_object_set_length(object, count);
	
	object->prototype = tyran_array_prototype;
	
	return object;
}
