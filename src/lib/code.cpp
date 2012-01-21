#include "code.h"

#include <tyranscript/opcodes.h>
#include <tyranscript/config.h>



#define OPCODES_ALLOC(code) { \
		struct tyran_opcodes* r = tyran_opcodes_new(3); \
		tyran_opcodes_add_code(r, (code)); \
		return r; \
	}

#define OPCODES_ALLOC_INTEGER(code, extra) { \
		struct tyran_opcodes* r = tyran_opcodes_new(3); \
		tyran_opcodes_add_with_integer(r, (code), extra); \
		return r; \
	}

#define OPCODES_ALLOC_POINTER(code, extra) { \
		struct tyran_opcodes* r = tyran_opcodes_new(3); \
		tyran_opcodes_add_with_pointer(r, (code), (void*)extra); \
		return r; \
	}

typedef struct tyran_replace_info
{
	enum tyran_resolve_type type;
	int pop_count;
} tyran_replace_info;

struct tyran_opcodes* tyran_opcodes_new(int size)
{
	struct tyran_opcodes* ret = (struct tyran_opcodes*) TN_CALLOC(tyran_opcodes);
	ret->codes = (struct tyran_opcode*) tyran_malloc(sizeof(struct tyran_opcode) * size);
	ret->code_size = size;
	return ret;
}

struct tyran_opcode* tyran_opcodes_add_code(struct tyran_opcodes* c, tyran_opcode_id code)
{
	if (c->code_size == c->code_len)
	{
		c->code_size = c->code_size * 2 + 1;
		c->codes = (struct tyran_opcode*) realloc(c->codes, c->code_size * sizeof(struct tyran_opcode));
	}
	c->codes[c->code_len].opcode = code;
	c->code_len++;
	return &c->codes[c->code_len - 1];
}

void tyran_opcodes_add_with_pointer(struct tyran_opcodes* c, tyran_opcode_id opcode_id, void* param)
{
	struct tyran_opcode* code = tyran_opcodes_add_code(c, opcode_id);
	code->dd.data = param;
}

void tyran_opcodes_add_with_integer(struct tyran_opcodes* c, tyran_opcode_id opcode_id, int param)
{
	struct tyran_opcode* code = tyran_opcodes_add_code(c, opcode_id);
	code->dd.idata = param;
}

struct tyran_opcodes* tyran_opcodes_add(struct tyran_opcodes* a, struct tyran_opcodes* b)
{
	if (!a)
	{
		return b;
	}
	if (!b)
	{
		return a;
	}
	struct tyran_opcodes* ret = tyran_opcodes_new(a->code_len + b->code_len);
	tyran_memcpy(ret->codes, a->codes, a->code_len * sizeof(struct tyran_opcode));
	tyran_memcpy(&ret->codes[a->code_len], b->codes, b->code_len * sizeof(struct tyran_opcode));

	ret->code_size = a->code_len + b->code_len;
	ret->code_len = ret->code_size;
	ret->expression_count = a->expression_count + b->expression_count;

	tyran_free(a->codes);
	tyran_free(a);

	tyran_free(b->codes);
	tyran_free(b);

	return ret;
}

struct tyran_opcodes* tyran_opcodes_add3(struct tyran_opcodes* a, struct tyran_opcodes* b, struct tyran_opcodes* c)
{
	return tyran_opcodes_add(tyran_opcodes_add(a, b), c);
}

struct tyran_opcodes* tyran_opcodes_add4(struct tyran_opcodes* a, struct tyran_opcodes* b, struct tyran_opcodes* c, struct tyran_opcodes* d)
{
	return tyran_opcodes_add(tyran_opcodes_add(a, b), tyran_opcodes_add(c, d));
}

/* Stack */
struct tyran_opcodes* tyran_opcode_push_number(double *v)
{
	OPCODES_ALLOC_POINTER(TN_OP_PUSH_NUMBER, v);
}

struct tyran_opcodes* tyran_opcode_push_string(const unicode_char *str)
{
	OPCODES_ALLOC_POINTER(TN_OP_PUSH_STRING, str);
}

struct tyran_opcodes* tyran_opcode_push_variable(const unicode_char* varname)
{
	struct tyran_variable_name_info *n = (struct tyran_variable_name_info*) TN_CALLOC(tyran_variable_name_info);
	n->var.varname = varname;
	OPCODES_ALLOC_POINTER(TN_OP_PUSH_VARIABLE, n);
}

struct tyran_opcodes* tyran_opcode_push_undefined()
{
	OPCODES_ALLOC(TN_OP_PUSH_UNDEFINED);
}

struct tyran_opcodes* tyran_opcode_push_boolean(int v)
{
	OPCODES_ALLOC_INTEGER(TN_OP_PUSH_BOOLEAN, v);
}

struct tyran_opcodes* tyran_opcode_push_function(struct tyran_function *fun)
{
	OPCODES_ALLOC_POINTER(TN_OP_PUSH_FUNCTION, fun);
}

