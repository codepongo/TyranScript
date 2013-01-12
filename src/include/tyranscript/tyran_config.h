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

static const tyran_boolean TYRAN_TRUE = 1;
static const tyran_boolean TYRAN_FALSE = 0;

#include <tyranscript/tyran_memory.h>
#include <tyranscript/tyran_memory_pool.h>
#include <tyranscript/tyran_clib.h>
#include <tyranscript/tyran_log.h>

#endif
