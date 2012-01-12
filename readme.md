# TyranScript
Script engine designed to be embedded. Aimed to be compile fast, small footprint, as few opcodes as possible, minimal dependencies and very portable. Written in C.

## Opcodes

### Stack
* PUSH_NUMBER
* PUSH_STRING
* PUSH_VARIABLE
* PUSH_UNDEFINED
* PUSH_BOOLEAN
* PUSH_FUNCTION
* PUSH_ARGUMENTS
* PUSH_THIS
* PUSH_TOP (DUPLICATE)
* PUSH_TOP2 (DUPLICATE2)
* OBJECT
* ARRAY
* POP

### Arithmetic
* NEGATE
* POSITIVE
* NOT
* ADD
* SUBTRACT
* MULTIPLY
* DIVIDE
* MODULUS
* INCREASE
* DECREASE

### Bit operations
* B_AND
* B_OR
* B_XOR
* B_NOT
* SHIFT

### Compare
* EQUAL
* NOT_EQUAL
* LESS
* GREATER
* LESS_EQUAL
* GREATER_EQUAL
* STRICT_EQUAL
* STRICT_NOT_EQUAL

### Jumps and calls
* JUMP
* JUMP_TRUE
* JUMP_FALSE
* JUMP_POP
* CALL
* NEW (calls constructor)
* RETURN

### Object manipulation
* DELETE
* CHANGE_THIS
* ASSIGN
* SUBSCRIPT
* UNREFERENCE

### Object iteration
* KEY
* NEXT

### Exception
* TRY_START
* TRY_END
* CATCH_START
* CATCH_END
* FINALLY_START
* FINALLY_END
* THROW

### OTHER
* NOP
* BREAK