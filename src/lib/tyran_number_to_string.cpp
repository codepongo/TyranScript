#include <tyranscript/tyran_number.h>
#include <tyranscript/tyran_string.h>
#include "modp_numtoa.h"

void tyran_number_integer_to_string(int value, tyran_string* str)
{
	char string_buffer[100];
	
	modp_itoa10(value, string_buffer);

	const tyran_string* value_as_string = tyran_string_from_c_str(string_buffer);
	tyran_string_strcpy(str, value_as_string);
}

void tyran_number_to_string(double value, tyran_string* str, int prec)
{
	char string_buffer[100];

	modp_dtoa2(value, string_buffer, 4);

	const tyran_string* value_as_string = tyran_string_from_c_str(string_buffer);
	tyran_string_strcpy(str, value_as_string);
}
