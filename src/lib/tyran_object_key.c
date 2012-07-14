#include <tyranscript/tyran_object_key.h>
#include <tyranscript/tyran_config.h>
#include <tyranscript/tyran_string.h>


const struct tyran_object_key* tyran_object_key_new(const struct tyran_string* strkey, tyran_object_key_flag_type flag)
{
	tyran_object_key* key = TYRAN_MALLOC_TYPE(tyran_object_key, 1);
	key->str = tyran_string_alloc(strkey->len);
	tyran_string_strcpy((tyran_string *)key->str, (tyran_string*) strkey);
	key->flag = flag;

	return key;
}

void tyran_object_key_free(const struct tyran_object_key* key)
{
	tyran_free((void *)(((char*)key) - sizeof(tyran_string_length_type) - sizeof(tyran_object_key_flag_type)));
}

const struct tyran_object_key* tyran_object_key_clone(const struct tyran_object_key* ori)
{
	int size = ori->str->len * sizeof(tyran_string) + sizeof(tyran_string_length_type) + sizeof(tyran_object_key_flag_type);
	char *p = (char*) TYRAN_MALLOC(size);
	tyran_memcpy(p, (void *)(((char*)ori) - sizeof(tyran_string_length_type) - sizeof(tyran_object_key_flag_type)), size);

	return (const tyran_object_key*) (p + sizeof(tyran_string_length_type) + sizeof(tyran_object_key_flag_type));
}

int tyran_object_key_compare(void* key_a, void* key_b)
{
	tyran_object_key* a = (tyran_object_key*)key_a;
	tyran_object_key* b = (tyran_object_key*)key_b;

	return tyran_string_strcmp((const tyran_string*)b, (const tyran_string*)a);
}
