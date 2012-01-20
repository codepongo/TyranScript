#ifndef _TYRAN_UNICODE_H
#define _TYRAN_UNICODE_H

#include <tyranscript/config.h>

#define TYRAN_UNICODE_STRING(_len) struct{ unichar_length_type len; unicode_char unistr[(_len)]; }
#define TYRAN_UNICODE_STRLEN(str) (*((unichar_length_type *)(((char*)(str)) - sizeof(unichar_length_type))))

typedef tyran_uint16 unicode_char;
typedef tyran_uint16 unichar_length_type;

unicode_char* tyran_unicode_strdup(const unicode_char *str);
void tyran_unicode_strcpy(unicode_char *to, const unicode_char *from);
unicode_char* tyran_unicode_strcat(const unicode_char *str1, const unicode_char *str2);
int tyran_unicode_strcmp(const unicode_char *str1, const unicode_char *str2);
void tyran_unicode_free(const unicode_char* d);
const unicode_char* tyran_unicode_from_c_str(const char* str);
const char *tyran_unicode_to_c_str(const unicode_char* str);

#endif
