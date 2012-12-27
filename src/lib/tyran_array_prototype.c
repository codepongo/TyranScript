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

tyran_value* tyran_array_prototype;

int tyran_array_prototype_constructor(struct tyran_runtime* runtime, tyran_value* a, tyran_value* b, tyran_value* c, tyran_value* return_value, int is_constructor)
{
	if (is_constructor) {
		return 0;
	}

	tyran_value length;
	tyran_value_set_number(length, 0);

	tyran_value_object_insert_c_string_key(runtime, a, "length", &length);

	return 0;
}

int tyran_array_prototype_push(struct tyran_runtime* r, tyran_value* a, tyran_value* args, tyran_value* _this, tyran_value* c, int isconstructor)
{
	//int length = tyran_object_length(_this->data.object);
	//tyran_object_key_flag_type flag;
	//tyran_value* add = tyran_value_object_lookup_array(args, 0, &flag);
	//tyran_object_insert_array(_this->data.object, length, add);
	
	return 0;
}

int tyran_array_prototype_pop(struct tyran_runtime* r, tyran_value* a, tyran_value* b, tyran_value* _this, tyran_value* return_value, int isconstructor)
{
	int length = tyran_object_length(_this->data.object);
	//tyran_object_key_flag_type flag;
	TYRAN_ASSERT(length > 0, "You can not pop an empty array");
	
	length--;

	//tyran_value_copy(*return_value, *tyran_value_object_lookup_array(_this, length, &flag));
	// tyran_object_set_length(_this->data.object, length);
	return 0;
}

void tyran_array_prototype_init(const struct tyran_runtime* runtime, tyran_value* o) {
	TYRAN_MEMBER(o, "push", tyran_array_prototype_push);
	TYRAN_MEMBER(o, "constructor", tyran_array_prototype_constructor);
}

