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
#include <tyranscript/tyran_iterator_object.h>
#include <tyranscript/tyran_red_black_tree.h>


TYRAN_RUNTIME_CALL_FUNC(tyran_array_prototype_constructor)
{
	tyran_value length;
	tyran_value_set_number(length, argument_count);

	tyran_array* array = tyran_array_new(runtime->memory);

	tyran_object_set_array(self->data.object, array);


	tyran_value index;

	for (int i=0; i<argument_count; ++i) {
		tyran_value_set_number(index, i);
		tyran_array_insert(self->data.object->data.array, runtime->array_node_pool, &index, &arguments[i]);
	}

	tyran_value_object_insert_c_string_key(runtime, self, "length", &length);

	return 0;
}

TYRAN_RUNTIME_CALL_FUNC(tyran_array_prototype_push)
{
	tyran_value length;

	tyran_array* self_array = tyran_value_object_array(self);

	tyran_value_set_number(length, self_array->max_index + 1);
	tyran_array_insert(self_array, runtime->array_node_pool, &length, arguments);

	tyran_value_set_number(length, self_array->max_index + 1);
	tyran_value_object_insert_c_string_key(runtime, self, "length", &length);
	return 0;
}

TYRAN_RUNTIME_CALL_FUNC(tyran_array_prototype_pop)
{
	tyran_value length;

	tyran_array* self_array = tyran_value_object_array(self);

	tyran_value_set_number(length, self_array->max_index);
	TYRAN_LOG("pop:%d", self_array->max_index);

	tyran_value v;
	tyran_array_delete(&v, self_array, &length);
	tyran_value_move(*return_value, v);

	tyran_value_set_number(length, self_array->max_index + 1);
	tyran_value_object_insert_c_string_key(runtime, self, "length", &length);

	return 0;
}

TYRAN_RUNTIME_CALL_FUNC(tyran_array_prototype_index)
{
	tyran_array* self_array = tyran_value_object_array(self);
	tyran_value v;

	tyran_array_lookup(&v, self_array, arguments);

	tyran_value_move(*return_value, v);
	return 0;
}

TYRAN_RUNTIME_CALL_FUNC(tyran_array_prototype_index_set)
{
	tyran_array* self_array = tyran_value_object_array(self);
	tyran_array_insert(self_array, runtime->array_node_pool, &arguments[0], &arguments[1]);
	return 0;
}

TYRAN_RUNTIME_CALL_FUNC(tyran_array_prototype_add)
{
	tyran_array* added_array = tyran_array_add(runtime->memory, runtime->array_node_pool, self->data.object->data.array, arguments[0].data.object->data.array);
	tyran_object* obj = tyran_object_new(runtime);
	tyran_object_set_prototype(obj, runtime->_array_class);
	tyran_object_set_array(obj, added_array);
	tyran_value_replace_object(*return_value, obj);
	return 0;
}

TYRAN_RUNTIME_CALL_FUNC(tyran_array_prototype_iter)
{
	tyran_array* self_array = tyran_value_object_array(self);

	struct tyran_red_black_tree* root = self_array->tree;
	struct tyran_red_black_tree_iterator* iterator = tyran_red_black_tree_iterator_new(root);
	tyran_value* iterator_value = tyran_iterator_object_new(runtime, iterator);
	tyran_value_replace(*return_value, *iterator_value);
	return 0;
}

void tyran_array_prototype_init(const struct tyran_runtime* runtime, tyran_value* o)
{
	TYRAN_MEMBER(o, "constructor", tyran_array_prototype_constructor);
	TYRAN_MEMBER(o, "iter", tyran_array_prototype_iter);
	TYRAN_MEMBER(o, "[]=", tyran_array_prototype_index_set);
	TYRAN_MEMBER(o, "[]", tyran_array_prototype_index);
	TYRAN_MEMBER(o, "+", tyran_array_prototype_add);
	TYRAN_MEMBER(o, "push", tyran_array_prototype_push);
	TYRAN_MEMBER(o, "pop", tyran_array_prototype_pop);
}
