/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "2.3"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 1

/* Using locations.  */
#define YYLSP_NEEDED 1

/* Substitute the variable and function names.  */
#define yyparse TYRAN_PARSER_parse
#define yylex   TYRAN_PARSER_lex
#define yyerror TYRAN_PARSER_error
#define yylval  TYRAN_PARSER_lval
#define yychar  TYRAN_PARSER_char
#define yydebug TYRAN_PARSER_debug
#define yynerrs TYRAN_PARSER_nerrs
#define yylloc TYRAN_PARSER_lloc

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
     CLASS = 330,
     LOOP = 331,
     ELSE = 332,
     EXTENDS = 333
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
#define CLASS 330
#define LOOP 331
#define ELSE 332
#define EXTENDS 333




/* Copy the first part of user declarations.  */
#line 1 "tyran_script_parser.y"

	#include <tyranscript/parser/mocha/tyran_parser.h>	


/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 1
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif

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


/* Copy the second part of user declarations.  */


/* Line 216 of yacc.c.  */
#line 286 "tyran_script_parser.tab.c"

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int i)
#else
static int
YYID (i)
    int i;
#endif
{
  return i;
}
#endif

#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef _STDLIB_H
#      define _STDLIB_H 1
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined _STDLIB_H \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef _STDLIB_H
#    define _STDLIB_H 1
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
	 || (defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL \
	     && defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss;
  YYSTYPE yyvs;
    YYLTYPE yyls;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE) + sizeof (YYLTYPE)) \
      + 2 * YYSTACK_GAP_MAXIMUM)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack)					\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack, Stack, yysize);				\
	Stack = &yyptr->Stack;						\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  97
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   837

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  80
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  50
/* YYNRULES -- Number of rules.  */
#define YYNRULES  148
/* YYNRULES -- Number of states.  */
#define YYNSTATES  246

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   334

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     5,     7,    11,    14,    16,    18,    20,
      22,    24,    26,    28,    30,    32,    34,    36,    38,    40,
      43,    47,    49,    51,    53,    55,    57,    59,    61,    63,
      67,    72,    78,    80,    84,    90,    92,    94,    96,    98,
     101,   103,   105,   111,   114,   116,   118,   120,   122,   126,
     130,   135,   137,   140,   144,   146,   148,   150,   152,   155,
     157,   160,   163,   165,   167,   169,   171,   173,   175,   177,
     179,   182,   185,   188,   190,   194,   197,   199,   201,   205,
     207,   209,   213,   217,   222,   225,   229,   234,   240,   244,
     248,   250,   253,   256,   260,   262,   265,   268,   272,   274,
     276,   282,   286,   289,   292,   294,   296,   300,   304,   308,
     313,   315,   317,   319,   323,   327,   333,   336,   339,   345,
     353,   358,   365,   367,   370,   374,   379,   383,   389,   391,
     395,   399,   403,   406,   409,   412,   415,   418,   421,   424,
     428,   432,   436,   440,   444,   448,   452,   456,   460
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int16 yyrhs[] =
{
      81,     0,    -1,    82,    -1,    83,    -1,    82,     8,    83,
      -1,    82,     8,    -1,    85,    -1,    84,    -1,    93,    -1,
      94,    -1,   103,    -1,   110,    -1,    95,    -1,   129,    -1,
      90,    -1,   128,    -1,   123,    -1,   124,    -1,   109,    -1,
      11,    21,    -1,    11,    82,    21,    -1,     7,    -1,    34,
      -1,    33,    -1,    88,    -1,    16,    -1,    14,    -1,    17,
      -1,    18,    -1,   102,    56,    85,    -1,   102,    56,     8,
      85,    -1,   102,    56,    11,    85,    21,    -1,    92,    -1,
      92,    57,    85,    -1,    92,    57,    11,    85,    21,    -1,
      94,    -1,    87,    -1,    88,    -1,   113,    -1,    22,    85,
      -1,    22,    -1,     3,    -1,    38,    97,    13,    96,    86,
      -1,    96,    86,    -1,    61,    -1,    62,    -1,    58,    -1,
      98,    -1,    97,    58,    98,    -1,    97,     8,    98,    -1,
      97,    11,    97,    21,    -1,    99,    -1,    99,    68,    -1,
      99,    56,    85,    -1,    87,    -1,   113,    -1,   114,    -1,
     107,    -1,    85,    68,    -1,    87,    -1,   103,   104,    -1,
     110,   104,    -1,   113,    -1,   101,    -1,   114,    -1,   107,
      -1,   102,    -1,    89,    -1,   121,    -1,   116,    -1,    51,
      87,    -1,    59,    87,    -1,    53,    87,    -1,   105,    -1,
       9,   106,    23,    -1,    20,   105,    -1,    85,    -1,   117,
      -1,    65,   108,    66,    -1,    58,    -1,    91,    -1,   108,
      58,    91,    -1,   108,     8,    91,    -1,   108,    11,   108,
      21,    -1,    60,   101,    -1,    60,   101,    86,    -1,    60,
     101,    79,    85,    -1,    60,   101,    79,    85,    86,    -1,
     103,     7,   111,    -1,   110,     7,   111,    -1,    29,    -1,
      29,   111,    -1,    15,    25,    -1,    15,   118,    25,    -1,
      63,    -1,   112,    87,    -1,    69,    70,    -1,    69,   118,
      70,    -1,    67,    -1,    68,    -1,    69,    85,   115,    85,
      70,    -1,    85,   115,    85,    -1,    85,   115,    -1,   115,
      85,    -1,   115,    -1,   119,    -1,   118,    58,   119,    -1,
     118,     8,   119,    -1,    11,   118,    21,    -1,   118,    11,
     118,    21,    -1,    85,    -1,   100,    -1,    85,    -1,   120,
      58,    85,    -1,    71,    82,    72,    -1,    71,    11,    82,
      21,    72,    -1,    19,    85,    -1,   122,    86,    -1,    12,
      85,    11,   125,    21,    -1,    12,    85,    11,   125,    77,
      86,    21,    -1,    12,    11,   125,    21,    -1,    12,    11,
     125,    77,    86,    21,    -1,   126,    -1,   125,   126,    -1,
      37,   120,    86,    -1,    37,   120,    86,     8,    -1,    36,
      85,    86,    -1,   127,    77,    36,    85,    86,    -1,   127,
      -1,   127,    77,    86,    -1,    84,    31,    85,    -1,    85,
      31,    85,    -1,    47,    85,    -1,    48,    85,    -1,    55,
     101,    -1,    54,   101,    -1,   101,    55,    -1,   101,    54,
      -1,    85,    64,    -1,    85,    47,    85,    -1,    85,    48,
      85,    -1,    85,    49,    85,    -1,    85,    50,    85,    -1,
     101,    44,    85,    -1,   101,    43,    85,    -1,   101,    42,
      85,    -1,   101,    45,    85,    -1,   101,    46,    85,    -1,
     101,    78,    85,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   106,   106,   109,   110,   111,   114,   115,   118,   119,
     122,   123,   124,   125,   126,   127,   128,   129,   130,   133,
     134,   137,   140,   141,   144,   145,   146,   147,   148,   151,
     152,   153,   156,   157,   158,   159,   162,   163,   164,   167,
     168,   171,   174,   175,   178,   179,   183,   184,   185,   186,
     187,   190,   191,   192,   195,   196,   197,   198,   201,   204,
     205,   206,   207,   211,   212,   213,   216,   217,   218,   219,
     222,   223,   224,   225,   228,   229,   232,   233,   236,   239,
     240,   241,   242,   243,   246,   247,   248,   249,   252,   253,
     254,   255,   258,   259,   262,   265,   268,   269,   272,   273,
     276,   279,   280,   281,   282,   285,   286,   287,   288,   289,
     292,   293,   296,   297,   300,   301,   304,   307,   311,   312,
     313,   314,   317,   318,   321,   322,   325,   326,   329,   330,
     331,   332,   335,   336,   337,   338,   339,   340,   341,   342,
     343,   344,   345,   346,   347,   348,   349,   350,   351
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "COMMENT", "UNARY", "COMPARE", "FOROF",
  "IDENTIFIER", "TERMINATOR", "INDEX_START", "SHIFT", "INDENT", "SWITCH",
  "PARAM_END", "TYRAN_TOKEN_NULL", "CALL_START", "UNDEFINED",
  "TYRAN_TOKEN_TRUE", "TYRAN_TOKEN_FALSE", "WHILE", "INDEX_SOAK",
  "OUTDENT", "RETURN", "INDEX_END", "RELATION", "CALL_END", "MATH", "WHEN",
  "FOR", "SUPER", "LOGIC", "POST_IF", "FORIN", "STRING", "NUMBER", "BY",
  "IF", "LEADING_WHEN", "PARAM_START", "UNTIL", "OWN", "STATEMENT",
  "COMPOUND_MULTIPLY", "COMPOUND_DIVIDE", "COMPOUND_ADD",
  "COMPOUND_SUBTRACT", "COMPOUND_MODULUS", "ADD", "SUBTRACT", "MULTIPLY",
  "DIVIDE", "MEMBER", "SOAK_MEMBER", "SCOPING", "INCREMENT", "DECREMENT",
  "EQUAL", "COLON", "COMMA", "MEMBER_SOAK", "_CLASS", "FUNCTION_GLYPH",
  "FUNCTION_GLYPH_BOUND", "SELF", "QUESTION_MARK", "OBJECT_START",
  "OBJECT_END", "RANGE_INCLUSIVE", "RANGE_EXCLUSIVE", "BRACKET_LEFT",
  "BRACKET_RIGHT", "PARENTHESES_LEFT", "PARENTHESES_RIGHT", "MODULUS",
  "NOT", "CLASS", "LOOP", "ELSE", "EXTENDS", "\"extends\"", "$accept",
  "root", "body", "line", "statement", "expression", "block", "identifier",
  "alpha_numeric", "literal", "assignment", "object_assignment",
  "object_assignable", "return", "comment", "code", "function_glyph",
  "parameter_list", "parameter", "parameter_variable", "splat",
  "basic_assignable", "assignable", "value", "accessor", "index",
  "index_value", "object", "assign_list", "class", "invocation",
  "arguments", "self", "self_member", "array", "range_dots", "range",
  "slice", "argument_list", "argument", "basic_arguments", "parenthetical",
  "while_condition", "while", "switch", "whens", "when", "if_block", "if",
  "operation", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,   320,   321,   322,   323,   324,
     325,   326,   327,   328,   329,   330,   331,   332,   333,   334
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    80,    81,    82,    82,    82,    83,    83,    84,    84,
      85,    85,    85,    85,    85,    85,    85,    85,    85,    86,
      86,    87,    88,    88,    89,    89,    89,    89,    89,    90,
      90,    90,    91,    91,    91,    91,    92,    92,    92,    93,
      93,    94,    95,    95,    96,    96,    97,    97,    97,    97,
      97,    98,    98,    98,    99,    99,    99,    99,   100,   101,
     101,   101,   101,   102,   102,   102,   103,   103,   103,   103,
     104,   104,   104,   104,   105,   105,   106,   106,   107,   108,
     108,   108,   108,   108,   109,   109,   109,   109,   110,   110,
     110,   110,   111,   111,   112,   113,   114,   114,   115,   115,
     116,   117,   117,   117,   117,   118,   118,   118,   118,   118,
     119,   119,   120,   120,   121,   121,   122,   123,   124,   124,
     124,   124,   125,   125,   126,   126,   127,   127,   128,   128,
     128,   128,   129,   129,   129,   129,   129,   129,   129,   129,
     129,   129,   129,   129,   129,   129,   129,   129,   129
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     1,     3,     2,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     2,
       3,     1,     1,     1,     1,     1,     1,     1,     1,     3,
       4,     5,     1,     3,     5,     1,     1,     1,     1,     2,
       1,     1,     5,     2,     1,     1,     1,     1,     3,     3,
       4,     1,     2,     3,     1,     1,     1,     1,     2,     1,
       2,     2,     1,     1,     1,     1,     1,     1,     1,     1,
       2,     2,     2,     1,     3,     2,     1,     1,     3,     1,
       1,     3,     3,     4,     2,     3,     4,     5,     3,     3,
       1,     2,     2,     3,     1,     2,     2,     3,     1,     1,
       5,     3,     2,     2,     1,     1,     3,     3,     3,     4,
       1,     1,     1,     3,     3,     5,     2,     2,     5,     7,
       4,     6,     1,     2,     3,     4,     3,     5,     1,     3,
       3,     3,     2,     2,     2,     2,     2,     2,     2,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,    41,    21,     0,    26,    25,    27,    28,     0,    40,
      90,    23,    22,     0,     0,     0,     0,     0,     0,     0,
      44,    45,    94,     0,     0,     0,     0,     2,     3,     7,
       6,    59,    24,    67,    14,     8,     9,    12,     0,    63,
      66,    10,    65,    18,    11,     0,    62,    64,    69,    68,
       0,    16,    17,   128,    15,    13,     0,     0,     0,   116,
      39,     0,    91,     0,    46,     0,    54,     0,    47,    51,
      57,    55,    56,   132,   133,   135,    66,     0,     0,   134,
      84,    79,    36,    37,    80,    32,    35,     0,    38,     0,
      96,   110,   111,     0,   105,     0,     0,     1,     5,     0,
       0,     0,     0,     0,     0,   138,     0,    43,     0,     0,
       0,     0,     0,   137,   136,     0,     0,     0,     0,     0,
       0,     0,     0,    60,    73,     0,    61,    95,   117,     0,
       0,     0,   122,     0,    92,   110,     0,   126,     0,     0,
       0,     0,     0,    52,     0,    85,     0,     0,     0,     0,
      78,     0,    98,    99,     0,     0,     0,     0,    97,     0,
     114,     4,   130,   131,   139,   140,   141,   142,    19,     0,
     145,   144,   143,   146,   147,   148,     0,     0,    29,    88,
      99,    76,     0,   104,    77,    75,    70,    72,    71,    89,
       0,   129,   112,     0,   120,     0,   123,     0,    58,    93,
      49,     0,     0,    48,    53,    86,     0,    33,    82,     0,
      81,   108,     0,   107,     0,   106,     0,    20,    30,     0,
     102,    74,   103,     0,     0,   124,     0,   118,     0,    50,
      42,    87,     0,    83,   100,   109,   115,    31,   101,   127,
     113,   125,   121,     0,    34,   119
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    26,    27,    28,    57,   135,   107,    31,    32,    33,
      34,    84,    85,    35,    36,    37,    38,    67,    68,    69,
      92,    39,    40,    41,   123,   124,   182,    42,    87,    43,
      44,    62,    45,    46,    47,   154,    48,   184,    93,    94,
     193,    49,    50,    51,    52,   131,   132,    53,    54,    55
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -121
static const yytype_int16 yypact[] =
{
     740,  -121,  -121,   435,  -121,  -121,  -121,  -121,   740,   740,
      30,  -121,  -121,   740,   122,   740,   740,   763,   763,   763,
    -121,  -121,  -121,   209,   185,   496,    39,    38,  -121,    45,
     718,  -121,  -121,  -121,  -121,  -121,  -121,  -121,    55,   127,
      61,   283,  -121,  -121,   334,    84,  -121,  -121,  -121,  -121,
      55,  -121,  -121,    37,  -121,  -121,    87,    45,     3,   718,
     161,   246,  -121,    24,  -121,   185,  -121,    36,  -121,   -39,
    -121,  -121,  -121,   187,   187,   344,  -121,   283,   334,   344,
      11,  -121,  -121,  -121,  -121,    88,  -121,   219,  -121,   557,
    -121,   535,  -121,    49,  -121,   740,    -4,  -121,   740,   740,
     740,   740,   740,   740,   740,  -121,   618,  -121,   740,   740,
     740,   740,   740,  -121,  -121,   740,   311,    30,   372,   180,
      84,    84,    84,  -121,  -121,    30,  -121,  -121,  -121,    22,
     740,     5,  -121,    87,  -121,   657,    29,  -121,    58,   122,
     173,    58,   740,  -121,   740,  -121,   679,   263,   209,   263,
    -121,   220,  -121,   218,   740,   740,   557,   740,  -121,    40,
    -121,  -121,   718,   718,   187,   187,    28,   718,  -121,    48,
     161,   161,   161,   161,   161,   161,   740,   740,   161,  -121,
    -121,   596,   114,   740,  -121,  -121,  -121,  -121,  -121,  -121,
     740,  -121,   718,     1,  -121,    55,  -121,     6,  -121,  -121,
    -121,   349,    55,  -121,   718,    24,   740,   718,  -121,   401,
    -121,  -121,   767,  -121,   403,  -121,    96,  -121,   718,   427,
     740,  -121,   718,    24,   740,   152,   153,  -121,    55,  -121,
    -121,  -121,   488,  -121,  -121,  -121,  -121,  -121,   718,  -121,
     718,  -121,  -121,   177,  -121,  -121
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -121,  -121,   -20,   115,    80,     0,   -44,    18,   -16,  -121,
    -121,   -27,  -121,  -121,    15,  -121,    75,    78,   -45,  -121,
    -121,   176,   320,   350,    35,   103,  -121,     9,    90,  -121,
     381,   -36,  -121,   -13,    14,   -97,  -121,  -121,   -59,   -14,
    -121,  -121,  -121,  -121,  -121,   111,  -120,  -121,  -121,  -121
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -64
static const yytype_int16 yytable[] =
{
      30,    71,   136,    58,    98,    96,   128,    83,    59,    60,
      88,   196,   106,    63,   133,    73,    74,   142,   -63,   137,
     -63,   183,   106,    70,    91,    30,   194,   227,    72,   143,
     151,   -63,    66,   106,   100,   106,   145,   155,    86,    97,
     156,    82,   130,   130,   138,    61,    98,   139,    98,   140,
     101,   102,   103,   104,   199,   100,    98,   155,   190,   224,
     156,   216,   -63,   127,   -63,     2,   106,   105,   160,   217,
     -63,   101,   102,   103,   104,   159,    99,   196,   104,   126,
      29,   179,   195,   228,   220,   191,   169,   157,   105,   189,
     144,     2,   105,   200,   141,    30,   203,   214,    30,   162,
     163,   164,   165,   166,   167,    29,    30,   157,   170,   171,
     172,   173,   174,   126,   129,   175,   178,   116,   181,   158,
     208,    22,   210,    23,   130,    71,    71,    65,    71,     2,
     192,    83,    83,    83,    88,    88,    88,   221,   186,   187,
     188,   213,   204,   215,   205,   146,   207,    70,    70,   225,
      70,   226,    72,    72,   212,    72,    66,    66,   230,    66,
     241,   231,    86,    86,    86,    82,    82,    82,   236,   108,
     109,   110,   111,   112,   242,    29,   218,   219,    29,   239,
      64,   113,   114,   222,   243,    22,    29,    23,     1,   118,
     223,    65,     2,    75,    79,    80,    89,     3,   245,     4,
     119,     5,     6,     7,     8,   115,   232,     9,   101,   102,
     103,   104,     1,   161,    10,   202,     2,   201,    11,    12,
     238,    13,   185,    14,   240,   105,   -58,   147,   155,   -58,
     148,   156,    15,    16,    20,    21,   103,   104,   209,    17,
      18,   211,    11,    12,   197,    19,    20,    21,    22,     1,
      23,   105,     0,     2,    24,    90,    25,    89,     3,     0,
       4,     0,     5,     6,     7,     8,     1,    81,     9,     0,
       2,   134,    22,     0,     0,    10,   -58,   149,   157,    11,
      12,     0,    13,     0,    14,   150,     0,     0,   -58,     0,
     117,     0,   118,    15,    16,     0,    11,    12,     0,     0,
      17,    18,     0,   119,     0,     0,    19,    20,    21,    22,
       0,    23,     0,     0,     1,    24,     0,    25,     2,   176,
       0,     0,   177,     3,     0,     4,    22,     5,     6,     7,
       8,     0,     0,     9,   120,     0,   121,    76,    76,    76,
      10,   125,   122,   118,    11,    12,     0,    13,     0,    14,
       0,   -63,     0,   -63,   119,     0,     0,   138,    15,    16,
     139,     0,     0,     0,   -63,    17,    18,    77,    77,    77,
     229,    19,    20,    21,    22,     1,    23,     0,     0,     2,
      24,     0,    25,     0,     3,   120,     4,   121,     5,     6,
       7,     8,     0,   122,     9,   -63,     0,   -63,    78,    78,
      78,    10,     0,   -63,     0,    11,    12,   141,    13,   147,
      14,   155,   148,     0,   156,     0,     0,     0,     0,    15,
      16,     0,   233,     0,   235,     0,    17,    18,     0,     0,
       0,     0,    19,    20,    21,    22,     0,    23,     1,   152,
     180,    24,     2,    25,     0,     0,    56,     3,   237,     4,
       0,     5,     6,     7,     8,     0,     0,     9,   100,   149,
       0,   157,     0,     0,    10,     0,     0,     0,    11,    12,
       0,    13,     0,    14,   101,   102,   103,   104,     0,     0,
       0,     0,    15,    16,     0,     0,     0,     0,     0,    17,
      18,   105,     0,     0,     0,    19,    20,    21,    22,     1,
      23,     0,     0,     2,    24,     0,    25,    95,     3,   244,
       4,     0,     5,     6,     7,     8,     0,     0,     9,   100,
       0,     0,     0,     0,     0,    10,     0,     0,     0,    11,
      12,     0,    13,     0,    14,   101,   102,   103,   104,     0,
       0,     0,     0,    15,    16,     0,     0,     0,     0,     0,
      17,    18,   105,     0,     0,     0,    19,    20,    21,    22,
       1,    23,     0,     0,     2,    24,   100,    25,    89,     3,
       0,     4,     0,     5,     6,     7,     8,     0,     0,     9,
       0,     0,   101,   102,   103,   104,    10,     0,     0,     0,
      11,    12,     0,    13,     0,    14,     0,     0,     0,   105,
       0,     0,   152,   153,    15,    16,     0,     0,     0,     0,
       0,    17,    18,     0,     0,     0,     0,    19,    20,    21,
      22,     1,    23,     0,     0,     2,    24,   100,    25,     0,
       3,     0,     4,     0,     5,     6,     7,     8,     0,   168,
       9,     0,     0,   101,   102,   103,   104,    10,     0,     0,
       0,    11,    12,     0,    13,     0,    14,     0,     0,     0,
     105,     0,     0,   152,   180,    15,    16,     0,     0,     0,
       0,     0,    17,    18,     0,     0,     0,     0,    19,    20,
      21,    22,     1,    23,     0,     0,     2,    24,   100,    25,
     206,     3,     0,     4,     0,     5,     6,     7,     8,     0,
       0,     9,     0,     0,   101,   102,   103,   104,    10,     0,
       0,     0,    11,    12,     0,    13,     0,    14,     0,     0,
       0,   105,     0,     0,     0,   198,    15,    16,     0,     0,
       0,     0,     0,    17,    18,     0,     0,     0,     0,    19,
      20,    21,    22,     1,    23,     0,     0,     2,    24,   100,
      25,     0,     3,     0,     4,     0,     5,     6,     7,     8,
       0,     0,     9,     0,     0,   101,   102,   103,   104,    10,
       2,     0,     0,    11,    12,     0,    13,     4,    14,     5,
       6,     7,   105,     0,     0,     0,     0,    15,    16,     0,
       0,     0,    10,     0,    17,    18,    11,    12,   100,     0,
      19,    20,    21,    22,     0,    23,     0,     0,     0,    24,
       0,    25,     0,     0,   101,   102,   103,   104,     0,     0,
       0,     0,     0,     0,     0,     0,    22,     0,    23,     0,
       0,   105,    24,     0,    25,     0,     0,   234
};

static const yytype_int16 yycheck[] =
{
       0,    14,    61,     3,     8,    25,    50,    23,     8,     9,
      23,   131,    11,    13,    11,    15,    16,    56,     7,    63,
       9,   118,    11,    14,    24,    25,    21,    21,    14,    68,
      89,    20,    14,    11,    31,    11,    80,     8,    23,     0,
      11,    23,    37,    37,     8,    15,     8,    11,     8,    13,
      47,    48,    49,    50,    25,    31,     8,     8,    36,    58,
      11,    21,    51,    45,    53,     7,    11,    64,    72,    21,
      59,    47,    48,    49,    50,    95,    31,   197,    50,    44,
       0,   117,    77,    77,   181,   129,   106,    58,    64,   125,
      79,     7,    64,   138,    58,    95,   141,   156,    98,    99,
     100,   101,   102,   103,   104,    25,   106,    58,   108,   109,
     110,   111,   112,    78,    77,   115,   116,    56,   118,    70,
     147,    63,   149,    65,    37,   138,   139,    69,   141,     7,
     130,   147,   148,   149,   147,   148,   149,    23,   120,   121,
     122,   155,   142,   157,   144,    57,   146,   138,   139,   193,
     141,   195,   138,   139,   154,   141,   138,   139,   202,   141,
       8,   205,   147,   148,   149,   147,   148,   149,    72,    42,
      43,    44,    45,    46,    21,    95,   176,   177,    98,   223,
      58,    54,    55,   183,   228,    63,   106,    65,     3,     9,
     190,    69,     7,    17,    18,    19,    11,    12,    21,    14,
      20,    16,    17,    18,    19,    78,   206,    22,    47,    48,
      49,    50,     3,    98,    29,   140,     7,   139,    33,    34,
     220,    36,   119,    38,   224,    64,     8,     8,     8,    11,
      11,    11,    47,    48,    61,    62,    49,    50,   148,    54,
      55,    21,    33,    34,   133,    60,    61,    62,    63,     3,
      65,    64,    -1,     7,    69,    70,    71,    11,    12,    -1,
      14,    -1,    16,    17,    18,    19,     3,    58,    22,    -1,
       7,    25,    63,    -1,    -1,    29,    58,    58,    58,    33,
      34,    -1,    36,    -1,    38,    66,    -1,    -1,    70,    -1,
       7,    -1,     9,    47,    48,    -1,    33,    34,    -1,    -1,
      54,    55,    -1,    20,    -1,    -1,    60,    61,    62,    63,
      -1,    65,    -1,    -1,     3,    69,    -1,    71,     7,     8,
      -1,    -1,    11,    12,    -1,    14,    63,    16,    17,    18,
      19,    -1,    -1,    22,    51,    -1,    53,    17,    18,    19,
      29,     7,    59,     9,    33,    34,    -1,    36,    -1,    38,
      -1,     7,    -1,     9,    20,    -1,    -1,     8,    47,    48,
      11,    -1,    -1,    -1,    20,    54,    55,    17,    18,    19,
      21,    60,    61,    62,    63,     3,    65,    -1,    -1,     7,
      69,    -1,    71,    -1,    12,    51,    14,    53,    16,    17,
      18,    19,    -1,    59,    22,    51,    -1,    53,    17,    18,
      19,    29,    -1,    59,    -1,    33,    34,    58,    36,     8,
      38,     8,    11,    -1,    11,    -1,    -1,    -1,    -1,    47,
      48,    -1,    21,    -1,    21,    -1,    54,    55,    -1,    -1,
      -1,    -1,    60,    61,    62,    63,    -1,    65,     3,    67,
      68,    69,     7,    71,    -1,    -1,    11,    12,    21,    14,
      -1,    16,    17,    18,    19,    -1,    -1,    22,    31,    58,
      -1,    58,    -1,    -1,    29,    -1,    -1,    -1,    33,    34,
      -1,    36,    -1,    38,    47,    48,    49,    50,    -1,    -1,
      -1,    -1,    47,    48,    -1,    -1,    -1,    -1,    -1,    54,
      55,    64,    -1,    -1,    -1,    60,    61,    62,    63,     3,
      65,    -1,    -1,     7,    69,    -1,    71,    11,    12,    21,
      14,    -1,    16,    17,    18,    19,    -1,    -1,    22,    31,
      -1,    -1,    -1,    -1,    -1,    29,    -1,    -1,    -1,    33,
      34,    -1,    36,    -1,    38,    47,    48,    49,    50,    -1,
      -1,    -1,    -1,    47,    48,    -1,    -1,    -1,    -1,    -1,
      54,    55,    64,    -1,    -1,    -1,    60,    61,    62,    63,
       3,    65,    -1,    -1,     7,    69,    31,    71,    11,    12,
      -1,    14,    -1,    16,    17,    18,    19,    -1,    -1,    22,
      -1,    -1,    47,    48,    49,    50,    29,    -1,    -1,    -1,
      33,    34,    -1,    36,    -1,    38,    -1,    -1,    -1,    64,
      -1,    -1,    67,    68,    47,    48,    -1,    -1,    -1,    -1,
      -1,    54,    55,    -1,    -1,    -1,    -1,    60,    61,    62,
      63,     3,    65,    -1,    -1,     7,    69,    31,    71,    -1,
      12,    -1,    14,    -1,    16,    17,    18,    19,    -1,    21,
      22,    -1,    -1,    47,    48,    49,    50,    29,    -1,    -1,
      -1,    33,    34,    -1,    36,    -1,    38,    -1,    -1,    -1,
      64,    -1,    -1,    67,    68,    47,    48,    -1,    -1,    -1,
      -1,    -1,    54,    55,    -1,    -1,    -1,    -1,    60,    61,
      62,    63,     3,    65,    -1,    -1,     7,    69,    31,    71,
      11,    12,    -1,    14,    -1,    16,    17,    18,    19,    -1,
      -1,    22,    -1,    -1,    47,    48,    49,    50,    29,    -1,
      -1,    -1,    33,    34,    -1,    36,    -1,    38,    -1,    -1,
      -1,    64,    -1,    -1,    -1,    68,    47,    48,    -1,    -1,
      -1,    -1,    -1,    54,    55,    -1,    -1,    -1,    -1,    60,
      61,    62,    63,     3,    65,    -1,    -1,     7,    69,    31,
      71,    -1,    12,    -1,    14,    -1,    16,    17,    18,    19,
      -1,    -1,    22,    -1,    -1,    47,    48,    49,    50,    29,
       7,    -1,    -1,    33,    34,    -1,    36,    14,    38,    16,
      17,    18,    64,    -1,    -1,    -1,    -1,    47,    48,    -1,
      -1,    -1,    29,    -1,    54,    55,    33,    34,    31,    -1,
      60,    61,    62,    63,    -1,    65,    -1,    -1,    -1,    69,
      -1,    71,    -1,    -1,    47,    48,    49,    50,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    63,    -1,    65,    -1,
      -1,    64,    69,    -1,    71,    -1,    -1,    70
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,     7,    12,    14,    16,    17,    18,    19,    22,
      29,    33,    34,    36,    38,    47,    48,    54,    55,    60,
      61,    62,    63,    65,    69,    71,    81,    82,    83,    84,
      85,    87,    88,    89,    90,    93,    94,    95,    96,   101,
     102,   103,   107,   109,   110,   112,   113,   114,   116,   121,
     122,   123,   124,   127,   128,   129,    11,    84,    85,    85,
      85,    15,   111,    85,    58,    69,    87,    97,    98,    99,
     107,   113,   114,    85,    85,   101,   102,   103,   110,   101,
     101,    58,    87,    88,    91,    92,    94,   108,   113,    11,
      70,    85,   100,   118,   119,    11,    82,     0,     8,    31,
      31,    47,    48,    49,    50,    64,    11,    86,    42,    43,
      44,    45,    46,    54,    55,    78,    56,     7,     9,    20,
      51,    53,    59,   104,   105,     7,   104,    87,    86,    77,
      37,   125,   126,    11,    25,    85,   118,    86,     8,    11,
      13,    58,    56,    68,    79,    86,    57,     8,    11,    58,
      66,   118,    67,    68,   115,     8,    11,    58,    70,    82,
      72,    83,    85,    85,    85,    85,    85,    85,    21,    82,
      85,    85,    85,    85,    85,    85,     8,    11,    85,   111,
      68,    85,   106,   115,   117,   105,    87,    87,    87,   111,
      36,    86,    85,   120,    21,    77,   126,   125,    68,    25,
      98,    97,    96,    98,    85,    85,    11,    85,    91,   108,
      91,    21,    85,   119,   118,   119,    21,    21,    85,    85,
     115,    23,    85,    85,    58,    86,    86,    21,    77,    21,
      86,    86,    85,    21,    70,    21,    72,    21,    85,    86,
      85,     8,    21,    86,    21,    21
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */

#define YYFAIL		goto yyerrlab

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yytoken = YYTRANSLATE (yychar);				\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (&yylloc, parser, YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
#  define YY_LOCATION_PRINT(File, Loc)			\
     fprintf (File, "%d.%d-%d.%d",			\
	      (Loc).first_line, (Loc).first_column,	\
	      (Loc).last_line,  (Loc).last_column)
# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (&yylval, &yylloc, YYLEX_PARAM)
#else
# define YYLEX yylex (&yylval, &yylloc, parser)
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value, Location, parser); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp, tyran_parser* parser)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep, yylocationp, parser)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
    YYLTYPE const * const yylocationp;
    tyran_parser* parser;
#endif
{
  if (!yyvaluep)
    return;
  YYUSE (yylocationp);
  YYUSE (parser);
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp, tyran_parser* parser)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep, yylocationp, parser)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
    YYLTYPE const * const yylocationp;
    tyran_parser* parser;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  YY_LOCATION_PRINT (yyoutput, *yylocationp);
  YYFPRINTF (yyoutput, ": ");
  yy_symbol_value_print (yyoutput, yytype, yyvaluep, yylocationp, parser);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *bottom, yytype_int16 *top)
