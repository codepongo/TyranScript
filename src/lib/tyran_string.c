#include <tyranscript/tyran_string.h>
#include <tyranscript/tyran_config.h>

const tyran_string* tyran_string_new(tyran_memory_pool* string_pool, tyran_memory* memory, int len)
{
	tyran_string* str = TYRAN_MALLOC_TYPE(string_pool, tyran_string);
	str->buf = TYRAN_MALLOC_NO_POOL_TYPE_COUNT(memory, tyran_string_char, len);
	str->len = len;

	return str;
}

void tyran_string_free(const tyran_string* str)
{
	tyran_free(str->buf);
	TYRAN_MALLOC_FREE((void*)str);
}


const tyran_string* tyran_string_strdup(tyran_memory_pool* string_pool, tyran_memory* memory,  const tyran_string* str)
{
	int len = str->len;
	const tyran_string* duplicate = tyran_string_new(string_pool, memory, len);
	tyran_memcpy_type(tyran_string_char, duplicate->buf, str->buf, len);
	return duplicate;
}

const tyran_string* tyran_string_strdup_str(tyran_memory_pool* string_pool, tyran_memory* memory, const char* str)
{
	int len = tyran_strlen(str);
	int i;

	const tyran_string* rr = tyran_string_new(string_pool, memory, len);

	for (i = 0; i < len; ++i) {
		rr->buf[i] = str[i];
	}

	return rr;
}

const tyran_string* tyran_string_substr(tyran_memory_pool* string_pool, tyran_memory* memory, const tyran_string* str, int start, int len)
{
	int source_string_length = str->len;

	if (start < 0) {
		start += source_string_length;
	} else if (start >= source_string_length) {
		return tyran_string_strdup_str(string_pool, memory, "");
	}

	int characters_to_copy = source_string_length - start;
	characters_to_copy = characters_to_copy < len ? characters_to_copy : len;
	const tyran_string* rr = tyran_string_new(string_pool, memory, characters_to_copy);

	tyran_memcpy_type(tyran_string_char, rr->buf, str->buf + start, characters_to_copy);

	return rr;
}

const tyran_string* tyran_string_strcpy(tyran_memory_pool* string_pool, tyran_memory* memory, const tyran_string* from)
{
	int len = from->len;
	const tyran_string* to = tyran_string_new(string_pool, memory, len);
	tyran_memcpy_type(tyran_string_char, to->buf, from->buf, len);

	return to;
}

void tyran_string_to_c_str(char* buf, int tyran_string_max_length, const tyran_string* str)
{
	int i;
	int len = str->len;

	for (i = 0; i < len && i < tyran_string_max_length - 1; ++i) {
		buf[i] = (char)str->buf[i];
	}
	buf[i] = 0;
}

const tyran_string* tyran_string_from_c_str(tyran_memory_pool* string_pool, tyran_memory* memory, const char* str)
{
	int len = tyran_strlen(str);
	const tyran_string* target = tyran_string_new(string_pool, memory, len);
	tyran_string_length_type i;

	for (i = 0; i < len; ++i) {
		target->buf[i] = str[i];
	}

	return target;
}

const tyran_string* tyran_string_from_characters(tyran_memory_pool* string_pool, tyran_memory* memory, const tyran_string_char* str, int len)
{
	const tyran_string* target = tyran_string_new(string_pool, memory, len);

	tyran_memcpy_type(tyran_string_char, target->buf, str, len);

	return target;
}


int tyran_string_strcmp(const tyran_string* str1, const tyran_string* str2)
{
	int len1 = str1->len;
	int len2 = str2->len;

	int i, r;

	if (len1 != len2) {
		return len1 - len2;
	}

	for (i = 0; i < len1; ++i) {
		r = str1->buf[i] - str2->buf[i];
		if (r) {
			return r;
		}
	}
	return 0;
}

const tyran_string* tyran_string_strcat(tyran_memory_pool* string_pool, tyran_memory* memory, const tyran_string* str1, const tyran_string* str2)
{
	int len = str1->len + str2->len;
	const tyran_string* rr = tyran_string_new(string_pool, memory, len);

	tyran_memcpy_type(tyran_string_char, rr->buf, str1->buf, str1->len);
	tyran_memcpy_type(tyran_string_char, rr->buf + str1->len, str2->buf, str2->len);
	return rr;
}
