#include <tyranscript/tyran_function_prototype.h>
#include <tyranscript/tyran_object_prototype.h>
#include <tyranscript/tyran_runtime.h>
#include <tyranscript/tyran_function_object.h>
#include <tyranscript/tyran_object.h>
#include <tyranscript/tyran_value_object.h>
#include "tyran_value_convert.h"

#include <tyranscript/debug/tyran_print_value.h>

struct tyran_value* tyran_string_prototype;

int tyran_string_prototype_constructor(tyran_runtime* r, tyran_value* a, tyran_value* args, tyran_value* _this, tyran_value* d, int is_constructor)
{
	tyran_value* str;

	if (!is_constructor) {
		return 0;
	}

	tyran_object_key_flag_type flag;
	 str = tyran_value_object_lookup_array(args, 0, &flag);
	tyran_object_set_length(_this->data.object, TYRAN_UNICODE_STRLEN(str->data.str));
	tyran_value_object_insert_string_key(_this, tyran_string_from_c_str("str"), str);

	return 0;
}

int tyran_string_prototype_char_at(tyran_runtime* r, tyran_value* a, tyran_value* args, tyran_value* _this, tyran_value* return_value, int is_constructor)
{
	tyran_object_key_flag_type flag;
	tyran_value* value = tyran_value_object_lookup(_this, tyran_string_from_c_str("str"), &flag);
	TYRAN_ASSERT(value != 0, "Couldn't find str member");
	
	tyran_value* start = tyran_value_object_lookup_array(args, 0, &flag);

	TYRAN_ASSERT(tyran_value_is_string(value), "Illegal string");
	
	const tyran_string* duplicate = tyran_string_substr(value->data.str, tyran_value_to_integer(start), 1);

	tyran_value_replace_string(*return_value, duplicate);

	return 0;
}

int tyran_string_prototype_from_char_code(tyran_runtime* r, tyran_value* a, tyran_value* args, tyran_value* d, tyran_value* return_value, int is_constructor)
{
	char buf[100];
	tyran_object_key_flag_type flag;
	tyran_value* char_code = tyran_value_object_lookup_array(args, 0, &flag);
	buf[0] = (char) tyran_value_to_integer(char_code);
	buf[1] = 0;

	const tyran_string* duplicate = tyran_string_strdup_str(buf);
	tyran_value_replace_string(*return_value, duplicate);

	return 0;
}

void tyran_string_prototype_init(const struct tyran_runtime* runtime, tyran_value* constructor_prototype)
{
	tyran_string_prototype = constructor_prototype;
	
	tyran_value* function_call = tyran_function_object_new_callback(runtime, tyran_string_prototype_char_at);
	tyran_value_object_insert_string_key(constructor_prototype, tyran_string_from_c_str("charAt"), function_call);
	tyran_value_object_set_prototype(function_call, tyran_function_prototype);

	tyran_value* from_char_code = tyran_function_object_new_callback(runtime, tyran_string_prototype_from_char_code);
	tyran_value_object_insert_string_key(constructor_prototype, tyran_string_from_c_str("fromCharCode"), from_char_code);
	tyran_value_object_set_prototype(from_char_code, tyran_function_prototype);
}
