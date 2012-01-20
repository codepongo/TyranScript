#include "code.h"

#include <tyranscript/opcodes.h>
#include <tyranscript/config.h>



#define OPCODES_ALLOC(code) { \
		tyran_opcodes* r = tyran_opcodes_new(3); \
		tyran_opcodes_add_code(r, (code)); \
		return r; \
	}

#define OPCODES_ALLOC_INTEGER(code, extra) { \
		tyran_opcodes* r = tyran_opcodes_new(3); \
		tyran_opcodes_add_with_integer(r, (code), extra); \
		return r; \
	}

#define OPCODES_ALLOC_POINTER(code, extra) { \
		tyran_opcodes* r = tyran_opcodes_new(3); \
		tyran_opcodes_add_with_pointer(r, (code), (void*)extra); \
		return r; \
	}

typedef struct tyran_replace_info
{
	enum tyran_resolve_type type;
	int pop_count;
} tyran_replace_info;

tyran_opcodes* tyran_opcodes_new(int size)
{
	tyran_opcodes* ret = (tyran_opcodes*) TN_CALLOC(tyran_opcodes);
	ret->codes = (tyran_opcode*) tyran_malloc(sizeof(tyran_opcode) * size);
	ret->code_size = size;
	return ret;
}

tyran_opcode* tyran_opcodes_add_code(tyran_opcodes* c, tyran_opcode_id code)
{
	if (c->code_size == c->code_len)
	{
		c->code_size = c->code_size * 2 + 1;
		c->codes = (tyran_opcode*) realloc(c->codes, c->code_size * sizeof(tyran_opcode));
	}
	c->codes[c->code_len].opcode = code;
	c->code_len++;
	return &c->codes[c->code_len - 1];
}

void tyran_opcodes_add_with_pointer(tyran_opcodes* c, tyran_opcode_id opcode_id, void* param)
{
	tyran_opcode* code = tyran_opcodes_add_code(c, opcode_id);
	code->dd.data = param;
}

void tyran_opcodes_add_with_integer(tyran_opcodes* c, tyran_opcode_id opcode_id, int param)
{
	tyran_opcode* code = tyran_opcodes_add_code(c, opcode_id);
	code->dd.idata = param;
}

tyran_opcodes* tyran_opcodes_add(tyran_opcodes* a, tyran_opcodes* b)
{
	tyran_opcodes* ret = tyran_opcodes_new(a->code_len + b->code_len);
	tyran_memcpy(ret->codes, a->codes, a->code_len * sizeof(tyran_opcode));
	tyran_memcpy(&ret->codes[a->code_len], b->codes, b->code_len * sizeof(tyran_opcode));

	ret->code_size = a->code_len + b->code_len;
	ret->code_len = ret->code_size;
	ret->expression_count = a->expression_count + b->expression_count;

	tyran_free(a->codes);
	tyran_free(a);

	tyran_free(b->codes);
	tyran_free(b);

	return ret;
}

tyran_opcodes* tyran_opcodes_add3(tyran_opcodes* a, tyran_opcodes* b, tyran_opcodes* c)
{
	return tyran_opcodes_add(tyran_opcodes_add(a, b), c);
}

tyran_opcodes* tyran_opcodes_add4(tyran_opcodes* a, tyran_opcodes* b, tyran_opcodes* c, tyran_opcodes* d)
{
	return tyran_opcodes_add(tyran_opcodes_add(a, b), tyran_opcodes_add(c, d));
}

/* Stack */
tyran_opcodes* code_push_number(double *v)
{
	OPCODES_ALLOC_POINTER(TN_OP_PUSH_NUMBER, v);
}

tyran_opcodes* code_push_string(const unicode_char *str)
{
	OPCODES_ALLOC_POINTER(TN_OP_PUSH_STRING, str);
}

tyran_opcodes* code_push_variable(const unicode_char* varname)
{
	tyran_variable_name_info *n = (tyran_variable_name_info*) TN_CALLOC(tyran_variable_name_info);
	n->var.varname = varname;
	OPCODES_ALLOC_POINTER(TN_OP_PUSH_VARIABLE, n);
}

tyran_opcodes* code_push_undefined()
{
	OPCODES_ALLOC(TN_OP_PUSH_UNDEFINED);
}

