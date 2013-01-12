#include <tyranscript/tyran_object.h>
#include <tyranscript/tyran_object_macros.h>
#include <tyranscript/tyran_function_object.h>
#include <tyranscript/tyran_value.h>
#include <tyranscript/tyran_value_object.h>
#include <tyranscript/tyran_object_prototype.h>
#include <tyranscript/tyran_runtime.h>
#include "tyran_number_to_string.h"
#include <tyranscript/tyran_rb_tree.h>
#include <tyranscript/tyran_number.h>

void tyran_object_retain(struct tyran_object* o)
{
	TYRAN_ASSERT(o->retain_count >= 0, "Retain count is bad:%d", o->retain_count);
	o->retain_count++;
}

void tyran_object_release(struct tyran_object* o)
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
	case TYRAN_OBJECT_TYPE_ARRAY_ITERATOR:
		// tyran_object_iterator_free(object->data.iterator);
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
		tyran_value_copy(object->properties[found].value, *value);
		object->properties[found].symbol = *symbol;
	} else {
		tyran_value_replace(object->properties[found].value, *value);
	}

}

tyran_value* tyran_object_lookup(struct tyran_object* object, const struct tyran_symbol* symbol)
{
	int found = tyran_object_find_property(object, symbol);
	if (found == -1) {
		return 0;
	} else {
		return &object->properties[found].value;
	}
}

void tyran_object_delete(struct tyran_object* object, const struct tyran_symbol* key)
{
}

void tyran_object_set_prototype(struct tyran_object* target, struct tyran_object* proto)
{
	TYRAN_ASSERT(target->prototype == 0, "Prototype already set, this is a problem");
	TYRAN_OBJECT_RETAIN(proto);
	target->prototype = proto;
}

tyran_value* tyran_object_lookup_prototype(struct tyran_object* o, const struct tyran_symbol* symbol)
{
	tyran_value* ret_value;
	ret_value = tyran_object_lookup(o, symbol);
	if (!ret_value) {
		if (o->prototype) {
			return tyran_object_lookup_prototype(o->prototype, symbol);
		}
	}

	return ret_value;
}

int tyran_object_length(const struct tyran_object* object)
{
	return -1;
}

struct tyran_range_iterator* tyran_object_range_iterator(struct tyran_object* o) {
	TYRAN_ASSERT(o->type == TYRAN_OBJECT_TYPE_RANGE_ITERATOR, "Must be range iterator");
	return o->data.range_iterator;
}
struct tyran_range* tyran_object_range(struct tyran_object* o) {
	TYRAN_ASSERT(o->type == TYRAN_OBJECT_TYPE_RANGE, "Must be range");
	return o->data.range;
}

struct tyran_red_black_tree_iterator* tyran_object_array_iterator(struct tyran_object* o) {
	TYRAN_ASSERT(o->type == TYRAN_OBJECT_TYPE_ARRAY_ITERATOR, "must be array iterator");
	return o->data.array_iterator;
}