#else
static void
yy_stack_print (bottom, top)
    yytype_int16 *bottom;
    yytype_int16 *top;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; bottom <= top; ++bottom)
    YYFPRINTF (stderr, " %d", *bottom);
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, YYLTYPE *yylsp, int yyrule, tyran_parser* parser)
#else
static void
yy_reduce_print (yyvsp, yylsp, yyrule, parser)
    YYSTYPE *yyvsp;
    YYLTYPE *yylsp;
    int yyrule;
    tyran_parser* parser;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      fprintf (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       , &(yylsp[(yyi + 1) - (yynrhs)])		       , parser);
      fprintf (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, yylsp, Rule, parser); \
} while (YYID (0))

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif



#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
	switch (*++yyp)
	  {
	  case '\'':
	  case ',':
	    goto do_not_strip_quotes;

	  case '\\':
	    if (*++yyp != '\\')
	      goto do_not_strip_quotes;
	    /* Fall through.  */
	  default:
	    if (yyres)
	      yyres[yyn] = *yyp;
	    yyn++;
	    break;

	  case '"':
	    if (yyres)
	      yyres[yyn] = '\0';
	    return yyn;
	  }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into YYRESULT an error message about the unexpected token
   YYCHAR while in state YYSTATE.  Return the number of bytes copied,
   including the terminating null byte.  If YYRESULT is null, do not
   copy anything; just return the number of bytes that would be
   copied.  As a special case, return 0 if an ordinary "syntax error"
   message will do.  Return YYSIZE_MAXIMUM if overflow occurs during
   size calculation.  */
