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

const char* tyran_value_to_c_string(const tyran_value* v)
{
	static char buf[256];

	switch (v->type) {
		case TYRAN_VALUE_TYPE_BOOLEAN:
			tyran_sprintf(buf, "%s ", v->data.boolean ? "true" : "false");
			break;
		case TYRAN_VALUE_TYPE_UNDEFINED:
			tyran_sprintf(buf, "undefined ");
			break;
		case TYRAN_VALUE_TYPE_NULL:
			tyran_sprintf(buf, "null ");
			break;
		case TYRAN_VALUE_TYPE_NUMBER:
			if (tyran_value_is_integer(v->data.number)) {
				tyran_sprintf(buf, "%d", (int)v->data.number);
			} else if (tyran_number_is_normal(v->data.number)) {
				tyran_sprintf(buf, "%g", v->data.number);
			} else if (tyran_number_is_nan(v->data.number)) {
				tyran_sprintf(buf, "NaN");
			} else {
				int s = tyran_number_is_infinity(v->data.number);
				if (s > 0) {
					tyran_sprintf(buf, "+Infinity");
				} else if (s < 0) {
					tyran_sprintf(buf, "-Infinity");
				}
			}
			break;
		case TYRAN_VALUE_TYPE_STRING:
			tyran_sprintf(buf, "'%s' ", tyran_string_to_c_str(v->data.str));
			break;
		case TYRAN_VALUE_TYPE_VARIABLE:
			tyran_sprintf(buf, "variable:%p (%p)", v->data.variable, v);
			break;
		case TYRAN_VALUE_TYPE_OBJECT:
			tyran_sprintf(buf, "object:%p ", v->data.object);
			break;
		default:
			TYRAN_ERROR("Unknown value type");
	}
    
    return buf;
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
		sprintf(prefix, "%s%s: (%p) ", tab_string, property, v);
	}

	char value[200];
	switch(v->type) {
		case TYRAN_VALUE_TYPE_OBJECT: {
			tyran_object* o = v->data.object;
			switch(o->type) {
				case TYRAN_OBJECT_TYPE_FUNCTION: {
					const tyran_function* f = o->data.function->static_function;
					if (f->type == tyran_function_type_normal) {
						tyran_sprintf(value, "function (");
						int i;
						for (i = 0; i < f->argument_names->count; ++i) {
							if (i != 0) {
								tyran_strcat(value, ", ");
							}
							tyran_strcat(value, tyran_string_to_c_str(tyran_string_array_get(f->argument_names, i)));
						}
						tyran_strcat(value, ") {");
					} else {
						tyran_sprintf(value, "function () { [Native code] }");
					}
					break;
				}
				case TYRAN_OBJECT_TYPE_OBJECT:
					tyran_sprintf(value, "object %p (program:%p)", o, o->program_specific);
					break;
				default:
					TYRAN_ERROR("Unexpected object type");
					break;
			}
			tyran_sprintf(value, "%s (ref:%d) ", value, o->retain_count);
			break;
		}
		default:
			strcpy(value, tyran_value_to_c_string(v));
			break;
	}
	
	TYRAN_LOG("%s %s", prefix, value);

	if (v->type == TYRAN_VALUE_TYPE_OBJECT) {
		tyran_object* o = v->data.object;
		int len = tyran_object_length(o);

		if (len > 0) {
			int i;
			tyran_value* nv;
			
			TYRAN_LOG("[]");
			char desc[256];
			for (i = 0; i < len; ++i) {
				nv = tyran_value_object_lookup_array(v, i, 0);
				tyran_sprintf(desc, "#%d: ", i);
				if (nv) tyran_print_value_helper(tabs, desc, nv, 1);
				else TYRAN_LOG("undefined");
			}
		} else {
			tabs++;
			tyran_object_iterator* target_iterator = tyran_object_iterator_new();
			tyran_object_get_keys(v, target_iterator);
			int flag;
			for (int i=0; i<target_iterator->count; ++i) {
				const tyran_object_key* key = target_iterator->keys[i];
				tyran_value* sub_value = tyran_value_object_lookup(v, key, &flag);
				if (sub_value) {
					tyran_print_value_helper(tabs, tyran_string_to_c_str((const tyran_string*)key), sub_value, quote);
				}
			}
			
			tyran_value* prototype = tyran_object_get_prototype(o);
			if (prototype) {
				if (prototype != v) {
					tyran_print_value_helper(tabs, "__proto__", prototype, quote);
				}
			}
			tabs--;
		}
	}
}

void tyran_print_value(const char* property, const tyran_value* v, int quote)
{
	tyran_print_value_helper(0, property, v, quote);
}
