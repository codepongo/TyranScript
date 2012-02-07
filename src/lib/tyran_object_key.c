#include <tyranscript/tyran_object_key.h>
#include <tyranscript/tyran_config.h>


const tyran_object_key* tyran_object_key_new(const tyran_string* strkey, tyran_object_key_flag_type flag)
{
	void *p = TYRAN_MALLOC(TYRAN_UNICODE_STRLEN(strkey)* sizeof(tyran_string) + sizeof(tyran_string_length_type) + sizeof(tyran_object_key_flag_type));
	tyran_object_key* ok = (tyran_object_key*) (((char*)p) + sizeof(tyran_string_length_type) + sizeof(tyran_object_key_flag_type));
	tyran_string_strcpy((tyran_string *)ok, strkey);
	TYRAN_OBJECT_KEY_SET_FLAG(ok, flag);

	return ok;
}

void tyran_object_key_free(const tyran_object_key* key)
{
	tyran_free((void *)(((char*)key) - sizeof(tyran_string_length_type) - sizeof(tyran_object_key_flag_type)));
}

const tyran_object_key* tyran_object_key_clone(const tyran_object_key* ori)
{
	int size = TYRAN_UNICODE_STRLEN(ori) * sizeof(tyran_string) + sizeof(tyran_string_length_type) + sizeof(tyran_object_key_flag_type);
	char *p = (char*) TYRAN_MALLOC(size);
	tyran_memcpy(p, (void *)(((char*)ori) - sizeof(tyran_string_length_type) - sizeof(tyran_object_key_flag_type)), size);

	return (const tyran_object_key*) (p + sizeof(tyran_string_length_type) + sizeof(tyran_object_key_flag_type));
}

int tyran_object_key_compare(void* key_a, void* key_b)
{
	tyran_object_key* a = (tyran_object_key*)key_a;
	tyran_object_key* b = (tyran_object_key*)key_b;

	return tyran_string_strcmp(b, a);
}
