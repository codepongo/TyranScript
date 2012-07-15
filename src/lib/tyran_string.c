#include <tyranscript/tyran_string.h>
#include <tyranscript/tyran_config.h>

const tyran_string* tyran_string_alloc(int len)
{
	tyran_string* str = TYRAN_MALLOC_TYPE(tyran_string, 1);
	str->buf = TYRAN_MALLOC_TYPE(tyran_string_char, len);
	str->len = len;
	
	return str;
}

void tyran_string_free(const tyran_string* str)
{
	tyran_free(str->buf);
	tyran_free((void*)str);
}


const tyran_string* tyran_string_strdup(const tyran_string* str)
{
	int len = str->len;
	const tyran_string* duplicate = tyran_string_alloc(len);
	tyran_memcpy(duplicate->buf, str->buf, len * sizeof(tyran_string_char));
	return duplicate;
}

const tyran_string* tyran_string_strdup_str(const char *str)
{
	int len = tyran_strlen(str);
	int i;

	const tyran_string* rr = tyran_string_alloc(len);

	for (i = 0; i < len; ++i) {
		rr->buf[i] = str[i];
	}

	return rr;
}

const tyran_string* tyran_string_substr(const tyran_string* str, int start, int len)
{
	int source_string_length = str->len;
	
	if (start < 0) {
		start += source_string_length;
	} else if (start >= source_string_length) {
		return tyran_string_strdup_str("");
	}

	int characters_to_copy = source_string_length - start;
	characters_to_copy = characters_to_copy < len ? characters_to_copy : len;
	const tyran_string* rr = tyran_string_alloc(characters_to_copy);

	tyran_memcpy(rr->buf, str->buf + start, characters_to_copy * sizeof(tyran_string_char));
	
	return rr;
}

const tyran_string* tyran_string_strcpy(const tyran_string* from)
{
	int len = from->len;
	const tyran_string* to = tyran_string_alloc(len);
	tyran_memcpy(to->buf, from->buf, len * sizeof(tyran_string_char));

	return to;
}

void tyran_string_to_c_str(char* buf, int tyran_string_max_length, const tyran_string* str)
{
	int i;
	int len = str->len;

	for (i = 0; i < len && i < tyran_string_max_length - 1; ++i) buf[i] = (char)str->buf[i];
	buf[i] = 0;
}

const tyran_string* tyran_string_from_c_str(const char* str)
{
	int len = tyran_strlen(str);
	const tyran_string* target = tyran_string_alloc(len);
	tyran_string_length_type i;

	for (i = 0; i < len; ++i) {
		target->buf[i] = str[i];
	}

	return target;
}

const tyran_string* tyran_string_from_characters(const tyran_string_char* str, int len)
{
	const tyran_string* target = tyran_string_alloc(len);

	tyran_memcpy(target->buf, str, len * sizeof(tyran_string_char));

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

const tyran_string* tyran_string_strcat(const tyran_string* str1, const tyran_string* str2)
{
	int len = str1->len + str2->len;
	const tyran_string* rr = tyran_string_alloc(len);

	tyran_memcpy(rr->buf, str1->buf, str1->len * sizeof(tyran_string_char));
	tyran_memcpy(rr->buf + str1->len, str2->buf, str2->len * sizeof(tyran_string_char));
	return rr;
}