static YYSIZE_T
yysyntax_error (char *yyresult, int yystate, int yychar)
{
  int yyn = yypact[yystate];

  if (! (YYPACT_NINF < yyn && yyn <= YYLAST))
    return 0;
  else
    {
      int yytype = YYTRANSLATE (yychar);
      YYSIZE_T yysize0 = yytnamerr (0, yytname[yytype]);
      YYSIZE_T yysize = yysize0;
      YYSIZE_T yysize1;
      int yysize_overflow = 0;
      enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
      char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
      int yyx;

# if 0
      /* This is so xgettext sees the translatable formats that are
	 constructed on the fly.  */
      YY_("syntax error, unexpected %s");
      YY_("syntax error, unexpected %s, expecting %s");
      YY_("syntax error, unexpected %s, expecting %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s");
# endif
      char *yyfmt;
      char const *yyf;
      static char const yyunexpected[] = "syntax error, unexpected %s";
      static char const yyexpecting[] = ", expecting %s";
      static char const yyor[] = " or %s";
      char yyformat[sizeof yyunexpected
		    + sizeof yyexpecting - 1
		    + ((YYERROR_VERBOSE_ARGS_MAXIMUM - 2)
		       * (sizeof yyor - 1))];
      char const *yyprefix = yyexpecting;

      /* Start YYX at -YYN if negative to avoid negative indexes in
	 YYCHECK.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;

      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yycount = 1;

      yyarg[0] = yytname[yytype];
      yyfmt = yystpcpy (yyformat, yyunexpected);

      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	  {
	    if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
	      {
		yycount = 1;
		yysize = yysize0;
		yyformat[sizeof yyunexpected - 1] = '\0';
		break;
	      }
	    yyarg[yycount++] = yytname[yyx];
	    yysize1 = yysize + yytnamerr (0, yytname[yyx]);
	    yysize_overflow |= (yysize1 < yysize);
	    yysize = yysize1;
	    yyfmt = yystpcpy (yyfmt, yyprefix);
	    yyprefix = yyor;
	  }

      yyf = YY_(yyformat);
      yysize1 = yysize + yystrlen (yyf);
      yysize_overflow |= (yysize1 < yysize);
      yysize = yysize1;

      if (yysize_overflow)
	return YYSIZE_MAXIMUM;

      if (yyresult)
	{
	  /* Avoid sprintf, as that infringes on the user's name space.
	     Don't have undefined behavior even if the translation
	     produced a string with the wrong number of "%s"s.  */
	  char *yyp = yyresult;
	  int yyi = 0;
	  while ((*yyp = *yyf) != '\0')
	    {
	      if (*yyp == '%' && yyf[1] == 's' && yyi < yycount)
		{
		  yyp += yytnamerr (yyp, yyarg[yyi++]);
		  yyf += 2;
		}
	      else
		{
		  yyp++;
		  yyf++;
		}
	    }
	}
      return yysize;
    }
}
#endif /* YYERROR_VERBOSE */


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep, YYLTYPE *yylocationp, tyran_parser* parser)
#else
static void
yydestruct (yymsg, yytype, yyvaluep, yylocationp, parser)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
    YYLTYPE *yylocationp;
    tyran_parser* parser;
