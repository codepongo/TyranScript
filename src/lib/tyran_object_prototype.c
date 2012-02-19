#include <tyranscript/tyran_object_prototype.h>
#include <tyranscript/tyran_value_object.h>
#include <tyranscript/tyran_value.h>

tyran_value* tyran_object_prototype;
struct tyran_runtime;

void tyran_object_prototype_init(const struct tyran_runtime* runtime, tyran_value* constructor_prototype)
{
	tyran_object_prototype = constructor_prototype;
}

int tyran_object_prototype_constructor(struct tyran_runtime* runtime, tyran_value* a, tyran_value* b, tyran_value* c, tyran_value* d, int is_constructor)
{
	return 0;
}
