#include <tyranscript/tyran_runtime.h>
#include <tyranscript/tyran_value.h>
#include <tyranscript/tyran_object.h>

#include <tyranscript/tyran_object_macros.h>

tyran_value* tyran_iterator_object_new(struct tyran_runtime* runtime, struct tyran_red_black_tree_iterator* iterator)
{
	tyran_object* o = tyran_object_new(runtime);
	tyran_object_set_array_iterator(o, iterator);
	tyran_object_set_prototype(o, runtime->_array_iterator_class);

	tyran_value* return_value = tyran_value_new(runtime->value_pool);
	tyran_value_set_object(*return_value, o);

	return return_value;
}
