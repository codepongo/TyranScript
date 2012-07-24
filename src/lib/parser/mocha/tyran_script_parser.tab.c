/* A Bison parser, made by GNU Bison 2.6.  */

/* Bison implementation for Yacc-like parsers in C
   
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
#define YYBISON_VERSION "2.6"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 1

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1


/* Substitute the variable and function names.  */
#define yyparse         TYRAN_PARSER_parse
#define yylex           TYRAN_PARSER_lex
#define yyerror         TYRAN_PARSER_error
#define yylval          TYRAN_PARSER_lval
#define yychar          TYRAN_PARSER_char
#define yydebug         TYRAN_PARSER_debug
#define yynerrs         TYRAN_PARSER_nerrs
#define yylloc          TYRAN_PARSER_lloc

/* Copy the first part of user declarations.  */

/* Line 336 of yacc.c  */
#line 1 "tyran_script_parser.y"

	#include <tyranscript/parser/mocha/tyran_parser.h>	


/* Line 336 of yacc.c  */
#line 82 "tyran_script_parser.tab.c"

# ifndef YY_NULL
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULL nullptr
#  else
#   define YY_NULL 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 1
#endif

/* In a future release of Bison, this section will be replaced
   by #include "tyran_script_parser.tab.h".  */
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

/* Copy the second part of user declarations.  */


/* Line 353 of yacc.c  */
#line 235 "tyran_script_parser.tab.c"

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
YYID (int yyi)
#else
static int
YYID (yyi)
    int yyi;
#endif
{
  return yyi;
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
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
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
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
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
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
  YYLTYPE yyls_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE) + sizeof (YYLTYPE)) \
      + 2 * YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)				\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack_alloc, Stack, yysize);			\
	Stack = &yyptr->Stack_alloc;					\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (YYID (0))
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  99
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   913

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  76
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  50
/* YYNRULES -- Number of rules.  */
#define YYNRULES  146
/* YYNRULES -- Number of states.  */
#define YYNSTATES  243

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   330

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
      75
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
     427,   431,   435,   439,   443,   447,   453
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      77,     0,    -1,    78,    -1,    79,    -1,    78,     8,    79,
      -1,    78,     8,    -1,    81,    -1,    80,    -1,    89,    -1,
      90,    -1,    99,    -1,   106,    -1,    91,    -1,   125,    -1,
      86,    -1,   124,    -1,   119,    -1,   120,    -1,   105,    -1,
      11,    21,    -1,    11,    78,    21,    -1,     7,    -1,    34,
      -1,    33,    -1,    84,    -1,    16,    -1,    14,    -1,    17,
      -1,    18,    -1,    98,    52,    81,    -1,    98,    52,     8,
      81,    -1,    98,    52,    11,    81,    21,    -1,    88,    -1,
      88,    53,    81,    -1,    88,    53,    11,    81,    21,    -1,
      90,    -1,    83,    -1,    84,    -1,   109,    -1,    22,    81,
      -1,    22,    -1,     3,    -1,    38,    93,    13,    92,    82,
      -1,    92,    82,    -1,    57,    -1,    58,    -1,    54,    -1,
      94,    -1,    93,    54,    94,    -1,    93,     8,    94,    -1,
      93,    11,    93,    21,    -1,    95,    -1,    95,    64,    -1,
      95,    52,    81,    -1,    83,    -1,   109,    -1,   110,    -1,
     103,    -1,    81,    64,    -1,    83,    -1,    99,   100,    -1,
     106,   100,    -1,   109,    -1,    97,    -1,   110,    -1,   103,
      -1,    98,    -1,    85,    -1,   117,    -1,   112,    -1,    47,
      83,    -1,    55,    83,    -1,    49,    83,    -1,   101,    -1,
       9,   102,    23,    -1,    20,   101,    -1,    81,    -1,   113,
      -1,    61,   104,    62,    -1,    54,    -1,    87,    -1,   104,
      54,    87,    -1,   104,     8,    87,    -1,   104,    11,   104,
      21,    -1,    56,    97,    -1,    56,    97,    82,    -1,    56,
      97,    75,    81,    -1,    56,    97,    75,    81,    82,    -1,
      99,     7,   107,    -1,   106,     7,   107,    -1,    29,    -1,
      29,   107,    -1,    15,    25,    -1,    15,   114,    25,    -1,
      59,    -1,   108,    83,    -1,    65,    66,    -1,    65,   114,
      66,    -1,    63,    -1,    64,    -1,    65,    81,   111,    81,
      66,    -1,    81,   111,    81,    -1,    81,   111,    -1,   111,
      81,    -1,   111,    -1,   115,    -1,   114,    54,   115,    -1,
     114,     8,   115,    -1,    11,   114,    21,    -1,   114,    11,
     114,    21,    -1,    81,    -1,    96,    -1,    81,    -1,   116,
      54,    81,    -1,    67,    78,    68,    -1,    67,    11,    78,
      21,    68,    -1,    19,    81,    -1,   118,    82,    -1,    12,
      81,    11,   121,    21,    -1,    12,    81,    11,   121,    73,
      82,    21,    -1,    12,    11,   121,    21,    -1,    12,    11,
     121,    73,    82,    21,    -1,   122,    -1,   121,   122,    -1,
      37,   116,    82,    -1,    37,   116,    82,     8,    -1,    36,
      81,    82,    -1,   123,    73,    36,    81,    82,    -1,   123,
      -1,   123,    73,    82,    -1,    80,    31,    81,    -1,    81,
      31,    81,    -1,     4,    81,    -1,    43,    81,    -1,    44,
      81,    -1,    51,    97,    -1,    50,    97,    -1,    97,    51,
      -1,    97,    50,    -1,    81,    60,    -1,    81,    43,    81,
      -1,    81,    44,    81,    -1,    81,    45,    81,    -1,    81,
      46,    81,    -1,    97,    42,    81,    -1,    97,    42,    11,
      81,    21,    -1,    97,    74,    81,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   102,   102,   105,   106,   107,   110,   111,   114,   115,
     118,   119,   120,   121,   122,   123,   124,   125,   126,   129,
     130,   133,   136,   137,   140,   141,   142,   143,   144,   147,
     148,   149,   152,   153,   154,   155,   158,   159,   160,   163,
     164,   167,   170,   171,   174,   175,   179,   180,   181,   182,
     183,   186,   187,   188,   191,   192,   193,   194,   197,   200,
     201,   202,   203,   207,   208,   209,   212,   213,   214,   215,
     218,   219,   220,   221,   224,   225,   228,   229,   232,   235,
     236,   237,   238,   239,   242,   243,   244,   245,   248,   249,
     250,   251,   254,   255,   258,   261,   264,   265,   268,   269,
     272,   275,   276,   277,   278,   281,   282,   283,   284,   285,
     288,   289,   292,   293,   296,   297,   300,   303,   307,   308,
     309,   310,   313,   314,   317,   318,   321,   322,   325,   326,
     327,   328,   331,   332,   333,   334,   335,   336,   337,   338,
     339,   340,   341,   342,   343,   344,   345
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 1
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
  "COMPOUND_ASSIGNMENT", "ADD", "SUBTRACT", "MULTIPLY", "DIVIDE", "MEMBER",
  "SOAK_MEMBER", "SCOPING", "INCREMENT", "DECREMENT", "EQUAL", "COLON",
  "COMMA", "MEMBER_SOAK", "_CLASS", "FUNCTION_GLYPH",
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
  "operation", YY_NULL
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
     325,   326,   327,   328,   329,   330
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    76,    77,    78,    78,    78,    79,    79,    80,    80,
      81,    81,    81,    81,    81,    81,    81,    81,    81,    82,
      82,    83,    84,    84,    85,    85,    85,    85,    85,    86,
      86,    86,    87,    87,    87,    87,    88,    88,    88,    89,
      89,    90,    91,    91,    92,    92,    93,    93,    93,    93,
      93,    94,    94,    94,    95,    95,    95,    95,    96,    97,
      97,    97,    97,    98,    98,    98,    99,    99,    99,    99,
     100,   100,   100,   100,   101,   101,   102,   102,   103,   104,
     104,   104,   104,   104,   105,   105,   105,   105,   106,   106,
     106,   106,   107,   107,   108,   109,   110,   110,   111,   111,
     112,   113,   113,   113,   113,   114,   114,   114,   114,   114,
     115,   115,   116,   116,   117,   117,   118,   119,   120,   120,
     120,   120,   121,   121,   122,   122,   123,   123,   124,   124,
     124,   124,   125,   125,   125,   125,   125,   125,   125,   125,
     125,   125,   125,   125,   125,   125,   125
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
       3,     3,     2,     2,     2,     2,     2,     2,     2,     2,
       3,     3,     3,     3,     3,     5,     3
};

