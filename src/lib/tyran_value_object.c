#include <tyranscript/tyran_value_object.h>
#include <tyranscript/tyran_object_iterator.h>
#include <tyranscript/tyran_value_object.h>
#include <tyranscript/tyran_value.h>
#include <tyranscript/tyran_object.h>
#include <tyranscript/tyran_object_key.h>
#include <tyranscript/tyran_object_macros.h>
#include <tyranscript/tyran_number.h>
#include <tyranscript/tyran_string.h>
#include <tyranscript/tyran_runtime.h>
#include <tyranscript/tyran_symbol_table.h>

#include "tyran_value_convert.h"
#include <tyranscript/tyran_object_key.h>
#include "tyran_number_to_string.h"

tyran_value* tyran_value_object_new(const struct tyran_runtime* runtime)
{
	tyran_value* value = tyran_value_new(runtime->value_pool);
	tyran_value_set_object(*value, tyran_object_new(runtime));
	return value;
}

void tyran_value_object_insert_c_string_key(const struct tyran_runtime* runtime, struct tyran_value* target, const char* key, struct tyran_value* value)
{
	tyran_symbol symbol;
	tyran_symbol_table_add(runtime->symbol_table, &symbol, key);
	TYRAN_ASSERT(target->type == TYRAN_VALUE_TYPE_OBJECT, "Can only insert on objects");
	tyran_object_insert(target->data.object, &symbol, value);
}

void tyran_value_object_insert(const struct tyran_runtime* runtime, struct tyran_value* target, const tyran_value* key, struct tyran_value* value) {
	char temp[128];

	tyran_string_to_c_str(temp, 128, key->data.object->data.str);
	tyran_value_object_insert_c_string_key(runtime, target, temp, value);
}


void tyran_value_object_delete(tyran_value* target, tyran_value* key)
{
	TYRAN_ASSERT(target->type == TYRAN_VALUE_TYPE_OBJECT, "Can only delete objects");
	TYRAN_ASSERT(key->type == TYRAN_VALUE_TYPE_SYMBOL, "Can only delete symbols");
	tyran_object_delete(target->data.object, &key->data.symbol);
}

const tyran_value* tyran_value_object_lookup(const tyran_value* target, const struct tyran_value* key)
{
	TYRAN_ASSERT(target->type == TYRAN_VALUE_TYPE_OBJECT, "Can only subscript on objects");
	TYRAN_ASSERT(key->type == TYRAN_VALUE_TYPE_SYMBOL, "Can only delete symbols");
	return tyran_object_lookup(target->data.object, &key->data.symbol);
}

const tyran_value* tyran_value_object_lookup_prototype(const tyran_value* target, const struct tyran_value* key)
{
	TYRAN_ASSERT(target->type == TYRAN_VALUE_TYPE_OBJECT, "Can only subscript on objects");
	TYRAN_ASSERT(key->type == TYRAN_VALUE_TYPE_SYMBOL, "Can only delete symbols");
	return tyran_object_lookup_prototype(target->data.object, &key->data.symbol);
}

void tyran_value_object_set_prototype(struct tyran_value* target, struct tyran_value* prototype)
{
	TYRAN_ASSERT(target->type == TYRAN_VALUE_TYPE_OBJECT, "Can only set prototype on objects");
	TYRAN_ASSERT(prototype->type == TYRAN_VALUE_TYPE_OBJECT, "Can only set prototype to objects");
	tyran_object_set_prototype(target->data.object, prototype);
}
