#ifndef _TYRAN_CONFIG_H
#define _TYRAN_CONFIG_H

#include <stdlib.h>
#include <memory.h>

#define tyran_memcpy memcpy
#define tyran_free free
#define tyran_malloc malloc
#define TN_CALLOC(T) calloc(1, sizeof(struct T));

typedef unsigned short tyran_uint16;

#endif