#endif
{
  YYUSE (yyvaluep);
  YYUSE (yylocationp);
  YYUSE (parser);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
	break;
    }
}


/* Prevent warnings from -Wmissing-prototypes.  */

#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (tyran_parser* parser);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */






/*----------.
| yyparse.  |
`----------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (tyran_parser* parser)
#else
int
yyparse (parser)
    tyran_parser* parser;
#endif
#endif
{
  /* The look-ahead symbol.  */
int yychar;

/* The semantic value of the look-ahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;
/* Location data for the look-ahead symbol.  */
YYLTYPE yylloc;

  int yystate;
  int yyn;
  int yyresult;
  /* Number of tokens to shift before error messages enabled.  */
  int yyerrstatus;
  /* Look-ahead token as an internal (translated) token number.  */
  int yytoken = 0;
#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

  /* Three stacks and their tools:
     `yyss': related to states,
     `yyvs': related to semantic values,
     `yyls': related to locations.

     Refer to the stacks thru separate pointers, to allow yyoverflow
     to reallocate them elsewhere.  */

  /* The state stack.  */
  yytype_int16 yyssa[YYINITDEPTH];
  yytype_int16 *yyss = yyssa;
  yytype_int16 *yyssp;

  /* The semantic value stack.  */
  YYSTYPE yyvsa[YYINITDEPTH];
  YYSTYPE *yyvs = yyvsa;
  YYSTYPE *yyvsp;

  /* The location stack.  */
  YYLTYPE yylsa[YYINITDEPTH];
  YYLTYPE *yyls = yylsa;
  YYLTYPE *yylsp;
  /* The locations where the error started and ended.  */
  YYLTYPE yyerror_range[2];

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N), yylsp -= (N))

  YYSIZE_T yystacksize = YYINITDEPTH;

  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
  YYLTYPE yyloc;

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY;		/* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */

  yyssp = yyss;
  yyvsp = yyvs;
  yylsp = yyls;
#if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
  /* Initialize the default location before parsing starts.  */
  yylloc.first_line   = yylloc.last_line   = 1;
  yylloc.first_column = yylloc.last_column = 0;
#endif

  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack.  Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	yytype_int16 *yyss1 = yyss;
	YYLTYPE *yyls1 = yyls;

	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),
		    &yyls1, yysize * sizeof (*yylsp),
		    &yystacksize);
	yyls = yyls1;
	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	yytype_int16 *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyexhaustedlab;
	YYSTACK_RELOCATE (yyss);
	YYSTACK_RELOCATE (yyvs);
	YYSTACK_RELOCATE (yyls);
#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;
      yylsp = yyls + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     look-ahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to look-ahead token.  */
  yyn = yypact[yystate];
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a look-ahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid look-ahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yyn == 0 || yyn == YYTABLE_NINF)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the look-ahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token unless it is eof.  */
  if (yychar != YYEOF)
    yychar = YYEMPTY;

  yystate = yyn;
  *++yyvsp = yylval;
  *++yylsp = yylloc;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];

  /* Default location.  */
  YYLLOC_DEFAULT (yyloc, (yylsp - yylen), yylen);
  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:
#line 106 "tyran_script_parser.y"
    { (yyval) = (yyvsp[(1) - (1)]); tyran_parser_root(parser, (yyvsp[(1) - (1)])); ;}
    break;

  case 3:
#line 109 "tyran_script_parser.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;

  case 19:
#line 133 "tyran_script_parser.y"
    { (yyval) = tyran_parser_block(0); ;}
    break;

  case 20:
#line 134 "tyran_script_parser.y"
    { (yyval) = tyran_parser_block((yyvsp[(2) - (3)])); ;}
    break;

  case 21:
#line 137 "tyran_script_parser.y"
    { (yyval) = tyran_parser_literal_identifier((yyvsp[(1) - (1)])); ;}
    break;

  case 22:
#line 140 "tyran_script_parser.y"
    { (yyval) = tyran_parser_literal_number((yyvsp[(1) - (1)])); ;}
    break;

  case 23:
#line 141 "tyran_script_parser.y"
    { (yyval) = tyran_parser_literal_string((yyvsp[(1) - (1)])); ;}
    break;

  case 25:
#line 145 "tyran_script_parser.y"
    { (yyval) = tyran_parser_undefined(); ;}
    break;

  case 26:
#line 146 "tyran_script_parser.y"
    { (yyval) = tyran_parser_null(); ;}
    break;

  case 27:
#line 147 "tyran_script_parser.y"
    { (yyval) = tyran_parser_bool(1); ;}
    break;

  case 28:
#line 148 "tyran_script_parser.y"
    { (yyval) = tyran_parser_bool(0); ;}
    break;

  case 29:
#line 151 "tyran_script_parser.y"
    { (yyval) = tyran_parser_assignment((yyvsp[(1) - (3)]), (yyvsp[(3) - (3)])); ;}
    break;

  case 30:
#line 152 "tyran_script_parser.y"
    { (yyval) = tyran_parser_assignment((yyvsp[(1) - (4)]), (yyvsp[(4) - (4)])); ;}
    break;

  case 31:
#line 153 "tyran_script_parser.y"
    { (yyval) = tyran_parser_assignment((yyvsp[(1) - (5)]), (yyvsp[(4) - (5)])); ;}
    break;

  case 32:
#line 156 "tyran_script_parser.y"
    {;}
    break;

  case 33:
#line 157 "tyran_script_parser.y"
    { (yyval) = tyran_parser_object_assignment(tyran_parser_value((yyvsp[(1) - (3)])), (yyvsp[(3) - (3)])); ;}
    break;

  case 34:
#line 158 "tyran_script_parser.y"
    { (yyval) = tyran_parser_object_assignment(tyran_parser_value((yyvsp[(1) - (5)])), (yyvsp[(4) - (5)])); ;}
    break;

  case 39:
#line 167 "tyran_script_parser.y"
    {(yyval) = tyran_parser_return((yyvsp[(2) - (2)]));;}
    break;

  case 40:
#line 168 "tyran_script_parser.y"
    {(yyval) = tyran_parser_return(0);;}
    break;

  case 41:
#line 171 "tyran_script_parser.y"
    {(yyval) = tyran_parser_comment((yyvsp[(1) - (1)]));;}
    break;

  case 42:
#line 174 "tyran_script_parser.y"
    {(yyval) = tyran_parser_code((yyvsp[(2) - (5)]), (yyvsp[(5) - (5)]), (yyvsp[(4) - (5)]));;}
    break;

  case 43:
#line 175 "tyran_script_parser.y"
    {(yyval) = tyran_parser_code(0, (yyvsp[(2) - (2)]), (yyvsp[(1) - (2)]));;}
    break;

  case 44:
#line 178 "tyran_script_parser.y"
    {;}
    break;

  case 45:
#line 179 "tyran_script_parser.y"
    {;}
    break;

  case 47:
#line 184 "tyran_script_parser.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;

  case 48:
#line 185 "tyran_script_parser.y"
    {(yyval) = tyran_parser_concat((yyvsp[(1) - (3)]), (yyvsp[(3) - (3)]));;}
    break;

  case 49:
#line 186 "tyran_script_parser.y"
    {(yyval) = tyran_parser_concat((yyvsp[(1) - (3)]), (yyvsp[(3) - (3)]));;}
    break;

  case 50:
#line 187 "tyran_script_parser.y"
    {(yyval) = tyran_parser_concat((yyvsp[(1) - (4)]), (yyvsp[(3) - (4)]));;}
    break;

  case 51:
#line 190 "tyran_script_parser.y"
    {(yyval) = tyran_parser_parameter((yyvsp[(1) - (1)]), 0, 0);;}
    break;

  case 52:
#line 191 "tyran_script_parser.y"
    {(yyval) = tyran_parser_parameter((yyvsp[(1) - (2)]), 0, 0);;}
    break;

  case 53:
#line 192 "tyran_script_parser.y"
    {(yyval) = tyran_parser_parameter((yyvsp[(1) - (3)]), (yyvsp[(3) - (3)]), 0);;}
    break;

  case 58:
#line 201 "tyran_script_parser.y"
    { (yyval) = tyran_parser_splat((yyvsp[(1) - (2)])); ;}
    break;

  case 59:
#line 204 "tyran_script_parser.y"
    {(yyval) = tyran_parser_value((yyvsp[(1) - (1)]));;}
    break;

  case 60:
#line 205 "tyran_script_parser.y"
    { (yyval) = tyran_parser_accessor((yyvsp[(2) - (2)])); ;}
    break;

  case 61:
#line 206 "tyran_script_parser.y"
    { (yyval) = tyran_parser_concat(tyran_parser_value((yyvsp[(1) - (2)])), (yyvsp[(2) - (2)])); ;}
    break;

  case 64:
#line 212 "tyran_script_parser.y"
    { (yyval) = tyran_parser_value((yyvsp[(1) - (1)])); ;}
    break;

  case 65:
#line 213 "tyran_script_parser.y"
    { (yyval) = tyran_parser_value((yyvsp[(1) - (1)])); ;}
    break;

  case 67:
#line 217 "tyran_script_parser.y"
    { (yyval) = tyran_parser_value((yyvsp[(1) - (1)])); ;}
    break;

  case 68:
#line 218 "tyran_script_parser.y"
    { (yyval) = tyran_parser_value((yyvsp[(1) - (1)])); ;}
    break;

  case 69:
