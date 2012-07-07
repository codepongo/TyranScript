#include <tyranscript/tyran_object_pool.h>
#include <tyranscript/tyran_config.h>
#include <tyranscript/tyran_object.h>

void tyran_object_pool_free(tyran_object_pool* pool, struct tyran_object* o)
{
}

struct tyran_object* tyran_object_pool_alloc(tyran_object_pool* pool)
{
	return tyran_object_new(0);
}
