#ifndef TYRAN_NUMBER_OPERATOR_H
#define TYRAN_NUMBER_OPERATOR_H

#include <tyranscript/tyran_config.h>

struct tyran_value;

tyran_boolean tyran_number_operator_comparison(int comparison, tyran_number a, tyran_number b);
void tyran_number_operator_binary(struct tyran_value* value, int operator_index, tyran_number a, tyran_number b);

#endif
