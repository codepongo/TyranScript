#include <tyranscript/tyran_object.h>
#include <tyranscript/tyran_object_macros.h>
#include <tyranscript/tyran_function_object.h>
#include <tyranscript/tyran_value.h>
#include <tyranscript/tyran_value_object.h>
#include <tyranscript/tyran_object_prototype.h>
#include <tyranscript/tyran_runtime.h>
#include <tyranscript/tyran_red_black_tree.h>
#include <tyranscript/tyran_number.h>
#include <tyranscript/tyran_string.h>

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
	TYRAN_LOG("Object free:%p, runtime:%p", (void*)object, (void*)runtime);
	if (runtime->delete_callback) {
		runtime->delete_callback(runtime, object);
	}

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
	object->created_in_runtime = 0;

	TYRAN_MALLOC_FREE(object);
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

void tyran_object_lookup(tyran_value* x, struct tyran_object* object, const struct tyran_symbol* symbol)
{
	int found = tyran_object_find_property(object, symbol);
	if (found == -1) {
		tyran_value_set_nil(*x);
	} else {
		tyran_value_copy(*x, object->properties[found].value);
	}
}

void tyran_object_delete(struct tyran_object* object, const struct tyran_symbol* key)
{
}

void tyran_object_set_prototype(struct tyran_object* target, struct tyran_object* proto)
{
	if (target->prototype) {
		TYRAN_OBJECT_RELEASE(target->prototype);
	}
	TYRAN_ASSERT(proto != target, "Can not set prototype to self");

	TYRAN_OBJECT_RETAIN(proto);
	target->prototype = proto;
}

void tyran_object_lookup_prototype(tyran_value* x, struct tyran_object* o, const struct tyran_symbol* symbol)
{
	tyran_object_lookup(x, o, symbol);
	if (tyran_value_is_nil(x) && o->prototype) {
		tyran_object_lookup_prototype(x, o->prototype, symbol);
	}
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

const struct tyran_string* tyran_object_string(struct tyran_object* o) {
	TYRAN_ASSERT(o->type == TYRAN_OBJECT_TYPE_STRING, "must be array iterator");
	return o->data.str;
}

struct tyran_array* tyran_object_array(struct tyran_object* o) {
	TYRAN_ASSERT(o->type == TYRAN_OBJECT_TYPE_ARRAY, "must be array");
	return o->data.array;
}

const struct tyran_function* tyran_object_function(struct tyran_object* o) {
	TYRAN_ASSERT(o->type == TYRAN_OBJECT_TYPE_FUNCTION, "must be array");
	return o->data.function->static_function;
}

