#ifndef tyran_array_h
#define tyran_array_h

#include <tyranscript/tyran_value.h>

struct tyran_red_black_tree;
struct tyran_memory;

struct tyran_memory_pool;

typedef u16t tyran_array_key_flag_type;

typedef struct tyran_array_key {
	tyran_value key_value;
	tyran_array_key_flag_type flag;
} tyran_array_key;

typedef struct tyran_array {
	struct tyran_red_black_tree* tree;
	int max_index;
} tyran_array;

typedef struct tyran_array_node {
	tyran_array_key key;
	tyran_value value;
} tyran_array_node;


tyran_array* tyran_array_new(struct tyran_memory* memory);
void tyran_array_insert(tyran_array* array, struct tyran_memory_pool* array_node_pool, const struct tyran_value* key, struct tyran_value* value);
void tyran_array_delete(struct tyran_value* v, struct tyran_array* array, const struct tyran_value* key);
void tyran_array_lookup(struct tyran_value* v, const tyran_array* array, const struct tyran_value* key);
tyran_array* tyran_array_add(struct tyran_memory* memory, tyran_memory_pool* array_node_pool, const tyran_array* a1, const tyran_array* a2);

#endif