struct tyran_opcodes* tyran_opcode_push_scope()
{
	OPCODES_ALLOC(TN_OP_PUSH_SCOPE);
}

struct tyran_opcodes* tyran_opcode_push_this()
{
	OPCODES_ALLOC(TN_OP_PUSH_THIS);
}

struct tyran_opcodes* tyran_opcode_push_top()
{
	OPCODES_ALLOC(TN_OP_PUSH_TOP);
}

struct tyran_opcodes* tyran_opcode_push_top2()
{
	OPCODES_ALLOC(TN_OP_PUSH_TOP2);
}

struct tyran_opcodes* tyran_opcode_pop(int n)
{
	OPCODES_ALLOC_INTEGER(TN_OP_POP, n);
}


/* Arithmetic */
struct tyran_opcodes* tyran_opcode_negative()
{
	OPCODES_ALLOC(TN_OP_NEGATIVE);
}

struct tyran_opcodes* tyran_opcode_positive()
{
	OPCODES_ALLOC(TN_OP_POSITIVE);
}

struct tyran_opcodes* tyran_opcode_not()
{
	OPCODES_ALLOC(TN_OP_NOT);
}

struct tyran_opcodes* tyran_opcode_add()
{
	OPCODES_ALLOC(TN_OP_ADD);
}

struct tyran_opcodes* tyran_opcode_subtract()
{
	OPCODES_ALLOC(TN_OP_SUBTRACT);
}

struct tyran_opcodes* tyran_opcode_multiply()
{
	OPCODES_ALLOC(TN_OP_MULTIPLY);
}

struct tyran_opcodes* tyran_opcode_divide()
{
	OPCODES_ALLOC(TN_OP_DIVIDE);
}

struct tyran_opcodes* tyran_opcode_modulus()
{
	OPCODES_ALLOC(TN_OP_MODULUS);
}

struct tyran_opcodes* tyran_opcode_increase(int e)
{
	OPCODES_ALLOC_INTEGER(TN_OP_INCREASE, e);
}

struct tyran_opcodes* tyran_opcode_decrease(int e)
{
	OPCODES_ALLOC_INTEGER(TN_OP_DECREASE, e);
}

/* Bitwise */
struct tyran_opcodes* tyran_opcode_bitwise_not()
{
	OPCODES_ALLOC(TN_OP_BITWISE_NOT);
}

struct tyran_opcodes* tyran_opcode_bitwise_and()
{
	OPCODES_ALLOC(TN_OP_BITWISE_AND);
}

struct tyran_opcodes* tyran_opcode_bitwise_or()
{
	OPCODES_ALLOC(TN_OP_BITWISE_OR);
}

struct tyran_opcodes* tyran_opcode_bitwise_xor()
{
	OPCODES_ALLOC(TN_OP_BITWISE_XOR);
}

struct tyran_opcodes* tyran_opcode_bitwise_shift(enum tyran_shift_mode mode)
{
	OPCODES_ALLOC_INTEGER(TN_OP_BITWISE_SHIFT, mode);
}

/* Compare */
struct tyran_opcodes* tyran_opcode_compare_equal()
{
	OPCODES_ALLOC(TN_OP_COMPARE_EQUAL);
}

struct tyran_opcodes* tyran_opcode_compare_not_equal()
{
	OPCODES_ALLOC(TN_OP_COMPARE_NOT_EQUAL);
}

struct tyran_opcodes* tyran_opcode_compare_less()
{
	OPCODES_ALLOC(TN_OP_COMPARE_LESS);
}

struct tyran_opcodes* tyran_opcode_compare_less_equal()
{
	OPCODES_ALLOC(TN_OP_COMPARE_LESS_EQUAL);
}

struct tyran_opcodes* tyran_opcode_compare_greater()
{
	OPCODES_ALLOC(TN_OP_COMPARE_GREATER);
}

struct tyran_opcodes* tyran_opcode_compare_greater_equal()
{
	OPCODES_ALLOC(TN_OP_COMPARE_GREATER_EQUAL);
}

struct tyran_opcodes* tyran_opcode_compare_strict_equal()
{
	OPCODES_ALLOC(TN_OP_COMPARE_STRICT_EQUAL);
}

struct tyran_opcodes* tyran_opcode_compare_strict_not_equal()
{
	OPCODES_ALLOC(TN_OP_COMPARE_STRICT_NOT_EQUAL);
}

/* Jumps */
struct tyran_opcodes* tyran_opcode_jump_false(int off)
{
	OPCODES_ALLOC_INTEGER(TN_OP_JUMP_FALSE, off);
}

struct tyran_opcodes* tyran_opcode_jump_true(int off)
{
	OPCODES_ALLOC_INTEGER(TN_OP_JUMP_TRUE, off);
}

struct tyran_opcodes* tyran_opcode_jump_false_pop(int off)
{
	OPCODES_ALLOC_INTEGER(TN_OP_JUMP_FALSE_POP, off);
}

struct tyran_opcodes* tyran_opcode_jump_true_pop(int off)
{
	OPCODES_ALLOC_INTEGER(TN_OP_JUMP_TRUE_POP, off);
}

