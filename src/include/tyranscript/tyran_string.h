#ifndef _TYRAN_STRING_H
#define _TYRAN_STRING_H

#include <tyranscript/tyran_config.h>

typedef tyran_uint16 tyran_string_length_type;

typedef struct tyran_string {
	tyran_string_length_type len;
	tyran_uint16* buf;
} tyran_string;

tyran_string* tyran_string_alloc(int max_size);

const tyran_string* tyran_string_from_c_str(const char* str);
const tyran_string* tyran_string_strcat(const tyran_string* str1, const tyran_string* str2);
const tyran_string* tyran_string_strdup(const tyran_string* str);
const tyran_string* tyran_string_strdup_str(const char *str);
void tyran_string_free(const tyran_string* d);

void tyran_string_strcpy(tyran_string* to, const tyran_string* from);
const tyran_string* tyran_string_substr(const tyran_string* str, int start, int len);
void tyran_string_to_c_str(char* buf, int max_size, const tyran_string* str);

int tyran_string_strcmp(const tyran_string* str1, const tyran_string* str2);

#endif