tyran_opcodes* code_push_boolean(int v)
{
	OPCODES_ALLOC_INTEGER(TN_OP_PUSH_BOOLEAN, v);
}

tyran_opcodes* code_push_function(struct tyran_function *fun)
{
	OPCODES_ALLOC_POINTER(TN_OP_PUSH_FUNCTION, fun);
}

tyran_opcodes* code_push_scope()
{
	OPCODES_ALLOC(TN_OP_PUSH_SCOPE);
}

tyran_opcodes* code_push_this()
{
	OPCODES_ALLOC(TN_OP_PUSH_THIS);
}

tyran_opcodes* code_push_top()
{
	OPCODES_ALLOC(TN_OP_PUSH_TOP);
}

tyran_opcodes* code_push_top2()
{
	OPCODES_ALLOC(TN_OP_PUSH_TOP2);
}

tyran_opcodes* tyran_opcode_pop(int n)
{
	OPCODES_ALLOC_INTEGER(TN_OP_POP, n);
}


/* Arithmetic */
tyran_opcodes* code_negative()
{
	OPCODES_ALLOC(TN_OP_NEGATIVE);
}

tyran_opcodes* code_positive()
{
	OPCODES_ALLOC(TN_OP_POSITIVE);
}

tyran_opcodes* code_not()
{
	OPCODES_ALLOC(TN_OP_NOT);
}

tyran_opcodes* code_add()
{
	OPCODES_ALLOC(TN_OP_ADD);
}

tyran_opcodes* code_subtract()
{
	OPCODES_ALLOC(TN_OP_SUBTRACT);
}

tyran_opcodes* code_multiply()
{
	OPCODES_ALLOC(TN_OP_MULTIPLY);
}

tyran_opcodes* code_divide()
{
	OPCODES_ALLOC(TN_OP_DIVIDE);
}

tyran_opcodes* code_modulus()
{
	OPCODES_ALLOC(TN_OP_MODULUS);
}

tyran_opcodes* code_increase(int e)
{
	OPCODES_ALLOC_INTEGER(TN_OP_INCREASE, e);
}

tyran_opcodes* code_decrease(int e)
{
	OPCODES_ALLOC_INTEGER(TN_OP_DECREASE, e);
}

/* Bitwise */
tyran_opcodes* tyran_opcode_bitwise_not()
{
	OPCODES_ALLOC(TN_OP_BITWISE_NOT);
}

tyran_opcodes* tyran_opcode_bitwise_and()
{
	OPCODES_ALLOC(TN_OP_BITWISE_AND);
}

tyran_opcodes* tyran_opcode_bitwise_or()
{
	OPCODES_ALLOC(TN_OP_BITWISE_OR);
}

tyran_opcodes* tyran_opcode_bitwise_xor()
{
	OPCODES_ALLOC(TN_OP_BITWISE_XOR);
}

tyran_opcodes* tyran_opcode_bitwise_shift(enum tyran_shift_mode mode)
{
	OPCODES_ALLOC_INTEGER(TN_OP_BITWISE_SHIFT, mode);
}

/* Compare */
tyran_opcodes* tyran_opcode_compare_equal()
{
	OPCODES_ALLOC(TN_OP_COMPARE_EQUAL);
}

tyran_opcodes* tyran_opcode_compare_not_equal()
{
	OPCODES_ALLOC(TN_OP_COMPARE_NOT_EQUAL);
}

tyran_opcodes* tyran_opcode_compare_less()
{
	OPCODES_ALLOC(TN_OP_COMPARE_LESS);
}

tyran_opcodes* tyran_opcode_compare_less_equal()
{
	OPCODES_ALLOC(TN_OP_COMPARE_LESS_EQUAL);
}

tyran_opcodes* tyran_opcode_compare_greater()
{
	OPCODES_ALLOC(TN_OP_COMPARE_GREATER);
}

tyran_opcodes* tyran_opcode_compare_greater_equal()
{
	OPCODES_ALLOC(TN_OP_COMPARE_GREATER_EQUAL);
}

tyran_opcodes* tyran_opcode_compare_strict_equal()
{
	OPCODES_ALLOC(TN_OP_COMPARE_STRICT_EQUAL);
}

