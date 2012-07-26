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
     UNDEFINED = 270,
     TYRAN_TOKEN_TRUE = 271,
     TYRAN_TOKEN_FALSE = 272,
     WHILE = 273,
     INDEX_SOAK = 274,
     OUTDENT = 275,
     RETURN = 276,
     INDEX_END = 277,
     RELATION = 278,
     MATH = 279,
     WHEN = 280,
     FOR = 281,
     SUPER = 282,
     LOGIC = 283,
     POST_IF = 284,
     FORIN = 285,
     STRING = 286,
     NUMBER = 287,
     BY = 288,
     IF = 289,
     LEADING_WHEN = 290,
     PARAM_START = 291,
     UNTIL = 292,
     OWN = 293,
     STATEMENT = 294,
     COMPOUND_MULTIPLY = 295,
     COMPOUND_DIVIDE = 296,
     COMPOUND_ADD = 297,
     COMPOUND_SUBTRACT = 298,
     COMPOUND_MODULUS = 299,
     ADD = 300,
     SUBTRACT = 301,
     MULTIPLY = 302,
     DIVIDE = 303,
     MEMBER = 304,
     SOAK_MEMBER = 305,
     SCOPING = 306,
     INCREMENT = 307,
     DECREMENT = 308,
     EQUAL = 309,
     COLON = 310,
     COMMA = 311,
     MEMBER_SOAK = 312,
     _CLASS = 313,
     FUNCTION_GLYPH = 314,
     FUNCTION_GLYPH_BOUND = 315,
     SELF = 316,
     QUESTION_MARK = 317,
     OBJECT_START = 318,
     OBJECT_END = 319,
     RANGE_INCLUSIVE = 320,
     RANGE_EXCLUSIVE = 321,
     BRACKET_LEFT = 322,
     BRACKET_RIGHT = 323,
     PARENTHESES_LEFT = 324,
     PARENTHESES_RIGHT = 325,
     MODULUS = 326,
     NOT = 327,
     EXTENDS = 328,
     CLASS = 329,
     LOOP = 330,
     ELSE = 331
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
#define UNDEFINED 270
#define TYRAN_TOKEN_TRUE 271
#define TYRAN_TOKEN_FALSE 272
#define WHILE 273
#define INDEX_SOAK 274
#define OUTDENT 275
#define RETURN 276
#define INDEX_END 277
#define RELATION 278
#define MATH 279
#define WHEN 280
#define FOR 281
#define SUPER 282
#define LOGIC 283
#define POST_IF 284
#define FORIN 285
#define STRING 286
#define NUMBER 287
#define BY 288
#define IF 289
#define LEADING_WHEN 290
#define PARAM_START 291
#define UNTIL 292
#define OWN 293
#define STATEMENT 294
#define COMPOUND_MULTIPLY 295
#define COMPOUND_DIVIDE 296
#define COMPOUND_ADD 297
#define COMPOUND_SUBTRACT 298
#define COMPOUND_MODULUS 299
#define ADD 300
#define SUBTRACT 301
#define MULTIPLY 302
#define DIVIDE 303
#define MEMBER 304
#define SOAK_MEMBER 305
#define SCOPING 306
#define INCREMENT 307
#define DECREMENT 308
#define EQUAL 309
#define COLON 310
#define COMMA 311
#define MEMBER_SOAK 312
#define _CLASS 313
#define FUNCTION_GLYPH 314
#define FUNCTION_GLYPH_BOUND 315
#define SELF 316
#define QUESTION_MARK 317
#define OBJECT_START 318
#define OBJECT_END 319
#define RANGE_INCLUSIVE 320
#define RANGE_EXCLUSIVE 321
#define BRACKET_LEFT 322
#define BRACKET_RIGHT 323
#define PARENTHESES_LEFT 324
#define PARENTHESES_RIGHT 325
#define MODULUS 326
#define NOT 327
#define EXTENDS 328
#define CLASS 329
#define LOOP 330
#define ELSE 331




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