#line 219 "tyran_script_parser.y"
    { (yyval) = tyran_parser_value((yyvsp[(1) - (1)])); ;}
    break;

  case 70:
#line 222 "tyran_script_parser.y"
    { (yyval) = tyran_parser_accessor((yyvsp[(2) - (2)])); ;}
    break;

  case 71:
#line 223 "tyran_script_parser.y"
    { (yyval) = tyran_parser_accessor((yyvsp[(2) - (2)])); ;}
    break;

  case 72:
#line 224 "tyran_script_parser.y"
    { (yyval) = tyran_parser_accessor((yyvsp[(2) - (2)])); ;}
    break;

  case 73:
#line 225 "tyran_script_parser.y"
    {;}
    break;

  case 74:
#line 228 "tyran_script_parser.y"
    { (yyval) = (yyvsp[(2) - (3)]); ;}
    break;

  case 75:
#line 229 "tyran_script_parser.y"
    { tyran_parser_index_soak((yyvsp[(2) - (2)])); ;}
    break;

  case 76:
#line 232 "tyran_script_parser.y"
    { (yyval) = tyran_parser_index((yyvsp[(1) - (1)])); ;}
    break;

  case 77:
#line 233 "tyran_script_parser.y"
    { (yyval) = tyran_parser_slice((yyvsp[(1) - (1)])); ;}
    break;

  case 78:
#line 236 "tyran_script_parser.y"
    { (yyval) = tyran_parser_object((yyvsp[(2) - (3)])); ;}
    break;

  case 79:
#line 239 "tyran_script_parser.y"
    {;}
    break;

  case 80:
#line 240 "tyran_script_parser.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;

  case 81:
#line 241 "tyran_script_parser.y"
    { (yyval) = tyran_parser_concat((yyvsp[(1) - (3)]), (yyvsp[(3) - (3)])); ;}
    break;

  case 82:
#line 242 "tyran_script_parser.y"
    { (yyval) = tyran_parser_concat((yyvsp[(1) - (3)]), (yyvsp[(3) - (3)])); ;}
    break;

  case 83:
#line 243 "tyran_script_parser.y"
    { (yyval) = tyran_parser_concat((yyvsp[(1) - (4)]), (yyvsp[(3) - (4)])); ;}
    break;

  case 84:
#line 246 "tyran_script_parser.y"
    { (yyval) = tyran_parser_class(0, 0, 0); ;}
    break;

  case 85:
#line 247 "tyran_script_parser.y"
    { (yyval) = tyran_parser_class((yyvsp[(2) - (3)]), 0, (yyvsp[(3) - (3)])); ;}
    break;

  case 86:
#line 248 "tyran_script_parser.y"
    { (yyval) = tyran_parser_class((yyvsp[(2) - (4)]), (yyvsp[(4) - (4)]), 0); ;}
    break;

  case 87:
#line 249 "tyran_script_parser.y"
    { (yyval) = tyran_parser_class((yyvsp[(2) - (5)]), (yyvsp[(4) - (5)]), (yyvsp[(5) - (5)])); ;}
    break;

  case 88:
#line 252 "tyran_script_parser.y"
    { (yyval) = tyran_parser_call((yyvsp[(1) - (3)]), (yyvsp[(3) - (3)]), (yyvsp[(2) - (3)])); ;}
    break;

  case 89:
#line 253 "tyran_script_parser.y"
    { (yyval) = tyran_parser_call((yyvsp[(1) - (3)]), (yyvsp[(3) - (3)]), (yyvsp[(2) - (3)])); ;}
    break;

  case 90:
#line 254 "tyran_script_parser.y"
    { (yyval) = tyran_parser_call_super(0); ;}
    break;

  case 91:
#line 255 "tyran_script_parser.y"
    { (yyval) = tyran_parser_call_super((yyvsp[(2) - (2)])); ;}
    break;

  case 93:
#line 259 "tyran_script_parser.y"
    { (yyval) = tyran_parser_arguments((yyvsp[(2) - (3)])); ;}
    break;

  case 94:
#line 262 "tyran_script_parser.y"
    { (yyval) = tyran_parser_self(); ;}
    break;

  case 95:
#line 265 "tyran_script_parser.y"
    { tyran_parser_self_identifier((yyvsp[(2) - (2)])); ;}
    break;

  case 96:
#line 268 "tyran_script_parser.y"
    { (yyval) = tyran_parser_array(0); ;}
    break;

  case 97:
#line 269 "tyran_script_parser.y"
    { (yyval) = tyran_parser_array((yyvsp[(2) - (3)])); ;}
    break;

  case 98:
#line 272 "tyran_script_parser.y"
    {;}
    break;

  case 99:
#line 273 "tyran_script_parser.y"
    {;}
    break;

  case 100:
#line 276 "tyran_script_parser.y"
    { (yyval) = tyran_parser_range((yyvsp[(1) - (5)]), (yyvsp[(3) - (5)]), (yyvsp[(2) - (5)])); ;}
    break;

  case 101:
#line 279 "tyran_script_parser.y"
    { (yyval) = tyran_parser_range((yyvsp[(1) - (3)]), (yyvsp[(3) - (3)]), (yyvsp[(2) - (3)])); ;}
    break;

  case 102:
#line 280 "tyran_script_parser.y"
    {(yyval) = tyran_parser_range((yyvsp[(1) - (2)]), 0, (yyvsp[(2) - (2)])); ;}
    break;

  case 103:
#line 281 "tyran_script_parser.y"
    {(yyval) = tyran_parser_range((yyvsp[(0) - (2)]), (yyvsp[(2) - (2)]), (yyvsp[(1) - (2)])); ;}
    break;

  case 104:
#line 282 "tyran_script_parser.y"
    { (yyval) = tyran_parser_range(0, 0, (yyvsp[(1) - (1)])); ;}
    break;

  case 105:
#line 285 "tyran_script_parser.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;

  case 106:
#line 286 "tyran_script_parser.y"
    { (yyval) = tyran_parser_concat((yyvsp[(1) - (3)]), (yyvsp[(3) - (3)])); ;}
    break;

  case 107:
#line 287 "tyran_script_parser.y"
    { (yyval) = tyran_parser_concat((yyvsp[(1) - (3)]), (yyvsp[(3) - (3)])); ;}
    break;

  case 108:
#line 288 "tyran_script_parser.y"
    { (yyval) = (yyvsp[(2) - (3)]); ;}
    break;

  case 109:
#line 289 "tyran_script_parser.y"
    { (yyval) = tyran_parser_concat((yyvsp[(1) - (4)]), (yyvsp[(4) - (4)])); ;}
    break;

  case 113:
#line 297 "tyran_script_parser.y"
    { (yyval) = tyran_parser_concat((yyvsp[(1) - (3)]), (yyvsp[(3) - (3)])); ;}
    break;

  case 114:
#line 300 "tyran_script_parser.y"
    { (yyval) = tyran_parser_parens((yyvsp[(2) - (3)])); ;}
    break;

  case 115:
#line 301 "tyran_script_parser.y"
    { (yyval) = tyran_parser_parens((yyvsp[(3) - (5)])); ;}
    break;

  case 116:
#line 304 "tyran_script_parser.y"
    { (yyval) = tyran_parser_while((yyvsp[(2) - (2)])); ;}
    break;

  case 117:
