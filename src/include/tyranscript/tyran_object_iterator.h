#ifndef _TYRAN_OBJECT_ITERATOR_H
#define _TYRAN_OBJECT_ITERATOR_H

#include "tyran_object_key.h"

typedef struct tyran_object_iterator {
	const tyran_object_key** keys;
	int allocated_size;
	int count;
	int iterator;
} tyran_object_iterator;

tyran_object_iterator* tyran_object_iterator_new();
void tyran_object_iterator_free(tyran_object_iterator* iterator);
void tyran_object_iterator_insert(tyran_object_iterator* iterator, const tyran_object_key* key);

#endif
