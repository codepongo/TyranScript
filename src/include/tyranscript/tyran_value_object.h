#ifndef _TYRAN_VALUE_OBJECT_H
#define _TYRAN_VALUE_OBJECT_H

struct tyran_string;
struct tyran_value;
struct tyran_runtime;
struct tyran_object_key;
struct tyran_memory_pool;
struct tyran_array;

/* Create and Destroy */
struct tyran_value* tyran_value_object_new(const struct tyran_runtime* runtime);
void tyran_value_object_set_prototype(struct tyran_value* target, struct tyran_value* prototype);

/* Insert and Delete */
void tyran_value_object_insert_c_string_key(const struct tyran_runtime* runtime, struct tyran_value* target, const char* key, struct tyran_value* value);
void tyran_value_object_insert(const struct tyran_runtime* runtime, struct tyran_value* target, const struct tyran_value* key, struct tyran_value* value);
void tyran_value_object_delete(struct tyran_value* object, struct tyran_value* key);

/* Query */
void tyran_value_object_lookup(struct tyran_value* v, const struct tyran_value* object, const struct tyran_value* key);
void tyran_value_object_lookup_prototype(struct tyran_value* v, const struct tyran_value* object, const struct tyran_value* key);


const struct tyran_string* tyran_value_object_string(struct tyran_value* v);

struct tyran_array* tyran_value_object_array(struct tyran_value* v);

#endif
