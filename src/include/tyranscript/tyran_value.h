#ifndef _TYRAN_VALUE_H
#define _TYRAN_VALUE_H

#include <tyranscript/tyran_config.h>
#include <tyranscript/tyran_symbol.h>
#include <tyranscript/tyran_object_macros.h>

struct tyran_string;
struct tyran_object;
struct tyran_runtime_stack;
struct tyran_red_black_tree_iterator;

typedef enum {
	TYRAN_VALUE_TYPE_NIL,
	TYRAN_VALUE_TYPE_BOOLEAN,
	TYRAN_VALUE_TYPE_NUMBER,
	TYRAN_VALUE_TYPE_SYMBOL,
	TYRAN_VALUE_TYPE_OBJECT,
	TYRAN_VALUE_TYPE_STATIC_FUNCTION
} tyran_value_type;

typedef struct tyran_value {
	tyran_value_type type;
	union {
		tyran_boolean boolean;
		tyran_number number;
		tyran_symbol symbol;
		struct tyran_object* object;
		struct tyran_function* static_function;
		u32t data;
	} data;
} tyran_value;

#define tyran_value_clear(v, a) { \
	for (i=0; i<a; ++i) { \
		tyran_value_release_and_clear(v[i]); \
	} \
}

#define tyran_value_release(v) { \
	if ((v).type == TYRAN_VALUE_TYPE_OBJECT) { TYRAN_OBJECT_RELEASE((v).data.object) } \
}

#define tyran_value_release_and_clear(v) { \
	tyran_value_release(v); \
	(v).type = TYRAN_VALUE_TYPE_NIL; \
	(v).data.object = 0; \
}

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

#define tyran_value_set_symbol(v, n) { \
	(v).type = TYRAN_VALUE_TYPE_SYMBOL; \
	(v).data.symbol = (n); \
}

#define tyran_value_set_boolean(v, b) { \
	(v).type = TYRAN_VALUE_TYPE_BOOLEAN; \
	(v).data.boolean = (b); \
}

#define tyran_value_set_static_function(v, f) { \
	(v).type = TYRAN_VALUE_TYPE_STATIC_FUNCTION; \
	(v).data.static_function = (f); \
}


#define tyran_value_set_nil(v) { \
	(v).type = TYRAN_VALUE_TYPE_NIL; \
    (v).data.data = 0;  \
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

#define tyran_value_replace_nil(v) { \
	tyran_value_release(v); \
	tyran_value_set_nil(v); \
}

#define tyran_value_replace(v, b) { \
	tyran_value_release(v); \
	tyran_value_copy(v, b); \
}

#define tyran_value_move(v, b) { \
	tyran_value_replace(v, b); \
	tyran_value_release(b); \
}

#define tyran_value_is_false(pv) (tyran_value_is_nil(pv) || (tyran_value_is_boolean(pv) && !(pv)->data.boolean))

#define tyran_value_is_same_type(a, b) ((a)->type == (b)->type)
#define tyran_value_is_same(a, b) (tyran_value_is_same_type(a, b) && ((a)->data.data == (b)->data.data))
#define tyran_value_is_nil(pv) ((pv)->type == TYRAN_VALUE_TYPE_NIL)
#define tyran_value_is_null(pv) ((pv)->type == TYRAN_VALUE_TYPE_NIL)
#define tyran_value_is_integer(n) (tyran_number_is_normal(n) && (double)((int)(n)) == (n))
#define tyran_value_is_number(pv) ((pv)->type == TYRAN_VALUE_TYPE_NUMBER)
#define tyran_value_is_string(pv) (tyran_value_is_object(pv) && (pv)->data.object->type == TYRAN_OBJECT_TYPE_STRING)
#define tyran_value_is_boolean(pv) ((pv)->type == TYRAN_VALUE_TYPE_BOOLEAN)
#define tyran_value_is_function(pv) ((pv)->type == TYRAN_VALUE_TYPE_OBJECT && (pv)->data.object->type == TYRAN_OBJECT_TYPE_FUNCTION)
#define tyran_value_is_object(pv) ((pv)->type == TYRAN_VALUE_TYPE_OBJECT)
#define tyran_value_is_variable(pv) ((pv)->type == TYRAN_VALUE_TYPE_VARIABLE)


tyran_number tyran_value_number(tyran_value* v);
tyran_boolean tyran_value_boolean(tyran_value* v);
const struct tyran_string* tyran_value_string(tyran_value* v);
const struct tyran_function* tyran_value_function(tyran_value* v);

struct tyran_object* tyran_value_object(tyran_value* v);

tyran_value* tyran_value_new(tyran_memory_pool* pool);
tyran_value* tyran_value_duplicate(const tyran_value* v);
void tyran_value_free(tyran_value* data);

int tyran_value_is_true(const tyran_value* v);
int tyran_value_length(const tyran_value* v);

void tyran_value_set_program_specific(struct tyran_value* value, void* program_specific_context);
#define tyran_value_program_specific(v) v->data.object->program_specific

#endif
