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
#include <tyranscript/tyran_red_black_tree.h>


TYRAN_RUNTIME_CALL_FUNC(tyran_array_iterator_prototype_constructor)
{
	return 0;
}

TYRAN_RUNTIME_CALL_FUNC(tyran_array_iterator_prototype_next)
{
	tyran_object* object = tyran_value_object(self);
	struct tyran_red_black_tree_iterator* iterator = tyran_object_array_iterator(object);

	tyran_array_node* node = tyran_red_black_tree_iterator_next(iterator);
	if (node) {
		tyran_value_replace(*return_value, node->value);
	} else {
		tyran_value_replace_nil(*return_value);
	}

	return 0;
}


void tyran_array_iterator_prototype_init(const struct tyran_runtime* runtime, tyran_value* o)
{
	TYRAN_MEMBER(o, "constructor", tyran_array_iterator_prototype_constructor);
	TYRAN_MEMBER(o, "++", tyran_array_iterator_prototype_next);
}
