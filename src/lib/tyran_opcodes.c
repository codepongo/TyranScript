#include <tyranscript/tyran_opcodes.h>
#include <tyranscript/tyran_config.h>

#include <tyranscript/tyran_opcode.h>

#define OPCODES_ALLOC(code) { \
		struct tyran_opcodes* r = tyran_opcodes_new(3); \
		tyran_opcodes_insert_code(r, (code)); \
		return r; \
	}

#define OPCODES_ALLOC_INTEGER(code, extra) { \
		struct tyran_opcodes* r = tyran_opcodes_new(3); \
		tyran_opcodes_insert_code_with_integer(r, (code), extra); \
		return r; \
	}

#define OPCODES_ALLOC_POINTER(code, extra) { \
		struct tyran_opcodes* r = tyran_opcodes_new(3); \
		tyran_opcodes_insert_code_with_pointer(r, (code), (void*)extra); \
		return r; \
	}

typedef struct tyran_replace_info {
	enum tyran_resolve_type type;
	int pop_count;
} tyran_replace_info;

struct tyran_opcodes* tyran_opcodes_new(int size)
{
	struct tyran_opcodes* ret = (struct tyran_opcodes*) TYRAN_CALLOC(tyran_opcodes);
	ret->codes = (struct tyran_opcode*) tyran_malloc(sizeof(struct tyran_opcode) * size);
	ret->code_size = size;
	return ret;
}

void tyran_opcodes_free(struct tyran_opcodes* ops)
{
	tyran_free(ops->codes);
	tyran_free(ops);
}

