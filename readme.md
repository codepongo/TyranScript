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

### Register (4)
* **LD A X**. Load register. R(A) = R(X).
* **LDC A X**. Load constant. R(A) = C(X).
* **LDB A X**. Load boolean. R(A) = (BOOL)X.
* **LDN A X.** Load NULL. R(A..A+X) = NULL.

### Arithmetic (8)
* **ADD A X Y**. Add. R(A) = RC(X) + RC(Y).    
* **DIV A X Y**. Divide. R(A) = RC(X) / RC(Y).
* **MOD A X Y**. Modulus. R(A) = RC(X) % RC(Y).
* **MUL A X Y**. Multiply. R(A) = RC(X) * RC(Y).
* **NEG A X**. Negate. R(A) = -RC(X).
* **NOT A X**. Logical Not. R(A) = !RC(X).
* **POW A X Y**. Exponentiation. R(A) = RC(X) ^ RC(Y).
* **SUB A X Y**. Subtract. R(A) = RC(X) - RC(Y).

### Jumps and calls (8)
* **JB A X**. Jump boolean. if !(RC(X) != A) then PC++.
* **JBLD A X Y**. Jump boolean and load. if RC(X) != (BOOL)Y then R(A) = RC(X) else PC++.
* **JEQ A X Y**. Jump Equal. if (RC(X) == RC(Y)) != (BOOL)A then PC++.
* **JLT A X Y**. Jump less than. if (RC(X) < RC(Y)) != (BOOL)A then PC++.
* **JLE A X Y**. Jump less. if (RC(X) <= RC(Y)) != (BOOL)A then PC++.
* **JMP BR** . Jump. PC += BR.
* **RET A X**. Return from call. returns R(A .. A + X - 2).
* **CALL A X Y**. Call a function. R(A) holds the function object. X is number of arguments. Y is number of used return values. R(A+1) = SELF, R(A+2..A+X) are the arguments. Return values are stored in R(A+1..). 

### Function
* **FUNC A**. Create a function. R(A)=new function.


### Object (5)
* **SET A X Y**. R(A)[ RC(X) ] = R(Y).
* **GET A X Y**. R(A) = R(X)[ RC(Y) ].

* **LEN A X**. R(A) = length( R(X) ).
* **KEY A X**. R(A) = new iterator for object R(X).
* **NEXT A X**. R(A) = next key for iterator R(X).



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