/* YYDEFACT[STATE-NAME] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,    41,     0,    21,     0,    26,    25,    27,    28,     0,
      40,    90,    23,    22,     0,     0,     0,     0,     0,     0,
       0,    44,    45,    94,     0,     0,     0,     0,     2,     3,
       7,     6,    59,    24,    67,    14,     8,     9,    12,     0,
      63,    66,    10,    65,    18,    11,     0,    62,    64,    69,
      68,     0,    16,    17,   128,    15,    13,     0,   132,     0,
       0,   116,    39,     0,    91,     0,    46,     0,    54,     0,
      47,    51,    57,    55,    56,   133,   134,   136,    66,     0,
       0,   135,    84,    79,    36,    37,    80,    32,    35,     0,
      38,     0,    96,   110,   111,     0,   105,     0,     0,     1,
       5,     0,     0,     0,     0,     0,     0,   139,     0,    43,
       0,   138,   137,     0,     0,     0,     0,     0,     0,     0,
       0,    60,    73,     0,    61,    95,   117,     0,     0,     0,
     122,     0,    92,   110,     0,   126,     0,     0,     0,     0,
       0,    52,     0,    85,     0,     0,     0,     0,    78,     0,
      98,    99,     0,     0,     0,     0,    97,     0,   114,     4,
     130,   131,   140,   141,   142,   143,    19,     0,     0,   144,
     146,     0,     0,    29,    88,    99,    76,     0,   104,    77,
      75,    70,    72,    71,    89,     0,   129,   112,     0,   120,
       0,   123,     0,    58,    93,    49,     0,     0,    48,    53,
      86,     0,    33,    82,     0,    81,   108,     0,   107,     0,
     106,     0,    20,     0,    30,     0,   102,    74,   103,     0,
       0,   124,     0,   118,     0,    50,    42,    87,     0,    83,
     100,   109,   115,   145,    31,   101,   127,   113,   125,   121,
       0,    34,   119
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    27,    28,    29,    57,   133,   109,    32,    33,    34,
      35,    86,    87,    36,    37,    38,    39,    69,    70,    71,
      94,    40,    41,    42,   121,   122,   177,    43,    89,    44,
      45,    64,    46,    47,    48,   152,    49,   179,    95,    96,
     188,    50,    51,    52,    53,   129,   130,    54,    55,    56
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -123
static const yytype_int16 yypact[] =
{
     800,  -123,   800,  -123,   446,  -123,  -123,  -123,  -123,   800,
     800,    43,  -123,  -123,   800,    20,   800,   800,   846,   846,
     846,  -123,  -123,  -123,   179,   192,   505,    80,    46,  -123,
      34,   691,  -123,  -123,  -123,  -123,  -123,  -123,  -123,    84,
     230,    44,   185,  -123,  -123,   247,   111,  -123,  -123,  -123,
    -123,    84,  -123,  -123,    62,  -123,  -123,    34,   -18,   102,
     331,   691,   383,   257,  -123,   455,  -123,   192,  -123,    38,
    -123,   -34,  -123,  -123,  -123,    -5,    -5,   312,  -123,   185,
     247,   312,    12,  -123,  -123,  -123,  -123,   116,  -123,    36,
    -123,   564,  -123,   487,  -123,    45,  -123,   800,     3,  -123,
     800,   800,   800,   800,   800,   800,   800,  -123,   623,  -123,
     682,  -123,  -123,   800,   322,    43,   381,    48,   111,   111,
     111,  -123,  -123,    43,  -123,  -123,  -123,     9,   800,    70,
    -123,   102,  -123,   664,   216,  -123,    17,    20,   -22,    17,
     800,  -123,   800,  -123,   741,    30,   179,    30,  -123,   109,
    -123,    58,   800,   800,   564,   800,  -123,    54,  -123,  -123,
     691,   691,    -5,    -5,   -18,   691,  -123,    65,   800,   383,
     383,   800,   800,   383,  -123,  -123,   546,   139,   800,  -123,
    -123,  -123,  -123,  -123,  -123,   800,  -123,   691,    39,  -123,
      84,  -123,    94,  -123,  -123,  -123,   244,    84,  -123,   691,
     455,   800,   691,  -123,   342,  -123,  -123,   428,  -123,   397,
    -123,   120,  -123,   514,   691,   573,   800,  -123,   691,   455,
     800,   162,   156,  -123,    84,  -123,  -123,  -123,   603,  -123,
    -123,  -123,  -123,  -123,  -123,   691,  -123,   691,  -123,  -123,
     158,  -123,  -123
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -123,  -123,   -20,    89,    83,     0,   -43,    14,    -9,  -123,
    -123,   -26,  -123,  -123,    28,  -123,    55,    47,    51,  -123,
    -123,   199,   226,   265,   -32,    81,  -123,   -14,    56,  -123,
     269,    26,  -123,    19,   -10,  -104,  -123,  -123,   -60,    -7,
    -123,  -123,  -123,  -123,  -123,    66,  -122,  -123,  -123,  -123
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -64
static const yytype_int16 yytable[] =
{
      31,    72,    58,   134,    60,    74,    98,   191,   126,    61,
      62,   100,   178,   124,    65,    85,    75,    76,   140,   -63,
     108,   -63,   135,   108,     3,    93,    31,     3,   106,    68,
     141,   149,   -63,     1,    73,    21,    22,     3,    84,   143,
     105,   106,   107,    90,   145,   185,   136,   146,   124,   137,
     108,   138,    88,   153,   100,   107,   154,   116,    63,   -63,
     125,   -63,   100,    12,    13,   101,   -58,   -63,   117,   -58,
     191,   158,   216,   100,    66,   211,    23,   157,    24,    23,
      99,    24,    67,    30,   186,    67,   212,   142,   167,    23,
     147,   189,   139,   220,   209,   108,   114,    31,   148,   155,
      31,   160,   161,   162,   163,   164,   165,   128,    31,    30,
     169,   156,   -58,   170,   173,   223,   176,   153,     3,   203,
     154,   205,    72,    72,   -58,    72,    74,    74,   187,    74,
     206,   128,   181,   182,   183,   127,    85,    85,    85,   128,
     199,   174,   200,   190,   202,   221,   208,   222,   210,   184,
      68,    68,   207,    68,   226,    73,    73,   227,    73,    84,
      84,    84,   217,   155,    90,    90,    90,   224,   213,   144,
     238,   214,   215,    88,    88,    88,   236,   239,   218,   242,
      30,   240,     1,    30,   196,   219,     3,   195,   232,   159,
     198,    30,   115,   197,   116,     1,     2,   192,   180,     3,
       0,   228,   204,    91,     4,   117,     5,     0,     6,     7,
       8,     9,    12,    13,    10,     0,   235,    77,    81,    82,
     237,    11,     0,     0,   153,    12,    13,   154,    14,     0,
      15,     0,   118,    83,   119,    16,    17,     0,    23,     0,
     120,   194,    18,    19,    78,    78,    78,     0,    20,    21,
      22,    23,   136,    24,   123,   137,   116,    25,    92,    26,
       1,     2,     0,     0,     3,   225,     0,   117,    91,     4,
     155,     5,   110,     6,     7,     8,     9,     0,     0,    10,
     111,   112,   132,    79,    79,    79,    11,    80,    80,    80,
      12,    13,     0,    14,   118,    15,   119,     0,   139,     0,
      16,    17,   120,     0,   113,     0,     0,    18,    19,     0,
       0,     0,     0,    20,    21,    22,    23,     0,    24,   -63,
       0,   -63,    25,     0,    26,     1,     2,     0,     0,     3,
     171,     0,   -63,   172,     4,     0,     5,     0,     6,     7,
       8,     9,   131,     0,    10,     0,     0,     0,     0,     0,
     145,    11,     0,   146,     0,    12,    13,     0,    14,   -63,
      15,   -63,   102,   229,     0,    16,    17,   -63,     0,     0,
       0,     0,    18,    19,   103,   104,   105,   106,    20,    21,
      22,    23,     0,    24,     1,     2,     0,    25,     3,    26,
       0,   107,     0,     4,     0,     5,   147,     6,     7,     8,
       9,     0,     0,    10,     0,   153,     0,     0,   154,     0,
      11,     0,     0,     0,    12,    13,     0,    14,   231,    15,
       0,     0,     0,     0,    16,    17,   103,   104,   105,   106,
       0,    18,    19,     0,     0,     0,     0,    20,    21,    22,
      23,     0,    24,   107,   150,   175,    25,     0,    26,     1,
       2,   155,     0,     3,     0,     0,     0,    59,     4,   102,
       5,     0,     6,     7,     8,     9,   108,     0,    10,     0,
       0,   103,   104,   105,   106,    11,     0,     0,     0,    12,
      13,     0,    14,     0,    15,     0,   102,     0,   107,    16,
      17,     0,     0,     0,   230,     0,    18,    19,   103,   104,
     105,   106,    20,    21,    22,    23,     0,    24,     1,     2,
       0,    25,     3,    26,     0,   107,    97,     4,   102,     5,
       0,     6,     7,     8,     9,     0,     0,    10,     0,     0,
     103,   104,   105,   106,    11,   233,     0,     0,    12,    13,
       0,    14,     0,    15,     0,   102,     0,   107,    16,    17,
     150,   151,     0,     0,     0,    18,    19,   103,   104,   105,
     106,    20,    21,    22,    23,     0,    24,     1,     2,     0,
      25,     3,    26,     0,   107,    91,     4,   102,     5,     0,
       6,     7,     8,     9,     0,     0,    10,     0,     0,   103,
     104,   105,   106,    11,   234,     0,     0,    12,    13,     0,
      14,     0,    15,     0,   102,     0,   107,    16,    17,   150,
     175,     0,     0,     0,    18,    19,   103,   104,   105,   106,
      20,    21,    22,    23,   241,    24,     1,     2,     0,    25,
       3,    26,     0,   107,   102,     4,     0,     5,     0,     6,
       7,     8,     9,     0,   166,    10,   103,   104,   105,   106,
       0,     0,    11,     0,     0,     0,    12,    13,     0,    14,
       0,    15,     0,   107,     0,     0,    16,    17,     0,     0,
       0,     0,     0,    18,    19,     0,     0,     0,     0,    20,
      21,    22,    23,     0,    24,     1,     2,     0,    25,     3,
      26,     0,     0,   168,     4,   102,     5,     0,     6,     7,
       8,     9,     0,     0,    10,     0,     0,   103,   104,   105,
     106,    11,     0,     0,     0,    12,    13,     0,    14,     0,
      15,     0,   102,     0,   107,    16,    17,     0,   193,     0,
       0,     0,    18,    19,   103,   104,   105,   106,    20,    21,
      22,    23,     0,    24,     1,     2,     0,    25,     3,    26,
       0,   107,   201,     4,     0,     5,     0,     6,     7,     8,
       9,     0,     0,    10,     0,     0,     0,     0,     0,     0,
      11,     0,     0,     0,    12,    13,     0,    14,     0,    15,
       0,     0,     0,     0,    16,    17,     0,     0,     0,     0,
       0,    18,    19,     0,     0,     0,     0,    20,    21,    22,
      23,     0,    24,     1,     2,     0,    25,     3,    26,     0,
       0,     0,     4,     0,     5,     0,     6,     7,     8,     9,
       0,     0,    10,     0,     0,     0,     0,     0,     0,    11,
       0,     0,     0,    12,    13,     0,    14,     0,    15,     0,
       0,     0,     0,    16,    17,     0,     0,     0,     0,     0,
      18,    19,     0,     3,     0,     0,    20,    21,    22,    23,
       5,    24,     6,     7,     8,    25,     0,    26,     0,     0,
       0,     0,     0,     0,     0,    11,     0,     0,     0,    12,
      13,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    23,     0,    24,     0,     0,
       0,    25,     0,    26
};

#define yypact_value_is_default(yystate) \
  ((yystate) == (-123))

#define yytable_value_is_error(yytable_value) \
  YYID (0)

static const yytype_int16 yycheck[] =
{
       0,    15,     2,    63,     4,    15,    26,   129,    51,     9,
      10,     8,   116,    45,    14,    24,    16,    17,    52,     7,
      11,     9,    65,    11,     7,    25,    26,     7,    46,    15,
      64,    91,    20,     3,    15,    57,    58,     7,    24,    82,
      45,    46,    60,    24,     8,    36,     8,    11,    80,    11,
      11,    13,    24,     8,     8,    60,    11,     9,    15,    47,
      46,    49,     8,    33,    34,    31,     8,    55,    20,    11,
     192,    68,   176,     8,    54,    21,    59,    97,    61,    59,
       0,    61,    65,     0,   127,    65,    21,    75,   108,    59,
      54,    21,    54,    54,   154,    11,    52,    97,    62,    54,
     100,   101,   102,   103,   104,   105,   106,    37,   108,    26,
     110,    66,    54,   113,   114,    21,   116,     8,     7,   145,
      11,   147,   136,   137,    66,   139,   136,   137,   128,   139,
      21,    37,   118,   119,   120,    73,   145,   146,   147,    37,
     140,   115,   142,    73,   144,   188,   153,   190,   155,   123,
     136,   137,   152,   139,   197,   136,   137,   200,   139,   145,
     146,   147,    23,    54,   145,   146,   147,    73,   168,    53,
       8,   171,   172,   145,   146,   147,   219,    21,   178,    21,
      97,   224,     3,   100,   137,   185,     7,   136,    68,   100,
     139,   108,     7,   138,     9,     3,     4,   131,   117,     7,
      -1,   201,   146,    11,    12,    20,    14,    -1,    16,    17,
      18,    19,    33,    34,    22,    -1,   216,    18,    19,    20,
     220,    29,    -1,    -1,     8,    33,    34,    11,    36,    -1,
      38,    -1,    47,    54,    49,    43,    44,    -1,    59,    -1,
      55,    25,    50,    51,    18,    19,    20,    -1,    56,    57,
      58,    59,     8,    61,     7,    11,     9,    65,    66,    67,
       3,     4,    -1,    -1,     7,    21,    -1,    20,    11,    12,
      54,    14,    42,    16,    17,    18,    19,    -1,    -1,    22,
      50,    51,    25,    18,    19,    20,    29,    18,    19,    20,
      33,    34,    -1,    36,    47,    38,    49,    -1,    54,    -1,
      43,    44,    55,    -1,    74,    -1,    -1,    50,    51,    -1,
      -1,    -1,    -1,    56,    57,    58,    59,    -1,    61,     7,
      -1,     9,    65,    -1,    67,     3,     4,    -1,    -1,     7,
       8,    -1,    20,    11,    12,    -1,    14,    -1,    16,    17,
      18,    19,    11,    -1,    22,    -1,    -1,    -1,    -1,    -1,
       8,    29,    -1,    11,    -1,    33,    34,    -1,    36,    47,
      38,    49,    31,    21,    -1,    43,    44,    55,    -1,    -1,
      -1,    -1,    50,    51,    43,    44,    45,    46,    56,    57,
      58,    59,    -1,    61,     3,     4,    -1,    65,     7,    67,
      -1,    60,    -1,    12,    -1,    14,    54,    16,    17,    18,
      19,    -1,    -1,    22,    -1,     8,    -1,    -1,    11,    -1,
      29,    -1,    -1,    -1,    33,    34,    -1,    36,    21,    38,
      -1,    -1,    -1,    -1,    43,    44,    43,    44,    45,    46,
      -1,    50,    51,    -1,    -1,    -1,    -1,    56,    57,    58,
      59,    -1,    61,    60,    63,    64,    65,    -1,    67,     3,
       4,    54,    -1,     7,    -1,    -1,    -1,    11,    12,    31,
      14,    -1,    16,    17,    18,    19,    11,    -1,    22,    -1,
      -1,    43,    44,    45,    46,    29,    -1,    -1,    -1,    33,
      34,    -1,    36,    -1,    38,    -1,    31,    -1,    60,    43,
      44,    -1,    -1,    -1,    66,    -1,    50,    51,    43,    44,
      45,    46,    56,    57,    58,    59,    -1,    61,     3,     4,
      -1,    65,     7,    67,    -1,    60,    11,    12,    31,    14,
      -1,    16,    17,    18,    19,    -1,    -1,    22,    -1,    -1,
      43,    44,    45,    46,    29,    21,    -1,    -1,    33,    34,
      -1,    36,    -1,    38,    -1,    31,    -1,    60,    43,    44,
      63,    64,    -1,    -1,    -1,    50,    51,    43,    44,    45,
      46,    56,    57,    58,    59,    -1,    61,     3,     4,    -1,
      65,     7,    67,    -1,    60,    11,    12,    31,    14,    -1,
      16,    17,    18,    19,    -1,    -1,    22,    -1,    -1,    43,
      44,    45,    46,    29,    21,    -1,    -1,    33,    34,    -1,
      36,    -1,    38,    -1,    31,    -1,    60,    43,    44,    63,
      64,    -1,    -1,    -1,    50,    51,    43,    44,    45,    46,
      56,    57,    58,    59,    21,    61,     3,     4,    -1,    65,
       7,    67,    -1,    60,    31,    12,    -1,    14,    -1,    16,
      17,    18,    19,    -1,    21,    22,    43,    44,    45,    46,
      -1,    -1,    29,    -1,    -1,    -1,    33,    34,    -1,    36,
      -1,    38,    -1,    60,    -1,    -1,    43,    44,    -1,    -1,
      -1,    -1,    -1,    50,    51,    -1,    -1,    -1,    -1,    56,
      57,    58,    59,    -1,    61,     3,     4,    -1,    65,     7,
      67,    -1,    -1,    11,    12,    31,    14,    -1,    16,    17,
      18,    19,    -1,    -1,    22,    -1,    -1,    43,    44,    45,
      46,    29,    -1,    -1,    -1,    33,    34,    -1,    36,    -1,
      38,    -1,    31,    -1,    60,    43,    44,    -1,    64,    -1,
      -1,    -1,    50,    51,    43,    44,    45,    46,    56,    57,
      58,    59,    -1,    61,     3,     4,    -1,    65,     7,    67,
      -1,    60,    11,    12,    -1,    14,    -1,    16,    17,    18,
      19,    -1,    -1,    22,    -1,    -1,    -1,    -1,    -1,    -1,
      29,    -1,    -1,    -1,    33,    34,    -1,    36,    -1,    38,
      -1,    -1,    -1,    -1,    43,    44,    -1,    -1,    -1,    -1,
      -1,    50,    51,    -1,    -1,    -1,    -1,    56,    57,    58,
      59,    -1,    61,     3,     4,    -1,    65,     7,    67,    -1,
      -1,    -1,    12,    -1,    14,    -1,    16,    17,    18,    19,
      -1,    -1,    22,    -1,    -1,    -1,    -1,    -1,    -1,    29,
      -1,    -1,    -1,    33,    34,    -1,    36,    -1,    38,    -1,
      -1,    -1,    -1,    43,    44,    -1,    -1,    -1,    -1,    -1,
      50,    51,    -1,     7,    -1,    -1,    56,    57,    58,    59,
      14,    61,    16,    17,    18,    65,    -1,    67,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    29,    -1,    -1,    -1,    33,
      34,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    59,    -1,    61,    -1,    -1,
      -1,    65,    -1,    67
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,     4,     7,    12,    14,    16,    17,    18,    19,
      22,    29,    33,    34,    36,    38,    43,    44,    50,    51,
      56,    57,    58,    59,    61,    65,    67,    77,    78,    79,
      80,    81,    83,    84,    85,    86,    89,    90,    91,    92,
      97,    98,    99,   103,   105,   106,   108,   109,   110,   112,
     117,   118,   119,   120,   123,   124,   125,    80,    81,    11,
      81,    81,    81,    15,   107,    81,    54,    65,    83,    93,
      94,    95,   103,   109,   110,    81,    81,    97,    98,    99,
     106,    97,    97,    54,    83,    84,    87,    88,    90,   104,
     109,    11,    66,    81,    96,   114,   115,    11,    78,     0,
       8,    31,    31,    43,    44,    45,    46,    60,    11,    82,
      42,    50,    51,    74,    52,     7,     9,    20,    47,    49,
      55,   100,   101,     7,   100,    83,    82,    73,    37,   121,
     122,    11,    25,    81,   114,    82,     8,    11,    13,    54,
      52,    64,    75,    82,    53,     8,    11,    54,    62,   114,
      63,    64,   111,     8,    11,    54,    66,    78,    68,    79,
      81,    81,    81,    81,    81,    81,    21,    78,    11,    81,
      81,     8,    11,    81,   107,    64,    81,   102,   111,   113,
     101,    83,    83,    83,   107,    36,    82,    81,   116,    21,
      73,   122,   121,    64,    25,    94,    93,    92,    94,    81,
      81,    11,    81,    87,   104,    87,    21,    81,   115,   114,
     115,    21,    21,    81,    81,    81,   111,    23,    81,    81,
      54,    82,    82,    21,    73,    21,    82,    82,    81,    21,
      66,    21,    68,    21,    21,    81,    82,    81,     8,    21,
      82,    21,    21
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
   Once GCC version 2 has supplanted version 1, this can go.  However,
   YYFAIL appears to be in use.  Nevertheless, it is formally deprecated
   in Bison 2.4.2's NEWS entry, where a plan to phase it out is
   discussed.  */

