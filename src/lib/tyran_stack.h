#ifndef _TYRAN_STACK_H
#define _TYRAN_STACK_H

#define TYRAN_STACK_TOP	(stack[sp-1])
#define TYRAN_STACK_TOP2 (stack[sp-2])

#define TYRAN_STACK_POP_N(n) { \
	int t = n; \
	while (t > 0) { \
		tyran_value_release(stack[sp-t]); \
		--t; \
	} \
	sp -= n; \
}

#define TYRAN_STACK_POP() { \
	tyran_value_release(TYRAN_STACK_TOP); \
	--sp; \
}

#define TYRAN_STACK_TOP_VARIABLE_TO_VALUE() { \
	if (stack[sp - 1].type == TYRAN_VALUE_TYPE_VARIABLE) { \
		tyran_value* v = stack[sp - 1].data.variable; \
		tyran_value_copy(stack[sp - 1], *v); \
	} \
}

#define TYRAN_STACK_TOP2_VARIABLE_TO_VALUE() { \
	if (stack[sp - 1].type == TYRAN_VALUE_TYPE_VARIABLE) { \
		tyran_value* v = stack[sp - 1].data.variable; \
		tyran_value_copy(stack[sp - 1], *v); \
	} \
	if (stack[sp - 2].type == TYRAN_VALUE_TYPE_VARIABLE) { \
		tyran_value* v = stack[sp - 2].data.variable; \
		tyran_value_copy(stack[sp - 2], *v); \
	} \
}

#define TYRAN_STACK_TOP_N_VARIABLE_TO_VALUE(n) { \
	int a = n; \
	int c; \
	for (c = 1; c <= a; ++c) { \
		if (stack[sp - c].type == TYRAN_VALUE_TYPE_VARIABLE) { \
			tyran_value* v = stack[sp - c].data.variable; \
			tyran_value_copy(stack[sp - c], *v); \
		} \
	} \
}

#endif
