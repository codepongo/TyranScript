#ifndef _TYRAN_VALUE_OBJECT_H
#define _TYRAN_VALUE_OBJECT_H

#include "tyran_string.h"
#include "tyran_object_key.h"

struct tyran_value;

/* Create and Destroy */
struct tyran_value* tyran_value_object_new();
#define tyran_value_object_set_prototype(__target, __proto) __target->data.object->prototype = __proto; 

/* Insert and Delete */
void tyran_value_object_insert_key(struct tyran_value* object, const tyran_object_key* key, struct tyran_value* value);
struct tyran_value* tyran_value_object_insert_key_and_flag(struct tyran_value* object, struct tyran_value* key, const struct tyran_value* value, tyran_object_key_flag_type flag);
void tyran_value_object_insert_string_key(struct tyran_value* object, const tyran_string* key, struct tyran_value* value);
void tyran_value_object_insert_array(struct tyran_value* object, int key, struct tyran_value* value);
void tyran_value_object_delete(struct tyran_value* object, struct tyran_value* key);

/* Query */
void tyran_value_object_fetch_key_iterator(struct tyran_value* object, struct tyran_value* return_value);
struct tyran_value* tyran_value_object_lookup(const struct tyran_value* object, const tyran_object_key* key, int* flag);
struct tyran_value* tyran_value_object_lookup_prototype(const struct tyran_value* object, const tyran_object_key* key, int* flag);
struct tyran_value* tyran_value_object_lookup_array(const struct tyran_value* object, int index, int* flag);
int tyran_value_object_has_key(const struct tyran_value* object, const tyran_object_key* key);

#endif
