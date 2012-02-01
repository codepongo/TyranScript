#include <tyranscript/tyran_object.h>
#include <tyranscript/tyran_object_iterator.h>
#include <tyranscript/tyran_function_object.h>
#include <tyranscript/tyran_value.h>
#include <tyranscript/tyran_object_prototype.h>
#include <tyranscript/tyran_runtime.h>
#include "tyran_number_to_string.h"
#include <tyranscript/tyran_object_key.h>

static TYRAN_UNICODE_STRING(6) LENGTH_STRING = { 6, {'l','e','n','g','t','h'}};

typedef struct tyran_rb_tree_key_value_node {
	const tyran_object_key* key;
	struct tyran_value* value;
} tyran_rb_tree_key_value_node;

void* tyran_object_key_get(struct stree_node* node)
{
	return (void*) ((tyran_rb_tree_key_value_node*)(node->node))->key;
}

tyran_object* tyran_object_new()
{
	tyran_object* object = TYRAN_CALLOC(tyran_object);
	object->tree = new_rbtree(tyran_object_key_get, tyran_object_key_compare);
	return object;
}

void tyran_object_free(tyran_object* object)
{
	if (object->created_in_runtime) {
		tyran_runtime* runtime = object->created_in_runtime;
		runtime->delete_callback(runtime, object);
	}

	switch (object->type) {
		case TYRAN_OBJECT_TYPE_ITERATOR:
			tyran_object_iterator_free(object->data.iterator);
			break;
		case TYRAN_OBJECT_TYPE_FUNCTION:
			tyran_function_object_free(object->data.function);
			break;
		default:
			break;
	}
	destroy_rbtree(object->tree);
	tyran_free(object);
}

void tyran_object_extend_length_if_needed(tyran_object* object, int inserted_index)
{
	int len = tyran_object_length(object);
	if (len < 0) {
		return;
	}

	if (len < inserted_index + 1) {
		tyran_object_set_length(object, inserted_index + 1);
	}
}

void tyran_object_insert_key(tyran_object* object, const tyran_object_key* key, tyran_value* value)
{
	tyran_rb_tree_key_value_node* node = TYRAN_MALLOC_TYPE(tyran_rb_tree_key_value_node, 1);
	node->key = key;
	node->value = value;
	rb_tree_insert(object->tree, node);
}

void tyran_object_insert_string_key(tyran_object* object, const tyran_string* key_string, tyran_value* value)
{
	int flag = 0;
	const tyran_object_key* key = tyran_object_key_new(key_string, flag);
	tyran_object_insert_key(object, key, value);
}

void tyran_object_insert_array(tyran_object* object, int index, tyran_value* value)
{
	int flag = 0;

	TYRAN_UNICODE_STRING(12) string_buffer;
	tyran_number_integer_to_string(index, string_buffer.string);

	const tyran_object_key* key = tyran_object_key_new(string_buffer.string, flag);
	tyran_object_insert_key(object, key, value);
	tyran_object_extend_length_if_needed(object, index);
}

tyran_value* tyran_object_lookup(const tyran_object* object, const tyran_object_key* key, int* flag)
{
	tyran_rb_tree_key_value_node* node = (tyran_rb_tree_key_value_node*) search_rbtree(*object->tree, (void*)key);
	if (!node) {
		return 0;
	}
	return node->value;
}

void tyran_object_delete(tyran_object* object, const tyran_object_key* key)
{
	rb_tree_delete(object->tree, (void*)key);
}

void tyran_object_get_keys(const tyran_value* target, tyran_object_iterator* target_iterator)
{
	tree_root* root = target->data.object->tree;

	tree_iterator* iterator = new_tree_iterator(root);
	while (tree_iterator_has_next(iterator)) {
		tyran_rb_tree_key_value_node* node = (tyran_rb_tree_key_value_node*) tree_iterator_next(iterator);
		tyran_object_iterator_insert(target_iterator, node->key);
	}
	destroy_iterator(iterator);

	if (target->data.object->prototype) {
		tyran_object_get_keys(target->data.object->prototype, target_iterator);
	}
}

tyran_value* tyran_object_lookup_prototype(const tyran_object* o, const tyran_object_key* key, int* flag)
{
	tyran_value* retValue;
	retValue = tyran_object_lookup(o, key, flag);
	if (!retValue) {
		if (o->prototype) {
			return tyran_object_lookup_prototype(o->prototype->data.object, key, flag);
		}
	}
	
	return retValue;
}

tyran_object* tyran_object_new_from_items(const tyran_value* items, int count)
{
	tyran_object* object = tyran_object_new();
	const tyran_object_key* ok;
	tyran_value* v;
	int i;

	for (i = 0; i < count; i += 2) {
		ok = tyran_object_key_new(items[i].data.str, 0);
		v = tyran_value_new();
		tyran_value_copy(*v, items[i + 1]);
		tyran_object_insert_key(object, ok, v);
	}
	object->prototype = tyran_object_prototype;
	return object;
}

void tyran_object_set_length(tyran_object* object, int len)
{
	int flag = 0;
	tyran_value* r = tyran_object_lookup(object, (tyran_object_key*) LENGTH_STRING.string, &flag);
	if (!r) {
		tyran_value* n = tyran_value_new();
		tyran_value_set_number(*n, len);

		const tyran_object_key* nk = tyran_object_key_new(LENGTH_STRING.string, 0);
		tyran_object_insert_key(object, nk, n);
	} else {
		tyran_value_set_number(*r, len);
	}
}

int tyran_object_length(const tyran_object* object)
{
	int flag;
	tyran_value* r = tyran_object_lookup(object, (tyran_object_key*) LENGTH_STRING.string, &flag);
	if (r && tyran_value_is_number(r)) {
		if (tyran_value_is_integer(r->data.number)) return (int)r->data.number;
	}
	return -1;
}
