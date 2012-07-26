/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton interface for Bison's Yacc-like parsers in C

   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     COMMENT = 258,
     UNARY = 259,
     COMPARE = 260,
     FOROF = 261,
     IDENTIFIER = 262,
     TERMINATOR = 263,
     INDEX_START = 264,
     SHIFT = 265,
     INDENT = 266,
     SWITCH = 267,
     PARAM_END = 268,
     TYRAN_TOKEN_NULL = 269,
     CALL_START = 270,
     UNDEFINED = 271,
     TYRAN_TOKEN_TRUE = 272,
     TYRAN_TOKEN_FALSE = 273,
     WHILE = 274,
     INDEX_SOAK = 275,
     OUTDENT = 276,
     RETURN = 277,
     INDEX_END = 278,
     RELATION = 279,
     CALL_END = 280,
     MATH = 281,
     WHEN = 282,
     FOR = 283,
     SUPER = 284,
     LOGIC = 285,
     POST_IF = 286,
     FORIN = 287,
     STRING = 288,
     NUMBER = 289,
     BY = 290,
     IF = 291,
     LEADING_WHEN = 292,
     PARAM_START = 293,
     UNTIL = 294,
     OWN = 295,
     STATEMENT = 296,
     COMPOUND_MULTIPLY = 297,
     COMPOUND_DIVIDE = 298,
     COMPOUND_ADD = 299,
     COMPOUND_SUBTRACT = 300,
     COMPOUND_MODULUS = 301,
     ADD = 302,
     SUBTRACT = 303,
     MULTIPLY = 304,
     DIVIDE = 305,
     MEMBER = 306,
     SOAK_MEMBER = 307,
     SCOPING = 308,
     INCREMENT = 309,
     DECREMENT = 310,
     EQUAL = 311,
     COLON = 312,
     COMMA = 313,
     MEMBER_SOAK = 314,
     _CLASS = 315,
     FUNCTION_GLYPH = 316,
     FUNCTION_GLYPH_BOUND = 317,
     SELF = 318,
     QUESTION_MARK = 319,
     OBJECT_START = 320,
     OBJECT_END = 321,
     RANGE_INCLUSIVE = 322,
     RANGE_EXCLUSIVE = 323,
     BRACKET_LEFT = 324,
     BRACKET_RIGHT = 325,
     PARENTHESES_LEFT = 326,
     PARENTHESES_RIGHT = 327,
     MODULUS = 328,
     NOT = 329,
     EXTENDS = 330,
     CLASS = 331,
     LOOP = 332,
     ELSE = 333
   };
#endif
/* Tokens.  */
#define COMMENT 258
#define UNARY 259
#define COMPARE 260
#define FOROF 261
#define IDENTIFIER 262
#define TERMINATOR 263
#define INDEX_START 264
#define SHIFT 265
#define INDENT 266
#define SWITCH 267
#define PARAM_END 268
#define TYRAN_TOKEN_NULL 269
#define CALL_START 270
#define UNDEFINED 271
#define TYRAN_TOKEN_TRUE 272
#define TYRAN_TOKEN_FALSE 273
#define WHILE 274
#define INDEX_SOAK 275
#define OUTDENT 276
#define RETURN 277
#define INDEX_END 278
#define RELATION 279
#define CALL_END 280
#define MATH 281
#define WHEN 282
#define FOR 283
#define SUPER 284
#define LOGIC 285
#define POST_IF 286
#define FORIN 287
#define STRING 288
#define NUMBER 289
#define BY 290
#define IF 291
#define LEADING_WHEN 292
#define PARAM_START 293
#define UNTIL 294
#define OWN 295
#define STATEMENT 296
#define COMPOUND_MULTIPLY 297
#define COMPOUND_DIVIDE 298
#define COMPOUND_ADD 299
#define COMPOUND_SUBTRACT 300
#define COMPOUND_MODULUS 301
#define ADD 302
#define SUBTRACT 303
#define MULTIPLY 304
#define DIVIDE 305
#define MEMBER 306
#define SOAK_MEMBER 307
#define SCOPING 308
#define INCREMENT 309
#define DECREMENT 310
#define EQUAL 311
#define COLON 312
#define COMMA 313
#define MEMBER_SOAK 314
#define _CLASS 315
#define FUNCTION_GLYPH 316
#define FUNCTION_GLYPH_BOUND 317
#define SELF 318
#define QUESTION_MARK 319
#define OBJECT_START 320
#define OBJECT_END 321
#define RANGE_INCLUSIVE 322
#define RANGE_EXCLUSIVE 323
#define BRACKET_LEFT 324
#define BRACKET_RIGHT 325
#define PARENTHESES_LEFT 326
#define PARENTHESES_RIGHT 327
#define MODULUS 328
#define NOT 329
#define EXTENDS 330
#define CLASS 331
#define LOOP 332
#define ELSE 333




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif



#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
} YYLTYPE;
# define yyltype YYLTYPE /* obsolescent; will be withdrawn */
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif


