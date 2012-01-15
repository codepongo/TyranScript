# TyranScript
Script engine designed to be embedded. Aimed to be compiled fast, have a small footprint, as few opcodes as possible, minimal dependencies and very portable. It uses reference counting to avoid costly garbage collections. Written in C.

## Language

### Keywords
* if ... else
* var
* function
* return
* delete

### Loop and jumps
* for (in)
* while
* do ... while
* continue
* break
* switch ... case ... default

### Operands
* ","
* "="
* "+="
* "-="
* "*="
* "%="
* "<<="
* ">>="
* ">>>="
* "&="
* "|="
* "^="
* "/="
* "||"
* "&&"
* "|"
* "^"
* "&"
* "=="
* "!="
* "==="
* "!==="
* "<="
* ">="
* "+"
* "-"
* "*"
* "/"
* "%"
* "!"
* "++"
* "--"
* "new"
* "."
* "[]"
* "()"

## Opcodes

### Stack
(10)

* PUSH_NUMBER double
* PUSH_STRING string
* PUSH_VARIABLE variable_info* 
* PUSH_UNDEFINED
* PUSH_BOOLEAN int [0 or 1]
* PUSH_FUNCTION function*
* PUSH_THIS
* PUSH_TOP
* PUSH_TOP2
* POP int number_of_elements

### Arithmetic
(10)

* NEGATIVE
* POSITIVE (convert to number)
* NOT
* ADD
* SUBTRACT
* MULTIPLY
* DIVIDE
* MODULUS
* INCREASE
* DECREASE

### Bitwise operations
(5)

* BITWISE_AND
* BITWISE_OR
* BITWISE_XOR
* BITWISE_NOT
* BITWISE_SHIFT int (0=left, 1=right, 2=unsigned right)

### Compare
(8)

* COMPARE_EQUAL
* COMPARE_NOT_EQUAL
* COMPARE_LESS
* COMPARE_GREATER
* COMPARE_LESS_EQUAL
* COMPARE_GREATER_EQUAL
* COMPARE_STRICT_EQUAL
* COMPARE_STRICT_NOT_EQUAL

### Jumps and calls
(8)

* JUMP int offset
* JUMP_TRUE_POP int offset
* JUMP_FALSE_POP int offset
* JUMP_TRUE int offset
* JUMP_FALSE int offset
* CALL int argument_count
* NEW (same as CALL, but creates new object as this) int argument_count
* RETURN int pop_count

### Object manipulation
(6)

* MAKE_OBJECT int number_of_elements
* MAKE_ARRAY int number_of_elements
* DELETE int number_of_elements (1=variable, 2=object member)
* ASSIGN int number_of_elements (1=variable, 2=object member)
* SUBSCRIPT
* UNREFERENCE

### Object iteration
(2)

* KEY
* NEXT

### OTHER
(1)

* SET_THIS (LOAD_THIS?)
* NOP
* DEBUG_BREAK
