#ifndef _TYRAN_PRINT_VALUE_H
#define _TYRAN_PRINT_VALUE_H

struct tyran_value;

const char* tyran_value_to_c_string(const tyran_value* v);
void tyran_print_value(const char* property, const tyran_value* v, int quote);

#endif
