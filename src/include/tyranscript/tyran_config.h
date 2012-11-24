#ifndef _TYRAN_CONFIG_H
#define _TYRAN_CONFIG_H

#include <stdlib.h>
#include <memory.h>
#include <stdio.h>

#include <string.h>
#include <math.h>

typedef unsigned char u8t;
typedef unsigned short u16t;
typedef unsigned int u32t;
typedef float tyran_number;
typedef int tyran_boolean;

#define TYRAN_TRUE (1)
#define TYRAN_FALSE (0)


typedef unsigned short tyran_uint16;

typedef struct tyran_memory
{
	u8t* memory;
	size_t size;
	u8t* next;
} tyran_memory;

typedef struct tyran_memory_pool
{
	u8t* memory;
	size_t size;
	u8t* next;
} tyran_memory_pool;


void tyran_memory_construct(tyran_memory* memory, u8t* start, size_t size);
void* tyran_memory_alloc(tyran_memory* memory, size_t size);
void* tyran_memory_alloc_debug(tyran_memory* memory, size_t size, const char* source_file, int line, const char* description);

#define TYRAN_MEMORY_ALLOC(memory, size, description) tyran_memory_alloc_debug(memory, size, __FILE__, __LINE__, description);



tyran_memory_pool* tyran_memory_pool_construct(tyran_memory* memory, size_t struct_size, size_t count);
void* tyran_memory_pool_alloc(tyran_memory_pool*, size_t count);
void* tyran_memory_pool_calloc(tyran_memory_pool*, size_t count);
void tyran_memory_pool_free(void*);


char* tyran_str_dup(tyran_memory* pool, const char* str);

#define TYRAN_MEMORY_POOL_CONSTRUCT(memory, T, count) tyran_memory_pool_construct(memory, sizeof(T), count)


#define tyran_malloc malloc
#define tyran_realloc realloc
#define tyran_free tyran_memory_pool_free


#define TYRAN_CALLOC_TYPE(pool, T) (T*) tyran_memory_pool_calloc(pool, 1);
#define TYRAN_CALLOC_TYPE_COUNT(pool, cnt, T) (T*) tyran_memory_pool_calloc(pool, cnt);

#define TYRAN_MALLOC_TYPE(pool, type) (type*) tyran_memory_pool_alloc(pool, 1);
#define TYRAN_MALLOC_TYPE_COUNT(pool, type, count) (type*) tyran_memory_pool_alloc(pool, count);
#define TYRAN_MALLOC_FREE(p) tyran_memory_pool_free(p);

#define TYRAN_MALLOC_NO_POOL_TYPE_COUNT(memory, type, count) (type*) tyran_memory_alloc(memory, count * sizeof(type));
#define TYRAN_MALLOC_NO_POOL_TYPE(memory, type) (type*) tyran_memory_alloc(memory, sizeof(type));

#define tyran_memcpy_type(T, dest, source, N) memcpy(dest, source, (N) * sizeof(T))


#define tyran_memcmp memcmp
#define tyran_memset_type(T, V) memset(T, V, sizeof(*T))
#define tyran_memset_type_n(T, V, N) memset(T, V, sizeof(*T) * (N))
#define tyran_mem_clear(D, T, N) memset(D, 0, (T)*(N))


#if defined WIN32
	#pragma warning( disable : 4100 )

	#define tyran_sscanf sscanf_s
	#define tyran_snprintf sprintf_s
	#define tyran_strncpy(dest, dest_size, source, source_size) strncpy_s(dest, dest_size, source, source_size)
	#define tyran_fopen fopen_s
	#define tyran_fread fread
	#define tyran_fclose fclose
	#define tyran_strncat strncat_s
#else
	#define tyran_sscanf sscanf
	#define tyran_snprintf snprintf
	#define tyran_strncpy(dest, dest_size, source, source_size) strncpy(dest, source, dest_size)
	#define tyran_strncat strncat
	#define tyran_fopen(F, N, M) *F = fopen(N, M)
	#define tyran_fread fread
	#define tyran_fclose fclose
	#define tyran_strncat strncat
#endif

#define tyran_strcmp strcmp
#define tyran_strlen strlen
#define tyran_strncmp strncmp
#define tyran_printf printf
#define tyran_fflush fflush
#define tyran_strdup(pool, str) tyran_str_dup(pool, str)

#define tyran_fmod fmod
#define tyran_pow pow


#define TYRAN_LOG(...) { tyran_printf(__VA_ARGS__); tyran_printf("\n"); tyran_fflush(stdout); }
#define TYRAN_LOG_NO_LF(...) { tyran_printf(__VA_ARGS__); tyran_fflush(stdout); }
#define TYRAN_SOFT_ERROR(...) TYRAN_LOG(__VA_ARGS__);
#define TYRAN_BREAK abort()
#define TYRAN_ERROR(...) TYRAN_LOG(__VA_ARGS__); TYRAN_BREAK;
#define TYRAN_ASSERT(expression, ...) if (!(expression)) { TYRAN_LOG(__VA_ARGS__); TYRAN_BREAK; }

#endif