tyran_opcodes* tyran_opcode_compare_strict_not_equal()
{
	OPCODES_ALLOC(TN_OP_COMPARE_STRICT_NOT_EQUAL);
}

/* Jumps */
tyran_opcodes* tyran_opcode_jump_false(int off)
{
	OPCODES_ALLOC_INTEGER(TN_OP_JUMP_FALSE, off);
}

tyran_opcodes* tyran_opcode_jump_true(int off)
{
	OPCODES_ALLOC_INTEGER(TN_OP_JUMP_TRUE, off);
}

tyran_opcodes* tyran_opcode_jump_false_pop(int off)
{
	OPCODES_ALLOC_INTEGER(TN_OP_JUMP_FALSE_POP, off);
}

tyran_opcodes* tyran_opcode_jump_true_pop(int off)
{
	OPCODES_ALLOC_INTEGER(TN_OP_JUMP_TRUE_POP, off);
}

tyran_opcodes* tyran_opcode_jump(int off)
{
	OPCODES_ALLOC_INTEGER(TN_OP_JUMP, off);
}

tyran_jump_pop_info* tyran_opcodes_jump_pop_info_new(int offset, int pop_count)
{
	tyran_jump_pop_info *r = (tyran_jump_pop_info*) malloc(sizeof(tyran_jump_pop_info));
	r->offset = offset;
	r->pop_count = pop_count;
	return r;
}

tyran_opcodes* tyran_opcode_jump_pop(int offset, int pop_count)
{
	OPCODES_ALLOC_POINTER(TN_OP_JUMP_POP, tyran_opcodes_jump_pop_info_new(offset, pop_count));
}

tyran_opcodes* tyran_opcode_call(int argc)
{
	OPCODES_ALLOC_INTEGER(TN_OP_CALL, argc);
}

tyran_opcodes* tyran_opcode_new(int argc)
{
	OPCODES_ALLOC_INTEGER(TN_OP_NEW, argc);
}

tyran_opcodes* tyran_opcode_return(int pop_count)
{
	OPCODES_ALLOC_INTEGER(TN_OP_RETURN, pop_count);
}

/* Object */
tyran_opcodes* tyran_opcode_assign(enum tyran_assign_mode mode)
{
	OPCODES_ALLOC_INTEGER(TN_OP_ASSIGN, mode);
}

tyran_opcodes* tyran_opcode_unreference()
{
	OPCODES_ALLOC(TN_OP_UNREFERENCE);
}

tyran_opcodes* tyran_opcode_subscript(int is_right_value)
{
	OPCODES_ALLOC_INTEGER(TN_OP_SUBSCRIPT, is_right_value);
}

/* Object iteration */
tyran_opcodes* tyran_opcode_key()
{
	OPCODES_ALLOC(TN_OP_KEY);
}

tyran_opcodes* tyran_opcode_next()
{
	OPCODES_ALLOC(TN_OP_NEXT);
}

/* Other */
tyran_opcodes* tyran_opcode_nop()
{
	OPCODES_ALLOC(TN_OP_NOP);
}

tyran_opcodes* tyran_opcode_load_this(int n)
{
	OPCODES_ALLOC_INTEGER(TN_OP_LOAD_THIS, n);
}

tyran_opcodes* tyran_opcode_make_object(int c)
{
	OPCODES_ALLOC_INTEGER(TN_OP_MAKE_OBJECT, c);
}

tyran_opcodes* tyran_opcode_make_array(int c)
{
	OPCODES_ALLOC_INTEGER(TN_OP_MAKE_ARRAY, c);
}

tyran_opcodes* tyran_opcode_delete(int n)
{
	OPCODES_ALLOC_INTEGER(TN_OP_DELETE, n);
}

void tyran_opcodes_free(tyran_opcodes* ops)
{
	tyran_free(ops->codes);
	tyran_free(ops);
}

tyran_opcodes* tyran_opcodes_mark_for_resolve(enum tyran_resolve_type type)
{
	tyran_replace_info *ri = (tyran_replace_info*) malloc(sizeof(tyran_replace_info));
	ri->type = type;
	ri->pop_count = 0;
	OPCODES_ALLOC_POINTER(TN_OP_INTERNAL, ri);
}

void tyran_opcodes_resolve(tyran_opcodes* ops, int step_len, int break_only, int pop_count)
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

