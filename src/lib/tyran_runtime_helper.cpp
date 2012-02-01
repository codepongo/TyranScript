#include <tyranscript/tyran_value.h>
#include <tyranscript/tyran_value_object.h>
#include <tyranscript/tyran_runtime.h>

#include "tyran_runtime_helper.h"
#include "tyran_value_convert.h"

tyran_runtime* tyran_runtime_new()
{
	tyran_runtime* rt = TYRAN_CALLOC(tyran_runtime);
	return rt;
}

void tyran_runtime_free(tyran_runtime* rt)
{
	tyran_free(rt);
}

void tyran_runtime_logical_less(tyran_value v1, tyran_value v2, tyran_value* res)
{
	TYRAN_ASSERT(tyran_value_is_same_type(&v2, &v1), "Must be same type");
	TYRAN_ASSERT(tyran_value_is_number(&v1) && tyran_value_is_number(&v2), "Must compare numbers");
	TYRAN_ASSERT(tyran_number_is_normal(v1.data.number) && tyran_number_is_normal(v2.data.number), "Numbers are bad");
	int val = (v1.data.number < v2.data.number);
	tyran_value_replace_boolean(*res, val);
}

void tyran_runtime_value_object_subscript(tyran_value* target, tyran_value* key, tyran_value* existing_value, enum tyran_subscript_mode mode)
{
	TYRAN_ASSERT(target->type == TYRAN_VALUE_TYPE_OBJECT, "Can only subscript objects");

	tyran_value_convert_to_string(key);

	int flag;
	tyran_value* r = tyran_value_object_lookup((const tyran_value*)target, (const tyran_object_key*) key->data.str, &flag);
	if (!r) {
		if (target->data.object->prototype) {
			tyran_runtime_value_object_subscript(target->data.object->prototype, key, existing_value, tyran_subscript_read);
		}
		if (mode == tyran_subscript_write) {
			tyran_value* value = tyran_value_new();
			tyran_value_copy(*value, *existing_value);

			const tyran_object_key* nk = tyran_object_key_new(key->data.str, 0);
			tyran_value_object_insert_key(target, nk, value);
			tyran_value_replace_variable(*existing_value, value);
		}
	} else {
		if (mode == tyran_subscript_read) {
			tyran_value_copy(*existing_value, *r);
		} else {
			tyran_value_set_variable(*existing_value, r);
		}
	}
}

