/* A Bison parser, made by GNU Bison 2.6.  */

/* Bison interface for Yacc-like parsers in C
   
      Copyright (C) 1984, 1989-1990, 2000-2012 Free Software Foundation, Inc.
   
   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

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

#ifndef TYRAN_PARSER_TYRAN_SCRIPT_PARSER_TAB_H
# define TYRAN_PARSER_TYRAN_SCRIPT_PARSER_TAB_H
/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif
#if YYDEBUG
extern int TYRAN_PARSER_debug;
#endif

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
     COMPOUND_ASSIGNMENT = 297,
     ADD = 298,
     SUBTRACT = 299,
     MULTIPLY = 300,
     DIVIDE = 301,
     MEMBER = 302,
     SOAK_MEMBER = 303,
     SCOPING = 304,
     INCREMENT = 305,
     DECREMENT = 306,
     EQUAL = 307,
     COLON = 308,
     COMMA = 309,
     MEMBER_SOAK = 310,
     _CLASS = 311,
     FUNCTION_GLYPH = 312,
     FUNCTION_GLYPH_BOUND = 313,
     SELF = 314,
     QUESTION_MARK = 315,
     OBJECT_START = 316,
     OBJECT_END = 317,
     RANGE_INCLUSIVE = 318,
     RANGE_EXCLUSIVE = 319,
     BRACKET_LEFT = 320,
     BRACKET_RIGHT = 321,
     PARENTHESES_LEFT = 322,
     PARENTHESES_RIGHT = 323,
     MODULUS = 324,
     NOT = 325,
     CLASS = 326,
     LOOP = 327,
     ELSE = 328,
     EXTENDS = 329
   };
#endif


#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
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


#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int TYRAN_PARSER_parse (void *YYPARSE_PARAM);
#else
int TYRAN_PARSER_parse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int TYRAN_PARSER_parse (tyran_parser* parser);
#else
int TYRAN_PARSER_parse ();
#endif
#endif /* ! YYPARSE_PARAM */

#endif /* !TYRAN_PARSER_TYRAN_SCRIPT_PARSER_TAB_H  */
