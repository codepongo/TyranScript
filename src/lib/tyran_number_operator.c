#include <tyranscript/tyran_number_operator.h>
#include <tyranscript/tyran_value.h>
#include <tyranscript/tyran_object.h>

tyran_boolean tyran_number_operator_comparison(int comparison, tyran_number a, tyran_number b)
{
	tyran_boolean result;

	switch (comparison) {
		case 8:
			result = (a==b);
			break;
		case 9:
			result = (a<b);
			break;
		case 10:
			result = (a<=b);
			break;
		default:
			result = 0;
			TYRAN_ERROR("Unknown comparison:%d", comparison);
	}

	return result;
}

void tyran_number_operator_binary(tyran_value* value, int operator_index, tyran_number a, tyran_number b)
{
	tyran_number result;

	switch (operator_index) {
		case 0:
			result = a + b;
			break;
		case 1:
			result = a / b;
			break;
		case 2:
			result = tyran_fmod(a, b);
			break;
		case 3:
			result = a * b;
			break;
		case 4:
			result = tyran_pow(a, b);
			break;
		case 5:
			result = a - b;
			break;
		default:
			result = 0;
			TYRAN_ERROR("Unknown operator:%d", operator_index);
	}

	tyran_value_replace_number(*value, result);
}
