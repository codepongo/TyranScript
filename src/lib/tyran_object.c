#include <tyranscript/tyran_object.h>
#include <tyranscript/tyran_object_macros.h>
#include <tyranscript/tyran_object_iterator.h>
#include <tyranscript/tyran_function_object.h>
#include <tyranscript/tyran_value.h>
#include <tyranscript/tyran_value_object.h>
#include <tyranscript/tyran_object_prototype.h>
#include <tyranscript/tyran_runtime.h>
#include "tyran_number_to_string.h"
#include <tyranscript/tyran_object_key.h>
#include <tyranscript/tyran_rb_tree.h>
#include <tyranscript/tyran_number.h>




void tyran_object_retain(struct tyran_object* o)
{
	TYRAN_ASSERT(o->retain_count >= 0, "Retain count is bad:%d", o->retain_count);
	TYRAN_ASSERT(o->tree != 0, "object tree is null");
	o->retain_count++;
}

void tyran_object_release(struct tyran_object *o)
{
	TYRAN_ASSERT(o->retain_count > 0, "Retain count is bad:%d", o->retain_count);
	TYRAN_ASSERT(o->tree != 0, "object tree is null");
	o->retain_count--;
	if (o->retain_count == 0) {
		tyran_object_free(o);
	}
}

void* tyran_object_key_get(struct stree_node* node)
{
	return (void*) ((tyran_rb_tree_key_value_node*)(node->node))->key;
}

tyran_object* tyran_object_new(tyran_memory_pool* object_pool, const struct tyran_runtime* runtime)
{
	tyran_object* object = TYRAN_CALLOC_TYPE(object_pool, tyran_object);
	object->tree = new_rbtree(tyran_object_key_get, tyran_object_key_compare);
	object->created_in_runtime = runtime;
	return object;
}

void tyran_object_free(struct tyran_object* object)
{
	const tyran_runtime* runtime = object->created_in_runtime;
	runtime->delete_callback(runtime, object);

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

	tyran_memset_type(object, 0);
	object->retain_count = -9999;

	tyran_free(object);
}

void tyran_object_insert_key(tyran_memory_pool* rb_node_pool, struct tyran_object* object, const struct tyran_object_key* key, struct tyran_value* value)
{
	tyran_rb_tree_key_value_node* node = TYRAN_MALLOC_TYPE_COUNT(rb_node_pool, tyran_rb_tree_key_value_node, 1);
	node->key = key;
	tyran_value_copy(node->value, *value);
	rb_tree_insert(object->tree, node);
}

void tyran_object_insert_c_string_key(tyran_memory_pool* string_pool, tyran_memory* memory, tyran_memory_pool* object_key_pool, tyran_memory_pool* rb_node_pool, struct tyran_object* object, const char* key_string, struct tyran_value* value)
{
	const tyran_string* s = tyran_string_from_c_str(string_pool, memory, key_string);
	TYRAN_ASSERT(s, "couldn't allocate string");
	tyran_object_insert_string_key(string_pool, memory, object_key_pool, rb_node_pool, object, s, value);
}

void tyran_object_insert_string_key(tyran_memory_pool* string_pool, tyran_memory* memory, tyran_memory_pool* object_key_pool, tyran_memory_pool* rb_node_pool, struct tyran_object* object, const struct tyran_string* key_string, struct tyran_value* value)
{
	tyran_object_key_flag_type flag = tyran_object_key_flag_normal;
	const struct tyran_object_key* key = tyran_object_key_new(string_pool, memory, object_key_pool, key_string, flag);
	TYRAN_ASSERT(key, "must be able to create key");
	tyran_object_insert_key(rb_node_pool, object, key, value);
}

void tyran_object_insert_array(struct tyran_object* object, int index, struct tyran_value* value)
{
	//tyran_object_key_flag_type flag = tyran_object_key_flag_normal;

	// TYRAN_UNICODE_STRING(12) string_buffer;
	//tyran_number_integer_to_string(index, string_buffer.string);

	//const tyran_object_key* key = tyran_object_key_new(string_buffer.string, flag);
	//tyran_object_insert_key(object, key, value);
	//tyran_object_extend_length_if_needed(object, index);
}

tyran_value* tyran_object_lookup(const struct tyran_object* object, const struct tyran_object_key* key, tyran_object_key_flag_type* flag)
{
	TYRAN_LOG("Search_rbtree");
	tyran_rb_tree_key_value_node* node = (tyran_rb_tree_key_value_node*) search_rbtree(*object->tree, (void*)key);
	if (!node) {
		TYRAN_LOG("No node");
		return 0;
	}
	TYRAN_LOG("flag");
	*flag = node->key->flag;
	return &node->value;
}

void tyran_object_delete(struct tyran_object* object, const struct tyran_object_key* key)
{
	rb_tree_delete(object->tree, (void*)key);
}

void tyran_object_get_keys(tyran_memory_pool* string_pool, tyran_memory* memory, tyran_memory_pool* object_key_pool, const struct tyran_object* target, tyran_object_iterator* target_iterator)
{
	tree_root* root = target->tree;

	tree_iterator* iterator = new_tree_iterator(root);
	while (tree_iterator_has_next(iterator)) {
		tyran_rb_tree_key_value_node* node = (tyran_rb_tree_key_value_node*) tree_iterator_next(iterator);
		if (tyran_object_key_has_enumerate(node->key)) {
			tyran_object_iterator_insert(string_pool, memory, object_key_pool, target_iterator, node->key);
		}
	}
	destroy_iterator(iterator);

	if (target->prototype) {
		tyran_object_get_keys(string_pool, memory, object_key_pool, target->prototype->data.object, target_iterator);
	}
}

void tyran_object_set_prototype(struct tyran_object* target, struct tyran_value* proto)
{
	// TYRAN_ASSERT(target->prototype == 0, "Prototype already set, this is a problem");
	TYRAN_OBJECT_RETAIN(proto->data.object);
	// tyran_object_insert_key(target, target->created_in_runtime->prototype_key, proto);
	target->prototype = proto;
}

tyran_value* tyran_object_lookup_prototype(const struct tyran_object* o, const struct tyran_object_key* key, tyran_object_key_flag_type* flag)
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


int tyran_object_length(const struct tyran_object* object)
{
	tyran_object_key_flag_type flag;
	tyran_value* r = tyran_object_lookup(object, object->created_in_runtime->length_key, &flag);
	if (r && tyran_value_is_number(r)) {
		if (tyran_value_is_integer(r->data.number)) return (int)r->data.number;
	}
	return -1;
}
