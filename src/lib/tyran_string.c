#include <tyranscript/tyran_string.h>
#include <tyranscript/tyran_config.h>


tyran_string* tyran_string_alloc(int len)
{
	char* r = (char*) TYRAN_MALLOC(len * sizeof(tyran_string) + sizeof(tyran_string_length_type) );
	tyran_string* rr = (tyran_string *)(r + sizeof(tyran_string_length_type));
	*((tyran_string_length_type *)r) = (tyran_string_length_type) len;

	return rr;
}

const tyran_string* tyran_string_strdup(const tyran_string* str)
{
	int len = TYRAN_UNICODE_STRLEN(str);
	tyran_string* rr = tyran_string_alloc(len);
	tyran_memcpy(rr, str, (len) * sizeof(tyran_string));
	return rr;
}



const tyran_string* tyran_string_strdup_str(const char *str)
{
	int len = tyran_strlen(str);
	int i;

	tyran_string* rr = tyran_string_alloc(len);

	for (i = 0; i < len; ++i) {
		rr[i] = str[i];
	}

	return rr;
}

const tyran_string* tyran_string_substr(const tyran_string* str, int start, int len)
{
	int source_string_length = TYRAN_UNICODE_STRLEN(str);
	
	if (start < 0) {
		start += source_string_length;
	} else if (start >= source_string_length) {
		return tyran_string_strdup_str("");
	}

	int characters_to_copy = source_string_length - start;
	characters_to_copy = characters_to_copy < len ? characters_to_copy : len;
	tyran_string* rr = tyran_string_alloc(characters_to_copy);

	tyran_memcpy(rr, str + start, characters_to_copy * sizeof(tyran_string));
	
	return rr;
}

void tyran_string_strcpy(tyran_string* to, const tyran_string* from)
{
	int len = TYRAN_UNICODE_STRLEN(from);
	int i;
	for (i = 0; i < len; ++i) to[i] = from[i];

	TYRAN_UNICODE_STRLEN(to) = (tyran_string_length_type) len;
}

void tyran_string_free(const tyran_string* d)
{
	tyran_free((void *)(((char*)d) - sizeof(tyran_string_length_type) ));
}

void tyran_string_to_c_str(char* buf, int tyran_string_max_length, const tyran_string* str)
{
	int i;
	int len = TYRAN_UNICODE_STRLEN(str);

	for (i = 0; i < len && i < tyran_string_max_length - 1; ++i) buf[i] = (char)str[i];
	buf[i] = 0;
}

const tyran_string* tyran_string_from_c_str(const char* str)
{
	const int tyran_string_max_length = 512;
	static tyran_string buf[tyran_string_max_length];
	tyran_string_length_type *len = (tyran_string_length_type *)buf;
	tyran_string* b = (tyran_string *)((char*)buf + sizeof(tyran_string_length_type));
	tyran_string_length_type i;

	for (i = 0; str[i] && i < tyran_string_max_length; ++i) {
		b[i] = str[i];
	}
	*len = i;

	return b;
}

int tyran_string_strcmp(const tyran_string* str1, const tyran_string* str2)
{
	int len1 = TYRAN_UNICODE_STRLEN(str1);
	int len2 = TYRAN_UNICODE_STRLEN(str2);

	int i, r;
	if (len1 != len2) return len1 - len2;

	for (i = 0; i < len1; ++i) {
		r = str1[i] - str2[i];
		if (r) {
			return r;
		}
	}
	return 0;
}

const tyran_string* tyran_string_strcat(const tyran_string* str1, const tyran_string* str2)
{
	int len = TYRAN_UNICODE_STRLEN(str1) + TYRAN_UNICODE_STRLEN(str2);
	tyran_string* rr = tyran_string_alloc(len);

	tyran_memcpy(rr, str1, TYRAN_UNICODE_STRLEN(str1) * sizeof(tyran_string));
	tyran_memcpy(rr + TYRAN_UNICODE_STRLEN(str1), str2, TYRAN_UNICODE_STRLEN(str2) * sizeof(tyran_string));
	return rr;
}
