#ifndef _TYRAN_PRINT_VALUE_H
#define _TYRAN_PRINT_VALUE_H

struct tyran_value;
struct tyran_memory_pool;
struct tyran_symbol_table;

void tyran_value_to_c_string(const struct tyran_symbol_table* symbol_table, const struct tyran_value* v, char* buf, int max_length, int quote);
void tyran_print_value(const char* property, const struct tyran_value* v, int quote, const struct tyran_symbol_table* symbol_table, struct tyran_memory_pool* object_iterator_pool, struct tyran_memory_pool* string_pool, struct tyran_memory* memory);

#endif
