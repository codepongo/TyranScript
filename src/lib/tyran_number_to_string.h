#ifndef _TYRAN_NUMBER_TO_STRING_H
#define _TYRAN_NUMBER_TO_STRING_H

#include <tyranscript/tyran_string.h>

void tyran_number_integer_to_string(int value, tyran_string* str);
void tyran_number_to_string(double value, tyran_string* str, int precision);

#endif
