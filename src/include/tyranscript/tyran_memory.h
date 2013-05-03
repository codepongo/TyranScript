#ifndef TYRAN_MEMORY_H
#define TYRAN_MEMORY_H

#include "tyran_types.h"

typedef struct tyran_memory {
	u8t* memory;
	size_t size;
	u8t* next;
} tyran_memory;

void* tyran_memory_alloc_debug(struct tyran_memory* memory, size_t size, const char* source_file, int line, const char* description);
void* tyran_memory_calloc_debug(struct tyran_memory* memory, size_t size, const char* source_file, int line, const char* description);
void tyran_memory_construct(struct tyran_memory* memory, u8t* start, size_t size);
void tyran_memory_free(void* p);

#define TYRAN_MEMORY_ALLOC(memory, size, description) tyran_memory_alloc_debug(memory, size, __FILE__, __LINE__, description)
#define TYRAN_MEMORY_CALLOC(memory, size, description) tyran_memory_calloc_debug(memory, size, __FILE__, __LINE__, description)

#define TYRAN_MEMORY_CALLOC_TYPE_COUNT(memory, type, count) (type*) TYRAN_MEMORY_CALLOC(memory, count * sizeof(type), #type);
#define TYRAN_MEMORY_CALLOC_TYPE(memory, type) (type*) TYRAN_MEMORY_CALLOC(memory, sizeof(type), #type);

#define TYRAN_MALLOC_NO_POOL_TYPE_COUNT TYRAN_MEMORY_CALLOC_TYPE_COUNT
#define TYRAN_MALLOC_NO_POOL_TYPE TYRAN_MEMORY_CALLOC_TYPE

#define TYRAN_MEMORY_FREE(p) tyran_memory_free(p);

#endif
