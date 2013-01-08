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

int tyran_string_prototype_constructor(tyran_runtime* r, tyran_value* a, tyran_value* args, int argument_count, tyran_value* _this, tyran_value* d, int is_constructor)
{
	if (!is_constructor) {
		return 0;
	}
	return 0;
}

int tyran_string_prototype_char_at(tyran_runtime* r, tyran_value* a, tyran_value* args, int argument_count, tyran_value* _this, tyran_value* return_value, int is_constructor)
{
	return 0;
}

int tyran_string_prototype_from_char_code(tyran_runtime* r, tyran_value* a, tyran_value* args, int argument_count, tyran_value* d, tyran_value* return_value, int is_constructor)
{
	return 0;
}

int tyran_string_prototype_add(tyran_runtime* r, tyran_value* a, tyran_value* args, int argument_count, tyran_value* _this, tyran_value* return_value, int is_constructor)
{
	tyran_print_value("ADD (this)", _this, 1, r->symbol_table, 0, 0, 0);
	tyran_print_value("ADD (param)", args, 1, r->symbol_table, 0, 0, 0);

	const tyran_string* s = tyran_string_strcat(r->string_pool, r->memory, _this->data.object->data.str, args->data.object->data.str);
	tyran_value* value = tyran_string_object_new(r, s);
	tyran_value_replace(*return_value, *value);

	return 0;
}

int tyran_string_prototype_equal(tyran_runtime* r, tyran_value* a, tyran_value* args, int argument_count, tyran_value* _this, tyran_value* return_value, int is_constructor)
{
	tyran_print_value("EQUAL (this)", _this, 1, r->symbol_table, 0, 0, 0);
	tyran_print_value("EQUAL (param)", args, 1, r->symbol_table, 0, 0, 0);

	int diff = tyran_string_strcmp(_this->data.object->data.str, args->data.object->data.str);
	tyran_value_replace_boolean(*return_value, diff == 0);

	return 0;
}

int tyran_string_prototype_lte(tyran_runtime* r, tyran_value* a, tyran_value* args, int argument_count, tyran_value* _this, tyran_value* return_value, int is_constructor)
{
	tyran_print_value("LTE (this)", _this, 1, r->symbol_table, 0, 0, 0);
	tyran_print_value("LTE (param)", args, 1, r->symbol_table, 0, 0, 0);

	int diff = tyran_string_strcmp(_this->data.object->data.str, args->data.object->data.str);
	tyran_value_replace_boolean(*return_value, diff <= 0);

	return 0;
}

int tyran_string_prototype_lt(tyran_runtime* r, tyran_value* a, tyran_value* args, int argument_count, tyran_value* _this, tyran_value* return_value, int is_constructor)
{
	tyran_print_value("LT (this)", _this, 1, r->symbol_table, 0, 0, 0);
	tyran_print_value("LT (param)", args, 1, r->symbol_table, 0, 0, 0);

	int diff = tyran_string_strcmp(_this->data.object->data.str, args->data.object->data.str);
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
