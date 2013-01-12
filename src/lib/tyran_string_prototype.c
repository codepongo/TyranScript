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

TYRAN_RUNTIME_CALL_FUNC(tyran_string_prototype_from_char_code)
{
	return 0;
}

TYRAN_RUNTIME_CALL_FUNC(tyran_string_prototype_add)
{
	tyran_print_value("ADD (this)", self, 1, runtime->symbol_table, 0, 0, 0);
	tyran_print_value("ADD (param)", arguments, 1, runtime->symbol_table, 0, 0, 0);

	const tyran_string* s = tyran_string_strcat(runtime->string_pool, runtime->memory, self->data.object->data.str, arguments->data.object->data.str);
	tyran_value* value = tyran_string_object_new(runtime, s);
	tyran_value_replace(*return_value, *value);

	return 0;
}

TYRAN_RUNTIME_CALL_FUNC(tyran_string_prototype_equal)
{
	tyran_print_value("EQUAL (this)", self, 1, runtime->symbol_table, 0, 0, 0);
	tyran_print_value("EQUAL (param)", arguments, 1, runtime->symbol_table, 0, 0, 0);

	int diff = tyran_string_strcmp(self->data.object->data.str, arguments->data.object->data.str);
	tyran_value_replace_boolean(*return_value, diff == 0);

	return 0;
}

TYRAN_RUNTIME_CALL_FUNC(tyran_string_prototype_lte)
{
	tyran_print_value("LTE (this)", self, 1, runtime->symbol_table, 0, 0, 0);
	tyran_print_value("LTE (param)", arguments, 1, runtime->symbol_table, 0, 0, 0);

	int diff = tyran_string_strcmp(self->data.object->data.str, arguments->data.object->data.str);
	tyran_value_replace_boolean(*return_value, diff <= 0);

	return 0;
}

TYRAN_RUNTIME_CALL_FUNC(tyran_string_prototype_lt)
{
	tyran_print_value("LT (this)", self, 1, runtime->symbol_table, 0, 0, 0);
	tyran_print_value("LT (param)", arguments, 1, runtime->symbol_table, 0, 0, 0);

	int diff = tyran_string_strcmp(self->data.object->data.str, arguments->data.object->data.str);
	tyran_value_replace_boolean(*return_value, diff < 0);

	return 0;
}

void tyran_string_prototype_init(const struct tyran_runtime* runtime, tyran_value* o)
{
	TYRAN_MEMBER(o, "+", tyran_string_prototype_add);
	TYRAN_MEMBER(o, "==", tyran_string_prototype_equal);
	TYRAN_MEMBER(o, "<=", tyran_string_prototype_lte);
	TYRAN_MEMBER(o, "<", tyran_string_prototype_lt);
}
