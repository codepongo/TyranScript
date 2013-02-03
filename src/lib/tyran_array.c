#include <tyranscript/tyran_array.h>
#include <tyranscript/tyran_red_black_tree.h>
#include <tyranscript/tyran_value.h>
#include <tyranscript/tyran_object.h>
#include <tyranscript/tyran_object_macros.h>
#include <tyranscript/tyran_string.h>

void* tyran_array_key_get(struct tyran_red_black_tree_node* node)
{
	return (void*) (&((tyran_array_node*)(node->node))->key);
}

int tyran_array_key_compare(void* key_a, void* key_b)
{
	tyran_array_key* a = (tyran_array_key*)key_a;
	tyran_array_key* b = (tyran_array_key*)key_b;

	if (a->key_value.type != b->key_value.type) {
		return (a->key_value.type < b->key_value.type) ? -1 : 1;
	}

	switch (a->key_value.type) {
		case TYRAN_VALUE_TYPE_NUMBER: {
			int a_int = (int)a->key_value.data.number;
			int b_int = (int)b->key_value.data.number;
			int result = a_int - b_int;

			return result;
		}
		break;
		case TYRAN_VALUE_TYPE_OBJECT:
			switch (a->key_value.data.object->type) {
				case TYRAN_OBJECT_TYPE_STRING:
					return tyran_string_strcmp(b->key_value.data.object->data.str, a->key_value.data.object->data.str);
					break;
				default:
					TYRAN_ERROR("UNKNOWN OBJECT");
					break;
			}
			break;
		default:
			TYRAN_ERROR("Unknown type");
			break;
	}

	return 0;
}

tyran_array* tyran_array_new(struct tyran_memory* memory)
{
	tyran_array* array = TYRAN_MALLOC_NO_POOL_TYPE(memory, tyran_array);
	array->tree = tyran_red_black_tree_new(tyran_array_key_get, tyran_array_key_compare);
	array->max_index = -1;
	return array;
}

void tyran_array_copy(tyran_memory_pool* array_node_pool, tyran_array* target, tyran_red_black_tree* source, int offset)
{
	tyran_red_black_tree_iterator* iterator = tyran_red_black_tree_iterator_new(source);
	tyran_array_node* node;
	while ((node = (tyran_array_node*) tyran_red_black_tree_iterator_next(iterator))) {
		tyran_value key = node->key.key_value;
		if (offset != 0) {
			key.data.number += offset;
		}
		tyran_array_insert(target, array_node_pool, &key, &node->value);
	}
	tyran_red_black_tree_iterator_destroy(iterator);
}

tyran_array* tyran_array_dup(struct tyran_memory* memory, tyran_memory_pool* array_node_pool, const tyran_array* a1)
{
	tyran_array* duplicated_array = tyran_array_new(memory);

	tyran_array_copy(array_node_pool, duplicated_array, a1->tree, 0);

	return duplicated_array;
}

tyran_array* tyran_array_add(struct tyran_memory* memory, tyran_memory_pool* array_node_pool, const tyran_array* a1, const tyran_array* a2)
{
	tyran_array* array = tyran_array_dup(memory, array_node_pool, a1);
	tyran_array_copy(array_node_pool, array, a2->tree, a1->max_index + 1);

	return array;
}

void tyran_array_free_node(tyran_array_node* node)
{
	tyran_value_release(node->key.key_value);
	tyran_value_release(node->value);
	TYRAN_MALLOC_FREE(node);
}

void tyran_array_insert_helper(tyran_array* array, tyran_memory_pool* array_node_pool, const tyran_array_key* key, tyran_value* value)
{
	tyran_array_node* node = TYRAN_MALLOC_TYPE(array_node_pool, tyran_array_node);
	tyran_value_copy(node->key.key_value, key->key_value);
	tyran_value_copy(node->value, *value);
	tyran_array_node* node_to_delete = (tyran_array_node*) tyran_red_black_tree_insert(array->tree, node);
	if (node_to_delete) {
		tyran_array_free_node(node_to_delete);
	}
}

void tyran_array_insert(tyran_array* array, tyran_memory_pool* array_node_pool, const tyran_value* key, tyran_value* value)
{
	tyran_array_key object_key;

	object_key.key_value = *key;
	object_key.flag = 0;
	if (tyran_value_is_number(key)) {
		int index = (int) key->data.number;
		if (index > array->max_index) {
			array->max_index = index;
		}
	}
	tyran_array_insert_helper(array, array_node_pool, &object_key, value);
}


void tyran_array_lookup_helper(tyran_value* dest, const tyran_array* array, const tyran_array_key* key, tyran_array_key_flag_type* flag)
{
	tyran_array_node* node = (tyran_array_node*) tyran_red_black_tree_search(*array->tree, (void*)key);
	if (!node) {
		tyran_value_set_nil(*dest);
		return;
	}
	*flag = 0;
	tyran_value_copy(*dest, node->value);
}

void tyran_array_lookup(tyran_value* dest, const tyran_array* array, const tyran_value* key)
{
	tyran_array_key object_key;
	tyran_array_key_flag_type flag;

	object_key.key_value = *key;
	object_key.flag = 0;
	tyran_array_lookup_helper(dest, array, &object_key, &flag);
}

void tyran_array_delete_helper(tyran_value* v, tyran_array* array, const tyran_array_key* key, tyran_array_key_flag_type* flag)
{
	tyran_array_node* node = (tyran_array_node*) tyran_red_black_tree_delete(array->tree, (void*)key);
	TYRAN_ASSERT(node, "Something went wrong");

	tyran_value_copy(*v, node->value);
	tyran_array_free_node(node);
}

void tyran_array_delete(tyran_value* v, tyran_array* array, const tyran_value* key)
{
	tyran_array_key object_key;
	tyran_array_key_flag_type flag;

	object_key.key_value = *key;
	object_key.flag = 0;

	if (tyran_value_is_number(key)) {
		int index = (int) key->data.number;
		if (index == array->max_index) {
			TYRAN_LOG("Must be pop delete");
			array->max_index -= 1;
		}
	}

	tyran_array_delete_helper(v, array, &object_key, &flag);
}
