#include <tyranscript/tyran_value_object.h>
#include <tyranscript/tyran_value_object.h>
#include <tyranscript/tyran_value.h>
#include <tyranscript/tyran_object.h>
#include <tyranscript/tyran_object_macros.h>
#include <tyranscript/tyran_number.h>
#include <tyranscript/tyran_string.h>
#include <tyranscript/tyran_runtime.h>
#include <tyranscript/tyran_symbol_table.h>

tyran_value* tyran_value_object_new(const struct tyran_runtime* runtime)
{
	tyran_value* value = tyran_value_new(runtime->value_pool);
	tyran_value_set_object(*value, tyran_object_new(runtime));
	return value;
}

void tyran_value_object_insert(const struct tyran_runtime* runtime, struct tyran_value* target, const tyran_value* key, struct tyran_value* value)
{
	TYRAN_ASSERT(target->type == TYRAN_VALUE_TYPE_OBJECT, "Can only insert to objects");
	TYRAN_ASSERT(key->type == TYRAN_VALUE_TYPE_SYMBOL, "Can only insert using symbols");
	tyran_object_insert(target->data.object, &key->data.symbol, value);
}

void tyran_value_object_insert_c_string_key(const struct tyran_runtime* runtime, struct tyran_value* target, const char* key, struct tyran_value* value)
{
	tyran_symbol symbol;
	tyran_symbol_table_add(runtime->symbol_table, &symbol, key);

	tyran_value symbol_value;
	tyran_value_set_symbol(symbol_value, symbol);

	tyran_value_object_insert(runtime, target, &symbol_value, value);
}

void tyran_value_object_delete(tyran_value* target, tyran_value* key)
{
	TYRAN_ASSERT(target->type == TYRAN_VALUE_TYPE_OBJECT, "Can only delete objects");
	TYRAN_ASSERT(key->type == TYRAN_VALUE_TYPE_SYMBOL, "Can only delete symbols");
	tyran_object_delete(target->data.object, &key->data.symbol);
}

void tyran_value_object_lookup(tyran_value* t, const tyran_value* target, const struct tyran_value* key)
{
	TYRAN_ASSERT(target->type == TYRAN_VALUE_TYPE_OBJECT, "Can only subscript on objects");
	TYRAN_ASSERT(key->type == TYRAN_VALUE_TYPE_SYMBOL, "Can only lookup symbols");
	tyran_object_lookup(t, target->data.object, &key->data.symbol);
}

void tyran_value_object_lookup_prototype(tyran_value* v, const tyran_value* target, const struct tyran_value* key)
{
	TYRAN_ASSERT(target->type == TYRAN_VALUE_TYPE_OBJECT, "Can only subscript on objects");
	TYRAN_ASSERT(key->type == TYRAN_VALUE_TYPE_SYMBOL, "Can only lookup symbols");
	TYRAN_ASSERT(target->data.object, "Object is 0");
	tyran_object_lookup_prototype(v, target->data.object, &key->data.symbol);
}

void tyran_value_object_set_prototype(struct tyran_value* target, struct tyran_value* prototype)
{
	TYRAN_ASSERT(target->type == TYRAN_VALUE_TYPE_OBJECT, "value_object: Can only set prototype on objects");
	TYRAN_ASSERT(prototype->type == TYRAN_VALUE_TYPE_OBJECT, "value_object: Can only set prototype to an object");
	tyran_object_set_prototype(target->data.object, prototype->data.object);
}

const struct tyran_string* tyran_value_object_string(struct tyran_value* target) {
	TYRAN_ASSERT(target->type == TYRAN_VALUE_TYPE_OBJECT, "value_object: Can only get string from objects");
	return tyran_object_string(target->data.object);
}

struct tyran_array* tyran_value_object_array(struct tyran_value* target) {
	TYRAN_ASSERT(target->type == TYRAN_VALUE_TYPE_OBJECT, "value_object: Can only get array from objects");
	return tyran_object_array(target->data.object);
}


