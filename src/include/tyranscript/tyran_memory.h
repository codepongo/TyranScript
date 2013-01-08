#ifndef TYRAN_MEMORY_H
#define TYRAN_MEMORY_H

struct tyran_memory;

void* tyran_memory_alloc_debug(struct tyran_memory* memory, size_t size, const char* source_file, int line, const char* description);
void* tyran_memory_calloc_debug(struct tyran_memory* memory, size_t size, const char* source_file, int line, const char* description);
void tyran_memory_construct(struct tyran_memory* memory, u8t* start, size_t size);

#endif
