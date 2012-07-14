#ifndef _TYRAN_VALUE_OBJECT_H
#define _TYRAN_VALUE_OBJECT_H

#include <tyranscript/tyran_object_key.h>

struct tyran_string;
struct tyran_value;
struct tyran_runtime;
struct tyran_object_key;

/* Create and Destroy */
struct tyran_value* tyran_value_object_new(const struct tyran_runtime* runtime);
void tyran_value_object_set_prototype(struct tyran_value* target, struct tyran_value* prototype);

/* Insert and Delete */
void tyran_value_object_insert_c_string_key(struct tyran_value* target, const char* key, struct tyran_value* value);
void tyran_value_object_insert_key(struct tyran_value* object, const struct tyran_object_key* key, struct tyran_value* value);
struct tyran_value* tyran_value_object_insert_key_and_flag(struct tyran_value* object, struct tyran_value* key, const struct tyran_value* value, tyran_object_key_flag_type flag);
void tyran_value_object_insert_string_key(struct tyran_value* object, const struct tyran_string* key, struct tyran_value* value);
void tyran_value_object_insert_array(struct tyran_value* object, int key, struct tyran_value* value);
void tyran_value_object_delete(struct tyran_value* object, struct tyran_value* key);

/* Query */
void tyran_value_object_fetch_key_iterator(const struct tyran_runtime* runtime, struct tyran_value* object, struct tyran_value* return_value);
struct tyran_value* tyran_value_object_lookup_string(const struct tyran_value* object, const struct tyran_string* key, tyran_object_key_flag_type* flag);
struct tyran_value* tyran_value_object_lookup(const struct tyran_value* object, const struct tyran_object_key* key, tyran_object_key_flag_type* flag);
struct tyran_value* tyran_value_object_lookup_prototype(const struct tyran_value* object, const struct tyran_object_key* key, tyran_object_key_flag_type* flag);
struct tyran_value* tyran_value_object_lookup_array(const struct tyran_value* object, int index, tyran_object_key_flag_type* flag);
int tyran_value_object_has_key(const struct tyran_value* object, const struct tyran_object_key* key);

#endif
