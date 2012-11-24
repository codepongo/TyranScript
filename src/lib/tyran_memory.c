#include <tyranscript/tyran_config.h>

void tyran_memory_construct(tyran_memory* memory, u8t* start, size_t size)
{
}

void* tyran_memory_alloc(tyran_memory* memory, size_t size)
{
	return tyran_malloc(size);
}

void* tyran_memory_alloc_debug(tyran_memory* memory, size_t size, const char* source_file, int line, const char* description)
{
	return tyran_memory_alloc(memory, size);
}


