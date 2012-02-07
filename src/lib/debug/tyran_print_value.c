#include <tyranscript/tyran_value.h>
#include <tyranscript/tyran_config.h>
#include <tyranscript/tyran_object_prototype.h>
#include <tyranscript/tyran_array_prototype.h>
#include <tyranscript/tyran_function_prototype.h>
#include <tyranscript/tyran_function.h>
#include <tyranscript/tyran_function_object.h>
#include <tyranscript/tyran_object_iterator.h>
#include <tyranscript/tyran_object.h>
#include <tyranscript/tyran_value_object.h>

#include "../tyran_string_array.h"
#include <tyranscript/debug/tyran_print_value.h>

void tyran_value_to_c_string(const tyran_value* v, char* buf, int max_length, int quote)
{
	const int temp_buffer_size = 512;
	char temp_buffer[temp_buffer_size];
	switch (v->type) {
		case TYRAN_VALUE_TYPE_BOOLEAN:
			tyran_snprintf(buf, max_length, "%s", v->data.boolean ? "true" : "false");
			break;
		case TYRAN_VALUE_TYPE_UNDEFINED:
			tyran_snprintf(buf, max_length, "undefined");
			break;
		case TYRAN_VALUE_TYPE_NULL:
			tyran_snprintf(buf, max_length, "null");
			break;
		case TYRAN_VALUE_TYPE_NUMBER:
			if (tyran_value_is_integer(v->data.number)) {
				tyran_snprintf(buf, max_length, "%d", (int)v->data.number);
			} else if (tyran_number_is_normal(v->data.number)) {
				tyran_snprintf(buf, max_length, "%g", v->data.number);
			} else if (tyran_number_is_nan(v->data.number)) {
				tyran_snprintf(buf, max_length, "NaN");
			} else {
				int s = tyran_number_is_infinity(v->data.number);
				if (s > 0) {
					tyran_snprintf(buf, max_length, "+Infinity");
				} else if (s < 0) {
					tyran_snprintf(buf, max_length, "-Infinity");
				}
			}
			break;
		case TYRAN_VALUE_TYPE_STRING:
			tyran_string_to_c_str(temp_buffer, temp_buffer_size, v->data.str);
			if (quote) {
				tyran_snprintf(buf, max_length, "'%s'", temp_buffer);
			} else {
				tyran_strncpy(buf, temp_buffer, temp_buffer_size);
			}
			break;
		case TYRAN_VALUE_TYPE_VARIABLE: {
				const int max_reference_size = 2048;
				char referenced_value[max_reference_size];
				tyran_value_to_c_string(v->data.variable, referenced_value, max_reference_size, quote);
				// %p (%p)
				// 
				tyran_snprintf(buf, max_length, "variable:%s", referenced_value);
			}
			break;
		case TYRAN_VALUE_TYPE_OBJECT:
			switch (v->data.object->type)
			{
			case TYRAN_OBJECT_TYPE_OBJECT:
				tyran_snprintf(buf, max_length, "object:%p ", (void*) v->data.object);
			break;
			case TYRAN_OBJECT_TYPE_FUNCTION:
				tyran_snprintf(buf, max_length, "function:%p ", (void*) v->data.object);
			break;
			case TYRAN_OBJECT_TYPE_ITERATOR:
				tyran_snprintf(buf, max_length, "iterator:%p ", (void*)v->data.object);
			break;
			}

			break;
			
		case TYRAN_VALUE_TYPE_RUNTIME_STACK:
			tyran_snprintf(buf, max_length, "runtime_stack:%p ", (void*)v->data.runtime_stack);
			break;
		default:
			TYRAN_ERROR("Unknown value type");
	}

}

