#include <tyranscript/tyran_memory.h>
#include <tyranscript/tyran_config.h>

void tyran_memory_construct(tyran_memory* memory, u8t* start, size_t size)
{
}

void* tyran_memory_calloc(tyran_memory* memory, size_t size)
{
	void* p = tyran_malloc(size);
	tyran_mem_clear(p, size, 1);
	return p;
}

void* tyran_memory_alloc(tyran_memory* memory, size_t size)
{
	return tyran_malloc(size);
}

void* tyran_memory_alloc_debug(tyran_memory* memory, size_t size, const char* source_file, int line, const char* description)
{
	// TYRAN_LOG("Allocating memory from '%s':%d", source_file, line);
	return tyran_memory_alloc(memory, size);
}

void* tyran_memory_calloc_debug(tyran_memory* memory, size_t size, const char* source_file, int line, const char* description)
{

	// TYRAN_LOG("Allocating zeroed memory from '%s':%d", source_file, line);
	return tyran_memory_calloc(memory, size);
}

void tyran_memory_free(void* p)
{
	tyran_free(p);
}
