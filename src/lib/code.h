#ifndef _TYRAN_CODE_H
#define _TYRAN_CODE_H

#include <tyranscript/unicode_char.h>
#include <tyranscript/opcode_enums.h>

struct tyran_function;
struct tyran_opcodes;

/* Opcodes */
struct tyran_opcodes* tyran_opcodes_new(int size);
void tyran_opcodes_free(struct tyran_opcodes* codes);

struct tyran_opcodes* tyran_opcodes_add(struct tyran_opcodes* a, struct tyran_opcodes* b);
struct tyran_opcodes* tyran_opcodes_add3(struct tyran_opcodes* a, struct tyran_opcodes* b, struct tyran_opcodes* c);
struct tyran_opcodes* tyran_opcodes_add4(struct tyran_opcodes* a, struct tyran_opcodes* b, struct tyran_opcodes* c, struct tyran_opcodes* d);
struct tyran_opcodes* tyran_opcodes_mark_for_resolve(enum tyran_resolve_type type);
void tyran_opcodes_resolve(struct tyran_opcodes* codes, int step_len, int break_only, int pop_count);

/* Stack */
struct tyran_opcodes* tyran_opcode_push_number(double *v);
struct tyran_opcodes* tyran_opcode_push_string(const unicode_char* str);
struct tyran_opcodes* tyran_opcode_push_variable(const unicode_char* varname);
struct tyran_opcodes* tyran_opcode_push_undefined();
struct tyran_opcodes* tyran_opcode_push_boolean(int v);
struct tyran_opcodes* tyran_opcode_push_function(struct tyran_function* fun);
struct tyran_opcodes* tyran_opcode_push_scope();
struct tyran_opcodes* tyran_opcode_push_this();
struct tyran_opcodes* tyran_opcode_push_top();
struct tyran_opcodes* tyran_opcode_push_top2();
struct tyran_opcodes* tyran_opcode_pop(int count);

/* Arithmetic */
struct tyran_opcodes* tyran_opcode_negative();
struct tyran_opcodes* tyran_opcode_positive();
struct tyran_opcodes* tyran_opcode_not();
struct tyran_opcodes* tyran_opcode_add();
struct tyran_opcodes* tyran_opcode_subtract();
struct tyran_opcodes* tyran_opcode_multiply();
struct tyran_opcodes* tyran_opcode_divide();
struct tyran_opcodes* tyran_opcode_modulus();
struct tyran_opcodes* tyran_opcode_increase(int amount);
struct tyran_opcodes* tyran_opcode_decrease(int amount);

/* Bitwise */
struct tyran_opcodes* tyran_opcode_bitwise_not();
struct tyran_opcodes* tyran_opcode_bitwise_and();
struct tyran_opcodes* tyran_opcode_bitwise_or();
struct tyran_opcodes* tyran_opcode_bitwise_xor();
struct tyran_opcodes* tyran_opcode_bitwise_shift(enum tyran_shift_mode shift_type);

/* Compare */
struct tyran_opcodes* tyran_opcode_compare_equal();
struct tyran_opcodes* tyran_opcode_compare_not_equal();
struct tyran_opcodes* tyran_opcode_compare_less();
struct tyran_opcodes* tyran_opcode_compare_less_equal();
struct tyran_opcodes* tyran_opcode_compare_greater();
struct tyran_opcodes* tyran_opcode_compare_greater_equal();
struct tyran_opcodes* tyran_opcode_compare_strict_equal();
struct tyran_opcodes* tyran_opcode_compare_strict_not_equal();

/* Jumps */
struct tyran_opcodes* tyran_opcode_jump_false_pop(int off);
struct tyran_opcodes* tyran_opcode_jump_true_pop(int off);
struct tyran_opcodes* tyran_opcode_jump_false(int off);
struct tyran_opcodes* tyran_opcode_jump_true(int off);
struct tyran_opcodes* tyran_opcode_jump(int off);

struct tyran_opcodes* tyran_opcode_call(int argument_count);
struct tyran_opcodes* tyran_opcode_new(int argument_count);
struct tyran_opcodes* tyran_opcode_return(int pop_count);

/* Object */
struct tyran_opcodes* tyran_opcode_assign(enum tyran_assign_mode mode);
struct tyran_opcodes* tyran_opcode_unreference();
struct tyran_opcodes* tyran_opcode_subscript(int is_right_value);
struct tyran_opcodes* tyran_opcode_make_object(int count);
struct tyran_opcodes* tyran_opcode_make_array(int count);
struct tyran_opcodes* tyran_opcode_delete(enum tyran_assign_mode mode);

/* Object iteration */
struct tyran_opcodes* tyran_opcode_key();
struct tyran_opcodes* tyran_opcode_next();

/* Other */
struct tyran_opcodes* tyran_opcode_nop();
struct tyran_opcodes* tyran_opcode_load_this(int n);

#endif