void tyran_print_value_helper(int tabs, const char* property, const tyran_value* v, int quote)
{
	int t;

	if (v == tyran_object_prototype || v == tyran_array_prototype || v == tyran_function_prototype) {
		return;
	}

	char tab_string[100];

	for (t = 0; t < tabs; ++t) {
		tab_string[t * 2] = '.';
		tab_string[t * 2 + 1] = '.';
	}
	tab_string[tabs * 2] = 0;

	char prefix[100];
	prefix[0] = 0;
	if (property != 0) {
		tyran_snprintf(prefix, "%s%s: (%p) ", tab_string, property, (void*)v);
	}

	const int max_size = 200;
	char value[max_size];

	const int temp_buffer_size = 512;
	char temp_buffer[temp_buffer_size];

	int max_size_left = max_size;
	switch(v->type) {
		case TYRAN_VALUE_TYPE_OBJECT: {
			tyran_object* o = v->data.object;
			switch(o->type) {
				case TYRAN_OBJECT_TYPE_FUNCTION: {
					const tyran_function* f = o->data.function->static_function;
					if (f->type == tyran_function_type_normal) {
						tyran_snprintf(value, max_size, "function (");
						int i;
						for (i = 0; i < f->argument_names->count; ++i) {
							if (i != 0) {
								tyran_strncat(value, ", ", max_size_left);
								max_size_left -= 2;
							}
							tyran_string_to_c_str(temp_buffer, temp_buffer_size, tyran_string_array_get(f->argument_names, i));
							const char* argument_name = temp_buffer;
							tyran_strncat(value, argument_name, max_size_left);
							max_size_left -= tyran_strlen(argument_name);
						}
						tyran_strncat(value, ") {", max_size_left);
						max_size_left -= 3;
					} else {
						tyran_snprintf(value, max_size, "function () { [Native code] }");
					}
					break;
				}
				case TYRAN_OBJECT_TYPE_OBJECT:
					tyran_snprintf(value, max_size, "object %p (program:%p)", (void*)o, (void*)o->program_specific);
					break;
				default:
					TYRAN_ERROR("Unexpected object type");
					break;
			}
			tyran_snprintf(value, max_size, "%s (ref:%d) ", value, o->retain_count);
			break;
		}
		default: {
			char buf[2048];
			tyran_value_to_c_string(v, buf, 2048, quote);
			tyran_strncpy(value, buf, max_size);
			}
			break;
	}

	TYRAN_LOG("%s %s", prefix, value);

	if (v->type == TYRAN_VALUE_TYPE_OBJECT) {
		tyran_object* o = v->data.object;
		if (o->prototype == tyran_array_prototype) {
			TYRAN_LOG("[]");
			int len = tyran_object_length(o);
			int i;
			tyran_value* nv;

			const int max_size_description = 2048;
			char desc[max_size_description];
			for (i = 0; i < len; ++i) {
				nv = tyran_value_object_lookup_array(v, i, 0);
				if (nv) {
					tyran_snprintf(desc, max_size_description, "#%d: ", i);
					// TYRAN_ASSERT(nv != 0, "Must be able to lookup all indexes");
					tyran_print_value_helper(tabs, desc, nv, 1);
				}
			}
		} else {
			tabs++;
			tyran_object_iterator* target_iterator = tyran_object_iterator_new();
			tyran_object_get_keys(v->data.object, target_iterator);
			tyran_object_key_flag_type flag;
			int i;
			for (i=0; i<target_iterator->count; ++i) {
				const tyran_object_key* key = target_iterator->keys[i];
				tyran_value* sub_value = tyran_value_object_lookup(v, key, &flag);
				if (sub_value) {
					tyran_string_to_c_str(temp_buffer, temp_buffer_size, (const tyran_string*)key);
					tyran_print_value_helper(tabs, temp_buffer, sub_value, quote);
				}
			}

			tabs--;
		}

		if (tyran_object_get_prototype(o)) {
			tyran_print_value_helper(tabs + 1, "__proto__", tyran_object_get_prototype(o), quote);
		}
	}
}

void tyran_print_value(const char* property, const tyran_value* v, int quote)
{
	tyran_print_value_helper(0, property, v, quote);
}
