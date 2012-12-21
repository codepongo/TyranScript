#include <tyranscript/tyran_value_object.h>
#include <tyranscript/tyran_object_iterator.h>
#include <tyranscript/tyran_value_object.h>
#include <tyranscript/tyran_value.h>
#include <tyranscript/tyran_object.h>
#include <tyranscript/tyran_object_key.h>
#include <tyranscript/tyran_object_macros.h>
#include <tyranscript/tyran_number.h>
#include <tyranscript/tyran_string.h>

#include "tyran_value_convert.h"
#include <tyranscript/tyran_object_key.h>
#include "tyran_number_to_string.h"

tyran_value* tyran_value_object_new(tyran_memory_pool* value_pool, tyran_memory_pool* object_pool, const struct tyran_runtime* runtime)
{
	tyran_value* value = tyran_value_new(value_pool);
	tyran_value_set_object(*value, tyran_object_new(object_pool, runtime));
	return value;
}
void tyran_value_object_insert_array(tyran_value* target, int key, tyran_value* value)
{
	TYRAN_ASSERT(target->type == TYRAN_VALUE_TYPE_OBJECT, "Only objects can contain arrays");
	tyran_object_insert_array(target->data.object, key, value);
}


void tyran_value_object_delete(tyran_value* target, tyran_value* key)
{
	TYRAN_ASSERT(target->type == TYRAN_VALUE_TYPE_OBJECT, "Can only delete objects");

	tyran_value_convert_to_string(key);

	tyran_object_delete(target->data.object, (const struct tyran_object_key*)key->data.str);
}

tyran_value* tyran_value_object_lookup(const tyran_value* target, const struct tyran_object_key* key, tyran_object_key_flag_type* flag)
{
	TYRAN_LOG("tyran_value");
	TYRAN_ASSERT(target->type == TYRAN_VALUE_TYPE_OBJECT, "Can only subscript on objects");
	return tyran_object_lookup(target->data.object, key, flag);
}


void tyran_value_object_insert_c_string_key(tyran_memory_pool* string_pool, tyran_memory* memory, struct tyran_memory_pool* object_key_pool, struct tyran_memory_pool* rb_node_pool, struct tyran_value* target, const char* key, struct tyran_value* value)
{
	TYRAN_ASSERT(target->type == TYRAN_VALUE_TYPE_OBJECT, "Can only subscript on objects");
	tyran_object_insert_c_string_key(string_pool, memory, object_key_pool, rb_node_pool, target->data.object, key, value);
}

void tyran_value_object_insert_string_key(struct tyran_value* object, const struct tyran_string* key, struct tyran_value* value)
{
}

tyran_value* tyran_value_object_lookup_prototype(const tyran_value* target, const struct tyran_object_key* key, tyran_object_key_flag_type* flag)
{
	TYRAN_ASSERT(target->type == TYRAN_VALUE_TYPE_OBJECT, "Can only subscript on objects");
	return tyran_object_lookup_prototype(target->data.object, key, flag);
}

struct tyran_value* tyran_value_object_lookup_array(const struct tyran_value* object, int index, tyran_object_key_flag_type* flag)
{
	return 0;
}

void tyran_value_object_set_prototype(struct tyran_value* target, struct tyran_value* prototype)
{
	if (!prototype) {
		return;
	}
	TYRAN_ASSERT(target->type == TYRAN_VALUE_TYPE_OBJECT, "Can only set prototype on objects");
	TYRAN_ASSERT(prototype->type == TYRAN_VALUE_TYPE_OBJECT, "Can only set prototype to objects");
	tyran_object_set_prototype(target->data.object, prototype);
}

int tyran_value_object_has_key(const tyran_value* target, const struct tyran_object_key* key)
{
	tyran_object_key_flag_type flag;
	TYRAN_ASSERT(target->type == TYRAN_VALUE_TYPE_OBJECT, "Only objects has keys");


	if (tyran_value_object_lookup(target, key, &flag)) {
		return 1;
	}

	if (!target->data.object->prototype) {
		return 0;
	}
	return tyran_value_object_has_key(target->data.object->prototype, key);
}
