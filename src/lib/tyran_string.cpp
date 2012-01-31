#include <tyranscript/tyran_string.h>
#include <tyranscript/tyran_config.h>

const tyran_string* tyran_string_strdup(const tyran_string* str)
{
	int len = TYRAN_UNICODE_STRLEN(str);

	tyran_string* r = (tyran_string*) TYRAN_MALLOC(len * sizeof(tyran_string) + sizeof(tyran_string_length_type) );
	tyran_string* rr = (tyran_string *)((char*)r + sizeof(tyran_string_length_type));

	*((tyran_string_length_type *)r) = len;

	tyran_memcpy(rr, str, (len) * sizeof(tyran_string));
	return rr;
}

const tyran_string* tyran_string_strdup_str(const char *str)
{
	int len = tyran_strlen(str);

	tyran_string* r = (tyran_string*) TYRAN_MALLOC(len * sizeof(tyran_string) + sizeof(tyran_string_length_type));
	tyran_string* rr = (tyran_string *)((char*)r + sizeof(tyran_string_length_type));
	int i;

	*((tyran_string_length_type *)r) = len;

	for (i = 0; i < len; ++i) rr[i] = str[i];

	return rr;
}

void tyran_string_strcpy(tyran_string* to, const tyran_string* from)
{
	int len = TYRAN_UNICODE_STRLEN(from);
	int i;
	for (i = 0; i < len; ++i) to[i] = from[i];

	TYRAN_UNICODE_STRLEN(to) = len;
}

void tyran_string_free(const tyran_string* d)
{
	tyran_free((void *)(((char*)d) - sizeof(tyran_string_length_type) ));
}

const int max_string_len = 512;

const char *tyran_string_to_c_str(const tyran_string* str)
{
	static char buf[max_string_len];
	int i;
	int len = TYRAN_UNICODE_STRLEN(str);

	for (i = 0; i < len && i < max_string_len; ++i) buf[i] = (char)str[i];
	buf[i] = 0;
	return buf;
}

const tyran_string* tyran_string_from_c_str(const char* str)
{
	static tyran_string buf[max_string_len];
	tyran_string_length_type *len = (tyran_string_length_type *)buf;
	tyran_string* b = (tyran_string *)((char*)buf + sizeof(tyran_string_length_type));
	tyran_string_length_type i;

	for (i = 0; str[i] && i < max_string_len; ++i) {
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
		if ((r = str1[i] - str2[i])) return r;
	}
	return 0;
}

const tyran_string* tyran_string_strcat(const tyran_string* str1, const tyran_string* str2)
{
	int len = TYRAN_UNICODE_STRLEN(str1) + TYRAN_UNICODE_STRLEN(str2);
	tyran_string* r = (tyran_string*) TYRAN_MALLOC(len * sizeof(tyran_string) + sizeof(tyran_string_length_type) );
	tyran_string* rr = (tyran_string *)((char*)r + sizeof(tyran_string_length_type));

	*((tyran_string_length_type *)r) = len;

	tyran_memcpy(rr, str1, TYRAN_UNICODE_STRLEN(str1) * sizeof(tyran_string));
	tyran_memcpy(rr + TYRAN_UNICODE_STRLEN(str1), str2, TYRAN_UNICODE_STRLEN(str2) * sizeof(tyran_string));
	return rr;
}
