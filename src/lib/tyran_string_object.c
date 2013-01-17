#include <tyranscript/tyran_string_object.h>
#include <tyranscript/tyran_value.h>
#include <tyranscript/tyran_object.h>
#include <tyranscript/tyran_object_macros.h>
#include <tyranscript/tyran_runtime.h>
#include <tyranscript/tyran_string.h>
#include <tyranscript/tyran_value_object.h>

tyran_value* tyran_string_object_new(struct tyran_runtime* runtime, const struct tyran_string* string)
{
	tyran_object* o = tyran_object_new(runtime);
	tyran_object_set_string(o, string);
	tyran_object_set_prototype(o, runtime->_string_class);

	tyran_value* return_value = tyran_value_new(runtime->value_pool);
	tyran_value_set_object(*return_value, o);


	tyran_value length_value;
	tyran_value_set_number(length_value, string->len);
	tyran_value_object_insert_c_string_key(runtime, return_value, "length", &length_value);

	return return_value;
}
