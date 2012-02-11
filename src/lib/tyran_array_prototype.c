#include <tyranscript/parser/tyran_parser_state.h>
#include <tyranscript/tyran_value.h>
#include <tyranscript/tyran_function.h>
#include <tyranscript/tyran_function_object.h>

#include <tyranscript/tyran_object_prototype.h>
#include <tyranscript/tyran_function_prototype.h>

#include <tyranscript/tyran_value_object.h>

tyran_value* tyran_array_prototype;

int tyran_array_prototype_constructor(struct tyran_runtime* runtime, tyran_value* a, tyran_value* b, tyran_value* c, tyran_value* return_value, int is_constructor)
{
	if (is_constructor) {
		return 0;
	}

	tyran_object* o = tyran_object_new();
	tyran_object_set_length(o, 0);
	tyran_value_set_object(*return_value, o);

	return 0;
}

int tyran_array_prototype_push(struct tyran_runtime* r, tyran_value* a, tyran_value* args, tyran_value* _this, tyran_value* c, int isconstructor)
{
	int length = tyran_object_length(_this->data.object);
	tyran_object_key_flag_type flag;
	tyran_value* add = tyran_value_object_lookup_array(args, 0, &flag);
	tyran_object_insert_array(_this->data.object, length, add);
	
	return 0;
}

int tyran_array_prototype_pop(struct tyran_runtime* r, tyran_value* a, tyran_value* b, tyran_value* _this, tyran_value* return_value, int isconstructor)
{
	int length = tyran_object_length(_this->data.object);
	tyran_object_key_flag_type flag;
	TYRAN_ASSERT(length > 0, "You can not pop an empty array");
	
	length--;

	tyran_value_copy(*return_value, *tyran_value_object_lookup_array(_this, length, &flag));
	tyran_object_set_length(_this->data.object, length);
	return 0;
}

typedef struct tyran_function_info {
	const char *name;
	tyran_function_callback static_function;
} tyran_function_info;

static tyran_function_info tyran_array_functions[] = {
	{ "push", tyran_array_prototype_push },
	{ "pop", tyran_array_prototype_pop }
};

void tyran_array_prototype_init(tyran_value* constructor_prototype)
{
	tyran_array_prototype = constructor_prototype;
	size_t i;
	for (i = 0; i < sizeof(tyran_array_functions) / sizeof(struct tyran_function_info); ++i) {
		tyran_value* n = tyran_function_object_new_callback(tyran_array_functions[i].static_function);
		tyran_value_object_set_prototype(n, tyran_function_prototype);
		tyran_value_object_insert_string_key(constructor_prototype, tyran_string_from_c_str(tyran_array_functions[i].name), n);
	}
}

