#include <tyranscript/tyran_function_prototype.h>
#include <tyranscript/tyran_object_prototype.h>
#include <tyranscript/tyran_runtime.h>
#include <tyranscript/tyran_function_object.h>
#include <tyranscript/tyran_object.h>
#include <tyranscript/tyran_object_macros.h>
#include <tyranscript/tyran_value.h>
#include <tyranscript/tyran_value_object.h>
#include <tyranscript/tyran_string.h>
#include <tyranscript/tyran_string_object.h>

#include <tyranscript/debug/tyran_print_value.h>

TYRAN_RUNTIME_CALL_FUNC(tyran_string_prototype_constructor)
{
	if (!is_constructor) {
		return 0;
	}
	return 0;
}

TYRAN_RUNTIME_CALL_FUNC(tyran_string_prototype_char_at)
{
	return 0;
}

TYRAN_RUNTIME_CALL_FUNC(tyran_string_prototype_add)
{
	const tyran_string* self_string = tyran_value_object_string(self);
	const tyran_string* add_string = tyran_value_object_string(arguments);
	TYRAN_LOG("String add!");
	const tyran_string* s = tyran_string_strcat(runtime->string_pool, runtime->memory, self_string, add_string);
	tyran_value copy_value;
	tyran_string_object_new(&copy_value, runtime, s);
	tyran_value_move(*return_value, copy_value);

	return 0;
}

TYRAN_RUNTIME_CALL_FUNC(tyran_string_prototype_equal)
{
	int diff = tyran_string_strcmp(self->data.object->data.str, arguments->data.object->data.str);
	tyran_value_replace_boolean(*return_value, diff == 0);

	return 0;
}

TYRAN_RUNTIME_CALL_FUNC(tyran_string_prototype_lte)
{
	int diff = tyran_string_strcmp(self->data.object->data.str, arguments->data.object->data.str);
	tyran_value_replace_boolean(*return_value, diff <= 0);

	return 0;
}

TYRAN_RUNTIME_CALL_FUNC(tyran_string_prototype_lt)
{
	int diff = tyran_string_strcmp(self->data.object->data.str, arguments->data.object->data.str);
	tyran_value_replace_boolean(*return_value, diff < 0);

	return 0;
}

int tyran_string_prototype_string_index(const tyran_string* s, tyran_value* v)
{
	int index = (int) tyran_value_number(v);
	index %= s->len;
	return index;
}

TYRAN_RUNTIME_CALL_FUNC(tyran_string_prototype_index)
{
	const tyran_string* str = tyran_value_object_string(self);
	int index = tyran_string_prototype_string_index(str, arguments);

	const tyran_string* copy = tyran_string_substr(runtime->string_pool, runtime->memory, str, index, 1);

	tyran_value copy_value;
	tyran_string_object_new(&copy_value, runtime, copy);
	tyran_value_move(*return_value, copy_value);

	return 0;
}

TYRAN_RUNTIME_CALL_FUNC(tyran_string_prototype_from_char_code)
{
	int char_code = (int) tyran_value_number(arguments);

	char temp[2];
	temp[0] = char_code;
	temp[1] = 0;

	const tyran_string* str = tyran_string_from_c_str(runtime->string_pool, runtime->memory, temp);
	tyran_value copy_value;
	tyran_string_object_new(&copy_value, runtime, str);
	tyran_value_move(*return_value, copy_value);

	return 0;
}


void tyran_string_prototype_init(const struct tyran_runtime* runtime, tyran_value* o)
{
	TYRAN_MEMBER(o, "+", tyran_string_prototype_add);
	TYRAN_MEMBER(o, "==", tyran_string_prototype_equal);
	TYRAN_MEMBER(o, "<=", tyran_string_prototype_lte);
	TYRAN_MEMBER(o, "<", tyran_string_prototype_lt);
	TYRAN_MEMBER(o, "[]", tyran_string_prototype_index);
	TYRAN_MEMBER(o, "fromCharCode", tyran_string_prototype_from_char_code);
}
