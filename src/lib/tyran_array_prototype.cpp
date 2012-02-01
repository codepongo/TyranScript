#include <tyranscript/parser/tyran_parser_state.h>
#include <tyranscript/tyran_value.h>
#include <tyranscript/tyran_function.h>
#include <tyranscript/tyran_function_object.h>

#include <tyranscript/tyran_object_prototype.h>
#include <tyranscript/tyran_function_prototype.h>

#include <tyranscript/tyran_value_object.h>

tyran_value* tyran_array_prototype;

int tyran_array_prototype_constructor(struct tyran_runtime *ps, tyran_value* static_function, tyran_value* args, tyran_value* _this, tyran_value* ret, int is_constructor)
{
	return 0;
}

int tyran_array_prototype_push(struct tyran_runtime* ps,  tyran_value* static_function, tyran_value* args, tyran_value* _this, tyran_value* ret, int is_constructor)
{
	return 0;
}

int tyran_array_prototype_pop(struct tyran_runtime* ps,  tyran_value* static_function, tyran_value* args, tyran_value* _this, tyran_value* ret, int is_constructor)
{
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

void tyran_array_prototype_init()
{
	tyran_array_prototype = tyran_value_object_new();
	tyran_value_object_set_prototype(tyran_array_prototype, tyran_object_prototype);
	tyran_object_set_length(tyran_array_prototype->data.object, 0);

	size_t i;
	for (i = 0; i < sizeof(tyran_array_functions) / sizeof(struct tyran_function_info); ++i) {
		tyran_value* n = tyran_function_object_new_callback(tyran_array_functions[i].static_function);
		tyran_value_object_set_prototype(n, tyran_function_prototype);
		tyran_value_object_insert_string_key(tyran_array_prototype, tyran_string_from_c_str(tyran_array_functions[i].name), n);
	}
}

