#ifndef _TYRAN_OPCODES_H
#define _TYRAN_OPCODES_H

#include <tyranscript/tyran_opcode_enums.h>
#include <tyranscript/tyran_string.h>

struct tyran_function;
struct tyran_opcode;

typedef struct tyran_opcodes {
	struct tyran_opcode* codes;
	int code_len;
	int code_size;

	int expression_count;
	enum tyran_assign_mode lvalue_flag;
	const tyran_string* lvalue_name;
} tyran_opcodes;

/* Opcodes */
struct tyran_opcodes* tyran_opcodes_new(int size);
void tyran_opcodes_free(struct tyran_opcodes* codes);

struct tyran_opcodes* tyran_opcodes_merge(struct tyran_opcodes* a, struct tyran_opcodes* b);
struct tyran_opcodes* tyran_opcodes_merge3(struct tyran_opcodes* a, struct tyran_opcodes* b, struct tyran_opcodes* c);
struct tyran_opcodes* tyran_opcodes_merge4(struct tyran_opcodes* a, struct tyran_opcodes* b, struct tyran_opcodes* c, struct tyran_opcodes* d);

struct tyran_opcodes* tyran_opcodes_insert_mark_for_resolve(enum tyran_resolve_type type);
void tyran_opcodes_resolve(struct tyran_opcodes* codes, int step_len, int break_only, int pop_count);

/* Stack */
struct tyran_opcodes* tyran_opcodes_insert_push_number(const double *v);
struct tyran_opcodes* tyran_opcodes_insert_push_string(const tyran_string* str);
struct tyran_opcodes* tyran_opcodes_insert_push_variable(const tyran_string* variable_name);
struct tyran_opcodes* tyran_opcodes_insert_push_undefined();
struct tyran_opcodes* tyran_opcodes_insert_push_boolean(int v);
struct tyran_opcodes* tyran_opcodes_insert_push_function(const struct tyran_function* func);
struct tyran_opcodes* tyran_opcodes_insert_push_scope();
struct tyran_opcodes* tyran_opcodes_insert_push_this();
struct tyran_opcodes* tyran_opcodes_insert_push_top();
struct tyran_opcodes* tyran_opcodes_insert_push_top2();
struct tyran_opcodes* tyran_opcodes_insert_pop(int count);

/* Arithmetic */
struct tyran_opcodes* tyran_opcodes_insert_negate();
struct tyran_opcodes* tyran_opcodes_insert_not();
struct tyran_opcodes* tyran_opcodes_insert_add();
struct tyran_opcodes* tyran_opcodes_insert_subtract();
struct tyran_opcodes* tyran_opcodes_insert_multiply();
struct tyran_opcodes* tyran_opcodes_insert_divide();
struct tyran_opcodes* tyran_opcodes_insert_modulus();
struct tyran_opcodes* tyran_opcodes_insert_increase(int amount);
struct tyran_opcodes* tyran_opcodes_insert_decrease(int amount);

/* Bitwise */
struct tyran_opcodes* tyran_opcodes_insert_bitwise_not();
struct tyran_opcodes* tyran_opcodes_insert_bitwise_and();
struct tyran_opcodes* tyran_opcodes_insert_bitwise_or();
struct tyran_opcodes* tyran_opcodes_insert_bitwise_xor();
struct tyran_opcodes* tyran_opcodes_insert_bitwise_shift(enum tyran_shift_mode shift_type);

/* Compare */
struct tyran_opcodes* tyran_opcodes_insert_compare_equal();
struct tyran_opcodes* tyran_opcodes_insert_compare_not_equal();
struct tyran_opcodes* tyran_opcodes_insert_compare_less();
struct tyran_opcodes* tyran_opcodes_insert_compare_less_equal();
struct tyran_opcodes* tyran_opcodes_insert_compare_greater();
struct tyran_opcodes* tyran_opcodes_insert_compare_greater_equal();
struct tyran_opcodes* tyran_opcodes_insert_compare_strict_equal();
struct tyran_opcodes* tyran_opcodes_insert_compare_strict_not_equal();

/* Jumps */
struct tyran_opcodes* tyran_opcodes_insert_jump_false_pop(int offset);
struct tyran_opcodes* tyran_opcodes_insert_jump_true_pop(int offset);
struct tyran_opcodes* tyran_opcodes_insert_jump_false(int offset);
struct tyran_opcodes* tyran_opcodes_insert_jump_true(int offset);
struct tyran_opcodes* tyran_opcodes_insert_jump(int offset);

struct tyran_opcodes* tyran_opcodes_insert_call(int argument_count);
struct tyran_opcodes* tyran_opcodes_insert_new_call(int argument_count);
struct tyran_opcodes* tyran_opcodes_insert_return(int pop_count);

/* Object */
struct tyran_opcodes* tyran_opcodes_insert_assign(enum tyran_assign_mode mode);
struct tyran_opcodes* tyran_opcodes_insert_unreference();
struct tyran_opcodes* tyran_opcodes_insert_subscript(int is_right_value);
struct tyran_opcodes* tyran_opcodes_insert_make_object(int count);
struct tyran_opcodes* tyran_opcodes_insert_make_array(int count);
struct tyran_opcodes* tyran_opcodes_insert_delete(enum tyran_assign_mode mode);

/* Object iteration */
struct tyran_opcodes* tyran_opcodes_insert_key();
struct tyran_opcodes* tyran_opcodes_insert_next();

/* Other */
struct tyran_opcodes* tyran_opcodes_insert_nop();
struct tyran_opcodes* tyran_opcodes_insert_load_this(int n);

#endif