#define YYFAIL		goto yyerrlab
#if defined YYFAIL
  /* This is here to suppress warnings from the GCC cpp's
     -Wunused-macros.  Normally we don't worry about that warning, but
     some users do, and we want to make it easy for users to remove
     YYFAIL uses, which will produce warnings from Bison 2.5.  */
#endif

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
do                                                              \
  if (yychar == YYEMPTY)                                        \
    {                                                           \
      yychar = (Token);                                         \
      yylval = (Value);                                         \
      YYPOPSTACK (yylen);                                       \
      yystate = *yyssp;                                         \
      goto yybackup;                                            \
    }                                                           \
  else                                                          \
    {                                                           \
      yyerror (&yylloc, parser, YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256

/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)                                \
    do                                                                  \
      if (YYID (N))                                                     \
        {                                                               \
          (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;        \
          (Current).first_column = YYRHSLOC (Rhs, 1).first_column;      \
          (Current).last_line    = YYRHSLOC (Rhs, N).last_line;         \
          (Current).last_column  = YYRHSLOC (Rhs, N).last_column;       \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).first_line   = (Current).last_line   =              \
            YYRHSLOC (Rhs, 0).last_line;                                \
          (Current).first_column = (Current).last_column =              \
            YYRHSLOC (Rhs, 0).last_column;                              \
        }                                                               \
    while (YYID (0))
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K])



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
  FILE *yyo = yyoutput;
  YYUSE (yyo);
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
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
#else
static void
yy_stack_print (yybottom, yytop)
    yytype_int16 *yybottom;
    yytype_int16 *yytop;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
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
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       , &(yylsp[(yyi + 1) - (yynrhs)])		       , parser);
      YYFPRINTF (stderr, "\n");
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

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULL, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  YYSIZE_T yysize1;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULL;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - Assume YYFAIL is not used.  It's too flawed to consider.  See
       <http://lists.gnu.org/archive/html/bison-patches/2009-12/msg00024.html>
       for details.  YYERROR is fine as it does not invoke this
       function.
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                yysize1 = yysize + yytnamerr (YY_NULL, yytname[yyx]);
                if (! (yysize <= yysize1
                       && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                  return 2;
                yysize = yysize1;
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  yysize1 = yysize + yystrlen (yyformat);
  if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
    return 2;
  yysize = yysize1;

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
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
/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;

/* Location data for the lookahead symbol.  */
YYLTYPE yylloc;

    /* Number of syntax errors so far.  */
    int yynerrs;

    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       `yyss': related to states.
       `yyvs': related to semantic values.
       `yyls': related to locations.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    /* The location stack.  */
    YYLTYPE yylsa[YYINITDEPTH];
    YYLTYPE *yyls;
    YYLTYPE *yylsp;

    /* The locations where the error started and ended.  */
    YYLTYPE yyerror_range[3];

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
  YYLTYPE yyloc;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N), yylsp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yytoken = 0;
  yyss = yyssa;
  yyvs = yyvsa;
  yyls = yylsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */

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
  yylloc.first_column = yylloc.last_column = 1;
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
	YYSTACK_RELOCATE (yyss_alloc, yyss);
	YYSTACK_RELOCATE (yyvs_alloc, yyvs);
	YYSTACK_RELOCATE (yyls_alloc, yyls);
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

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
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
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
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

/* Line 1803 of yacc.c  */
#line 102 "tyran_script_parser.y"
    { (yyval) = (yyvsp[(1) - (1)]); tyran_parser_root(parser, (yyvsp[(1) - (1)])); }
    break;

  case 3:

/* Line 1803 of yacc.c  */
#line 105 "tyran_script_parser.y"
    { (yyval) = (yyvsp[(1) - (1)]); }
    break;

  case 19:

/* Line 1803 of yacc.c  */
#line 129 "tyran_script_parser.y"
    { (yyval) = tyran_parser_block(0); }
    break;

  case 20:

/* Line 1803 of yacc.c  */
#line 130 "tyran_script_parser.y"
    { (yyval) = tyran_parser_block((yyvsp[(2) - (3)])); }
    break;

  case 21:

/* Line 1803 of yacc.c  */
#line 133 "tyran_script_parser.y"
    { (yyval) = tyran_parser_literal_identifier((yyvsp[(1) - (1)])); }
    break;

  case 22:

/* Line 1803 of yacc.c  */
#line 136 "tyran_script_parser.y"
    { (yyval) = tyran_parser_literal_number((yyvsp[(1) - (1)])); }
    break;

  case 23:

/* Line 1803 of yacc.c  */
#line 137 "tyran_script_parser.y"
    { (yyval) = tyran_parser_literal_string((yyvsp[(1) - (1)])); }
    break;

  case 25:

/* Line 1803 of yacc.c  */
#line 141 "tyran_script_parser.y"
    { (yyval) = tyran_parser_undefined(); }
    break;

  case 26:

/* Line 1803 of yacc.c  */
#line 142 "tyran_script_parser.y"
    { (yyval) = tyran_parser_null(); }
    break;

  case 27:

/* Line 1803 of yacc.c  */
#line 143 "tyran_script_parser.y"
    { (yyval) = tyran_parser_bool(1); }
    break;

  case 28:

/* Line 1803 of yacc.c  */
#line 144 "tyran_script_parser.y"
    { (yyval) = tyran_parser_bool(0); }
    break;

  case 29:

/* Line 1803 of yacc.c  */
#line 147 "tyran_script_parser.y"
    { (yyval) = tyran_parser_assignment((yyvsp[(1) - (3)]), (yyvsp[(3) - (3)])); }
    break;

  case 30:

/* Line 1803 of yacc.c  */
#line 148 "tyran_script_parser.y"
    { (yyval) = tyran_parser_assignment((yyvsp[(1) - (4)]), (yyvsp[(4) - (4)])); }
    break;

  case 31:

/* Line 1803 of yacc.c  */
#line 149 "tyran_script_parser.y"
    { (yyval) = tyran_parser_assignment((yyvsp[(1) - (5)]), (yyvsp[(4) - (5)])); }
    break;

  case 32:

/* Line 1803 of yacc.c  */
#line 152 "tyran_script_parser.y"
    {}
    break;

  case 33:

/* Line 1803 of yacc.c  */
#line 153 "tyran_script_parser.y"
    { (yyval) = tyran_parser_object_assignment(tyran_parser_value((yyvsp[(1) - (3)])), (yyvsp[(3) - (3)])); }
    break;

  case 34:

/* Line 1803 of yacc.c  */
#line 154 "tyran_script_parser.y"
    { (yyval) = tyran_parser_object_assignment(tyran_parser_value((yyvsp[(1) - (5)])), (yyvsp[(4) - (5)])); }
    break;

  case 39:

/* Line 1803 of yacc.c  */
#line 163 "tyran_script_parser.y"
    {(yyval) = tyran_parser_return((yyvsp[(2) - (2)]));}
    break;

  case 40:

/* Line 1803 of yacc.c  */
#line 164 "tyran_script_parser.y"
    {(yyval) = tyran_parser_return(0);}
    break;

  case 41:

/* Line 1803 of yacc.c  */
#line 167 "tyran_script_parser.y"
    {(yyval) = tyran_parser_comment((yyvsp[(1) - (1)]));}
    break;

  case 42:

/* Line 1803 of yacc.c  */
#line 170 "tyran_script_parser.y"
    {(yyval) = tyran_parser_code((yyvsp[(2) - (5)]), (yyvsp[(5) - (5)]), (yyvsp[(4) - (5)]));}
    break;

  case 43:

/* Line 1803 of yacc.c  */
#line 171 "tyran_script_parser.y"
    {(yyval) = tyran_parser_code(0, (yyvsp[(2) - (2)]), (yyvsp[(1) - (2)]));}
    break;

  case 44:

/* Line 1803 of yacc.c  */
#line 174 "tyran_script_parser.y"
    {}
    break;

  case 45:

/* Line 1803 of yacc.c  */
#line 175 "tyran_script_parser.y"
    {}
    break;

  case 47:

/* Line 1803 of yacc.c  */
#line 180 "tyran_script_parser.y"
    { (yyval) = (yyvsp[(1) - (1)]); }
    break;

  case 48:

/* Line 1803 of yacc.c  */
#line 181 "tyran_script_parser.y"
    {(yyval) = tyran_parser_concat((yyvsp[(1) - (3)]), (yyvsp[(3) - (3)]));}
    break;

  case 49:

/* Line 1803 of yacc.c  */
#line 182 "tyran_script_parser.y"
    {(yyval) = tyran_parser_concat((yyvsp[(1) - (3)]), (yyvsp[(3) - (3)]));}
    break;

  case 50:

/* Line 1803 of yacc.c  */
#line 183 "tyran_script_parser.y"
    {(yyval) = tyran_parser_concat((yyvsp[(1) - (4)]), (yyvsp[(3) - (4)]));}
    break;

  case 51:

/* Line 1803 of yacc.c  */
#line 186 "tyran_script_parser.y"
    {(yyval) = tyran_parser_parameter((yyvsp[(1) - (1)]), 0, 0);}
    break;

  case 52:

/* Line 1803 of yacc.c  */
#line 187 "tyran_script_parser.y"
    {(yyval) = tyran_parser_parameter((yyvsp[(1) - (2)]), 0, 0);}
    break;

  case 53:

/* Line 1803 of yacc.c  */
#line 188 "tyran_script_parser.y"
    {(yyval) = tyran_parser_parameter((yyvsp[(1) - (3)]), (yyvsp[(3) - (3)]), 0);}
    break;

  case 58:

/* Line 1803 of yacc.c  */
#line 197 "tyran_script_parser.y"
    { (yyval) = tyran_parser_splat((yyvsp[(1) - (2)])); }
    break;

  case 59:

/* Line 1803 of yacc.c  */
#line 200 "tyran_script_parser.y"
    {(yyval) = tyran_parser_value((yyvsp[(1) - (1)]));}
    break;

  case 60:

/* Line 1803 of yacc.c  */
#line 201 "tyran_script_parser.y"
    { (yyval) = tyran_parser_accessor((yyvsp[(2) - (2)])); }
    break;

  case 61:

/* Line 1803 of yacc.c  */
#line 202 "tyran_script_parser.y"
    { (yyval) = tyran_parser_concat(tyran_parser_value((yyvsp[(1) - (2)])), (yyvsp[(2) - (2)])); }
    break;

  case 64:

/* Line 1803 of yacc.c  */
#line 208 "tyran_script_parser.y"
    { (yyval) = tyran_parser_value((yyvsp[(1) - (1)])); }
    break;

  case 65:

/* Line 1803 of yacc.c  */
#line 209 "tyran_script_parser.y"
    { (yyval) = tyran_parser_value((yyvsp[(1) - (1)])); }
    break;

  case 67:

/* Line 1803 of yacc.c  */
#line 213 "tyran_script_parser.y"
    { (yyval) = tyran_parser_value((yyvsp[(1) - (1)])); }
    break;

  case 68:

/* Line 1803 of yacc.c  */
#line 214 "tyran_script_parser.y"
    { (yyval) = tyran_parser_value((yyvsp[(1) - (1)])); }
    break;

  case 69:

/* Line 1803 of yacc.c  */
#line 215 "tyran_script_parser.y"
    { (yyval) = tyran_parser_value((yyvsp[(1) - (1)])); }
    break;

  case 70:

/* Line 1803 of yacc.c  */
#line 218 "tyran_script_parser.y"
    { (yyval) = tyran_parser_accessor((yyvsp[(2) - (2)])); }
    break;

  case 71:

/* Line 1803 of yacc.c  */
#line 219 "tyran_script_parser.y"
    { (yyval) = tyran_parser_accessor((yyvsp[(2) - (2)])); }
    break;

  case 72:

/* Line 1803 of yacc.c  */
#line 220 "tyran_script_parser.y"
    { (yyval) = tyran_parser_accessor((yyvsp[(2) - (2)])); }
    break;

  case 73:

/* Line 1803 of yacc.c  */
#line 221 "tyran_script_parser.y"
    {}
    break;

  case 74:

/* Line 1803 of yacc.c  */
#line 224 "tyran_script_parser.y"
    { (yyval) = (yyvsp[(2) - (3)]); }
    break;

  case 75:

/* Line 1803 of yacc.c  */
#line 225 "tyran_script_parser.y"
    { tyran_parser_index_soak((yyvsp[(2) - (2)])); }
    break;

  case 76:

/* Line 1803 of yacc.c  */
#line 228 "tyran_script_parser.y"
    { (yyval) = tyran_parser_index((yyvsp[(1) - (1)])); }
    break;

  case 77:

/* Line 1803 of yacc.c  */
#line 229 "tyran_script_parser.y"
    { (yyval) = tyran_parser_slice((yyvsp[(1) - (1)])); }
    break;

  case 78:

/* Line 1803 of yacc.c  */
#line 232 "tyran_script_parser.y"
    { (yyval) = tyran_parser_object((yyvsp[(2) - (3)])); }
    break;

  case 79:

/* Line 1803 of yacc.c  */
#line 235 "tyran_script_parser.y"
    {}
    break;

  case 80:

/* Line 1803 of yacc.c  */
#line 236 "tyran_script_parser.y"
    { (yyval) = (yyvsp[(1) - (1)]); }
    break;

  case 81:

/* Line 1803 of yacc.c  */
#line 237 "tyran_script_parser.y"
    { (yyval) = tyran_parser_concat((yyvsp[(1) - (3)]), (yyvsp[(3) - (3)])); }
    break;

  case 82:

/* Line 1803 of yacc.c  */
#line 238 "tyran_script_parser.y"
    { (yyval) = tyran_parser_concat((yyvsp[(1) - (3)]), (yyvsp[(3) - (3)])); }
    break;

  case 83:

/* Line 1803 of yacc.c  */
#line 239 "tyran_script_parser.y"
    { (yyval) = tyran_parser_concat((yyvsp[(1) - (4)]), (yyvsp[(3) - (4)])); }
    break;

  case 84:

/* Line 1803 of yacc.c  */
#line 242 "tyran_script_parser.y"
    { (yyval) = tyran_parser_class(0, 0, 0); }
    break;

  case 85:

/* Line 1803 of yacc.c  */
#line 243 "tyran_script_parser.y"
    { (yyval) = tyran_parser_class((yyvsp[(2) - (3)]), 0, (yyvsp[(3) - (3)])); }
    break;

  case 86:

/* Line 1803 of yacc.c  */
#line 244 "tyran_script_parser.y"
    { (yyval) = tyran_parser_class((yyvsp[(2) - (4)]), (yyvsp[(4) - (4)]), 0); }
    break;

  case 87:

/* Line 1803 of yacc.c  */
#line 245 "tyran_script_parser.y"
    { (yyval) = tyran_parser_class((yyvsp[(2) - (5)]), (yyvsp[(4) - (5)]), (yyvsp[(5) - (5)])); }
    break;

  case 88:

/* Line 1803 of yacc.c  */
#line 248 "tyran_script_parser.y"
    { (yyval) = tyran_parser_call((yyvsp[(1) - (3)]), (yyvsp[(3) - (3)]), (yyvsp[(2) - (3)])); }
    break;

  case 89:

/* Line 1803 of yacc.c  */
#line 249 "tyran_script_parser.y"
    { (yyval) = tyran_parser_call((yyvsp[(1) - (3)]), (yyvsp[(3) - (3)]), (yyvsp[(2) - (3)])); }
    break;

  case 90:

/* Line 1803 of yacc.c  */
#line 250 "tyran_script_parser.y"
    { (yyval) = tyran_parser_call_super(0); }
    break;

  case 91:

/* Line 1803 of yacc.c  */
#line 251 "tyran_script_parser.y"
    { (yyval) = tyran_parser_call_super((yyvsp[(2) - (2)])); }
    break;

  case 93:

/* Line 1803 of yacc.c  */
#line 255 "tyran_script_parser.y"
    { (yyval) = tyran_parser_arguments((yyvsp[(2) - (3)])); }
    break;

  case 94:

/* Line 1803 of yacc.c  */
#line 258 "tyran_script_parser.y"
    { (yyval) = tyran_parser_self(); }
    break;

  case 95:

/* Line 1803 of yacc.c  */
#line 261 "tyran_script_parser.y"
    { tyran_parser_self_identifier((yyvsp[(2) - (2)])); }
    break;

  case 96:

/* Line 1803 of yacc.c  */
#line 264 "tyran_script_parser.y"
    { (yyval) = tyran_parser_array(0); }
    break;

  case 97:

/* Line 1803 of yacc.c  */
#line 265 "tyran_script_parser.y"
    { (yyval) = tyran_parser_array((yyvsp[(2) - (3)])); }
    break;

  case 98:

/* Line 1803 of yacc.c  */
#line 268 "tyran_script_parser.y"
    {}
    break;

  case 99:

/* Line 1803 of yacc.c  */
#line 269 "tyran_script_parser.y"
    {}
    break;

  case 100:

/* Line 1803 of yacc.c  */
#line 272 "tyran_script_parser.y"
    { (yyval) = tyran_parser_range((yyvsp[(1) - (5)]), (yyvsp[(3) - (5)]), (yyvsp[(2) - (5)])); }
    break;

  case 101:

/* Line 1803 of yacc.c  */
#line 275 "tyran_script_parser.y"
    { (yyval) = tyran_parser_range((yyvsp[(1) - (3)]), (yyvsp[(3) - (3)]), (yyvsp[(2) - (3)])); }
    break;

  case 102:

/* Line 1803 of yacc.c  */
#line 276 "tyran_script_parser.y"
    {(yyval) = tyran_parser_range((yyvsp[(1) - (2)]), 0, (yyvsp[(2) - (2)])); }
    break;

  case 103:

/* Line 1803 of yacc.c  */
#line 277 "tyran_script_parser.y"
    {(yyval) = tyran_parser_range((yyvsp[(0) - (2)]), (yyvsp[(2) - (2)]), (yyvsp[(1) - (2)])); }
    break;

  case 104:

/* Line 1803 of yacc.c  */
#line 278 "tyran_script_parser.y"
    { (yyval) = tyran_parser_range(0, 0, (yyvsp[(1) - (1)])); }
    break;

  case 105:

/* Line 1803 of yacc.c  */
#line 281 "tyran_script_parser.y"
    { (yyval) = (yyvsp[(1) - (1)]); }
    break;

  case 106:

/* Line 1803 of yacc.c  */
#line 282 "tyran_script_parser.y"
    { (yyval) = tyran_parser_concat((yyvsp[(1) - (3)]), (yyvsp[(3) - (3)])); }
    break;

  case 107:

/* Line 1803 of yacc.c  */
#line 283 "tyran_script_parser.y"
    { (yyval) = tyran_parser_concat((yyvsp[(1) - (3)]), (yyvsp[(3) - (3)])); }
    break;

  case 108:

/* Line 1803 of yacc.c  */
#line 284 "tyran_script_parser.y"
    { (yyval) = (yyvsp[(2) - (3)]); }
    break;

  case 109:

/* Line 1803 of yacc.c  */
#line 285 "tyran_script_parser.y"
    { (yyval) = tyran_parser_concat((yyvsp[(1) - (4)]), (yyvsp[(4) - (4)])); }
    break;

  case 113:

/* Line 1803 of yacc.c  */
#line 293 "tyran_script_parser.y"
    { (yyval) = tyran_parser_concat((yyvsp[(1) - (3)]), (yyvsp[(3) - (3)])); }
    break;

  case 114:

/* Line 1803 of yacc.c  */
#line 296 "tyran_script_parser.y"
    { (yyval) = tyran_parser_parens((yyvsp[(2) - (3)])); }
    break;

  case 115:

/* Line 1803 of yacc.c  */
#line 297 "tyran_script_parser.y"
    { (yyval) = tyran_parser_parens((yyvsp[(3) - (5)])); }
    break;

  case 116:

/* Line 1803 of yacc.c  */
#line 300 "tyran_script_parser.y"
    { (yyval) = tyran_parser_while((yyvsp[(2) - (2)])); }
    break;

  case 117:

/* Line 1803 of yacc.c  */
#line 303 "tyran_script_parser.y"
    { (yyval) = tyran_parser_while_condition((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); }
    break;

  case 118:

/* Line 1803 of yacc.c  */
#line 307 "tyran_script_parser.y"
    { (yyval) = tyran_parser_switch((yyvsp[(2) - (5)]), (yyvsp[(4) - (5)]), 0); }
    break;

  case 119:

/* Line 1803 of yacc.c  */
#line 308 "tyran_script_parser.y"
    { (yyval) = tyran_parser_switch((yyvsp[(2) - (7)]), (yyvsp[(4) - (7)]), (yyvsp[(6) - (7)])); }
    break;

  case 120:

/* Line 1803 of yacc.c  */
#line 309 "tyran_script_parser.y"
    { (yyval) = tyran_parser_switch((yyvsp[(2) - (4)]), (yyvsp[(4) - (4)]), 0); }
    break;

  case 121:

/* Line 1803 of yacc.c  */
#line 310 "tyran_script_parser.y"
    { (yyval) = tyran_parser_switch((yyvsp[(2) - (6)]), (yyvsp[(4) - (6)]), 0); }
    break;

  case 123:

/* Line 1803 of yacc.c  */
#line 314 "tyran_script_parser.y"
    { tyran_parser_concat((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); }
    break;

  case 124:

/* Line 1803 of yacc.c  */
#line 317 "tyran_script_parser.y"
    { tyran_parser_when((yyvsp[(2) - (3)]), (yyvsp[(3) - (3)])); }
    break;

  case 125:

/* Line 1803 of yacc.c  */
#line 318 "tyran_script_parser.y"
    { tyran_parser_when((yyvsp[(2) - (4)]), (yyvsp[(3) - (4)])); }
    break;

  case 126:

/* Line 1803 of yacc.c  */
#line 321 "tyran_script_parser.y"
    { (yyval) = tyran_parser_if((yyvsp[(2) - (3)]), (yyvsp[(3) - (3)])); }
    break;

  case 127:

/* Line 1803 of yacc.c  */
#line 322 "tyran_script_parser.y"
    {tyran_parser_if_else((yyvsp[(1) - (5)]), (yyvsp[(3) - (5)])); }
    break;

  case 129:

/* Line 1803 of yacc.c  */
#line 326 "tyran_script_parser.y"
    { tyran_parser_if_else((yyvsp[(1) - (3)]), (yyvsp[(3) - (3)])); }
    break;

  case 130:

/* Line 1803 of yacc.c  */
#line 327 "tyran_script_parser.y"
    {}
    break;

  case 131:

/* Line 1803 of yacc.c  */
#line 328 "tyran_script_parser.y"
    {}
    break;

  case 132:

/* Line 1803 of yacc.c  */
#line 331 "tyran_script_parser.y"
    { (yyval) = tyran_parser_operand((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); }
    break;

  case 133:

/* Line 1803 of yacc.c  */
#line 332 "tyran_script_parser.y"
    { (yyval) = tyran_parser_operand((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); }
    break;

  case 134:

/* Line 1803 of yacc.c  */
#line 333 "tyran_script_parser.y"
    { (yyval) = tyran_parser_operand((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); }
    break;

  case 135:

/* Line 1803 of yacc.c  */
#line 334 "tyran_script_parser.y"
    { (yyval) = tyran_parser_operand((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); }
    break;

  case 136:

/* Line 1803 of yacc.c  */
#line 335 "tyran_script_parser.y"
    { (yyval) = tyran_parser_operand((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); }
    break;

  case 137:

/* Line 1803 of yacc.c  */
#line 336 "tyran_script_parser.y"
    {(yyval) = tyran_parser_operand((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); }
    break;

  case 138:

/* Line 1803 of yacc.c  */
#line 337 "tyran_script_parser.y"
    {(yyval) = tyran_parser_operand((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); }
    break;

  case 139:

/* Line 1803 of yacc.c  */
#line 338 "tyran_script_parser.y"
    {(yyval) = tyran_parser_operand((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); }
    break;

  case 140:

/* Line 1803 of yacc.c  */
#line 339 "tyran_script_parser.y"
    { (yyval) = tyran_parser_operand_binary('+', (yyvsp[(1) - (3)]), (yyvsp[(3) - (3)])); }
    break;

  case 141:

/* Line 1803 of yacc.c  */
#line 340 "tyran_script_parser.y"
    { (yyval) = tyran_parser_operand_binary('-', (yyvsp[(1) - (3)]), (yyvsp[(3) - (3)])); }
    break;

  case 142:

/* Line 1803 of yacc.c  */
#line 341 "tyran_script_parser.y"
    { (yyval) = tyran_parser_operand_binary('*', (yyvsp[(1) - (3)]), (yyvsp[(3) - (3)])); }
    break;

  case 143:

/* Line 1803 of yacc.c  */
#line 342 "tyran_script_parser.y"
    { (yyval) = tyran_parser_operand_binary('/', (yyvsp[(1) - (3)]), (yyvsp[(3) - (3)])); }
    break;

  case 144:

/* Line 1803 of yacc.c  */
#line 343 "tyran_script_parser.y"
    { (yyval) = tyran_parser_compound_assignment((yyvsp[(1) - (3)]), (yyvsp[(3) - (3)]), (yyvsp[(2) - (3)])); }
    break;

  case 145:

/* Line 1803 of yacc.c  */
#line 344 "tyran_script_parser.y"
    {(yyval) = tyran_parser_compound_assignment((yyvsp[(1) - (5)]), (yyvsp[(3) - (5)]), (yyvsp[(2) - (5)])); }
    break;

  case 146:

/* Line 1803 of yacc.c  */
#line 345 "tyran_script_parser.y"
    { tyran_parser_extends((yyvsp[(1) - (3)]), (yyvsp[(3) - (3)])); }
    break;



/* Line 1803 of yacc.c  */
#line 2663 "tyran_script_parser.tab.c"
      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
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
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (&yylloc, parser, YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (&yylloc, parser, yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }

  yyerror_range[1] = yylloc;

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
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

  /* Else will try to reuse lookahead token after shifting the error
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

  yyerror_range[1] = yylsp[1-yylen];
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
      if (!yypact_value_is_default (yyn))
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

      yyerror_range[1] = *yylsp;
      yydestruct ("Error: popping",
		  yystos[yystate], yyvsp, yylsp, parser);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  *++yyvsp = yylval;

  yyerror_range[2] = yylloc;
  /* Using YYLLOC is tempting, but would change the location of
     the lookahead.  YYLOC is available though.  */
  YYLLOC_DEFAULT (yyloc, yyerror_range, 2);
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

#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (&yylloc, parser, YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval, &yylloc, parser);
    }
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



/* Line 2049 of yacc.c  */
#line 346 "tyran_script_parser.y"


