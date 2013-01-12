#ifndef tyran_array_h
#define tyran_array_h

#include <tyranscript/tyran_value.h>

struct tree_root;
struct tyran_memory;

struct tyran_memory_pool;

typedef u16t tyran_array_key_flag_type;

typedef struct tyran_array_key {
	tyran_value key_value;
	tyran_array_key_flag_type flag;
} tyran_array_key;

typedef struct tyran_array {
	struct tree_root* tree;
	int max_index;
} tyran_array;

typedef struct tyran_array_node {
	tyran_array_key key;
	tyran_value value;
} tyran_array_node;


tyran_array* tyran_array_new(struct tyran_memory* memory);
void tyran_array_insert(tyran_array* array, struct tyran_memory_pool* rb_node_pool, const struct tyran_value* key, struct tyran_value* value);
struct tyran_value* tyran_array_lookup(const tyran_array* array, const struct tyran_value* key);
tyran_array* tyran_array_add(struct tyran_memory* memory, tyran_memory_pool* rb_node_pool, const tyran_array* a1, const tyran_array* a2);

#endif
