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
		case TYRAN_VALUE_TYPE_NIL:
			tyran_snprintf(buf, max_length, "nil");
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
			switch (v->data.object->type) {
				case TYRAN_OBJECT_TYPE_OBJECT:
					tyran_snprintf(buf, max_length, "object:%p (%d)", (void*) v->data.object, v->data.object->retain_count);
					break;
				case TYRAN_OBJECT_TYPE_FUNCTION:
					tyran_snprintf(buf, max_length, "function:%p (%d)", (void*) v->data.object, v->data.object->retain_count);
					break;
				case TYRAN_OBJECT_TYPE_ARRAY_ITERATOR:
					tyran_snprintf(buf, max_length, "iterator:%p (%d)", (void*)v->data.object, v->data.object->retain_count);
					break;
				case TYRAN_OBJECT_TYPE_ARRAY:
					tyran_snprintf(buf, max_length, "array:%p (%d)", (void*)v->data.object, v->data.object->retain_count);
					break;
				case TYRAN_OBJECT_TYPE_RANGE:
					tyran_snprintf(buf, max_length, "range:%p (%d)", (void*)v->data.object, v->data.object->retain_count);
					break;
				case TYRAN_OBJECT_TYPE_RANGE_ITERATOR:
					tyran_snprintf(buf, max_length, "range_iterator:%p (%d)", (void*)v->data.object, v->data.object->retain_count);
					break;
				case TYRAN_OBJECT_TYPE_STRING: {
					static const int temp_buffer_size = 512;
					char temp_buffer[temp_buffer_size];
					tyran_string_to_c_str(temp_buffer, temp_buffer_size, v->data.object->data.str);
					if (quote) {
						tyran_snprintf(buf, max_length, "'%s' (%d)", temp_buffer, v->data.object->retain_count);
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
			TYRAN_ERROR("Unknown value type:%d", v->type);
	}

}

void tyran_print_value_helper(int tabs, const char* property, const tyran_value* v, int quote, const tyran_symbol_table* symbol_table, tyran_memory_pool* object_iterator_pool, tyran_memory_pool* string_pool, tyran_memory* memory)
{
	int t;

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

		for (int i=0; i<o->property_count; ++i) {
			tyran_object_property* property = &o->properties[i];

			const char* symbol_name;
			symbol_name = tyran_symbol_table_lookup(symbol_table, &property->symbol);

			tyran_print_value_helper(tabs + 1, symbol_name, &property->value, quote, symbol_table, object_iterator_pool, string_pool, memory);
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
