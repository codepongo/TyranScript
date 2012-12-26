#include <tyranscript/tyran_object.h>
#include <tyranscript/tyran_object_macros.h>
#include <tyranscript/tyran_object_iterator.h>
#include <tyranscript/tyran_function_object.h>
#include <tyranscript/tyran_value.h>
#include <tyranscript/tyran_value_object.h>
#include <tyranscript/tyran_object_prototype.h>
#include <tyranscript/tyran_runtime.h>
#include "tyran_number_to_string.h"
#include <tyranscript/tyran_object_key.h>
#include <tyranscript/tyran_rb_tree.h>
#include <tyranscript/tyran_number.h>

void tyran_object_retain(struct tyran_object* o)
{
	TYRAN_ASSERT(o->retain_count >= 0, "Retain count is bad:%d", o->retain_count);
	o->retain_count++;
}

void tyran_object_release(struct tyran_object *o)
{
	TYRAN_ASSERT(o->retain_count > 0, "Retain count is bad:%d", o->retain_count);
	o->retain_count--;
	if (o->retain_count == 0) {
		tyran_object_free(o);
	}
}

tyran_object* tyran_object_new(const struct tyran_runtime* runtime)
{
	tyran_object* object = TYRAN_CALLOC_TYPE(runtime->object_pool, tyran_object);
	object->created_in_runtime = runtime;
	return object;
}

void tyran_object_free(struct tyran_object* object)
{
	const tyran_runtime* runtime = object->created_in_runtime;
	runtime->delete_callback(runtime, object);

	switch (object->type) {
		case TYRAN_OBJECT_TYPE_ITERATOR:
			tyran_object_iterator_free(object->data.iterator);
			break;
		case TYRAN_OBJECT_TYPE_FUNCTION:
			tyran_function_object_free(object->data.function);
			break;
		case TYRAN_OBJECT_TYPE_STRING:
			tyran_string_free(object->data.str);
			break;
		default:
			break;
	}

	tyran_memset_type(object, 0);
	object->retain_count = -9999;

	tyran_free(object);
}

int tyran_object_find_property(const struct tyran_object* object, const tyran_symbol* symbol)
{
	int found = -1;

	for (int i=0; i<object->property_count; ++i) {
		if (object->properties[i].symbol.hash == symbol->hash) {
			found = i;
			break;
		}
	}

	return found;
}

void tyran_object_insert(struct tyran_object* object, const tyran_symbol* symbol, struct tyran_value* value)
{
	int found = tyran_object_find_property(object, symbol);
	if (found == -1) {
		found = object->property_count;
		object->property_count++;
		TYRAN_LOG("Inserting property to #%d count:%d", found, object->property_count);
		tyran_value_copy(object->properties[found].value, *value);
		object->properties[found].symbol = *symbol;
	} else {
		tyran_value_replace(object->properties[found].value, *value);
	}

}

const tyran_value* tyran_object_lookup(const struct tyran_object* object, const struct tyran_symbol* symbol)
{
	int found = tyran_object_find_property(object, symbol);
	if (found == -1) {
		TYRAN_LOG("Couldn't find symbol: %04X", symbol->hash);
		return 0;
	} else {
		TYRAN_LOG("Found symbol: %04X", object->properties[found].value.data.symbol.hash);
		return &object->properties[found].value;
	}
}

void tyran_object_delete(struct tyran_object* object, const struct tyran_symbol* key)
{
}

void tyran_object_set_prototype(struct tyran_object* target, struct tyran_value* proto)
{
	TYRAN_ASSERT(target->prototype == 0, "Prototype already set, this is a problem");
	TYRAN_OBJECT_RETAIN(proto->data.object);
	target->prototype = proto;
}

const tyran_value* tyran_object_lookup_prototype(const struct tyran_object* o, const struct tyran_symbol* symbol)
{
	const tyran_value* ret_value;
	ret_value = tyran_object_lookup(o, symbol);
	if (!ret_value) {
		if (o->prototype) {
			return tyran_object_lookup_prototype(o->prototype->data.object, symbol);
		}
	}
	
	return ret_value;
}

int tyran_object_length(const struct tyran_object* object)
{
	return -1;
}
