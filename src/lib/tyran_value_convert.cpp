#include "tyran_value_convert.h"
#include <tyranscript/tyran_string.h>
#include <tyranscript/tyran_value.h>
#include "tyran_number_to_string.h"

static TYRAN_UNICODE_STRING(15) OBJECT_STRING = { 15, {'[','o','b','j','e','c','t',' ','O','b','j','e','c','t',']'}};
static TYRAN_UNICODE_STRING(4) TRUE_STRING = { 4, {'t','r','u','e'}};
static TYRAN_UNICODE_STRING(5) FALSE_STRING = { 5, {'f','a','l','s','e'}};
static TYRAN_UNICODE_STRING(4) NULL_STRING = { 4, {'n','u','l','l'}};
static TYRAN_UNICODE_STRING(9) UNDEFINED_STRING = { 9, {'u','n','d','e','f','i','n','e','d'}};
static TYRAN_UNICODE_STRING(3) NAN_STRING = { 3, {'N','a','N'}};
static TYRAN_UNICODE_STRING(8) INFINITY_STRING = { 8, {'I','n','f','i','n','i','t','y'}};
static TYRAN_UNICODE_STRING(9) NEGATIVE_INFINITY_STRING = { 9, {'-','I','n','f','i','n','i','t','y'}};

void tyran_value_convert_to_string(tyran_value* v)
{
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
}

int tyran_value_to_integer(tyran_value* v)
{
	TYRAN_ASSERT(tyran_value_is_number(v), "Can only convert numbers to integers");
	TYRAN_ASSERT(tyran_number_is_normal(v), "Can not convert to integer since number is not normal");
	return ((int)v->data.number);
}
