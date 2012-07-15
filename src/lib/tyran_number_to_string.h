#ifndef _TYRAN_NUMBER_TO_STRING_H
#define _TYRAN_NUMBER_TO_STRING_H

#include <tyranscript/tyran_string.h>

void tyran_number_integer_to_string(int value, const tyran_string** str);
void tyran_number_to_string(double value, const tyran_string** str, int precision);

#endif