struct tyran_opcodes* tyran_opcode_jump(int off)
{
	OPCODES_ALLOC_INTEGER(TN_OP_JUMP, off);
}

struct tyran_jump_pop_info* tyran_opcodes_jump_pop_info_new(int offset, int pop_count)
{
	struct tyran_jump_pop_info *r = (struct tyran_jump_pop_info*) malloc(sizeof(struct tyran_jump_pop_info));
	r->offset = offset;
	r->pop_count = pop_count;
	return r;
}

struct tyran_opcodes* tyran_opcode_jump_pop(int offset, int pop_count)
{
	OPCODES_ALLOC_POINTER(TN_OP_JUMP_POP, tyran_opcodes_jump_pop_info_new(offset, pop_count));
}

struct tyran_opcodes* tyran_opcode_call(int argc)
{
	OPCODES_ALLOC_INTEGER(TN_OP_CALL, argc);
}

struct tyran_opcodes* tyran_opcode_new(int argc)
{
	OPCODES_ALLOC_INTEGER(TN_OP_NEW, argc);
}

struct tyran_opcodes* tyran_opcode_return(int pop_count)
{
	OPCODES_ALLOC_INTEGER(TN_OP_RETURN, pop_count);
}

/* Object */
struct tyran_opcodes* tyran_opcode_assign(enum tyran_assign_mode mode)
{
	OPCODES_ALLOC_INTEGER(TN_OP_ASSIGN, mode);
}

struct tyran_opcodes* tyran_opcode_unreference()
{
	OPCODES_ALLOC(TN_OP_UNREFERENCE);
}

struct tyran_opcodes* tyran_opcode_subscript(int is_right_value)
{
	OPCODES_ALLOC_INTEGER(TN_OP_SUBSCRIPT, is_right_value);
}

/* Object iteration */
struct tyran_opcodes* tyran_opcode_key()
{
	OPCODES_ALLOC(TN_OP_KEY);
}

struct tyran_opcodes* tyran_opcode_next()
{
	OPCODES_ALLOC(TN_OP_NEXT);
}

/* Other */
struct tyran_opcodes* tyran_opcode_nop()
{
	OPCODES_ALLOC(TN_OP_NOP);
}

struct tyran_opcodes* tyran_opcode_load_this(int n)
{
	OPCODES_ALLOC_INTEGER(TN_OP_LOAD_THIS, n);
}

struct tyran_opcodes* tyran_opcode_make_object(int c)
{
	OPCODES_ALLOC_INTEGER(TN_OP_MAKE_OBJECT, c);
}

struct tyran_opcodes* tyran_opcode_make_array(int c)
{
	OPCODES_ALLOC_INTEGER(TN_OP_MAKE_ARRAY, c);
}

struct tyran_opcodes* tyran_opcode_delete(enum tyran_assign_mode mode)
{
	OPCODES_ALLOC_INTEGER(TN_OP_DELETE, mode);
}

void tyran_opcodes_free(struct tyran_opcodes* ops)
{
	tyran_free(ops->codes);
	tyran_free(ops);
}

struct tyran_opcodes* tyran_opcodes_mark_for_resolve(enum tyran_resolve_type type)
{
	tyran_replace_info *ri = (tyran_replace_info*) malloc(sizeof(tyran_replace_info));
	ri->type = type;
	ri->pop_count = 0;
	OPCODES_ALLOC_POINTER(TN_OP_INTERNAL, ri);
}

void tyran_opcodes_resolve(struct tyran_opcodes* ops, int step_len, int break_only, int pop_count)
{
	int i;

	for (i = 0; i < ops->code_len; ++i)
	{
		if (ops->codes[i].opcode != TN_OP_INTERNAL)
		{
			continue;
		}
		
		tyran_replace_info *ri = (tyran_replace_info*) ops->codes[i].dd.data;

		switch (ri->type)
		{
			case tyran_resolve_continue:
			{
				if (break_only)
				{
					ri->pop_count += pop_count;
					continue;
				}
				else
				{
					int pop_count = ri->pop_count;
					tyran_free(ri);
					if (pop_count)
					{
						ops->codes[i].dd.data = tyran_opcodes_jump_pop_info_new(ops->code_len - i, pop_count);
						ops->codes[i].opcode = TN_OP_JUMP_POP;
					}
					else
					{
						ops->codes[i].dd.idata = ops->code_len - i;
						ops->codes[i].opcode = TN_OP_JUMP;
					}
				}
			}
			break;
			case tyran_resolve_break:
			{
				int pop_count = ri->pop_count;
				tyran_free(ri);
				if (pop_count)
				{
					ops->codes[i].dd.data = tyran_opcodes_jump_pop_info_new(step_len + ops->code_len - i, pop_count);
					ops->codes[i].opcode = TN_OP_JUMP_POP;
				}
				else
				{
					ops->codes[i].dd.idata = step_len + ops->code_len - i;
					ops->codes[i].opcode = TN_OP_JUMP;
				}
			}
			break;
		}
	}
}

