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
#include <tyranscript/tyran_array.h>
#include <tyranscript/tyran_runtime.h>

int tyran_array_prototype_constructor(struct tyran_runtime* runtime, tyran_value* a, tyran_value* b, tyran_value* _this, tyran_value* return_value, int is_constructor)
{
	tyran_value length;
	tyran_value_set_number(length, 0);

	tyran_array* array = tyran_array_new(runtime->memory);

	tyran_object_set_array(_this->data.object, array);

	tyran_value_object_insert_c_string_key(runtime, _this, "length", &length);

	return 0;
}

int tyran_array_prototype_push(struct tyran_runtime* runtime, tyran_value* a, tyran_value* args, tyran_value* _this, tyran_value* c, int isconstructor)
{
	tyran_value length;

	tyran_value_set_number(length, 0);
	tyran_array_insert(_this->data.object->data.array, runtime->rb_node_pool, &length, args);

	tyran_value_set_number(length, 1);
	tyran_value_object_insert_c_string_key(runtime, _this, "length", &length);
	return 0;
}

int tyran_array_prototype_index(struct tyran_runtime* runtime, tyran_value* a, tyran_value* args, tyran_value* _this, tyran_value* return_value, int isconstructor)
{
	int index = (int) args->data.number;
	TYRAN_LOG("******* INDEX!!:%d", index);
	tyran_value* v = tyran_array_lookup(_this->data.object->data.array, args);
	if (!v) {
		tyran_value_set_undefined(*return_value);
	} else {
		tyran_value_copy(*return_value, *v);
	}
	return 0;
}

int tyran_array_prototype_index_set(struct tyran_runtime* runtime, tyran_value* a, tyran_value* args, tyran_value* _this, tyran_value* return_value, int isconstructor)
{
	int index = (int) args->data.number;
	TYRAN_LOG("******* INDEX_SET!!:%d", index);
	tyran_array_insert(_this->data.object->data.array, runtime->rb_node_pool, &args[0], &args[1]);
	tyran_value_set_undefined(*return_value);
	return 0;
}



int tyran_array_prototype_pop(struct tyran_runtime* r, tyran_value* a, tyran_value* b, tyran_value* _this, tyran_value* return_value, int isconstructor)
{
	return 0;
}

void tyran_array_prototype_init(const struct tyran_runtime* runtime, tyran_value* o) {
	TYRAN_MEMBER(o, "[]=", tyran_array_prototype_index_set);
	TYRAN_MEMBER(o, "[]", tyran_array_prototype_index);
	TYRAN_MEMBER(o, "push", tyran_array_prototype_push);
	TYRAN_MEMBER(o, "constructor", tyran_array_prototype_constructor);
}
