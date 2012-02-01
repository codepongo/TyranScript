#ifndef _TYRAN_VALUE_CONVERT_H
#define _TYRAN_VALUE_CONVERT_H

struct tyran_value;

void tyran_value_convert_to_string(struct tyran_value* v);
int tyran_value_to_integer(struct tyran_value* v);

#endif
