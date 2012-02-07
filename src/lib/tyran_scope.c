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

		tyran_value* v = tyran_value_object_lookup_array(scope, i, 0);
		if (v) {
			const tyran_object_key* strkey = tyran_object_key_new(argkey, tyran_object_key_flag_normal);
			tyran_value_object_insert_key(scope, strkey, v);
		} else {
			const tyran_object_key* strkey = tyran_object_key_new(argkey, tyran_object_key_flag_normal);
			tyran_value_object_insert_key(scope, strkey, tyran_value_new());
		}
	}
}

void tyran_scope_set_local_variables(tyran_value* arguments, const tyran_function* function)
{
	if (!function->local_variable_names) {
		return;
	} 

	int i;

	for (i = 0; i < function->local_variable_names->count; ++i) {
		const tyran_string* argkey = tyran_string_array_get(function->local_variable_names, i);
		if (argkey) {
			const tyran_object_key* strkey = tyran_object_key_new(argkey, tyran_object_key_flag_normal);
			tyran_value_object_insert_key(arguments, strkey, tyran_value_new());
		}
	}
}
