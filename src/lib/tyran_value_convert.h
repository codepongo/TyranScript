#ifndef _TYRAN_VALUE_CONVERT_H
#define _TYRAN_VALUE_CONVERT_H

struct tyran_value;

void tyran_value_convert_to_string(tyran_value* v);
int tyran_value_to_integer(tyran_value* v);

#endif
