#ifndef _TYRAN_VALUE_H
#define _TYRAN_VALUE_H

#include <tyranscript/tyran_config.h>

struct tyran_string;
struct tyran_object;
struct tyran_runtime_stack;

typedef enum {
	TYRAN_VALUE_TYPE_UNDEFINED,
	TYRAN_VALUE_TYPE_NULL,
	TYRAN_VALUE_TYPE_BOOLEAN,
	TYRAN_VALUE_TYPE_NUMBER,
	TYRAN_VALUE_TYPE_STRING,
	TYRAN_VALUE_TYPE_OBJECT,
	TYRAN_VALUE_TYPE_STATIC_FUNCTION
} tyran_value_type;

typedef struct tyran_value {
	tyran_value_type type;
	union {
		tyran_boolean boolean;
		tyran_number number;
		const struct tyran_string* str;
		struct tyran_object* object;
		struct tyran_function* static_function;
		u32t data;
	} data;
} tyran_value;

#define tyran_value_release(v) { \
	if ((v).type == TYRAN_VALUE_TYPE_STRING) tyran_string_free((v).data.str); \
	else if ((v).type == TYRAN_VALUE_TYPE_OBJECT) TYRAN_OBJECT_RELEASE((v).data.object) \
	(v).type = TYRAN_VALUE_TYPE_UNDEFINED; \
	(v).data.object = 0; \
}

/* if ((to).type == TYRAN_VALUE_TYPE_STRING) (to).data.str = tyran_string_strdup((to).data.str); */

#define tyran_value_copy(to, from) { \
	(to) = (from); \
	if ((to).type == TYRAN_VALUE_TYPE_OBJECT) TYRAN_OBJECT_RETAIN((to).data.object);			\
} 

#define tyran_value_set_object(v, o) { \
	(v).type = TYRAN_VALUE_TYPE_OBJECT; \
	(v).data.object = (o); \
	TYRAN_OBJECT_RETAIN(o); \
}

#define tyran_value_set_number(v, n) { \
	(v).type = TYRAN_VALUE_TYPE_NUMBER; \
	(v).data.number = (n); \
}

#define tyran_value_set_boolean(v, b) { \
	(v).type = TYRAN_VALUE_TYPE_BOOLEAN; \
	(v).data.boolean = (b); \
}

#define tyran_value_set_static_function(v, f) { \
	(v).type = TYRAN_VALUE_TYPE_STATIC_FUNCTION; \
	(v).data.static_function = (f); \
}


#define tyran_value_set_string(v, s) { \
	(v).type = TYRAN_VALUE_TYPE_STRING; \
	(v).data.str = (s); \
}

#define tyran_value_set_undefined(v) { \
	(v).type = TYRAN_VALUE_TYPE_UNDEFINED; \
}

#define tyran_value_set_null(v) { \
	(v).type = TYRAN_VALUE_TYPE_NULL; \
}


#define tyran_value_set_variable(v, var) { \
	(v).type = TYRAN_VALUE_TYPE_VARIABLE; \
	(v).data.variable = var; \
}

#define tyran_value_replace_object(v, o) { \
	tyran_value_release(v); \
	tyran_value_set_object(v, o); \
}

#define tyran_value_replace_number(v, n) { \
	tyran_value_release(v); \
	tyran_value_set_number(v, n); \
}

#define tyran_value_replace_boolean(v, b) { \
	tyran_value_release(v); \
	tyran_value_set_boolean(v, b); \
}

#define tyran_value_replace_string(v, s) { \
	tyran_value_release(v); \
	tyran_value_set_string(v, s); \
}

#define tyran_value_replace_undefined(v) { \
	tyran_value_release(v); \
	tyran_value_set_undefined(v); \
}

#define tyran_value_replace_variable(v, var) { \
	tyran_value_release(v); \
	tyran_value_set_variable(v, var); \
}

#define tyran_value_replace(v, b) { \
	tyran_value_release(v); \
	tyran_value_copy(v, b); \
}

#define tyran_value_is_same_type(a, b) ((a)->type == (b)->type)
#define tyran_value_is_same(a, b) (tyran_value_is_same_type(a, b) && (((a)->type == TYRAN_VALUE_TYPE_STRING && tyran_string_strcmp((a)->data.str, (b)->data.str) == 0) || ((a)->data.data == (b)->data.data) )) 
#define tyran_value_is_undefined(pv) ((pv)->type == TYRAN_VALUE_TYPE_UNDEFINED)
#define tyran_value_is_null(pv) ((pv)->type == TYRAN_VALUE_TYPE_NULL)
#define tyran_value_is_integer(n) (tyran_number_is_normal(n) && (double)((int)(n)) == (n))
#define tyran_value_is_number(pv) ((pv)->type == TYRAN_VALUE_TYPE_NUMBER)
#define tyran_value_is_string(pv) ((pv)->type == TYRAN_VALUE_TYPE_STRING)
#define tyran_value_is_boolean(pv) ((pv)->type == TYRAN_VALUE_TYPE_BOOLEAN)
#define tyran_value_is_function(pv) ((pv)->type == TYRAN_VALUE_TYPE_OBJECT && (pv)->data.object->type == TYRAN_OBJECT_TYPE_FUNCTION)
#define tyran_value_is_object(pv) ((pv)->type == TYRAN_VALUE_TYPE_OBJECT)
#define tyran_value_is_variable(pv) ((pv)->type == TYRAN_VALUE_TYPE_VARIABLE)


tyran_value* tyran_value_new(tyran_memory_pool* pool);
tyran_value* tyran_value_duplicate(const tyran_value* v);
void tyran_value_free(tyran_value* data);

int tyran_value_is_true(const tyran_value* v);
int tyran_value_length(const tyran_value* v);

void tyran_value_set_program_specific(struct tyran_value* value, void* program_specific_context);

#endif
