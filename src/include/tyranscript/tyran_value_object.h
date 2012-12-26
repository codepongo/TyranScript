#ifndef _TYRAN_VALUE_OBJECT_H
#define _TYRAN_VALUE_OBJECT_H

#include <tyranscript/tyran_object_key.h>

struct tyran_string;
struct tyran_value;
struct tyran_runtime;
struct tyran_object_key;
struct tyran_memory_pool;

/* Create and Destroy */
struct tyran_value* tyran_value_object_new(const struct tyran_runtime* runtime);
void tyran_value_object_set_prototype(struct tyran_value* target, struct tyran_value* prototype);

/* Insert and Delete */
void tyran_value_object_insert_c_string_key(struct tyran_runtime* runtime, struct tyran_value* target, const char* key, struct tyran_value* value);
void tyran_value_object_insert(struct tyran_runtime* runtime, struct tyran_value* target, const struct tyran_value* key, struct tyran_value* value);
void tyran_value_object_delete(struct tyran_value* object, struct tyran_value* key);

/* Query */
const struct tyran_value* tyran_value_object_lookup(const struct tyran_value* object, const struct tyran_value* key);
const struct tyran_value* tyran_value_object_lookup_prototype(const struct tyran_value* object, const struct tyran_value* key);

#endif
