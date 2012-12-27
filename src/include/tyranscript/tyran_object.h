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
	TYRAN_OBJECT_TYPE_STRING,
	TYRAN_OBJECT_TYPE_FUNCTION,
	TYRAN_OBJECT_TYPE_ITERATOR,
} tyran_object_type;

typedef struct tyran_object_property {
	tyran_symbol symbol;
	tyran_value value;
} tyran_object_property;

typedef struct tyran_object {
	struct tyran_object* prototype;

	tyran_object_type type;
	union {
		int value;
		const struct tyran_string* str;
		struct tyran_function_object* function;
		struct tyran_object_iterator* iterator;
	} data;

	int retain_count;
	tyran_object_property properties[32];
	int property_count;

	const struct tyran_runtime* created_in_runtime;
	void* program_specific;

	int flags;
} tyran_object;

/* Create and destroy */
tyran_object* tyran_object_new(const struct tyran_runtime* runtime);
void tyran_object_free(tyran_object* object);

/* Prototype */
void tyran_object_set_prototype(tyran_object* target, struct tyran_object* proto);
#define tyran_object_get_prototype(__target) __target->prototype

/* Length */
void tyran_object_set_length(tyran_memory_pool* value_pool, tyran_object* object, int len);
int tyran_object_length(const tyran_object* object);

/* Insert and Delete */
void tyran_object_insert(struct tyran_object* object, const tyran_symbol* symbol, struct tyran_value* value);
void tyran_object_delete(struct tyran_object* object, const struct tyran_symbol* symbol);

/* Find */
struct tyran_value* tyran_object_lookup(struct tyran_object* object, const struct tyran_symbol* key);
struct tyran_value* tyran_object_lookup_prototype(struct tyran_object* o, const struct tyran_symbol* key);

#endif
