#include <tyranscript/tyran_value.h>
#include <tyranscript/tyran_number.h>
#include <tyranscript/tyran_object.h>
#include <tyranscript/tyran_object_macros.h>
#include <tyranscript/tyran_string.h>

extern tyran_value* tyran_object_prototype;
extern tyran_value* tyran_array_prototype;

void tyran_value_set_program_specific(tyran_value* value, void* program_specific_context)
{
	value->data.object->program_specific = program_specific_context;
}

tyran_value* tyran_value_new(tyran_memory_pool* value_pool)
{
	tyran_value* value = TYRAN_CALLOC_TYPE(value_pool, tyran_value);
	return value;
}

void tyran_value_free(tyran_value* value)
{
	tyran_value_release(*value);
	tyran_free(value);
}

tyran_number tyran_value_number(tyran_value* v)
{
	TYRAN_ASSERT(tyran_value_is_number(v), "Must be number");
	return v->data.number;
}

tyran_boolean tyran_value_boolean(tyran_value* v)
{
	TYRAN_ASSERT(tyran_value_is_boolean(v), "Must be number");
	return v->data.boolean;
}

tyran_object* tyran_value_object(tyran_value* v)
{
	TYRAN_ASSERT(tyran_value_is_object(v), "Must be object");
	return v->data.object;
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
		if (value->data.number == 0.0 || tyran_number_is_nan(value->data.number)) {
			return 0;
		}
		return 1;
	case TYRAN_VALUE_TYPE_OBJECT:
		return 1;
	default:
		TYRAN_ERROR("Can not convert value to true");
		break;
	}
}
