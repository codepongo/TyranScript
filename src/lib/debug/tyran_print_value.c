#include <tyranscript/tyran_value.h>
#include <tyranscript/tyran_config.h>
#include <tyranscript/tyran_object_prototype.h>
#include <tyranscript/tyran_array_prototype.h>
#include <tyranscript/tyran_function_prototype.h>
#include <tyranscript/tyran_function.h>
#include <tyranscript/tyran_function_object.h>
#include <tyranscript/tyran_object.h>
#include <tyranscript/tyran_object_macros.h>
#include <tyranscript/tyran_value_object.h>
#include <tyranscript/tyran_number.h>
#include <tyranscript/tyran_string.h>
#include <tyranscript/tyran_symbol_table.h>

#include <tyranscript/debug/tyran_print_value.h>

void tyran_value_to_c_string(const tyran_symbol_table* symbol_table, const tyran_value* v, char* buf, int max_length, int quote)
{
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
		case TYRAN_VALUE_TYPE_SYMBOL: {
			const char* symbol_name;
			symbol_name = tyran_symbol_table_lookup(symbol_table, &v->data.symbol);
			tyran_snprintf(buf, max_length, ":%s", symbol_name);
			}
			break;
		case TYRAN_VALUE_TYPE_OBJECT:
			switch (v->data.object->type)
			{
			case TYRAN_OBJECT_TYPE_OBJECT:
				tyran_snprintf(buf, max_length, "object:%p (%d)", (void*) v->data.object, v->data.object->retain_count);
			break;
			case TYRAN_OBJECT_TYPE_FUNCTION:
				tyran_snprintf(buf, max_length, "function:%p (%d)", (void*) v->data.object, v->data.object->retain_count);
			break;
			case TYRAN_OBJECT_TYPE_ITERATOR:
				tyran_snprintf(buf, max_length, "iterator:%p (%d)", (void*)v->data.object, v->data.object->retain_count);
			break;
			case TYRAN_OBJECT_TYPE_ARRAY:
				tyran_snprintf(buf, max_length, "array:%p (%d)", (void*)v->data.object, v->data.object->retain_count);
			break;
			case TYRAN_OBJECT_TYPE_STRING: {
				static const int temp_buffer_size = 512;
				char temp_buffer[temp_buffer_size];
				tyran_string_to_c_str(temp_buffer, temp_buffer_size, v->data.object->data.str);
				if (quote) {
					tyran_snprintf(buf, max_length, "'%s'", temp_buffer);
				} else {
					tyran_strncpy(buf, max_length, temp_buffer, temp_buffer_size);
				}
			}
			break;
			}

			break;
		case TYRAN_VALUE_TYPE_STATIC_FUNCTION:
			tyran_snprintf(buf, max_length, "static func");
			break;
		default:
			TYRAN_ERROR("Unknown value type");
	}

}

void tyran_print_value_helper(int tabs, const char* property, const tyran_value* v, int quote, const tyran_symbol_table* symbol_table, tyran_memory_pool* object_iterator_pool, tyran_memory_pool* string_pool, tyran_memory* memory)
{
	int t;

	if (v == tyran_object_prototype) {
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
		tyran_snprintf(prefix, 100, "%s%s: (%p) ", tab_string, property, (void*)v);
	}

	const int max_size = 200;
	char value[max_size];

	//const int temp_buffer_size = 512;
	// char temp_buffer[temp_buffer_size];

	switch(v->type) {
		default: {
			char buf[2048];
			tyran_value_to_c_string(symbol_table, v, buf, 2048, quote);
			tyran_strncpy(value, max_size, buf, 2048);
			}
			break;
	}

	TYRAN_LOG("%s %s", prefix, value);

	if (v->type == TYRAN_VALUE_TYPE_OBJECT) {
		tyran_object* o = v->data.object;
		if (o->prototype == 0) {
			TYRAN_LOG("[]");
			/*
			int len = tyran_object_length(o);
			int i;
			tyran_value* nv;

			const int max_size_description = 2048;
			char desc[max_size_description];
			for (i = 0; i < len; ++i) {
				tyran_object_key_flag_type flag;
				nv = tyran_value_object_lookup_array(v, i, &flag);
				if (nv) {
					tyran_snprintf(desc, max_size_description, "#%d: ", i);
					// TYRAN_ASSERT(nv != 0, "Must be able to lookup all indexes");
					tyran_print_value_helper(tabs, desc, nv, 1, object_iterator_pool, string_pool, memory);
				}
			}
			*/
		} /*else*/ {
			/*
			tabs++;
			tyran_object_iterator* target_iterator = tyran_object_iterator_new(object_iterator_pool);
			tyran_object_get_keys(string_pool, memory, 0, v->data.object, target_iterator);
			tyran_object_key_flag_type flag;
			int i;
			for (i=0; i<target_iterator->count; ++i) {
				const tyran_object_key* key = target_iterator->keys[i];
				tyran_value* sub_value = tyran_value_object_lookup(v, key, &flag);
				if (sub_value) {
					tyran_string_to_c_str(temp_buffer, temp_buffer_size, key->str);
					tyran_print_value_helper(tabs, temp_buffer, sub_value, quote, object_iterator_pool, string_pool, memory);
				}
			}

			tabs--;
			*/
		}

		if (tyran_object_get_prototype(o)) {
			tyran_value prototype_value;
			tyran_value_set_object(prototype_value, tyran_object_get_prototype(o));
			tyran_print_value_helper(tabs + 1, "__proto__", &prototype_value, quote, symbol_table, object_iterator_pool, string_pool, memory);
		}
	}
}

void tyran_print_value(const char* property, const tyran_value* v, int quote, const tyran_symbol_table* symbol_table, tyran_memory_pool* object_iterator_pool, tyran_memory_pool* string_pool, tyran_memory* memory)
{
	tyran_print_value_helper(0, property, v, quote, symbol_table, object_iterator_pool, string_pool, memory);
}
