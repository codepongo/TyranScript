#include <tyranscript/parser/tyran_parser_state.h>
#include <tyranscript/tyran_value.h>
#include <tyranscript/tyran_string.h>
#include <tyranscript/tyran_function.h>
#include <tyranscript/tyran_function_object.h>

#include <tyranscript/tyran_object_prototype.h>
#include <tyranscript/tyran_function_prototype.h>

#include <tyranscript/tyran_value_object.h>
#include <tyranscript/tyran_object.h>
#include <tyranscript/tyran_object_macros.h>

int tyran_array_prototype_constructor(struct tyran_runtime* runtime, tyran_value* a, tyran_value* b, tyran_value* _this, tyran_value* return_value, int is_constructor)
{
	tyran_value length;
	tyran_value_set_number(length, 0);

	tyran_value_object_insert_c_string_key(runtime, _this, "length", &length);

	return 0;
}

int tyran_array_prototype_push(struct tyran_runtime* runtime, tyran_value* a, tyran_value* args, tyran_value* _this, tyran_value* c, int isconstructor)
{
	tyran_value length;
	tyran_value_set_number(length, 1);

	tyran_value_object_insert_c_string_key(runtime, _this, "length", &length);
	return 0;
}

int tyran_array_prototype_pop(struct tyran_runtime* r, tyran_value* a, tyran_value* b, tyran_value* _this, tyran_value* return_value, int isconstructor)
{
	return 0;
}

void tyran_array_prototype_init(const struct tyran_runtime* runtime, tyran_value* o) {
	TYRAN_MEMBER(o, "push", tyran_array_prototype_push);
	TYRAN_MEMBER(o, "constructor", tyran_array_prototype_constructor);
}
