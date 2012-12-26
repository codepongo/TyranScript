#ifndef _TYRAN_PRINT_CONSTANTS_H
#define _TYRAN_PRINT_CONSTANTS_H

struct tyran_constants;
struct tyran_memory_pool;
struct tyran_symbol_table;

void tyran_print_constants(tyran_constants* constants, struct tyran_memory_pool* object_iterator_pool, tyran_memory_pool* string_pool, tyran_memory* memory);

#endif
