#include <tyranscript/tyran_object_prototype.h>
#include <tyranscript/tyran_value_object.h>
#include <tyranscript/tyran_value.h>

tyran_value* tyran_object_prototype;
struct tyran_runtime;

void tyran_object_prototype_init(tyran_value* constructor_prototype)
{
	tyran_object_prototype = constructor_prototype;
}

int tyran_object_prototype_constructor(struct tyran_runtime *ps, tyran_value* static_function, tyran_value* args, tyran_value* _this, tyran_value* ret, int is_constructor)
{
	return 0;
}
