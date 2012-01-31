#ifndef _TYRAN_VALUE_OBJECT_H
#define _TYRAN_VALUE_OBJECT_H

#include "tyran_string.h"
#include "tyran_object_key.h"

struct tyran_value;

/* Create and Destroy */
tyran_value* tyran_value_object_new();
#define tyran_value_object_set_prototype(__target, __proto) __target->data.object->prototype = __proto; 

/* Insert and Delete */
void tyran_value_object_insert_key(tyran_value* object, const tyran_object_key* key, tyran_value* value);
tyran_value* tyran_value_object_insert_key_and_flag(tyran_value* object, tyran_value* key, const tyran_value* value, tyran_object_key_flag_type flag);
void tyran_value_object_insert_string_key(tyran_value* object, const tyran_string* key, tyran_value* value);
void tyran_value_object_insert_array(tyran_value* object, int key, tyran_value* value);
void tyran_value_object_delete(tyran_value* object, tyran_value* key);

/* Query */
void tyran_value_object_fetch_key_iterator(tyran_value* object, tyran_value* return_value);
tyran_value* tyran_value_object_lookup(const tyran_value* object, const tyran_object_key* key, int* flag);
tyran_value* tyran_value_object_lookup_prototype(const tyran_value* object, const tyran_object_key* key, int* flag);
tyran_value* tyran_value_object_lookup_array(const tyran_value* object, int index, int* flag);
int tyran_value_object_has_key(const tyran_value* object, const tyran_object_key* key);

#endif
