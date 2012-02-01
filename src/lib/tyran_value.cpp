#include <tyranscript/tyran_value.h>
#include "tyran_number.h"

extern tyran_value* tyran_object_prototype;
extern tyran_value* tyran_array_prototype;

void tyran_value_set_program_specific(tyran_value* value, struct tyran_runtime* runtime, void* program_specific_context)
{
	value->data.object->program_specific = program_specific_context;
	value->data.object->created_in_runtime = runtime;
}

tyran_value* tyran_value_new()
{
	tyran_value* value = TYRAN_CALLOC(tyran_value);
	return value;
}

tyran_value* tyran_value_duplicate(const tyran_value* value)
{
	tyran_value* duplicate = tyran_value_new();
	tyran_value_copy(*duplicate, *value);
	return duplicate;
}

void tyran_value_free(tyran_value* value)
{
	tyran_value_release(*value);
	tyran_free(value);
}

int tyran_value_length(const tyran_value* value)
{
	if (value->type != TYRAN_VALUE_TYPE_OBJECT) {
		return -1;
	}

	return tyran_object_length(value->data.object);
}

int tyran_value_is_true(const tyran_value* value)
{
	switch(value->type) {
		case TYRAN_VALUE_TYPE_UNDEFINED:
		case TYRAN_VALUE_TYPE_NULL:
			return 0;
		case TYRAN_VALUE_TYPE_BOOLEAN:
			return value->data.boolean ? 1 : 0;
		case TYRAN_VALUE_TYPE_NUMBER:
			if (value->data.number == 0.0 || tyran_number_is_nan(value->data.number))
				return 0;
			return 1;
		case TYRAN_VALUE_TYPE_STRING:
			return TYRAN_UNICODE_STRLEN(value->data.str) ? 1 : 0;
		case TYRAN_VALUE_TYPE_OBJECT:
			return 1;
		default:
			TYRAN_ERROR("Can not convert value to true");
			break;
	}
	return 0;
}
