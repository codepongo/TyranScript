#include <tyranscript/tyran_config.h>
#include <tyranscript/tyran_range.h>

tyran_range* tyran_range_new(tyran_memory* memory, int start, int end)
{
	tyran_range* range = TYRAN_MALLOC_NO_POOL_TYPE(memory, tyran_range);
	range->start = start;
	range->end = end;
	return range;
}
