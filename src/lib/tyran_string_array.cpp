#include "tyran_string_array.h"

tyran_string_array* tyran_string_array_new()
{
	tyran_string_array* ret = TYRAN_CALLOC(tyran_string_array);
	return ret;
}

void tyran_string_array_free(tyran_string_array* array)
{
	int i;

	for (i = 0; i < array->count; ++i) {
		tyran_string_free(array->strings[i]);
	}

	tyran_free(array->strings);
	tyran_free(array);
}

void tyran_string_array_add(tyran_string_array* array, const tyran_string* str)
{
	if (array->count == array->size) {
		array->size++;
		array->size *= 2;
		array->strings = (const tyran_string**) tyran_realloc(array->strings, (array->size) * sizeof(tyran_string *));
	}
	array->strings[array->count] = tyran_string_strdup(str);
	array->count++;
}

tyran_string_array* tyran_string_array_clone(const tyran_string_array* array)
{
	tyran_string_array* cloned_array = tyran_string_array_new();
	int i;

	for (i = 0; i < array->count; ++i) {
		tyran_string_array_add(cloned_array, array->strings[i]);
	}
	return cloned_array;
}

const tyran_string* tyran_string_array_get(const tyran_string_array* array, int index)
{
	TYRAN_ASSERT(index >= 0 && index <= array->count, "Illegal index for string array");
	return array->strings[index];
}