struct tyran_opcodes* tyran_opcodes_merge(struct tyran_opcodes* a, struct tyran_opcodes* b)
{
	if (!a || !a->code_len) {
		return b;
	}
	if (!b || !b->code_len) {
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

struct tyran_opcodes* tyran_opcodes_merge3(struct tyran_opcodes* a, struct tyran_opcodes* b, struct tyran_opcodes* c)
{
	return tyran_opcodes_merge(tyran_opcodes_merge(a, b), c);
}

struct tyran_opcodes* tyran_opcodes_merge4(struct tyran_opcodes* a, struct tyran_opcodes* b, struct tyran_opcodes* c, struct tyran_opcodes* d)
{
	return tyran_opcodes_merge(tyran_opcodes_merge(a, b), tyran_opcodes_merge(c, d));
}

struct tyran_opcode* tyran_opcodes_insert_code(struct tyran_opcodes* c, tyran_opcode_id code)
{
	if (c->code_size == c->code_len) {
		c->code_size = c->code_size * 2 + 1;
		c->codes = (struct tyran_opcode*) realloc(c->codes, c->code_size * sizeof(struct tyran_opcode));
	}
	c->codes[c->code_len].opcode = code;
	c->code_len++;
	return &c->codes[c->code_len - 1];
}

void tyran_opcodes_insert_code_with_pointer(struct tyran_opcodes* c, tyran_opcode_id opcode_id, void* param)
{
	struct tyran_opcode* code = tyran_opcodes_insert_code(c, opcode_id);
	code->data.pointer = param;
}

void tyran_opcodes_insert_code_with_integer(struct tyran_opcodes* c, tyran_opcode_id opcode_id, int param)
{
	struct tyran_opcode* code = tyran_opcodes_insert_code(c, opcode_id);
	code->data.integer = param;
}

/* Stack */
struct tyran_opcodes* tyran_opcodes_insert_push_number(const double *v)
{
	OPCODES_ALLOC_POINTER(TYRAN_OPCODE_PUSH_NUMBER, v);
}

struct tyran_opcodes* tyran_opcodes_insert_push_string(const tyran_string* str)
{
	OPCODES_ALLOC_POINTER(TYRAN_OPCODE_PUSH_STRING, str);
}

struct tyran_opcodes* tyran_opcodes_insert_push_variable(const tyran_string* variable_name)
{
	struct tyran_variable_name_info* n = TYRAN_CALLOC(tyran_variable_name_info);
	n->data.variable_name = variable_name;
	OPCODES_ALLOC_POINTER(TYRAN_OPCODE_PUSH_VARIABLE, n);
}

struct tyran_opcodes* tyran_opcodes_insert_push_undefined()
{
	OPCODES_ALLOC(TYRAN_OPCODE_PUSH_UNDEFINED);
}

struct tyran_opcodes* tyran_opcodes_insert_push_boolean(int v)
{
	OPCODES_ALLOC_INTEGER(TYRAN_OPCODE_PUSH_BOOLEAN, v);
}

struct tyran_opcodes* tyran_opcodes_insert_push_function(const struct tyran_function *fun)
{
	OPCODES_ALLOC_POINTER(TYRAN_OPCODE_PUSH_FUNCTION, fun);
}

struct tyran_opcodes* tyran_opcodes_insert_push_scope()
{
	OPCODES_ALLOC(TYRAN_OPCODE_PUSH_SCOPE);
}

struct tyran_opcodes* tyran_opcodes_insert_push_this()
{
	OPCODES_ALLOC(TYRAN_OPCODE_PUSH_THIS);
}

struct tyran_opcodes* tyran_opcodes_insert_push_top()
{
	OPCODES_ALLOC(TYRAN_OPCODE_PUSH_TOP);
}

struct tyran_opcodes* tyran_opcodes_insert_push_top2()
{
	OPCODES_ALLOC(TYRAN_OPCODE_PUSH_TOP2);
}

struct tyran_opcodes* tyran_opcodes_insert_pop(int n)
{
	OPCODES_ALLOC_INTEGER(TYRAN_OPCODE_POP, n);
}

/* Arithmetic */
struct tyran_opcodes* tyran_opcodes_insert_negate()
{
	OPCODES_ALLOC(TYRAN_OPCODE_NEGATE);
}

struct tyran_opcodes* tyran_opcodes_insert_not()
{
	OPCODES_ALLOC(TYRAN_OPCODE_NOT);
}

struct tyran_opcodes* tyran_opcodes_insert_add()
{
	OPCODES_ALLOC(TYRAN_OPCODE_ADD);
}

struct tyran_opcodes* tyran_opcodes_insert_subtract()
{
	OPCODES_ALLOC(TYRAN_OPCODE_SUBTRACT);
}

struct tyran_opcodes* tyran_opcodes_insert_multiply()
{
	OPCODES_ALLOC(TYRAN_OPCODE_MULTIPLY);
}

struct tyran_opcodes* tyran_opcodes_insert_divide()
{
	OPCODES_ALLOC(TYRAN_OPCODE_DIVIDE);
}

struct tyran_opcodes* tyran_opcodes_insert_modulus()
{
	OPCODES_ALLOC(TYRAN_OPCODE_MODULUS);
}

struct tyran_opcodes* tyran_opcodes_insert_increase(int e)
{
	OPCODES_ALLOC_INTEGER(TYRAN_OPCODE_INCREASE, e);
}

struct tyran_opcodes* tyran_opcodes_insert_decrease(int e)
{
	OPCODES_ALLOC_INTEGER(TYRAN_OPCODE_DECREASE, e);
}

/* Bitwise */
struct tyran_opcodes* tyran_opcodes_insert_bitwise_not()
{
	OPCODES_ALLOC(TYRAN_OPCODE_BITWISE_NOT);
}

struct tyran_opcodes* tyran_opcodes_insert_bitwise_and()
{
	OPCODES_ALLOC(TYRAN_OPCODE_BITWISE_AND);
}

struct tyran_opcodes* tyran_opcodes_insert_bitwise_or()
{
	OPCODES_ALLOC(TYRAN_OPCODE_BITWISE_OR);
}

struct tyran_opcodes* tyran_opcodes_insert_bitwise_xor()
{
	OPCODES_ALLOC(TYRAN_OPCODE_BITWISE_XOR);
}

struct tyran_opcodes* tyran_opcodes_insert_bitwise_shift(enum tyran_shift_mode mode)
{
	OPCODES_ALLOC_INTEGER(TYRAN_OPCODE_BITWISE_SHIFT, mode);
}

/* Compare */
struct tyran_opcodes* tyran_opcodes_insert_compare_equal()
{
	OPCODES_ALLOC(TYRAN_OPCODE_COMPARE_EQUAL);
}

struct tyran_opcodes* tyran_opcodes_insert_compare_not_equal()
{
	OPCODES_ALLOC(TYRAN_OPCODE_COMPARE_NOT_EQUAL);
}

struct tyran_opcodes* tyran_opcodes_insert_compare_less()
{
	OPCODES_ALLOC(TYRAN_OPCODE_COMPARE_LESS);
}

struct tyran_opcodes* tyran_opcodes_insert_compare_less_equal()
{
	OPCODES_ALLOC(TYRAN_OPCODE_COMPARE_LESS_EQUAL);
}

struct tyran_opcodes* tyran_opcodes_insert_compare_greater()
{
	OPCODES_ALLOC(TYRAN_OPCODE_COMPARE_GREATER);
}

struct tyran_opcodes* tyran_opcodes_insert_compare_greater_equal()
{
	OPCODES_ALLOC(TYRAN_OPCODE_COMPARE_GREATER_EQUAL);
}

/* Jumps */
struct tyran_opcodes* tyran_opcodes_insert_jump_false(int offset)
{
	OPCODES_ALLOC_INTEGER(TYRAN_OPCODE_JUMP_FALSE, offset);
}

struct tyran_opcodes* tyran_opcodes_insert_jump_true(int offset)
{
	OPCODES_ALLOC_INTEGER(TYRAN_OPCODE_JUMP_TRUE, offset);
}

struct tyran_opcodes* tyran_opcodes_insert_jump_false_pop(int offset)
{
	OPCODES_ALLOC_INTEGER(TYRAN_OPCODE_JUMP_FALSE_POP, offset);
}

struct tyran_opcodes* tyran_opcodes_insert_jump_true_pop(int offset)
{
	OPCODES_ALLOC_INTEGER(TYRAN_OPCODE_JUMP_TRUE_POP, offset);
}

struct tyran_opcodes* tyran_opcodes_insert_jump(int offset)
{
	OPCODES_ALLOC_INTEGER(TYRAN_OPCODE_JUMP, offset);
}

struct tyran_jump_pop_info* tyran_opcodes_insert_jump_pop_info_new(int offset, int pop_count)
{
	struct tyran_jump_pop_info *r = (struct tyran_jump_pop_info*) tyran_malloc(sizeof(struct tyran_jump_pop_info));
	r->offset = offset;
	r->pop_count = pop_count;
	return r;
}

struct tyran_opcodes* tyran_opcodes_insert_call(int argc)
{
	OPCODES_ALLOC_INTEGER(TYRAN_OPCODE_CALL, argc);
}

struct tyran_opcodes* tyran_opcodes_insert_new_call(int argc)
{
	OPCODES_ALLOC_INTEGER(TYRAN_OPCODE_NEW, argc);
}

struct tyran_opcodes* tyran_opcodes_insert_return(int pop_count)
{
	OPCODES_ALLOC_INTEGER(TYRAN_OPCODE_RETURN, pop_count);
}

/* Object */
struct tyran_opcodes* tyran_opcodes_insert_assign(enum tyran_assign_mode mode)
{
	OPCODES_ALLOC_INTEGER(TYRAN_OPCODE_ASSIGN, mode);
}

struct tyran_opcodes* tyran_opcodes_insert_unreference()
{
	OPCODES_ALLOC(TYRAN_OPCODE_UNREFERENCE);
}

struct tyran_opcodes* tyran_opcodes_insert_subscript(int is_right_value)
{
	OPCODES_ALLOC_INTEGER(TYRAN_OPCODE_SUBSCRIPT, is_right_value);
}

/* tyran_object iteration */
struct tyran_opcodes* tyran_opcodes_insert_key()
{
	OPCODES_ALLOC(TYRAN_OPCODE_KEY);
}

struct tyran_opcodes* tyran_opcodes_insert_next()
{
	OPCODES_ALLOC(TYRAN_OPCODE_NEXT);
}

/* Other */
struct tyran_opcodes* tyran_opcodes_insert_nop()
{
	OPCODES_ALLOC(TYRAN_OPCODE_NOP);
}

struct tyran_opcodes* tyran_opcodes_insert_load_this()
{
	OPCODES_ALLOC(TYRAN_OPCODE_LOAD_THIS);
}

struct tyran_opcodes* tyran_opcodes_insert_make_object(int c)
{
	OPCODES_ALLOC_INTEGER(TYRAN_OPCODE_MAKE_OBJECT, c);
}

struct tyran_opcodes* tyran_opcodes_insert_make_array(int c)
{
	OPCODES_ALLOC_INTEGER(TYRAN_OPCODE_MAKE_ARRAY, c);
}

struct tyran_opcodes* tyran_opcodes_insert_delete(enum tyran_assign_mode mode)
{
	OPCODES_ALLOC_INTEGER(TYRAN_OPCODE_DELETE, mode);
}

struct tyran_opcodes* tyran_opcodes_insert_mark_for_resolve(enum tyran_resolve_type type)
{
	tyran_replace_info *ri = TYRAN_MALLOC_TYPE(tyran_replace_info, 1);
	ri->type = type;
	ri->pop_count = 0;
	OPCODES_ALLOC_POINTER(TYRAN_OPCODE_INTERNAL, ri);
}

void tyran_opcodes_resolve(struct tyran_opcodes* ops, int step_len, int break_only, int pop_count)
{
	int i;

	for (i = 0; i < ops->code_len; ++i)
	{
		if (ops->codes[i].opcode != TYRAN_OPCODE_INTERNAL) {
			continue;
		}
		
		tyran_replace_info *ri = (tyran_replace_info*) ops->codes[i].data.pointer;

		switch (ri->type) {
			case tyran_resolve_continue: {
				if (break_only) {
					ri->pop_count += pop_count;
					continue;
				} else {
					int pop_count = ri->pop_count;
					tyran_free(ri);
					if (pop_count) {
						ops->codes[i].data.pointer = tyran_opcodes_insert_jump_pop_info_new(ops->code_len - i, pop_count);
						ops->codes[i].opcode = TYRAN_OPCODE_JUMP_POP;
					} else {
						ops->codes[i].data.integer = ops->code_len - i;
						ops->codes[i].opcode = TYRAN_OPCODE_JUMP;
					}
				}
			}
			break;
			case tyran_resolve_break: {
				int pop_count = ri->pop_count;
				tyran_free(ri);
				if (pop_count) {
					ops->codes[i].data.pointer = tyran_opcodes_insert_jump_pop_info_new(step_len + ops->code_len - i, pop_count);
					ops->codes[i].opcode = TYRAN_OPCODE_JUMP_POP;
				} else {
					ops->codes[i].data.integer = step_len + ops->code_len - i;
					ops->codes[i].opcode = TYRAN_OPCODE_JUMP;
				}
			}
			break;
		}
	}
}