#line 307 "tyran_script_parser.y"
    { (yyval) = tyran_parser_while_condition((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); ;}
    break;

  case 118:
#line 311 "tyran_script_parser.y"
    { (yyval) = tyran_parser_switch((yyvsp[(2) - (5)]), (yyvsp[(4) - (5)]), 0); ;}
    break;

  case 119:
#line 312 "tyran_script_parser.y"
    { (yyval) = tyran_parser_switch((yyvsp[(2) - (7)]), (yyvsp[(4) - (7)]), (yyvsp[(6) - (7)])); ;}
    break;

  case 120:
#line 313 "tyran_script_parser.y"
    { (yyval) = tyran_parser_switch((yyvsp[(2) - (4)]), (yyvsp[(4) - (4)]), 0); ;}
    break;

  case 121:
#line 314 "tyran_script_parser.y"
    { (yyval) = tyran_parser_switch((yyvsp[(2) - (6)]), (yyvsp[(4) - (6)]), 0); ;}
    break;

  case 123:
#line 318 "tyran_script_parser.y"
    { tyran_parser_concat((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); ;}
    break;

  case 124:
#line 321 "tyran_script_parser.y"
    { tyran_parser_when((yyvsp[(2) - (3)]), (yyvsp[(3) - (3)])); ;}
    break;

  case 125:
#line 322 "tyran_script_parser.y"
    { tyran_parser_when((yyvsp[(2) - (4)]), (yyvsp[(3) - (4)])); ;}
    break;

  case 126:
#line 325 "tyran_script_parser.y"
    { (yyval) = tyran_parser_if((yyvsp[(2) - (3)]), (yyvsp[(3) - (3)])); ;}
    break;

  case 127:
#line 326 "tyran_script_parser.y"
    {tyran_parser_if_else((yyvsp[(1) - (5)]), (yyvsp[(3) - (5)])); ;}
    break;

  case 129:
#line 330 "tyran_script_parser.y"
    { tyran_parser_if_else((yyvsp[(1) - (3)]), (yyvsp[(3) - (3)])); ;}
    break;

  case 130:
#line 331 "tyran_script_parser.y"
    {;}
    break;

  case 131:
#line 332 "tyran_script_parser.y"
    {;}
    break;

  case 132:
#line 335 "tyran_script_parser.y"
    { (yyval) = tyran_parser_operand_unary(ADD, (yyvsp[(2) - (2)]), 0); ;}
    break;

  case 133:
#line 336 "tyran_script_parser.y"
    { (yyval) = tyran_parser_operand_unary(SUBTRACT, (yyvsp[(2) - (2)]), 0); ;}
    break;

  case 134:
#line 337 "tyran_script_parser.y"
    { (yyval) = tyran_parser_operand_unary(DECREMENT, (yyvsp[(2) - (2)]), 0); ;}
    break;

  case 135:
#line 338 "tyran_script_parser.y"
    { (yyval) = tyran_parser_operand_unary(INCREMENT, (yyvsp[(2) - (2)]), 0); ;}
    break;

  case 136:
#line 339 "tyran_script_parser.y"
    {(yyval) = tyran_parser_operand_unary(DECREMENT, (yyvsp[(1) - (2)]), 1); ;}
    break;

  case 137:
#line 340 "tyran_script_parser.y"
    {(yyval) = tyran_parser_operand_unary(INCREMENT, (yyvsp[(1) - (2)]), 1); ;}
    break;

  case 138:
#line 341 "tyran_script_parser.y"
    {(yyval) = tyran_parser_operand_unary(QUESTION_MARK, (yyvsp[(1) - (2)]), 1); ;}
    break;

  case 139:
#line 342 "tyran_script_parser.y"
    { (yyval) = tyran_parser_operand_binary('+', (yyvsp[(1) - (3)]), (yyvsp[(3) - (3)])); ;}
    break;

  case 140:
#line 343 "tyran_script_parser.y"
    { (yyval) = tyran_parser_operand_binary('-', (yyvsp[(1) - (3)]), (yyvsp[(3) - (3)])); ;}
    break;

  case 141:
#line 344 "tyran_script_parser.y"
    { (yyval) = tyran_parser_operand_binary('*', (yyvsp[(1) - (3)]), (yyvsp[(3) - (3)])); ;}
    break;

  case 142:
#line 345 "tyran_script_parser.y"
    { (yyval) = tyran_parser_operand_binary('/', (yyvsp[(1) - (3)]), (yyvsp[(3) - (3)])); ;}
    break;

  case 143:
#line 346 "tyran_script_parser.y"
    { (yyval) = tyran_parser_compound_assignment(COMPOUND_ADD, (yyvsp[(1) - (3)]), (yyvsp[(3) - (3)])); ;}
    break;

  case 144:
#line 347 "tyran_script_parser.y"
    { (yyval) = tyran_parser_compound_assignment(COMPOUND_DIVIDE, (yyvsp[(1) - (3)]), (yyvsp[(3) - (3)])); ;}
    break;

  case 145:
#line 348 "tyran_script_parser.y"
    { (yyval) = tyran_parser_compound_assignment(COMPOUND_MULTIPLY, (yyvsp[(1) - (3)]), (yyvsp[(3) - (3)])); ;}
    break;

  case 146:
#line 349 "tyran_script_parser.y"
    { (yyval) = tyran_parser_compound_assignment(COMPOUND_SUBTRACT, (yyvsp[(1) - (3)]), (yyvsp[(3) - (3)])); ;}
    break;

  case 147:
#line 350 "tyran_script_parser.y"
    { (yyval) = tyran_parser_compound_assignment(COMPOUND_SUBTRACT, (yyvsp[(1) - (3)]), (yyvsp[(3) - (3)])); ;}
    break;

  case 148:
#line 351 "tyran_script_parser.y"
    { tyran_parser_extends((yyvsp[(1) - (3)]), (yyvsp[(3) - (3)])); ;}
    break;


/* Line 1267 of yacc.c.  */
#line 2446 "tyran_script_parser.tab.c"
      default: break;
    }
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;
  *++yylsp = yyloc;

  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (&yylloc, parser, YY_("syntax error"));
#else
      {
	YYSIZE_T yysize = yysyntax_error (0, yystate, yychar);
	if (yymsg_alloc < yysize && yymsg_alloc < YYSTACK_ALLOC_MAXIMUM)
	  {
	    YYSIZE_T yyalloc = 2 * yysize;
	    if (! (yysize <= yyalloc && yyalloc <= YYSTACK_ALLOC_MAXIMUM))
	      yyalloc = YYSTACK_ALLOC_MAXIMUM;
	    if (yymsg != yymsgbuf)
	      YYSTACK_FREE (yymsg);
	    yymsg = (char *) YYSTACK_ALLOC (yyalloc);
	    if (yymsg)
	      yymsg_alloc = yyalloc;
	    else
	      {
		yymsg = yymsgbuf;
		yymsg_alloc = sizeof yymsgbuf;
	      }
	  }

	if (0 < yysize && yysize <= yymsg_alloc)
	  {
	    (void) yysyntax_error (yymsg, yystate, yychar);
	    yyerror (&yylloc, parser, yymsg);
	  }
	else
	  {
	    yyerror (&yylloc, parser, YY_("syntax error"));
	    if (yysize != 0)
	      goto yyexhaustedlab;
	  }
      }
#endif
    }

  yyerror_range[0] = yylloc;

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse look-ahead token after an
	 error, discard it.  */

      if (yychar <= YYEOF)
	{
	  /* Return failure if at end of input.  */
	  if (yychar == YYEOF)
	    YYABORT;
	}
      else
	{
	  yydestruct ("Error: discarding",
		      yytoken, &yylval, &yylloc, parser);
	  yychar = YYEMPTY;
	}
    }

  /* Else will try to reuse look-ahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  yyerror_range[0] = yylsp[1-yylen];
  /* Do not reclaim the symbols of the rule which action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (yyn != YYPACT_NINF)
	{
	  yyn += YYTERROR;
	  if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
	    {
	      yyn = yytable[yyn];
	      if (0 < yyn)
		break;
	    }
	}

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
	YYABORT;

      yyerror_range[0] = *yylsp;
      yydestruct ("Error: popping",
		  yystos[yystate], yyvsp, yylsp, parser);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  *++yyvsp = yylval;

  yyerror_range[1] = yylloc;
  /* Using YYLLOC is tempting, but would change the location of
     the look-ahead.  YYLOC is available though.  */
  YYLLOC_DEFAULT (yyloc, (yyerror_range - 1), 2);
  *++yylsp = yyloc;

  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#ifndef yyoverflow
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (&yylloc, parser, YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEOF && yychar != YYEMPTY)
     yydestruct ("Cleanup: discarding lookahead",
		 yytoken, &yylval, &yylloc, parser);
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp, yylsp, parser);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}


#line 352 "tyran_script_parser.y"


