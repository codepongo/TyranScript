#ifndef _TYRAN_OBJECT_ITERATOR_H
#define _TYRAN_OBJECT_ITERATOR_H

struct tyran_object_key;
struct tyran_memory_pool;

typedef struct tyran_object_iterator {
	const struct tyran_object_key** keys;
	int allocated_size;
	int count;
	int iterator;
} tyran_object_iterator;

tyran_object_iterator* tyran_object_iterator_new(tyran_memory_pool* iterator_pool);
void tyran_object_iterator_free(tyran_object_iterator* iterator);
void tyran_object_iterator_insert(tyran_memory_pool* string_pool, tyran_memory* memory, struct tyran_memory_pool* object_key_pool, tyran_object_iterator* iterator, const struct tyran_object_key* key);

#endif
