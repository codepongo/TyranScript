#ifndef _TYRAN_OPCODE_IDS_H
#define _TYRAN_OPCODE_IDS_H

typedef enum {
	/* Stack */
	TYRAN_OPCODE_NOP,
	TYRAN_OPCODE_PUSH_NUMBER,
	TYRAN_OPCODE_PUSH_STRING,
	TYRAN_OPCODE_PUSH_VARIABLE,
	TYRAN_OPCODE_PUSH_UNDEFINED,
	TYRAN_OPCODE_PUSH_NULL,
	TYRAN_OPCODE_PUSH_BOOLEAN,
	TYRAN_OPCODE_PUSH_FUNCTION,
	TYRAN_OPCODE_PUSH_SCOPE,
	TYRAN_OPCODE_PUSH_THIS,
	TYRAN_OPCODE_PUSH_TOP,
	TYRAN_OPCODE_TOC_DUP,
	TYRAN_OPCODE_PUSH_TOP2,
	TYRAN_OPCODE_POP,

	/* Arithmetic */
	TYRAN_OPCODE_NEGATE, 
	TYRAN_OPCODE_NOT,
	TYRAN_OPCODE_ADD,
	TYRAN_OPCODE_SUBTRACT,
	TYRAN_OPCODE_MULTIPLY,
	TYRAN_OPCODE_DIVIDE,
	TYRAN_OPCODE_MODULUS,
	TYRAN_OPCODE_INCREASE,
	TYRAN_OPCODE_DECREASE,

	/* Bitwise */
	TYRAN_OPCODE_BITWISE_AND,
	TYRAN_OPCODE_BITWISE_OR,
	TYRAN_OPCODE_BITWISE_XOR,
	TYRAN_OPCODE_BITWISE_NOT,
	TYRAN_OPCODE_BITWISE_SHIFT,

	/* Compares */
	TYRAN_OPCODE_COMPARE_EQUAL,
	TYRAN_OPCODE_COMPARE_NOT_EQUAL,
	TYRAN_OPCODE_COMPARE_LESS,
	TYRAN_OPCODE_COMPARE_GREATER,
	TYRAN_OPCODE_COMPARE_LESS_EQUAL,
	TYRAN_OPCODE_COMPARE_GREATER_EQUAL,

	/* Jump and call */
	TYRAN_OPCODE_JUMP,
	TYRAN_OPCODE_JUMP_POP,
	TYRAN_OPCODE_JUMP_TRUE,
	TYRAN_OPCODE_JUMP_FALSE,
	TYRAN_OPCODE_JUMP_TRUE_POP,
	TYRAN_OPCODE_JUMP_FALSE_POP,

	TYRAN_OPCODE_CALL,
	TYRAN_OPCODE_CALL_SET_THIS,
	TYRAN_OPCODE_NEW,
	TYRAN_OPCODE_RETURN,

	/* Object manipulation */
	TYRAN_OPCODE_MAKE_OBJECT,
	TYRAN_OPCODE_MAKE_ARRAY,
	TYRAN_OPCODE_DELETE,
	TYRAN_OPCODE_ASSIGN,
	TYRAN_OPCODE_SUBSCRIPT,
	TYRAN_OPCODE_UNREFERENCE,

	/* Object iteration */
	TYRAN_OPCODE_KEY,
	TYRAN_OPCODE_NEXT,

	/* Other */
	TYRAN_OPCODE_INTERNAL,
	
	TYRAN_OPCODE_MAX_ID
} tyran_opcode_id;

#endif
