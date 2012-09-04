#include <tyranscript/tyran_config.h>

tyran_memory_pool* tyran_memory_pool_construct(tyran_memory* memory, size_t struct_size, size_t count)
{
	return TYRAN_MEMORY_ALLOC(memory, struct_size * count, "Memory pool");
}

void* tyran_memory_pool_alloc(tyran_memory_pool* pool, size_t count)
{
	return 0;
}

char* tyran_str_dup(tyran_memory* memory, const char* str)
{
	int size = tyran_strlen(str);
	char* mem = TYRAN_MALLOC_NO_POOL_TYPE_COUNT(memory, char, size);
	
	tyran_strncpy(mem, size, str, size);
	
	return mem;
}
