#ifndef _TYRAN_CONSTANTS_H
#define _TYRAN_CONSTANTS_H

#include <tyranscript/tyran_value.h>
#include <tyranscript/tyran_opcodes.h>

typedef struct tyran_constants
{
	tyran_value* values;
	int size;
} tyran_constants;


tyran_constants* tyran_constants_new(int size);
void tyran_constants_free(tyran_constants* constants);

tyran_constant_index tyran_constants_add_number(tyran_constants* constants, tyran_number v);
tyran_constant_index tyran_constants_add_string(tyran_constants* constants, tyran_string* v);
tyran_constant_index tyran_constants_add_boolean(tyran_constants* constants, tyran_boolean v);

#endif
