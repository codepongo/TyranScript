#ifndef _TYRAN_OBJECT_ARRAY_H
#define _TYRAN_OBJECT_ARRAY_H

struct tyran_value;
struct tyran_object;
struct tyran_runtime;
struct tyran_memory_pool;
struct tyran_memory;

struct tyran_object* tyran_object_new_array(struct tyran_memory_pool* object_pool, struct tyran_memory_pool* object_key_pool,struct tyran_memory_pool* value_pool, struct tyran_memory_pool* array_node_pool, struct tyran_memory_pool* string_pool, struct tyran_memory* string_memory, const struct tyran_runtime* runtime, const struct tyran_value* items, int count);

#endif
