#ifndef _TYRAN_PROPERTY_ITERATOR_H
#define _TYRAN_PROPERTY_ITERATOR_H

#include <tyranscript/tyran_value.h>
#include <tyranscript/tyran_symbol.h>

struct tyran_object;

typedef struct tyran_property_iterator {
	struct tyran_object* object;
	int property_index;
	int visited_symbols_count;
	int visited_symbols_max_count;
	tyran_symbol visited_symbols[64];
} tyran_property_iterator;

void tyran_property_iterator_init(tyran_property_iterator* self, struct tyran_object* object);

tyran_boolean tyran_property_iterator_next(tyran_property_iterator* self, tyran_symbol* symbol, tyran_value** value);

void tyran_property_iterator_free(tyran_property_iterator* self);

#endif
