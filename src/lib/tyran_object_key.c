#include <tyranscript/tyran_object_key.h>
#include <tyranscript/tyran_config.h>
#include <tyranscript/tyran_string.h>

const struct tyran_object_key* tyran_object_key_new(tyran_memory_pool* object_key_pool, const struct tyran_string* strkey, tyran_object_key_flag_type flag)
{
	tyran_object_key* key = TYRAN_MALLOC_TYPE_COUNT(object_key_pool, tyran_object_key, 1);
	// key->str = tyran_string_strcpy(strkey);
	key->flag = flag;

	return key;
}

void tyran_object_key_free(const struct tyran_object_key* key)
{
	tyran_string_free(key->str);
	tyran_free((void*) key);
}

const struct tyran_object_key* tyran_object_key_clone(tyran_memory_pool* object_key_pool, const struct tyran_object_key* ori)
{
	tyran_object_key* key = TYRAN_MALLOC_TYPE_COUNT(object_key_pool, tyran_object_key, 1);
	// key->str = tyran_string_strcpy(ori->str);
	key->flag = ori->flag;
	return key;
}

int tyran_object_key_compare(void* key_a, void* key_b)
{
	tyran_object_key* a = (tyran_object_key*)key_a;
	tyran_object_key* b = (tyran_object_key*)key_b;

	return tyran_string_strcmp(b->str, a->str);
}
