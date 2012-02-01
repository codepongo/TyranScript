#ifndef _TYRAN_OBJECT_KEY_H
#define _TYRAN_OBJECT_KEY_H

#include <tyranscript/tyran_string.h>

typedef tyran_string tyran_object_key;
typedef tyran_uint16 tyran_object_key_flag_type;

#define TYRAN_OBJECT_KEY_FLAG(ok) (*((tyran_object_key_flag_type *)(((char*)(ok)) - sizeof(tyran_string_length_type) - sizeof(tyran_object_key_flag_type))))
#define TYRAN_OBJECT_KEY(_len) struct{ TYRAN_UNICODE_STRING(_len) str; }

const tyran_object_key* tyran_object_key_new(const tyran_string* string_key, tyran_object_key_flag_type flag);
extern void tyran_object_key_free(const tyran_object_key* key);
const tyran_object_key* tyran_object_key_clone(const tyran_object_key* key);

extern int tyran_object_key_compare(void* key_a, void* key_b);

#endif
