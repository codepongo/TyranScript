#include <tyranscript/tyran_constants.h>
#include <tyranscript/tyran_value.h>
#include <tyranscript/tyran_string.h>
#include <tyranscript/tyran_object_macros.h>

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

tyran_constant_index tyran_constants_reserve_index(struct tyran_constants* constants, tyran_value* v)
{
	int i;
	for (i=0; i<constants->size; ++i)
	{
		if (tyran_value_is_same(&constants->values[i], v)) {
			return i | TYRAN_OPCODE_CONSTANT_BIT;
		}
	}

	tyran_constant_index new_index = constants->size++;
	tyran_value_copy(constants->values[new_index], *v);
	return new_index | TYRAN_OPCODE_CONSTANT_BIT;
}

tyran_constant_index tyran_constants_add_number(tyran_constants* constants, tyran_number v)
{
	tyran_value value;
	tyran_value_set_number(value, v);
	return tyran_constants_reserve_index(constants, &value);
}

tyran_constant_index tyran_constants_add_string(tyran_constants* constants, const struct tyran_string* v)
{
	tyran_value value;
	tyran_value_set_string(value, v);
	return tyran_constants_reserve_index(constants, &value);
}

tyran_constant_index tyran_constants_add_boolean(tyran_constants* constants, tyran_boolean v)
{
	tyran_value value;
	tyran_value_set_boolean(value, v);
	return tyran_constants_reserve_index(constants, &value);
}
