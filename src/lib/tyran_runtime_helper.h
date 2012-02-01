#ifndef _TYRAN_RUNTIME_HELPER_H
#define _TYRAN_RUNTIME_HELPER_H

#include <tyranscript/tyran_value.h>
#include <tyranscript/tyran_opcode_enums.h>

#define tyran_runtime_arithmetic(operand) { \
	TYRAN_STACK_TOP2_VARIABLE_TO_VALUE(); \
	TYRAN_ASSERT(tyran_value_is_number(&TYRAN_STACK_TOP), "Must be numbers for bitwise operations"); \
	TYRAN_ASSERT(tyran_value_is_number(&TYRAN_STACK_TOP2), "Must be numbers for bitwise operations"); \
	TYRAN_STACK_TOP2.data.number = TYRAN_STACK_TOP2.data.number operand TYRAN_STACK_TOP.data.number; \
	TYRAN_STACK_POP(); \
}

#define tyran_runtime_bitwise_operation(operand) { \
	int a, b; \
	TYRAN_STACK_TOP2_VARIABLE_TO_VALUE(); \
	TYRAN_ASSERT(tyran_value_is_number(&TYRAN_STACK_TOP), "Must be numbers for bitwise operations"); \
	TYRAN_ASSERT(tyran_value_is_number(&TYRAN_STACK_TOP2), "Must be numbers for bitwise operations"); \
	a = (int) TYRAN_STACK_TOP2.data.number; \
	b = (int) TYRAN_STACK_TOP.data.number; \
	TYRAN_STACK_TOP2.data.number = (double)(a operand b); \
	TYRAN_STACK_POP(); \
}

void tyran_runtime_logical_less(tyran_value v1, tyran_value v2, tyran_value* res);
void tyran_runtime_value_object_subscript(tyran_value* target, tyran_value* key, tyran_value* existing_value, enum tyran_subscript_mode mode);

#endif
