#ifndef _TYRAN_OBJECT_KEY_H
#define _TYRAN_OBJECT_KEY_H

#include <tyranscript/tyran_config.h>

struct tyran_string;

typedef tyran_uint16 tyran_object_key_flag_type;

typedef struct tyran_object_key {
	const struct tyran_string* str;
	tyran_object_key_flag_type flag;
} tyran_object_key;

static const tyran_object_key_flag_type tyran_object_key_flag_enumerate = 1;
static const tyran_object_key_flag_type tyran_object_key_flag_normal = 1;

#define tyran_object_key_has_enumerate(key) (key->flag & tyran_object_key_flag_enumerate)

const struct tyran_object_key* tyran_object_key_new(tyran_memory_pool* object_key_pool, const struct tyran_string* string_key, tyran_object_key_flag_type flag);
extern void tyran_object_key_free(const struct tyran_object_key* key);
const struct tyran_object_key* tyran_object_key_clone(tyran_memory_pool* object_key_pool, const struct tyran_object_key* key);

extern int tyran_object_key_compare(void* key_a, void* key_b);

#endif
