#ifndef _TYRAN_CONFIG_H
#define _TYRAN_CONFIG_H

#include <stdlib.h>
#include <memory.h>
#include <stdio.h>

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

#define tyran_sscanf sscanf
#define tyran_sprintf sprintf
#define tyran_strcpy strcpy
#define tyran_strcmp strcmp
#define tyran_strlen strlen
#define tyran_strcat strcat
#define tyran_strncmp strncmp

#define TYRAN_LOG(...) { printf(__VA_ARGS__); printf("\n"); fflush(stdout); }
#define TYRAN_LOG_NO_LF(...) { printf(__VA_ARGS__); }
#define TYRAN_SOFT_ERROR(...) TYRAN_LOG(__VA_ARGS__);
#define TYRAN_BREAK abort()
#define TYRAN_ERROR(...) TYRAN_LOG(__VA_ARGS__); TYRAN_BREAK;
#define TYRAN_ASSERT(expression, description) if (!(expression)) { TYRAN_LOG(description); TYRAN_BREAK; }

#endif
