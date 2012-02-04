#ifndef _TYRAN_OBJECT_H
#define _TYRAN_OBJECT_H

#include "tyran_string.h"
#include "tyran_object_key.h"
#include "tyran_object_macros.h"
#include "tyran_rb_tree.h"

struct tyran_object_iterator;
struct tyran_function_object;
struct tyran_runtime;

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
		double number;
		tyran_string* str;
		struct tyran_function_object* function;
		struct tyran_object_iterator* iterator;
	} data;

	int retain_count;

	tree_root* tree;

	struct tyran_runtime* created_in_runtime;
	void* program_specific;

	int flags;
} tyran_object;

/* Create and destroy */
tyran_object* tyran_object_new();
tyran_object* tyran_object_new_from_items(const struct tyran_value* items, int count);
void tyran_object_free(tyran_object* object);

/* Prototype */
void tyran_object_set_prototype(tyran_object* target, tyran_value* proto);
#define tyran_object_get_prototype(__target) __target->prototype

/* Length */
void tyran_object_extend_length_if_needed(tyran_object* object, int inserted_index);
void tyran_object_set_length(tyran_object* object, int len);
int tyran_object_length(const tyran_object* object);

/* Insert and Delete */
void tyran_object_insert_key(tyran_object* object, const tyran_object_key* key, struct tyran_value* value);
void tyran_object_insert_string_key(tyran_object* object, const tyran_string* key, struct tyran_value* value);
void tyran_object_insert_array(tyran_object* object, int index, struct tyran_value* value);
void tyran_object_delete(tyran_object* object, const tyran_object_key* key);

/* Find */
struct tyran_value* tyran_object_lookup(const tyran_object* object, const tyran_object_key* key, int* flag);
struct tyran_value* tyran_object_lookup_prototype(const tyran_object* o, const tyran_object_key* key, int* flag);
void tyran_object_get_keys(const struct tyran_object* target, struct tyran_object_iterator* target_iterator);

#endif
