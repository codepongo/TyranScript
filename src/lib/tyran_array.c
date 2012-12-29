#include <tyranscript/tyran_array.h>
#include <tyranscript/tyran_rb_tree.h>
#include <tyranscript/tyran_value.h>
#include <tyranscript/tyran_object.h>
#include <tyranscript/tyran_object_macros.h>
#include <tyranscript/tyran_string.h>

void* tyran_array_key_get(struct stree_node* node) {
	return (void*) (&((tyran_array_key_node*)(node->node))->key);
}

int tyran_array_key_compare(void* key_a, void* key_b)
{
	tyran_array_key* a = (tyran_array_key*)key_a;
	tyran_array_key* b = (tyran_array_key*)key_b;

	if (a->key_value.type != b->key_value.type) {
		return (a->key_value.type < b->key_value.type) ? -1 : 1;
	}

	switch (a->key_value.type) {
		case TYRAN_VALUE_TYPE_NUMBER:
			return (a->key_value.data.number - b->key_value.data.number);
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



tyran_array* tyran_array_new(struct tyran_memory* memory) {
	tyran_array* array = TYRAN_MALLOC_NO_POOL_TYPE(memory, tyran_array);
	array->tree = new_rbtree(tyran_array_key_get, tyran_array_key_compare);
	return array;
}

void tyran_array_insert_helper(tyran_array* array, tyran_memory_pool* rb_node_pool, const tyran_array_key* key, tyran_value* value) {
        tyran_array_key_node* node = TYRAN_MALLOC_TYPE(rb_node_pool, tyran_array_key_node);
        node->key = *key;
        node->value = *value;
        rb_tree_insert(array->tree, node);
}

void tyran_array_insert(tyran_array* array, tyran_memory_pool* rb_node_pool, const tyran_value* key, tyran_value* value) {
	tyran_array_key object_key;

	//TYRAN_OBJECT_RETAIN(key->data.object);
	object_key.key_value = *key;
	object_key.flag = 0;
	tyran_array_insert_helper(array, rb_node_pool, &object_key, value);	
}


tyran_value* tyran_array_lookup_helper(const tyran_array* array, const tyran_array_key* key, tyran_array_key_flag_type* flag) {
        tyran_array_key_node* node = (tyran_array_key_node*) search_rbtree(*array->tree, (void*)key);
        if (!node) {
                return 0;
        }
        *flag = 0; //TYRAN_OBJECT_KEY_FLAG(node->key);
        return &node->value;
}

tyran_value* tyran_array_lookup(const tyran_array* array, const tyran_value* key) {
	tyran_array_key object_key;
	tyran_array_key_flag_type flag;

	object_key.key_value = *key;
	object_key.flag = 0;
	return tyran_array_lookup_helper(array, &object_key, &flag);
}

