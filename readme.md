# TyranScript
TyranScript is a tiny, embeddable scripting language written in C. Aimed to compile fast, have a small footprint, as few opcodes as possible, minimal dependencies and very portable. It uses reference counting to avoid costly garbage collections.

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
* , = += -= *= %= <<= >>= >>>= &= |= ^= /= || && | ^ & == != === !=== <= >= + - * / % ! ++ -- new . \[ \] \( \)

## Opcodes

### Stack

* PUSH_NUMBER double
* PUSH_STRING string
* PUSH_UNDEFINED
* PUSH_BOOLEAN (int bool) [0 or 1]
* PUSH_FUNCTION (function*)
* PUSH_THIS
* PUSH_TOP
* PUSH_TOP2
* PUSH_LOCAL (int index)
* PUSH_ARGUMENT (int index)
* TOC_DUP
* POP_LOCAL (int index)
* POP_ARGUMENT (int index)
* POP (int number_of_elements)

### Arithmetic

* NEGATIVE
* NOT
* ADD
* SUBTRACT
* MULTIPLY
* DIVIDE
* MODULUS
* INCREASE
* DECREASE

### Bitwise operations

* BITWISE_AND
* BITWISE_OR
* BITWISE_XOR
* BITWISE_NOT
* BITWISE_SHIFT (int mode) [0=left, 1=right, 2=unsigned right]

### Compare

* COMPARE_EQUAL
* COMPARE_NOT_EQUAL
* COMPARE_LESS
* COMPARE_GREATER
* COMPARE_LESS_EQUAL
* COMPARE_GREATER_EQUAL

### Jumps and calls

* JUMP (int offset)
* JUMP_POP jump_pop_info* (offset and pop_count)
* JUMP_TRUE_POP (int offset)
* JUMP_FALSE_POP (int offset)
* JUMP_TRUE (int offset)
* JUMP_FALSE (int offset)
* CALL (int argument_count)
* NEW (int argument_count) [same as CALL, but creates new object as this]
* RETURN (int pop_count)

### Object manipulation

* MAKE_OBJECT (int number_of_elements) [int32 member_id, value, ...]
* MAKE_ARRAY (int number_of_elements) [value, ...]
* DELETE (int member_id)
* ASSIGN (int32 member_id)
* SUBSCRIPT (int32 member_id)
* UNREFERENCE

### Object iteration

* KEY
* NEXT

### Other

* NOP


## Licenses

#### stringencoders
Fast number to string conversion using stringencoders:

Copyright (c) 2007, Nick Galbreath -- nickg [at] modp [dot] com

  * All rights reserved.
  * [stringencoders](http://code.google.com/p/stringencoders/)
  * Released under the MIT license.

#### Generic-Red-Black-Tree
 
Red Black Tree implementation by Frederico Gonçalves [Generic-Red-Black-Tree](https://github.com/fgoncalves/Generic-Red-Black-Tree)

Copyright (c) 2012 Frederico Gonçalves

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
