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

#include <tyranscript/tyran_range_iterator.h>


TYRAN_RUNTIME_CALL_FUNC(tyran_range_iterator_prototype_constructor)
{
	return 0;
}

TYRAN_RUNTIME_CALL_FUNC(tyran_range_iterator_prototype_next)
{
	tyran_object* object = tyran_value_object(self);
	tyran_range_iterator* iterator = tyran_object_range_iterator(object);

	int* next = tyran_range_iterator_next(iterator);
	if (!next) {
		tyran_value_replace_nil(*return_value);
	} else {
		tyran_value_replace_number(*return_value, (tyran_number) *next);
	}
	return 0;
}


void tyran_range_iterator_prototype_init(const struct tyran_runtime* runtime, tyran_value* o)
{
	TYRAN_MEMBER(o, "constructor", tyran_range_iterator_prototype_constructor);
	TYRAN_MEMBER(o, "++", tyran_range_iterator_prototype_next);
}
