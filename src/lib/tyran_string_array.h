#ifndef _TYRAN_STRING_ARRAY_H
#define _TYRAN_STRING_ARRAY_H

#include <tyranscript/tyran_string.h>

typedef struct tyran_string_array {
	const tyran_string** strings;
	int count;
	int size;
} tyran_string_array;

tyran_string_array* tyran_string_array_new();
void tyran_string_array_free(tyran_string_array* array);
tyran_string_array* tyran_string_array_clone(const tyran_string_array* array);

void tyran_string_array_add(tyran_string_array* array, const tyran_string* string);
const tyran_string* tyran_string_array_get(const tyran_string_array* array, int index);

#endif
