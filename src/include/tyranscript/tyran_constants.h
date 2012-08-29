#ifndef _TYRAN_CONSTANTS_H
#define _TYRAN_CONSTANTS_H

#include <tyranscript/tyran_config.h>
#include <tyranscript/tyran_opcodes.h>

struct tyran_value;
struct tyran_string;

typedef struct tyran_constants
{
	struct tyran_value* values;
	tyran_constant_index size;
} tyran_constants;

tyran_constants* tyran_constants_new(tyran_memory_pool* constants, tyran_memory_pool* constant_values, size_t size);
void tyran_constants_free(tyran_constants* constants);

tyran_constant_index tyran_constants_add_number(tyran_constants* constants, tyran_number v);
tyran_constant_index tyran_constants_add_string(tyran_constants* constants, const struct tyran_string* v);
tyran_constant_index tyran_constants_add_boolean(tyran_constants* constants, tyran_boolean v);
tyran_constant_index tyran_constants_add_function(tyran_memory_pool* function_pool, tyran_constants* constants, tyran_opcodes* opcodes);

#endif
