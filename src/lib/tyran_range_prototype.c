#include <tyranscript/parser/tyran_parser_state.h>
#include <tyranscript/tyran_value.h>
#include <tyranscript/tyran_string.h>
#include <tyranscript/tyran_function.h>
#include <tyranscript/tyran_function_object.h>

#include <tyranscript/tyran_object_prototype.h>
#include <tyranscript/tyran_function_prototype.h>

#include <tyranscript/tyran_value_object.h>
#include <tyranscript/tyran_object.h>
#include <tyranscript/tyran_object_macros.h>
#include <tyranscript/tyran_array.h>
#include <tyranscript/tyran_runtime.h>

#include <tyranscript/tyran_range.h>
#include <tyranscript/tyran_range_iterator.h>

TYRAN_RUNTIME_CALL_FUNC(tyran_range_prototype_constructor)
{
	int start = (int) tyran_value_number(&arguments[0]);
	int end = (int) tyran_value_number(&arguments[1]);
	tyran_boolean inclusive = tyran_value_boolean(&arguments[2]);
	if (!inclusive) {
		end--;
	}

	tyran_range* range = tyran_range_new(runtime->memory, start, end);
	tyran_object_set_range(self->data.object, range);

	return 0;
}

TYRAN_RUNTIME_CALL_FUNC(tyran_range_prototype_iter)
{
	tyran_object* self_object = tyran_value_object(self);
	tyran_range* range = tyran_object_range(self_object);
	if (!range) {
		return -1;
	}
	tyran_range_iterator* iterator = tyran_range_iterator_new(runtime->memory, range->start, range->end);

	tyran_object* iterator_object = tyran_object_new(runtime);
	tyran_object_set_prototype(iterator_object, runtime->_range_iterator_class);
	tyran_object_set_range_iterator(iterator_object, iterator);

	tyran_value_replace_object(*return_value, iterator_object);

	return 0;
}

void tyran_range_prototype_init(const struct tyran_runtime* runtime, tyran_value* o)
{
	TYRAN_MEMBER(o, "constructor", tyran_range_prototype_constructor);
	TYRAN_MEMBER(o, "iter", tyran_range_prototype_iter);
}
