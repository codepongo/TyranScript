#include <tyranscript/tyran_string_object.h>
#include <tyranscript/tyran_value.h>
#include <tyranscript/tyran_object.h>
#include <tyranscript/tyran_object_macros.h>
#include <tyranscript/tyran_runtime.h>

tyran_value* tyran_string_object_new(struct tyran_runtime* runtime, const struct tyran_string* string) {
	tyran_object* o = tyran_object_new(runtime);
	tyran_object_set_string(o, string);
	tyran_object_set_prototype(o, runtime->_string_class);

	tyran_value* return_value = tyran_value_new(runtime->value_pool);
	tyran_value_set_object(*return_value, o);

	return return_value;
}
