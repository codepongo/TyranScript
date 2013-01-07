#include <tyranscript/tyran_config.h>

tyran_memory_pool* tyran_memory_pool_construct(tyran_memory* memory, size_t struct_size, size_t count, const char* type)
{
	TYRAN_LOG("Allocating pool of type '%s' (%zu x %zu)", type, struct_size, count);
	tyran_memory_pool* pool = TYRAN_MEMORY_ALLOC(memory, sizeof(tyran_memory_pool), "Memory pool");
	pool->size = struct_size;
	pool->type_string = type;
	return pool;
}

void* tyran_memory_pool_alloc(tyran_memory_pool* pool, size_t count)
{
	TYRAN_LOG("Allocating from memory pool '%s' (%zu x %zu)", pool->type_string, pool->size, count);
	return tyran_malloc(pool->size * count);
}

void* tyran_memory_pool_calloc(tyran_memory_pool* pool, size_t count)
{
	void* p = tyran_memory_pool_alloc(pool, count);
	TYRAN_LOG("Clearing memory");
	tyran_mem_clear(p, pool->size, count);
	return p;
}


void tyran_memory_pool_free(void* p)
{
	free(p);
}

char* tyran_str_dup(tyran_memory* memory, const char* str)
{
	int size = tyran_strlen(str);
	char* mem = TYRAN_MALLOC_NO_POOL_TYPE_COUNT(memory, char, size);
	
	tyran_strncpy(mem, size, str, size);
	
	return mem;
}
