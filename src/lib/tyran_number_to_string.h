#ifndef _TYRAN_NUMBER_TO_STRING_H
#define _TYRAN_NUMBER_TO_STRING_H

struct tyran_memory_pool;
struct tyran_memory;

#include <tyranscript/tyran_string.h>

void tyran_number_integer_to_string(tyran_memory_pool* string_pool, tyran_memory* memory, int value, const tyran_string** str);
void tyran_number_to_string(tyran_memory_pool* string_pool, tyran_memory* memory, double value, const tyran_string** str, int precision);

#endif
