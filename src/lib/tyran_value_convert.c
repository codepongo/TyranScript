#include "tyran_value_convert.h"
#include <tyranscript/tyran_string.h>
#include <tyranscript/tyran_value.h>
#include <tyranscript/tyran_number.h>
#include "tyran_number_to_string.h"

void tyran_value_convert_to_string(tyran_value* v)
{
	/*
	const tyran_string* ntxt = 0;
	TYRAN_UNICODE_STRING(100) string_buffer;
	switch(v->type) {
		case TYRAN_VALUE_TYPE_STRING:
			return;
		case TYRAN_VALUE_TYPE_BOOLEAN:
			ntxt = v->data.boolean ? TRUE_STRING.string : FALSE_STRING.string;
			break;
		case TYRAN_VALUE_TYPE_NULL:
			ntxt = NULL_STRING.string;
			break;
		case TYRAN_VALUE_TYPE_NUMBER: {
			if (tyran_value_is_integer(v->data.number)) {
				tyran_number_integer_to_string((int)v->data.number, string_buffer.string);
				ntxt = string_buffer.string;
			} else if (tyran_number_is_normal(v->data.number)) {
				tyran_number_to_string(v->data.number, string_buffer.string, 10);
				ntxt = string_buffer.string;
			} else if (tyran_number_is_nan(v->data.number)) {
				ntxt = NAN_STRING.string;
			} else {
				int s = tyran_number_is_infinity(v->data.number);
				if (s > 0) ntxt = INFINITY_STRING.string;
				else if (s < 0) ntxt = NEGATIVE_INFINITY_STRING.string;
			}
			break;
		}
		case TYRAN_VALUE_TYPE_OBJECT: {
			ntxt = OBJECT_STRING.string;
			break;
		}
		case TYRAN_VALUE_TYPE_UNDEFINED:
			ntxt = UNDEFINED_STRING.string;
			break;
		default:
			TYRAN_ERROR("Unknown type");
			break;
	}
	tyran_value_replace_string(*v, tyran_string_strdup(ntxt));
	*/
}

int tyran_value_to_integer(tyran_value* v)
{
	TYRAN_ASSERT(tyran_value_is_number(v), "Can only convert numbers to integers");
	TYRAN_ASSERT(tyran_number_is_normal(v), "Can not convert to integer since number is not normal");
	return ((int)v->data.number);
}
