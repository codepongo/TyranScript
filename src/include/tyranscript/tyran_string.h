#ifndef _TYRAN_STRING_H
#define _TYRAN_STRING_H

#include <tyranscript/tyran_config.h>

typedef u16t tyran_string_length_type;

typedef u16t tyran_string_char;

typedef struct tyran_string {
	tyran_string_length_type len;
	tyran_string_char* buf;
} tyran_string;

void tyran_string_free(const tyran_string* str);
const tyran_string* tyran_string_new(tyran_memory_pool* string_pool, tyran_memory* memory, int len);
const tyran_string* tyran_string_from_c_str(tyran_memory_pool* string_pool, tyran_memory* memory, const char* str);
const tyran_string* tyran_string_from_characters(tyran_memory_pool* string_pool, tyran_memory* memory, const tyran_string_char* str, int len);
const tyran_string* tyran_string_strcat(tyran_memory_pool* string_pool, tyran_memory* memory, const tyran_string* str1, const tyran_string* str2);
const tyran_string* tyran_string_strdup(tyran_memory_pool* string_pool, tyran_memory* memory, const tyran_string* str);
const tyran_string* tyran_string_strdup_str(tyran_memory_pool* string_pool, tyran_memory* memory, const char* str);
void tyran_string_free(const tyran_string* d);

const tyran_string* tyran_string_strcpy(tyran_memory_pool* string_pool, tyran_memory* memory, const tyran_string* from);
const tyran_string* tyran_string_substr(tyran_memory_pool* string_pool, tyran_memory* memory, const tyran_string* str, int start, int len);
void tyran_string_to_c_str(char* buf, int max_size, const tyran_string* str);
int tyran_string_strcmp(const tyran_string* str1, const tyran_string* str2);

#endif
