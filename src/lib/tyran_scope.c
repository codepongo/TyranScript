#include <tyranscript/tyran_scope.h>
#include <tyranscript/tyran_value.h>
#include "tyran_string_array.h"
#include <tyranscript/tyran_value_object.h>
#include <tyranscript/tyran_function.h>

void tyran_scope_set_variable_names(tyran_value* scope, const tyran_string_array* argument_names)
{
	int i;

	if (!argument_names) {
		return;
	}

	for (i = 0; i < argument_names->count; ++i) {
		const tyran_string* argkey = tyran_string_array_get(argument_names, i);
		
		if (!argkey) {
			break;
		}

		tyran_object_key_flag_type flag;
		tyran_value* v = tyran_value_object_lookup_array(scope, i, &flag);
		
		if (v) {
			const tyran_object_key* strkey = tyran_object_key_new(argkey, tyran_object_key_flag_normal);
			tyran_value_object_insert_key(scope, strkey, v);
		} else {
			const tyran_object_key* strkey = tyran_object_key_new(argkey, tyran_object_key_flag_normal);
			tyran_value_object_insert_key(scope, strkey, tyran_value_new());
		}
	}
}
