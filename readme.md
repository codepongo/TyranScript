# TyranScript
TyranScript is a tiny, embeddable scripting language written in C. Aimed to compile fast, have a small footprint, as few opcodes as possible, minimal dependencies and very portable. It uses reference counting to avoid costly garbage collections.

## Opcodes
All opcodes are coded within a 32-bit instruction.

* 6 bits. Opcode index.
* 8 bits. Parameter A.
* 9 bits. Parameter X. 1 bit = Register / Constant.
* 9 bits. Parameter Y. 1 bit = Register / Constant.
* BR = (X << 8 + Y) - 32768.

### Variables
* R(). Registers, up to 256 values.
* C(). Constants, up to 256 values.
* RC(v). Register or Constant, depending on the high bit of v.
* S(). Stack.
* PC. Program Counter.

### Register (2)
* 0x01 **LD A X**. Load register. R(A) = R(X).
* 0x02 **LDC A X**. Load constant. R(A) = C(X).

### Operators (12)
* 0x05 **ADD A X Y**. Add. R(A) = RC(X) + RC(Y).    
* 0x06 **DIV A X Y**. Divide. R(A) = RC(X) / RC(Y).
* 0x07 **MOD A X Y**. Modulus. R(A) = RC(X) % RC(Y).
* 0x08 **MUL A X Y**. Multiply. R(A) = RC(X) * RC(Y).
* 0x09 **POW A X Y**. Exponentiation. R(A) = RC(X) ^ RC(Y).
* 0x0A **SUB A X Y**. Subtract. R(A) = RC(X) - RC(Y).
* 0x0D **NEG A X**. Negate. R(A) = -RC(X).
* 0x0E **NOT A X**. Logical Not. R(A) = !RC(X).
* xxxx **INDEX A X Y**. Index. R(A) = R(X)[ R(Y) ].
* xxxx **INDEX_SET A X Y**. Index Set. R(A)[ RC(X) ] = RC(Y).

### Jumps and calls (8)
* 0x11 **JEQ A X Y**. Jump Equal. if (RC(X) == RC(Y)) != (BOOL)A then PC++.
* 0x12 **JLT A X Y**. Jump less than. if (RC(X) < RC(Y)) != (BOOL)A then PC++.
* 0x13 **JLE A X Y**. Jump less. if (RC(X) <= RC(Y)) != (BOOL)A then PC++.
* 0x14 **JMP BR** . Jump. PC += BR.
* 0x15 **RET A X**. Return from call. returns R(A .. A + X - 2).
* 0x16 **CALL A X Y**. Call a function. R(A) holds the function object. X is number of arguments. Y is number of used return values. R(A+1) = SELF, R(A+2..A+X) are the arguments. Return values are stored in R(A+1..). 
* xxxx **NEW A X Y**. Call a function with a new object. R(A) holds the function object. X is number of arguments. Y is number of used return values. R(A+1) = SELF, R(A+2..A+X) are the arguments. Return values are stored in R(A+1..). 

### Function
* 0x17 **FUNC A**. Create a function. R(A)=new function.

### Object
* 0x0B **SET A X Y**. Sets member (symbol). R(A)[ RC(X) ] = R(Y).
* 0x0C **GET A X Y**. Gets member (symbol). R(A) = R(X)[ RC(Y) ].

## Syntax

##### Conditional
* if then else (with postfix)
* unless (if not)
* case/switch when

##### Loops
* while (with postfix)
* until (while not)
* for in/of (with postfix) [when EXPRESSION]

##### Array
* slicing [0..2]

##### Existential
* ?

##### Destructuring assignments
* [a, b, c] = [1, 2, 3]

##### Functions
* =>
* ->

##### Other
* Splats ...
* String interpolation "result:#{something.other()}"

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
