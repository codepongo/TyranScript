#include <tyranscript/tyran_config.h>

tyran_memory_pool* tyran_memory_pool_construct(tyran_memory* memory, size_t struct_size, size_t count)
{
	return TYRAN_MEMORY_ALLOC(memory, struct_size * count, "Memory pool");
}

void* tyran_memory_pool_alloc(tyran_memory_pool* pool, size_t count)
{
	return 0;
}
