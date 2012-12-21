#ifndef _TYRAN_OBJECT_H
#define _TYRAN_OBJECT_H

#include <tyranscript/tyran_object_key.h>

#include <tyranscript/tyran_value.h>

struct tyran_function_object;
struct tyran_object_iterator;
struct tyran_function_object;
struct tyran_runtime;
struct tree_root;
struct tyran_memory_pool;


typedef struct tyran_rb_tree_key_value_node {
	const struct tyran_object_key* key;
	tyran_value value;
} tyran_rb_tree_key_value_node;

typedef enum {
	TYRAN_OBJECT_TYPE_OBJECT,
	TYRAN_OBJECT_TYPE_FUNCTION,
	TYRAN_OBJECT_TYPE_ITERATOR,
} tyran_object_type;

typedef struct tyran_object {
	struct tyran_value* prototype;

	tyran_object_type type;
	union {
		int value;
		tyran_number number;
		struct tyran_string* str;
		struct tyran_function_object* function;
		struct tyran_object_iterator* iterator;
	} data;

	int retain_count;

	struct tree_root* tree;

	const struct tyran_runtime* created_in_runtime;
	void* program_specific;

	int flags;
} tyran_object;

/* Create and destroy */
tyran_object* tyran_object_new(tyran_memory_pool* object_pool, const struct tyran_runtime* runtime);
tyran_object* tyran_object_new_from_items(const struct tyran_runtime* runtime, const struct tyran_value* items, int count);
void tyran_object_free(tyran_object* object);

/* Prototype */
void tyran_object_set_prototype(tyran_object* target, struct tyran_value* proto);
#define tyran_object_get_prototype(__target) __target->prototype

/* Length */
void tyran_object_set_length(tyran_memory_pool* value_pool, tyran_object* object, int len);
int tyran_object_length(const tyran_object* object);

/* Insert and Delete */
void tyran_object_insert_key(struct tyran_memory_pool* rb_node_pool, struct tyran_object* object, const struct tyran_object_key* key, struct tyran_value* value);
void tyran_object_insert_c_string_key(tyran_memory_pool* string_pool, tyran_memory* memory, struct tyran_memory_pool* object_key_pool, struct tyran_memory_pool* rb_node_pool, struct tyran_object* object, const char* key, struct tyran_value* value);
void tyran_object_insert_string_key(tyran_memory_pool* string_pool, tyran_memory* memory, struct tyran_memory_pool* object_key_pool, struct tyran_memory_pool* rb_node_pool, struct tyran_object* object, const struct tyran_string* key, struct tyran_value* value);
void tyran_object_insert_array(struct tyran_object* object, int index, struct tyran_value* value);
void tyran_object_delete(struct tyran_object* object, const struct tyran_object_key* key);

/* Find */
struct tyran_value* tyran_object_lookup(const struct tyran_object* object, const struct tyran_object_key* key, tyran_object_key_flag_type* flag);
struct tyran_value* tyran_object_lookup_prototype(const struct tyran_object* o, const struct tyran_object_key* key, tyran_object_key_flag_type* flag);
void tyran_object_get_keys(tyran_memory_pool* string_pool, tyran_memory* memory, tyran_memory_pool* object_key_pool, const struct tyran_object* target, struct tyran_object_iterator* target_iterator);

#endif
