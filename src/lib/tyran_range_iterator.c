#include <tyranscript/tyran_config.h>
#include <tyranscript/tyran_range_iterator.h>

tyran_range_iterator* tyran_range_iterator_new(struct tyran_memory* memory, int start, int end)
{
	tyran_range_iterator* range_iterator = TYRAN_MALLOC_NO_POOL_TYPE(memory, tyran_range_iterator);
	range_iterator->max = end;
	range_iterator->delta = start <= end ? 1 : -1;
	range_iterator->current = start - range_iterator->delta;

	return range_iterator;
}

int* tyran_range_iterator_next(tyran_range_iterator* iterator)
{
	if (iterator->current == iterator->max) {
		return 0;
	}

	iterator->current += iterator->delta;

	return &iterator->current;
}
