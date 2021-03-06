#ifndef _TYRAN_CONFIG_H
#define _TYRAN_CONFIG_H

#include <stdlib.h>
#include <memory.h>
#include <stdio.h>

#include <string.h>
#include <math.h>

typedef unsigned short tyran_uint16;

#define tyran_malloc malloc
#define tyran_realloc realloc
#define tyran_free free
#define TYRAN_CALLOC(T) (T*) calloc(1, sizeof(T));
#define TYRAN_CALLOC_COUNT(cnt, T) (T*) calloc(cnt, sizeof(T));
#define TYRAN_MALLOC_TYPE(type, count) (type*) tyran_malloc(sizeof(type) * count);
#define TYRAN_MALLOC(count) tyran_malloc(count);
#define tyran_memcpy memcpy
#define tyran_memcmp memcmp
#define tyran_memset_type(T, V) memset(T, V, sizeof(*T))


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

#define tyran_fmod fmod



#define TYRAN_LOG(...) { printf(__VA_ARGS__); printf("\n"); fflush(stdout); }
#define TYRAN_LOG_NO_LF(...) { printf(__VA_ARGS__); fflush(stdout); }
#define TYRAN_SOFT_ERROR(...) TYRAN_LOG(__VA_ARGS__);
#define TYRAN_BREAK abort()
#define TYRAN_ERROR(...) TYRAN_LOG(__VA_ARGS__); TYRAN_BREAK;
#define TYRAN_ASSERT(expression, ...) if (!(expression)) { TYRAN_LOG(__VA_ARGS__); TYRAN_BREAK; }

#endif
