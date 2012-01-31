#include <tyranscript/tyran_value_object.h>
#include <tyranscript/tyran_object_iterator.h>
#include <tyranscript/tyran_value_object.h>
#include <tyranscript/tyran_value.h>
#include <tyranscript/tyran_object.h>

#include "tyran_value_convert.h"
#include <tyranscript/tyran_object_key.h>
#include "tyran_number_to_string.h"

tyran_value* tyran_value_object_new()
{
	tyran_value* value = tyran_value_new();
	tyran_value_set_object(*value, tyran_object_new());
	return value;
}

void tyran_value_object_insert_key(tyran_value* target, const tyran_object_key* key, tyran_value* value)
{
	TYRAN_ASSERT(target->type == TYRAN_VALUE_TYPE_OBJECT, "Can only insert keys on objects");
	tyran_object_insert_key(target->data.object, key, value);
}

void tyran_value_object_insert_string_key(tyran_value* target, const tyran_string* key, tyran_value* value)
{
	TYRAN_ASSERT(target->type == TYRAN_VALUE_TYPE_OBJECT, "Only objects can have keys");
	tyran_object_insert_string_key(target->data.object, key, value);
}

void tyran_value_object_insert_array(tyran_value* target, int key, tyran_value* value)
{
	TYRAN_ASSERT(target->type == TYRAN_VALUE_TYPE_OBJECT, "Only objects can contain arrays");
	tyran_object_insert_array(target->data.object, key, value);
}

tyran_value* tyran_value_object_insert_key_and_flag(tyran_value* target, tyran_value* key, const tyran_value* value, tyran_object_key_flag_type flag)
{
	const tyran_object_key* ok = 0;

	int arrayindex = -1;

	if (tyran_value_is_number(key) && tyran_value_is_integer(key->data.number) && key->data.number >= 0) {
		arrayindex = (int)key->data.number;
	}

	tyran_value_convert_to_string(key);
	ok = tyran_object_key_new(key->data.str, flag);

	tyran_value* v = tyran_value_new();
	tyran_value_copy(*v, *value);
	tyran_value_object_insert_key(target, ok, v);
	if (arrayindex >= 0) {
		tyran_object_extend_length_if_needed(target->data.object, arrayindex);
	}

	return v;
}

void tyran_value_object_delete(tyran_value* target, tyran_value* key)
{
	TYRAN_ASSERT(target->type == TYRAN_VALUE_TYPE_OBJECT, "Can only delete objects");

	tyran_value_convert_to_string(key);

	tyran_object_delete(target->data.object, (const tyran_object_key*)key->data.str);
}

tyran_value* tyran_value_object_lookup(const tyran_value* target, const tyran_object_key* key, int *flag)
{
	TYRAN_ASSERT(target->type == TYRAN_VALUE_TYPE_OBJECT, "Can only subscript on objects");
	return tyran_object_lookup(target->data.object, key, flag);
}

tyran_value* tyran_value_object_lookup_prototype(const tyran_value* target, const tyran_object_key* key, int *flag)
{
	TYRAN_ASSERT(target->type == TYRAN_VALUE_TYPE_OBJECT, "Can only subscript on objects");
	return tyran_object_lookup_prototype(target->data.object, key, flag);
}

tyran_value* tyran_value_object_lookup_array(const tyran_value* args, int index, int* flag)
{
	TYRAN_UNICODE_STRING(12) string_buffer;
	tyran_number_integer_to_string(index, string_buffer.string);
	return tyran_object_lookup(args->data.object, string_buffer.string, flag);
}

int tyran_value_object_has_key(const tyran_value* target, const tyran_object_key* key)
{
	TYRAN_ASSERT(target->type == TYRAN_VALUE_TYPE_OBJECT, "Only objects has keys");

	if (tyran_value_object_lookup(target, key, 0)) {
		return 1;
	}

	if (!target->data.object->prototype) {
		return 0;
	}
	return tyran_value_object_has_key(target->data.object->prototype, key);
}

void tyran_value_object_fetch_key_iterator(tyran_value* target, tyran_value* return_value)
{
	tyran_object_iterator* iterator = tyran_object_iterator_new();

	tyran_object_get_keys(target, iterator);

	tyran_object* r = tyran_object_new();
	r->type = TYRAN_OBJECT_TYPE_ITERATOR;
	r->data.iterator = iterator;

	tyran_value_set_object(*return_value, r);
}
