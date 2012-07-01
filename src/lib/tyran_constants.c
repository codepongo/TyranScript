#include <tyranscript/tyran_constants.h>

tyran_constants* tyran_constants_new(int size)
{
	tyran_constants* constants = TYRAN_CALLOC(tyran_constants);
	constants->values = TYRAN_MALLOC_TYPE(tyran_value, size);
	return constants;
}

void tyran_constants_free(tyran_constants* constants)
{
	tyran_free(constants->values);
	tyran_free(constants);
}

tyran_constant_index tyran_constants_add_number(tyran_constants* constants, tyran_number v)
{
	tyran_value_set_number(constants->values[constants->size], v);
	tyran_constant_index new_index = constants->size++;
	return new_index;
}

tyran_constant_index tyran_constants_add_string(tyran_constants* constants, tyran_string* v)
{
	tyran_value_set_string(constants->values[constants->size], v);
	tyran_constant_index new_index = constants->size++;
	return new_index;
}

tyran_constant_index tyran_constants_add_boolean(tyran_constants* constants, tyran_boolean v)
{
	tyran_value_set_boolean(constants->values[constants->size], v);
	tyran_constant_index new_index = constants->size++;
	return new_index;
}
