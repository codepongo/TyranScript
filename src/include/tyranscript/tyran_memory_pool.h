#ifndef tyran_memory_pool_h
#define tyran_memory_pool_h

struct tyran_memory_pool;

typedef struct tyran_memory_pool_entry {
	const char* file;
	int line;
	tyran_boolean allocated;
	struct tyran_memory_pool_entry* next_free;
	struct tyran_memory_pool* pool;
} tyran_memory_pool_entry;

typedef struct tyran_memory_pool {
	u8t* memory;
	size_t struct_size;
	size_t count;
	size_t max_count;
	u8t* next;
	const char* type_string;
	tyran_memory_pool_entry* first_free;
} tyran_memory_pool;

tyran_memory_pool* tyran_memory_pool_construct(struct tyran_memory* memory, size_t struct_size, size_t count, const char* type);
void* tyran_memory_pool_alloc_debug(tyran_memory_pool* pool, const char* type_name, size_t struct_size);
void* tyran_memory_pool_calloc_debug(tyran_memory_pool* pool, const char* type_name, size_t struct_size);
void tyran_memory_pool_free(void*);

#define TYRAN_MEMORY_POOL_CONSTRUCT(memory, T, count) tyran_memory_pool_construct(memory, sizeof(T), count, #T)

#define TYRAN_CALLOC_TYPE(pool, T) (T*) tyran_memory_pool_calloc_debug(pool, #T, sizeof(T));
#define TYRAN_MALLOC_TYPE(pool, type) (type*) tyran_memory_pool_alloc_debug(pool, #type, sizeof(type));
#define TYRAN_MALLOC_FREE(p) tyran_memory_pool_free(p);



#endif
