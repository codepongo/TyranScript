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



/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     TYRAN_TOKEN_STRING = 258,
     TYRAN_TOKEN_IDENTIFIER = 259,
     TYRAN_TOKEN_IF = 260,
     TYRAN_TOKEN_ELSE = 261,
     TYRAN_TOKEN_FOR = 262,
     TYRAN_TOKEN_IN = 263,
     TYRAN_TOKEN_WHILE = 264,
     TYRAN_TOKEN_DO = 265,
     TYRAN_TOKEN_SWITCH = 266,
     TYRAN_TOKEN_CONTINUE = 267,
     TYRAN_TOKEN_CASE = 268,
     TYRAN_TOKEN_DEFAULT = 269,
     TYRAN_TOKEN_BREAK = 270,
     TYRAN_TOKEN_FUNCTION = 271,
     TYRAN_TOKEN_LOCAL = 272,
     TYRAN_TOKEN_RETURN = 273,
     TYRAN_TOKEN_NEW = 274,
     TYRAN_TOKEN_DELETE = 275,
     TYRAN_TOKEN_ARGUMENTS = 276,
     TYRAN_TOKEN_UNDEFINED = 277,
     TYRAN_TOKEN_NUMBER = 278,
     TYRAN_TOKEN_TRUE = 279,
     TYRAN_TOKEN_FALSE = 280,
     TYRAN_TOKEN_THIS = 281,
     TYRAN_TOKEN_NULL = 282,
     TYRAN_TOKEN_BRACKET_RIGHT = 283,
     TYRAN_TOKEN_PARENTHESES_RIGHT = 284,
     TYRAN_TOKEN_EOL = 285,
     TYRAN_TOKEN_BLOCK_START = 286,
     TYRAN_TOKEN_BLOCK_END = 287,
     TYRAN_TOKEN_COMMA = 288,
     comma_precedence = 289,
     TYRAN_TOKEN_DIVIDE_ASSIGNMENT = 290,
     TYRAN_TOKEN_BITWISE_XOR_ASSIGNMENT = 291,
     TYRAN_TOKEN_BITWISE_OR_ASSIGNMENT = 292,
     TYRAN_TOKEN_BITWISE_AND_ASSIGNMENT = 293,
     TYRAN_TOKEN_UNSIGNED_SHIFT_RIGHT_ASSIGNMENT = 294,
     TYRAN_TOKEN_SHIFT_RIGHT_ASSIGNMENT = 295,
     TYRAN_TOKEN_SHIFT_LEFT_ASSIGNMENT = 296,
     TYRAN_TOKEN_MODULUS_ASSIGNMENT = 297,
     TYRAN_TOKEN_MULTIPLY_ASSIGNMENT = 298,
     TYRAN_TOKEN_SUBTRACT_ASSIGNMENT = 299,
     TYRAN_TOKEN_ADD_ASSIGNMENT = 300,
     TYRAN_TOKEN_ASSIGNMENT = 301,
     TYRAN_TOKEN_COLON = 302,
     TYRAN_TOKEN_QUESTION_MARK = 303,
     TYRAN_TOKEN_OR = 304,
     TYRAN_TOKEN_AND = 305,
     TYRAN_TOKEN_BITWISE_OR = 306,
     TYRAN_TOKEN_BITWISE_XOR = 307,
     TYRAN_TOKEN_BITWISE_AND = 308,
     TYRAN_TOKEN_STRICT_NOT_EQUAL = 309,
     TYRAN_TOKEN_STRICT_EQUAL = 310,
     TYRAN_TOKEN_NOT_EQUAL = 311,
     TYRAN_TOKEN_EQUAL = 312,
     TYRAN_TOKEN_GREATER_EQUAL = 313,
     TYRAN_TOKEN_LESS_EQUAL = 314,
     TYRAN_TOKEN_LESS = 315,
     TYRAN_TOKEN_GREATER = 316,
     TYRAN_TOKEN_SHIFT_RIGHT_UNSIGNED = 317,
     TYRAN_TOKEN_SHIFT_RIGHT = 318,
     TYRAN_TOKEN_SHIFT_LEFT = 319,
     TYRAN_TOKEN_SUBTRACT = 320,
     TYRAN_TOKEN_ADD = 321,
     TYRAN_TOKEN_MODULUS = 322,
     TYRAN_TOKEN_DIVIDE = 323,
     TYRAN_TOKEN_MULTIPLY = 324,
     TYRAN_TOKEN_BITWISE_NOT = 325,
     TYRAN_TOKEN_DECREASE = 326,
     TYRAN_TOKEN_INCREASE = 327,
     TYRAN_TOKEN_NOT = 328,
     TYRAN_TOKEN_NEGATIVE = 329,
     TYRAN_TOKEN_PARENTHESES_LEFT = 330,
     TYRAN_TOKEN_BRACKET_LEFT = 331,
     TYRAN_TOKEN_MEMBER = 332,
     function_precedence = 333
   };
#endif
/* Tokens.  */
#define TYRAN_TOKEN_STRING 258
#define TYRAN_TOKEN_IDENTIFIER 259
#define TYRAN_TOKEN_IF 260
#define TYRAN_TOKEN_ELSE 261
#define TYRAN_TOKEN_FOR 262
#define TYRAN_TOKEN_IN 263
#define TYRAN_TOKEN_WHILE 264
#define TYRAN_TOKEN_DO 265
#define TYRAN_TOKEN_SWITCH 266
#define TYRAN_TOKEN_CONTINUE 267
#define TYRAN_TOKEN_CASE 268
#define TYRAN_TOKEN_DEFAULT 269
#define TYRAN_TOKEN_BREAK 270
#define TYRAN_TOKEN_FUNCTION 271
#define TYRAN_TOKEN_LOCAL 272
#define TYRAN_TOKEN_RETURN 273
#define TYRAN_TOKEN_NEW 274
#define TYRAN_TOKEN_DELETE 275
#define TYRAN_TOKEN_ARGUMENTS 276
#define TYRAN_TOKEN_UNDEFINED 277
#define TYRAN_TOKEN_NUMBER 278
#define TYRAN_TOKEN_TRUE 279
#define TYRAN_TOKEN_FALSE 280
#define TYRAN_TOKEN_THIS 281
#define TYRAN_TOKEN_NULL 282
#define TYRAN_TOKEN_BRACKET_RIGHT 283
#define TYRAN_TOKEN_PARENTHESES_RIGHT 284
#define TYRAN_TOKEN_EOL 285
#define TYRAN_TOKEN_BLOCK_START 286
#define TYRAN_TOKEN_BLOCK_END 287
#define TYRAN_TOKEN_COMMA 288
#define comma_precedence 289
#define TYRAN_TOKEN_DIVIDE_ASSIGNMENT 290
#define TYRAN_TOKEN_BITWISE_XOR_ASSIGNMENT 291
#define TYRAN_TOKEN_BITWISE_OR_ASSIGNMENT 292
#define TYRAN_TOKEN_BITWISE_AND_ASSIGNMENT 293
#define TYRAN_TOKEN_UNSIGNED_SHIFT_RIGHT_ASSIGNMENT 294
#define TYRAN_TOKEN_SHIFT_RIGHT_ASSIGNMENT 295
#define TYRAN_TOKEN_SHIFT_LEFT_ASSIGNMENT 296
#define TYRAN_TOKEN_MODULUS_ASSIGNMENT 297
#define TYRAN_TOKEN_MULTIPLY_ASSIGNMENT 298
#define TYRAN_TOKEN_SUBTRACT_ASSIGNMENT 299
#define TYRAN_TOKEN_ADD_ASSIGNMENT 300
#define TYRAN_TOKEN_ASSIGNMENT 301
#define TYRAN_TOKEN_COLON 302
#define TYRAN_TOKEN_QUESTION_MARK 303
#define TYRAN_TOKEN_OR 304
#define TYRAN_TOKEN_AND 305
#define TYRAN_TOKEN_BITWISE_OR 306
#define TYRAN_TOKEN_BITWISE_XOR 307
#define TYRAN_TOKEN_BITWISE_AND 308
#define TYRAN_TOKEN_STRICT_NOT_EQUAL 309
#define TYRAN_TOKEN_STRICT_EQUAL 310
#define TYRAN_TOKEN_NOT_EQUAL 311
#define TYRAN_TOKEN_EQUAL 312
#define TYRAN_TOKEN_GREATER_EQUAL 313
#define TYRAN_TOKEN_LESS_EQUAL 314
#define TYRAN_TOKEN_LESS 315
#define TYRAN_TOKEN_GREATER 316
#define TYRAN_TOKEN_SHIFT_RIGHT_UNSIGNED 317
#define TYRAN_TOKEN_SHIFT_RIGHT 318
#define TYRAN_TOKEN_SHIFT_LEFT 319
#define TYRAN_TOKEN_SUBTRACT 320
#define TYRAN_TOKEN_ADD 321
#define TYRAN_TOKEN_MODULUS 322
#define TYRAN_TOKEN_DIVIDE 323
#define TYRAN_TOKEN_MULTIPLY 324
#define TYRAN_TOKEN_BITWISE_NOT 325
#define TYRAN_TOKEN_DECREASE 326
#define TYRAN_TOKEN_INCREASE 327
#define TYRAN_TOKEN_NOT 328
#define TYRAN_TOKEN_NEGATIVE 329
#define TYRAN_TOKEN_PARENTHESES_LEFT 330
#define TYRAN_TOKEN_BRACKET_LEFT 331
#define TYRAN_TOKEN_MEMBER 332
#define function_precedence 333




/* Copy the first part of user declarations.  */
#line 1 "tyran_parser.y"

#include <tyranscript/tyran_api.h>
#include "tyran_parser_includes.h"

/* -------------- Variable ------------- */

struct tyran_variable_info
{
	tyran_string* variable_name;
	struct tyran_opcodes* lvalue;
	struct tyran_opcodes* local;
};

struct tyran_variable_info* tyran_variable_info_new(tyran_string* variable_name, struct tyran_opcodes* local, struct tyran_opcodes* lvalue)
{
	struct tyran_variable_info* r = (struct tyran_variable_info*)malloc(sizeof(struct tyran_variable_info));
	r->variable_name = variable_name;
	r->local = local;
	r->lvalue = lvalue;
	return r;
}

/* -------------- Arguments ------------- */
typedef struct tyran_argument_list
{
	const tyran_string* argument_name;
	struct tyran_argument_list* tail;
	struct tyran_argument_list* next;
} tyran_argument_list;

static tyran_argument_list* tyran_argument_list_new(const tyran_string* name) 
{
	tyran_argument_list* a = (tyran_argument_list*) TYRAN_CALLOC(tyran_argument_list);
	a->argument_name = tyran_string_strdup(name);
	a->tail = a;
	return a;
}

static tyran_argument_list* tyran_argument_list_add(tyran_argument_list* a, const tyran_string* name)
{
	tyran_argument_list* b = (tyran_argument_list*) TYRAN_CALLOC(tyran_argument_list);
	b->argument_name = tyran_string_strdup(name);
	a->tail->next = b;
	a->tail = b;
	return a;
}

/* -------------- Switch ------------- */
typedef struct tyran_switch_info
{
	struct tyran_opcodes* expression;
	struct tyran_opcodes* statements;
	int is_default;
} tyran_switch_info;

struct tyran_switch_info* tyran_switch_info_new(struct tyran_opcodes* expression, struct tyran_opcodes* statements, int is_default)
{
	tyran_switch_info *r = (tyran_switch_info*) TYRAN_CALLOC(tyran_switch_info);
	r->expression = expression;
	r->statements = statements;
	r->is_default = is_default;
	return r;
}

typedef struct tyran_case_info
{
	tyran_switch_info* switch_info;
	struct tyran_case_info* next;
	struct tyran_case_info* tail;
	int offset;
} tyran_case_info;

static tyran_case_info* tyran_case_info_new(tyran_switch_info* switch_info)
{
	tyran_case_info *a = (tyran_case_info*) TYRAN_CALLOC(tyran_case_info);
	a->switch_info = switch_info;
	a->tail = a;
	return a;
}

static tyran_case_info* tyran_case_info_add(tyran_case_info* a, tyran_switch_info* switch_info)
{
	tyran_case_info* b = (tyran_case_info*) TYRAN_CALLOC(tyran_case_info);
	b->switch_info = switch_info;
	a->tail->next = b;
	a->tail = b;
	return a;
}

/* -------------- Helper functions ------------- */
static struct tyran_opcodes* tyran_operator_assign(struct tyran_opcodes* lvalue, struct tyran_opcodes* op, struct tyran_opcodes* opcode)
{
	struct tyran_opcodes* ret;

	if (lvalue->lvalue_flag == tyran_assign_variable)
	{
		ret = tyran_opcodes_merge3(lvalue, tyran_opcodes_merge3(tyran_opcodes_insert_push_top(), op, opcode), tyran_opcodes_insert_assign(tyran_assign_variable));
	}
	else
	{
		ret = tyran_opcodes_merge3(lvalue, tyran_opcodes_merge4(tyran_opcodes_insert_push_top2(), tyran_opcodes_insert_subscript(1), op, opcode), tyran_opcodes_insert_assign(tyran_assign_object));
	}

	return ret;
}

static struct  tyran_opcodes* make_forin(struct tyran_opcodes* lvalue, struct tyran_opcodes* expression, struct tyran_opcodes* statements)
{
	struct tyran_opcodes* init = tyran_opcodes_merge(expression, tyran_opcodes_insert_key());
	struct tyran_opcodes* condition = tyran_opcodes_merge3(lvalue, tyran_opcodes_insert_next(), tyran_opcodes_insert_jump_false_pop(statements->code_len + 2));
	struct tyran_opcodes* stat_jmp = tyran_opcodes_insert_jump(-(condition->code_len + statements->code_len));
	tyran_opcodes_resolve(statements, 1, 0, 2);
	return tyran_opcodes_merge3(tyran_opcodes_merge(init, condition), tyran_opcodes_merge(statements, stat_jmp), tyran_opcodes_insert_pop(2));
}



/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
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
#line 391 "tyran_parser.c"

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
#define YYFINAL  87
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   1471

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  79
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  35
/* YYNRULES -- Number of rules.  */
#define YYNRULES  143
/* YYNRULES -- Number of states.  */
#define YYNSTATES  287

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   333

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
      75,    76,    77,    78
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     4,     6,     9,    11,    13,    16,    18,
      21,    25,    28,    31,    35,    38,    42,    44,    46,    48,
      50,    52,    54,    56,    58,    60,    63,    66,    69,    72,
      74,    76,    79,    82,    86,    90,    94,    98,   102,   106,
     110,   114,   118,   122,   126,   130,   134,   138,   141,   145,
     149,   153,   157,   161,   165,   169,   173,   177,   181,   185,
     189,   193,   197,   201,   205,   209,   213,   217,   222,   226,
     229,   232,   237,   240,   246,   252,   260,   266,   272,   274,
     276,   278,   280,   282,   284,   286,   288,   290,   295,   299,
     301,   303,   304,   306,   308,   312,   314,   318,   320,   324,
     330,   338,   340,   343,   352,   360,   362,   365,   369,   370,
     372,   373,   375,   377,   383,   390,   397,   405,   407,   410,
     415,   419,   425,   428,   434,   441,   442,   444,   446,   450,
     454,   457,   464,   472,   479,   484,   488,   489,   491,   495,
     499,   503,   507,   510
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      80,     0,    -1,    -1,    81,    -1,    81,    83,    -1,    83,
      -1,    82,    -1,    81,    82,    -1,    30,    -1,    83,    30,
      -1,    31,    81,    32,    -1,    15,    30,    -1,    12,    30,
      -1,    18,    83,    30,    -1,    18,    30,    -1,    17,    88,
      30,    -1,    90,    -1,   113,    -1,   102,    -1,    92,    -1,
      97,    -1,    98,    -1,    99,    -1,    84,    -1,    85,    -1,
      85,    72,    -1,    85,    71,    -1,    72,    85,    -1,    71,
      85,    -1,   108,    -1,   104,    -1,    65,    83,    -1,    73,
      83,    -1,    83,    69,    83,    -1,    83,    68,    83,    -1,
      83,    67,    83,    -1,    83,    66,    83,    -1,    83,    65,
      83,    -1,    75,    83,    29,    -1,    83,    50,    83,    -1,
      83,    49,    83,    -1,    83,    60,    83,    -1,    83,    61,
      83,    -1,    83,    59,    83,    -1,    83,    58,    83,    -1,
      83,    57,    83,    -1,    83,    56,    83,    -1,    70,    83,
      -1,    83,    53,    83,    -1,    83,    51,    83,    -1,    83,
      52,    83,    -1,    83,    64,    83,    -1,    83,    63,    83,
      -1,    83,    62,    83,    -1,    85,    46,    83,    -1,    85,
      45,    83,    -1,    85,    44,    83,    -1,    85,    43,    83,
      -1,    85,    42,    83,    -1,    85,    41,    83,    -1,    85,
      40,    83,    -1,    85,    39,    83,    -1,    85,    38,    83,
      -1,    85,    37,    83,    -1,    85,    36,    83,    -1,    85,
      35,    83,    -1,    83,    33,    83,    -1,    83,    76,    83,
      28,    -1,    83,    77,     4,    -1,    19,    84,    -1,    19,
      85,    -1,    19,    75,    83,    29,    -1,    19,   104,    -1,
      19,    84,    75,    86,    29,    -1,    19,    85,    75,    86,
      29,    -1,    19,    75,    83,    29,    75,    86,    29,    -1,
      19,   104,    75,    86,    29,    -1,    83,    48,    83,    47,
      83,    -1,     3,    -1,   109,    -1,   112,    -1,    22,    -1,
      23,    -1,    24,    -1,    25,    -1,    27,    -1,     4,    -1,
      85,    76,    83,    28,    -1,    85,    77,     4,    -1,    21,
      -1,    26,    -1,    -1,    87,    -1,    83,    -1,    87,    33,
      83,    -1,    89,    -1,    88,    33,    89,    -1,     4,    -1,
       4,    46,    83,    -1,     5,    75,    83,    29,    91,    -1,
       5,    75,    83,    29,    91,     6,    91,    -1,    82,    -1,
      31,    32,    -1,     7,    75,    93,    94,    30,    95,    29,
      91,    -1,     7,    75,    96,     8,    83,    29,    91,    -1,
      30,    -1,    83,    30,    -1,    17,    88,    30,    -1,    -1,
      83,    -1,    -1,    83,    -1,    85,    -1,     9,    75,    83,
      29,    91,    -1,    10,    91,     9,    75,    83,    29,    -1,
      11,    75,    83,    29,    31,    32,    -1,    11,    75,    83,
      29,    31,   100,    32,    -1,   101,    -1,   100,   101,    -1,
      13,    83,    47,    81,    -1,    14,    47,    81,    -1,   103,
      75,   105,    29,   107,    -1,    16,     4,    -1,    16,    75,
     105,    29,   107,    -1,    16,     4,    75,   105,    29,   107,
      -1,    -1,   106,    -1,     4,    -1,   106,    33,     4,    -1,
      31,    81,    32,    -1,    31,    32,    -1,    83,    77,     4,
      75,    86,    29,    -1,    83,    76,    83,    28,    75,    86,
      29,    -1,    75,    83,    29,    75,    86,    29,    -1,    85,
      75,    86,    29,    -1,    31,   110,    32,    -1,    -1,   111,
      -1,   110,    33,   111,    -1,     4,    47,    83,    -1,     3,
      47,    83,    -1,    76,    87,    28,    -1,    76,    28,    -1,
      20,    85,    30,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   192,   192,   195,   198,   201,   209,   212,   218,   220,
     223,   226,   229,   232,   235,   238,   241,   244,   247,   250,
     253,   256,   259,   267,   270,   278,   285,   292,   299,   306,
     309,   312,   315,   318,   321,   324,   327,   330,   333,   336,
     340,   344,   347,   350,   353,   356,   359,   362,   365,   368,
     371,   374,   377,   380,   383,   386,   389,   392,   395,   398,
     401,   404,   407,   410,   413,   416,   419,   422,   425,   428,
     431,   438,   441,   444,   449,   461,   466,   471,   478,   481,
     484,   487,   490,   493,   496,   499,   505,   510,   517,   524,
     528,   534,   537,   543,   547,   557,   560,   566,   571,   579,
     583,   592,   595,   601,   611,   630,   633,   636,   641,   644,
     649,   652,   658,   667,   677,   686,   689,   729,   732,   738,
     741,   749,   757,   764,   768,   774,   778,   791,   794,   800,
     803,   808,   814,   820,   825,   841,   846,   849,   852,   860,
     863,   869,   872,   878
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "TYRAN_TOKEN_STRING",
  "TYRAN_TOKEN_IDENTIFIER", "TYRAN_TOKEN_IF", "TYRAN_TOKEN_ELSE",
  "TYRAN_TOKEN_FOR", "TYRAN_TOKEN_IN", "TYRAN_TOKEN_WHILE",
  "TYRAN_TOKEN_DO", "TYRAN_TOKEN_SWITCH", "TYRAN_TOKEN_CONTINUE",
  "TYRAN_TOKEN_CASE", "TYRAN_TOKEN_DEFAULT", "TYRAN_TOKEN_BREAK",
  "TYRAN_TOKEN_FUNCTION", "TYRAN_TOKEN_LOCAL", "TYRAN_TOKEN_RETURN",
  "TYRAN_TOKEN_NEW", "TYRAN_TOKEN_DELETE", "TYRAN_TOKEN_ARGUMENTS",
  "TYRAN_TOKEN_UNDEFINED", "TYRAN_TOKEN_NUMBER", "TYRAN_TOKEN_TRUE",
  "TYRAN_TOKEN_FALSE", "TYRAN_TOKEN_THIS", "TYRAN_TOKEN_NULL",
  "TYRAN_TOKEN_BRACKET_RIGHT", "TYRAN_TOKEN_PARENTHESES_RIGHT",
  "TYRAN_TOKEN_EOL", "TYRAN_TOKEN_BLOCK_START", "TYRAN_TOKEN_BLOCK_END",
  "TYRAN_TOKEN_COMMA", "comma_precedence", "TYRAN_TOKEN_DIVIDE_ASSIGNMENT",
  "TYRAN_TOKEN_BITWISE_XOR_ASSIGNMENT",
  "TYRAN_TOKEN_BITWISE_OR_ASSIGNMENT",
  "TYRAN_TOKEN_BITWISE_AND_ASSIGNMENT",
  "TYRAN_TOKEN_UNSIGNED_SHIFT_RIGHT_ASSIGNMENT",
  "TYRAN_TOKEN_SHIFT_RIGHT_ASSIGNMENT",
  "TYRAN_TOKEN_SHIFT_LEFT_ASSIGNMENT", "TYRAN_TOKEN_MODULUS_ASSIGNMENT",
  "TYRAN_TOKEN_MULTIPLY_ASSIGNMENT", "TYRAN_TOKEN_SUBTRACT_ASSIGNMENT",
  "TYRAN_TOKEN_ADD_ASSIGNMENT", "TYRAN_TOKEN_ASSIGNMENT",
  "TYRAN_TOKEN_COLON", "TYRAN_TOKEN_QUESTION_MARK", "TYRAN_TOKEN_OR",
  "TYRAN_TOKEN_AND", "TYRAN_TOKEN_BITWISE_OR", "TYRAN_TOKEN_BITWISE_XOR",
  "TYRAN_TOKEN_BITWISE_AND", "TYRAN_TOKEN_STRICT_NOT_EQUAL",
  "TYRAN_TOKEN_STRICT_EQUAL", "TYRAN_TOKEN_NOT_EQUAL", "TYRAN_TOKEN_EQUAL",
  "TYRAN_TOKEN_GREATER_EQUAL", "TYRAN_TOKEN_LESS_EQUAL",
  "TYRAN_TOKEN_LESS", "TYRAN_TOKEN_GREATER",
  "TYRAN_TOKEN_SHIFT_RIGHT_UNSIGNED", "TYRAN_TOKEN_SHIFT_RIGHT",
  "TYRAN_TOKEN_SHIFT_LEFT", "TYRAN_TOKEN_SUBTRACT", "TYRAN_TOKEN_ADD",
  "TYRAN_TOKEN_MODULUS", "TYRAN_TOKEN_DIVIDE", "TYRAN_TOKEN_MULTIPLY",
  "TYRAN_TOKEN_BITWISE_NOT", "TYRAN_TOKEN_DECREASE",
  "TYRAN_TOKEN_INCREASE", "TYRAN_TOKEN_NOT", "TYRAN_TOKEN_NEGATIVE",
  "TYRAN_TOKEN_PARENTHESES_LEFT", "TYRAN_TOKEN_BRACKET_LEFT",
  "TYRAN_TOKEN_MEMBER", "function_precedence", "$accept", "file",
  "statements", "statement", "expression", "value", "lvalue",
  "expression_list_optional", "expression_list", "variable_declarations",
  "variable_declaration", "if_statement", "statement_or_empty_block",
  "for_statement", "for_init", "for_condition", "expression_optional",
  "for_variable", "while_statement", "do_statement", "switch_statement",
  "cases", "case", "function_statement", "function_prefix",
  "function_expression", "arguments_optional", "arguments",
  "function_statement_block", "function_call_expression", "object",
  "object_items", "object_item", "array", "delete_statement", 0
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
     325,   326,   327,   328,   329,   330,   331,   332,   333
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    79,    80,    80,    80,    80,    81,    81,    82,    82,
      82,    82,    82,    82,    82,    82,    82,    82,    82,    82,
      82,    82,    82,    83,    83,    83,    83,    83,    83,    83,
      83,    83,    83,    83,    83,    83,    83,    83,    83,    83,
      83,    83,    83,    83,    83,    83,    83,    83,    83,    83,
      83,    83,    83,    83,    83,    83,    83,    83,    83,    83,
      83,    83,    83,    83,    83,    83,    83,    83,    83,    83,
      83,    83,    83,    83,    83,    83,    83,    83,    84,    84,
      84,    84,    84,    84,    84,    84,    85,    85,    85,    85,
      85,    86,    86,    87,    87,    88,    88,    89,    89,    90,
      90,    91,    91,    92,    92,    93,    93,    93,    94,    94,
      95,    95,    96,    97,    98,    99,    99,   100,   100,   101,
     101,   102,   103,   104,   104,   105,   105,   106,   106,   107,
     107,   108,   108,   108,   108,   109,   110,   110,   110,   111,
     111,   112,   112,   113
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     0,     1,     2,     1,     1,     2,     1,     2,
       3,     2,     2,     3,     2,     3,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     2,     2,     2,     2,     1,
       1,     2,     2,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     2,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     4,     3,     2,
       2,     4,     2,     5,     5,     7,     5,     5,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     4,     3,     1,
       1,     0,     1,     1,     3,     1,     3,     1,     3,     5,
       7,     1,     2,     8,     7,     1,     2,     3,     0,     1,
       0,     1,     1,     5,     6,     6,     7,     1,     2,     4,
       3,     5,     2,     5,     6,     0,     1,     1,     3,     3,
       2,     6,     7,     6,     4,     3,     0,     1,     3,     3,
       3,     3,     2,     3
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       2,    78,    86,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    89,    81,    82,    83,    84,
      90,    85,     8,   136,     0,     0,     0,     0,     0,     0,
       0,     0,     3,     6,     5,    23,    24,    16,    19,    20,
      21,    22,    18,     0,    30,    29,    79,    80,    17,     0,
       0,     0,   136,   101,     0,     0,     0,    12,    11,   122,
     125,    97,     0,    95,     0,    14,   136,     0,     0,    69,
      70,    72,     0,    78,    86,     0,     0,   137,    31,    47,
      28,    27,    32,     0,   142,    93,     0,     1,     7,     4,
       9,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    26,    25,    91,     0,
       0,   125,     0,     0,   105,     0,    24,   108,     0,     0,
     102,     0,     0,   125,   127,     0,   126,     0,    15,     0,
       0,     0,     0,    13,     0,    91,    91,    91,   143,     0,
       0,    10,   135,     0,    38,   141,     0,    66,     0,    40,
      39,    49,    50,    48,    46,    45,    44,    43,    41,    42,
      53,    52,    51,    37,    36,    35,    34,    33,     0,    68,
      65,    64,    63,    62,    61,    60,    59,    58,    57,    56,
      55,    54,     0,    92,     0,    88,     0,     0,     0,   106,
     109,     0,     0,     0,     0,     0,     0,     0,     0,    98,
      96,    71,     0,     0,     0,   140,   139,   138,    91,    94,
       0,    67,    91,   134,    87,     0,    99,   107,   110,     0,
     113,     0,     0,     0,     0,   123,   128,    91,    73,    74,
      76,     0,    77,    91,     0,   121,     0,   111,     0,     0,
     114,     0,     0,   115,     0,   117,   124,   130,     0,     0,
     133,     0,   131,   100,     0,   104,     0,     0,   116,   118,
     129,    75,   132,   103,     0,   120,   119
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    31,    75,    33,    54,    35,    36,   202,   203,    62,
      63,    37,    55,    38,   137,   211,   258,   138,    39,    40,
      41,   264,   265,    42,    43,    44,   145,   146,   245,    45,
      46,    76,    77,    47,    48
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -218
static const yytype_int16 yypact[] =
{
     490,  -218,  -218,   -39,   -37,   -18,   519,   -13,    -9,    21,
      -1,    65,   618,    61,    -2,  -218,  -218,  -218,  -218,  -218,
    -218,  -218,  -218,   593,   681,   681,    -2,    -2,   681,   681,
     651,    89,   490,  -218,  1079,  -218,  1298,  -218,  -218,  -218,
    -218,  -218,  -218,    16,  -218,  -218,  -218,  -218,  -218,   681,
     151,   681,   282,  -218,  1079,   109,   681,  -218,  -218,  -218,
     128,    95,   -22,  -218,     3,  -218,    28,  1119,   681,    68,
      18,    72,   -24,   101,   102,   312,    35,  -218,    63,    63,
      69,    69,    63,   793,  -218,  1328,    -8,  -218,  -218,  1079,
    -218,   681,   681,   681,   681,   681,   681,   681,   681,   681,
     681,   681,   681,   681,   681,   681,   681,   681,   681,   681,
     681,   681,   681,   147,   681,   681,   681,   681,   681,   681,
     681,   681,   681,   681,   681,   681,  -218,  -218,   681,   681,
     149,   128,   834,    65,  -218,  1159,     4,   681,   150,   875,
    -218,    82,   916,   128,  -218,   130,   133,   681,  -218,    65,
      88,   101,   102,  -218,   957,   681,   681,   681,  -218,   681,
     681,  -218,  -218,    28,    94,  -218,   681,  1328,  1196,  1295,
    1372,  1394,   303,   407,   509,   509,   668,   668,   668,   668,
     163,   163,   163,   -54,   -54,    63,    63,    63,   710,   104,
    1328,  1328,  1328,  1328,  1328,  1328,  1328,  1328,  1328,  1328,
    1328,  1328,   156,   153,   752,  -218,   159,   519,    33,  -218,
    1255,   161,   681,   519,   681,   158,   164,   167,   176,  1328,
    -218,   117,   165,   166,   171,  1328,  1328,  -218,   681,  1328,
     681,   124,   681,  -218,  -218,   167,   195,  -218,   681,   998,
    -218,  1039,    -4,   167,   386,  -218,  -218,   681,  -218,  -218,
    -218,   174,  1350,   681,   175,  -218,   519,  1255,   177,   519,
    -218,   681,   160,  -218,    58,  -218,  -218,  -218,   416,   180,
    -218,   181,  -218,  -218,   519,  -218,  1233,   490,  -218,  -218,
    -218,  -218,  -218,  -218,   490,   490,   490
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -218,  -218,     0,    -5,     5,   198,   170,   -97,   182,    80,
      66,  -218,   -69,  -218,  -218,  -218,  -218,  -218,  -218,  -218,
    -218,  -218,   -50,  -218,  -218,   205,  -127,  -218,  -217,  -218,
    -218,  -218,    62,  -218,  -218
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -113
static const yytype_int16 yytable[] =
{
      32,    53,     2,    59,   206,    34,   158,   150,   148,   261,
     262,   149,  -112,   109,   110,   111,   216,    67,   255,    15,
     165,    57,   112,   113,    20,   166,   266,    88,   263,    78,
      79,   151,   152,    82,    83,    85,    49,    89,    50,   114,
     115,   116,   117,   118,   119,   120,   121,   122,   123,   124,
     125,    58,   129,   130,   132,   135,   139,    51,   222,   223,
     224,   142,    56,   237,     1,     2,   149,   162,   163,    61,
      88,   261,   262,   154,    60,   126,   127,    64,    60,   128,
     129,   130,    15,    16,    17,    18,    19,    20,    21,    87,
     278,   131,    66,   156,   129,   130,   167,   168,   169,   170,
     171,   172,   173,   174,   175,   176,   177,   178,   179,   180,
     181,   182,   183,   184,   185,   186,   187,   188,   141,   190,
     191,   192,   193,   194,   195,   196,   197,   198,   199,   200,
     201,   251,   144,    85,   204,   254,    68,    30,   236,   112,
     113,   147,   210,   155,   240,   129,   130,   157,   159,   160,
     269,   189,   219,   205,     1,     2,   271,   214,   212,   217,
      85,    85,    85,   143,   225,   226,   218,    64,   133,   228,
      13,   229,    15,    16,    17,    18,    19,    20,    21,   232,
     246,   134,    66,    70,    72,   233,   166,   273,   235,   242,
     275,   238,   247,   243,   248,   249,    80,    81,   244,   253,
     250,   256,    53,   270,   272,   283,   274,   277,    53,   281,
     282,    69,    86,   208,   279,   220,    24,   239,    71,   241,
     136,    25,    26,    27,    28,   227,    29,    30,   107,   108,
     109,   110,   111,    85,     0,   252,     0,    85,     0,   112,
     113,     0,     0,   257,   268,     0,     0,     0,     0,     0,
       0,    53,    85,     0,    53,     0,     0,     0,    85,     0,
       0,     0,     0,    88,     0,     0,   276,     0,     0,    53,
       0,     0,     0,     0,     0,     0,     0,   285,     0,     0,
      88,    88,     0,     0,   286,    73,    74,     3,     0,     4,
       0,     5,     6,     7,     8,     0,     0,     9,    10,    11,
      12,    13,    14,    15,    16,    17,    18,    19,    20,    21,
       0,     0,    22,    23,   140,     1,     2,     3,     0,     4,
       0,     5,     6,     7,     8,     0,     0,     9,    10,    11,
      12,    13,    14,    15,    16,    17,    18,    19,    20,    21,
       0,     0,    22,    23,   161,     0,     0,    24,     0,     0,
       0,     0,    25,    26,    27,    28,    97,    29,    30,    98,
      99,   100,   101,   102,   103,   104,   105,   106,   107,   108,
     109,   110,   111,     0,     0,     0,     0,    24,     0,   112,
     113,     0,    25,    26,    27,    28,     0,    29,    30,     1,
       2,     3,     0,     4,     0,     5,     6,     7,     8,     0,
       0,     9,    10,    11,    12,    13,    14,    15,    16,    17,
      18,    19,    20,    21,     0,     0,    22,    23,   267,     1,
       2,     3,     0,     4,     0,     5,     6,     7,     8,     0,
       0,     9,    10,    11,    12,    13,    14,    15,    16,    17,
      18,    19,    20,    21,     0,     0,    22,    23,   280,     0,
       0,    24,     0,     0,     0,     0,    25,    26,    27,    28,
       0,    29,    30,    98,    99,   100,   101,   102,   103,   104,
     105,   106,   107,   108,   109,   110,   111,     0,     0,     0,
       0,    24,     0,   112,   113,     0,    25,    26,    27,    28,
       0,    29,    30,     1,     2,     3,     0,     4,     0,     5,
       6,     7,     8,     0,     0,     9,    10,    11,    12,    13,
      14,    15,    16,    17,    18,    19,    20,    21,     0,     0,
      22,    23,     1,     2,     3,     0,     4,     0,     5,     6,
       7,     8,     0,     0,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,     0,     0,    22,
      52,     0,     0,     0,     0,    24,     0,     0,     0,     0,
      25,    26,    27,    28,     0,    29,    30,   100,   101,   102,
     103,   104,   105,   106,   107,   108,   109,   110,   111,     0,
       0,     0,     0,     0,    24,   112,   113,     0,     0,    25,
      26,    27,    28,     0,    29,    30,    73,    74,     3,     0,
       4,     0,     5,     6,     7,     8,     0,     0,     9,    10,
      11,    12,    13,    14,    15,    16,    17,    18,    19,    20,
      21,     1,     2,    22,    23,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    64,     0,     0,    13,     0,    15,
      16,    17,    18,    19,    20,    21,     0,     0,    65,    66,
       0,     0,     0,     0,     1,     2,     0,     0,    24,     0,
       0,     0,     0,    25,    26,    27,    28,    64,    29,    30,
      13,     0,    15,    16,    17,    18,    19,    20,    21,    84,
       0,     0,    66,    24,     1,     2,     0,     0,    25,    26,
      27,    28,     0,    29,    30,     0,     0,    64,     0,     0,
      13,     0,    15,    16,    17,    18,    19,    20,    21,     0,
       0,     0,    66,     0,     0,     0,    24,     0,     0,     0,
       0,    25,    26,    27,    28,     0,    29,    30,     0,     0,
     104,   105,   106,   107,   108,   109,   110,   111,   231,     0,
       0,     0,     0,    91,   112,   113,    24,     0,     0,     0,
       0,    25,    26,    27,    28,     0,    29,    30,    92,    93,
      94,    95,    96,    97,     0,     0,    98,    99,   100,   101,
     102,   103,   104,   105,   106,   107,   108,   109,   110,   111,
     234,     0,     0,     0,     0,    91,   112,   113,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      92,    93,    94,    95,    96,    97,     0,     0,    98,    99,
     100,   101,   102,   103,   104,   105,   106,   107,   108,   109,
     110,   111,   164,     0,     0,     0,    91,     0,   112,   113,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    92,    93,    94,    95,    96,    97,     0,     0,    98,
      99,   100,   101,   102,   103,   104,   105,   106,   107,   108,
     109,   110,   111,   207,     0,     0,     0,    91,     0,   112,
     113,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    92,    93,    94,    95,    96,    97,     0,     0,
      98,    99,   100,   101,   102,   103,   104,   105,   106,   107,
     108,   109,   110,   111,   213,     0,     0,     0,    91,     0,
     112,   113,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    92,    93,    94,    95,    96,    97,     0,
       0,    98,    99,   100,   101,   102,   103,   104,   105,   106,
     107,   108,   109,   110,   111,   215,     0,     0,     0,    91,
       0,   112,   113,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    92,    93,    94,    95,    96,    97,
       0,     0,    98,    99,   100,   101,   102,   103,   104,   105,
     106,   107,   108,   109,   110,   111,   221,     0,     0,     0,
      91,     0,   112,   113,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    92,    93,    94,    95,    96,
      97,     0,     0,    98,    99,   100,   101,   102,   103,   104,
     105,   106,   107,   108,   109,   110,   111,   259,     0,     0,
       0,    91,     0,   112,   113,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    92,    93,    94,    95,
      96,    97,     0,     0,    98,    99,   100,   101,   102,   103,
     104,   105,   106,   107,   108,   109,   110,   111,   260,     0,
       0,     0,    91,     0,   112,   113,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    92,    93,    94,
      95,    96,    97,     0,     0,    98,    99,   100,   101,   102,
     103,   104,   105,   106,   107,   108,   109,   110,   111,    90,
       0,     0,    91,     0,     0,   112,   113,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    92,    93,    94,
      95,    96,    97,     0,     0,    98,    99,   100,   101,   102,
     103,   104,   105,   106,   107,   108,   109,   110,   111,   153,
       0,     0,    91,     0,     0,   112,   113,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    92,    93,    94,
      95,    96,    97,     0,     0,    98,    99,   100,   101,   102,
     103,   104,   105,   106,   107,   108,   109,   110,   111,   209,
       0,     0,    91,     0,     0,   112,   113,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    92,    93,    94,
      95,    96,    97,     0,     0,    98,    99,   100,   101,   102,
     103,   104,   105,   106,   107,   108,   109,   110,   111,    91,
       0,     0,     0,     0,     0,   112,   113,     0,     0,     0,
       0,     0,     0,   230,    92,    93,    94,    95,    96,    97,
       0,     0,    98,    99,   100,   101,   102,   103,   104,   105,
     106,   107,   108,   109,   110,   111,    91,     0,     0,     0,
       0,     0,   112,   113,     0,     0,     0,     0,     0,     0,
     284,    92,    93,    94,    95,    96,    97,     0,    91,    98,
      99,   100,   101,   102,   103,   104,   105,   106,   107,   108,
     109,   110,   111,    92,    93,    94,    95,    96,    97,   112,
     113,    98,    99,   100,   101,   102,   103,   104,   105,   106,
     107,   108,   109,   110,   111,     0,     0,     0,     0,     0,
       0,   112,   113,   114,   115,   116,   117,   118,   119,   120,
     121,   122,   123,   124,   125,    94,    95,    96,    97,     0,
       0,    98,    99,   100,   101,   102,   103,   104,   105,   106,
     107,   108,   109,   110,   111,     0,     0,     0,     0,   126,
     127,   112,   113,   128,   129,   130,    92,    93,    94,    95,
      96,    97,     0,     0,    98,    99,   100,   101,   102,   103,
     104,   105,   106,   107,   108,   109,   110,   111,     0,    93,
      94,    95,    96,    97,   112,   113,    98,    99,   100,   101,
     102,   103,   104,   105,   106,   107,   108,   109,   110,   111,
       0,     0,     0,    95,    96,    97,   112,   113,    98,    99,
     100,   101,   102,   103,   104,   105,   106,   107,   108,   109,
     110,   111,     0,     0,     0,     0,    96,    97,   112,   113,
      98,    99,   100,   101,   102,   103,   104,   105,   106,   107,
     108,   109,   110,   111,     0,     0,     0,     0,     0,     0,
     112,   113
};

static const yytype_int16 yycheck[] =
{
       0,     6,     4,     4,   131,     0,    30,     4,    30,    13,
      14,    33,     8,    67,    68,    69,   143,    12,   235,    21,
      28,    30,    76,    77,    26,    33,   243,    32,    32,    24,
      25,     3,     4,    28,    29,    30,    75,    32,    75,    35,
      36,    37,    38,    39,    40,    41,    42,    43,    44,    45,
      46,    30,    76,    77,    49,    50,    51,    75,   155,   156,
     157,    56,    75,    30,     3,     4,    33,    32,    33,     4,
      75,    13,    14,    68,    75,    71,    72,    16,    75,    75,
      76,    77,    21,    22,    23,    24,    25,    26,    27,     0,
      32,    75,    31,    75,    76,    77,    91,    92,    93,    94,
      95,    96,    97,    98,    99,   100,   101,   102,   103,   104,
     105,   106,   107,   108,   109,   110,   111,   112,     9,   114,
     115,   116,   117,   118,   119,   120,   121,   122,   123,   124,
     125,   228,     4,   128,   129,   232,    75,    76,   207,    76,
      77,    46,   137,    75,   213,    76,    77,    75,    47,    47,
     247,     4,   147,     4,     3,     4,   253,    75,     8,    29,
     155,   156,   157,    75,   159,   160,    33,    16,    17,    75,
      19,   166,    21,    22,    23,    24,    25,    26,    27,    75,
       4,    30,    31,    13,    14,    29,    33,   256,    29,    31,
     259,    30,    75,    29,    29,    29,    26,    27,    31,    75,
      29,     6,   207,    29,    29,   274,    29,    47,   213,    29,
      29,    13,    30,   133,   264,   149,    65,   212,    13,   214,
      50,    70,    71,    72,    73,   163,    75,    76,    65,    66,
      67,    68,    69,   228,    -1,   230,    -1,   232,    -1,    76,
      77,    -1,    -1,   238,   244,    -1,    -1,    -1,    -1,    -1,
      -1,   256,   247,    -1,   259,    -1,    -1,    -1,   253,    -1,
      -1,    -1,    -1,   268,    -1,    -1,   261,    -1,    -1,   274,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   277,    -1,    -1,
     285,   286,    -1,    -1,   284,     3,     4,     5,    -1,     7,
      -1,     9,    10,    11,    12,    -1,    -1,    15,    16,    17,
      18,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      -1,    -1,    30,    31,    32,     3,     4,     5,    -1,     7,
      -1,     9,    10,    11,    12,    -1,    -1,    15,    16,    17,
      18,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      -1,    -1,    30,    31,    32,    -1,    -1,    65,    -1,    -1,
      -1,    -1,    70,    71,    72,    73,    53,    75,    76,    56,
      57,    58,    59,    60,    61,    62,    63,    64,    65,    66,
      67,    68,    69,    -1,    -1,    -1,    -1,    65,    -1,    76,
      77,    -1,    70,    71,    72,    73,    -1,    75,    76,     3,
       4,     5,    -1,     7,    -1,     9,    10,    11,    12,    -1,
      -1,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    -1,    -1,    30,    31,    32,     3,
       4,     5,    -1,     7,    -1,     9,    10,    11,    12,    -1,
      -1,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    -1,    -1,    30,    31,    32,    -1,
      -1,    65,    -1,    -1,    -1,    -1,    70,    71,    72,    73,
      -1,    75,    76,    56,    57,    58,    59,    60,    61,    62,
      63,    64,    65,    66,    67,    68,    69,    -1,    -1,    -1,
      -1,    65,    -1,    76,    77,    -1,    70,    71,    72,    73,
      -1,    75,    76,     3,     4,     5,    -1,     7,    -1,     9,
      10,    11,    12,    -1,    -1,    15,    16,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    -1,    -1,
      30,    31,     3,     4,     5,    -1,     7,    -1,     9,    10,
      11,    12,    -1,    -1,    15,    16,    17,    18,    19,    20,
      21,    22,    23,    24,    25,    26,    27,    -1,    -1,    30,
      31,    -1,    -1,    -1,    -1,    65,    -1,    -1,    -1,    -1,
      70,    71,    72,    73,    -1,    75,    76,    58,    59,    60,
      61,    62,    63,    64,    65,    66,    67,    68,    69,    -1,
      -1,    -1,    -1,    -1,    65,    76,    77,    -1,    -1,    70,
      71,    72,    73,    -1,    75,    76,     3,     4,     5,    -1,
       7,    -1,     9,    10,    11,    12,    -1,    -1,    15,    16,
      17,    18,    19,    20,    21,    22,    23,    24,    25,    26,
      27,     3,     4,    30,    31,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    16,    -1,    -1,    19,    -1,    21,
      22,    23,    24,    25,    26,    27,    -1,    -1,    30,    31,
      -1,    -1,    -1,    -1,     3,     4,    -1,    -1,    65,    -1,
      -1,    -1,    -1,    70,    71,    72,    73,    16,    75,    76,
      19,    -1,    21,    22,    23,    24,    25,    26,    27,    28,
      -1,    -1,    31,    65,     3,     4,    -1,    -1,    70,    71,
      72,    73,    -1,    75,    76,    -1,    -1,    16,    -1,    -1,
      19,    -1,    21,    22,    23,    24,    25,    26,    27,    -1,
      -1,    -1,    31,    -1,    -1,    -1,    65,    -1,    -1,    -1,
      -1,    70,    71,    72,    73,    -1,    75,    76,    -1,    -1,
      62,    63,    64,    65,    66,    67,    68,    69,    28,    -1,
      -1,    -1,    -1,    33,    76,    77,    65,    -1,    -1,    -1,
      -1,    70,    71,    72,    73,    -1,    75,    76,    48,    49,
      50,    51,    52,    53,    -1,    -1,    56,    57,    58,    59,
      60,    61,    62,    63,    64,    65,    66,    67,    68,    69,
      28,    -1,    -1,    -1,    -1,    33,    76,    77,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      48,    49,    50,    51,    52,    53,    -1,    -1,    56,    57,
      58,    59,    60,    61,    62,    63,    64,    65,    66,    67,
      68,    69,    29,    -1,    -1,    -1,    33,    -1,    76,    77,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    48,    49,    50,    51,    52,    53,    -1,    -1,    56,
      57,    58,    59,    60,    61,    62,    63,    64,    65,    66,
      67,    68,    69,    29,    -1,    -1,    -1,    33,    -1,    76,
      77,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    48,    49,    50,    51,    52,    53,    -1,    -1,
      56,    57,    58,    59,    60,    61,    62,    63,    64,    65,
      66,    67,    68,    69,    29,    -1,    -1,    -1,    33,    -1,
      76,    77,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    48,    49,    50,    51,    52,    53,    -1,
      -1,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    29,    -1,    -1,    -1,    33,
      -1,    76,    77,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    48,    49,    50,    51,    52,    53,
      -1,    -1,    56,    57,    58,    59,    60,    61,    62,    63,
      64,    65,    66,    67,    68,    69,    29,    -1,    -1,    -1,
      33,    -1,    76,    77,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    48,    49,    50,    51,    52,
      53,    -1,    -1,    56,    57,    58,    59,    60,    61,    62,
      63,    64,    65,    66,    67,    68,    69,    29,    -1,    -1,
      -1,    33,    -1,    76,    77,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    48,    49,    50,    51,
      52,    53,    -1,    -1,    56,    57,    58,    59,    60,    61,
      62,    63,    64,    65,    66,    67,    68,    69,    29,    -1,
      -1,    -1,    33,    -1,    76,    77,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    48,    49,    50,
      51,    52,    53,    -1,    -1,    56,    57,    58,    59,    60,
      61,    62,    63,    64,    65,    66,    67,    68,    69,    30,
      -1,    -1,    33,    -1,    -1,    76,    77,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    48,    49,    50,
      51,    52,    53,    -1,    -1,    56,    57,    58,    59,    60,
      61,    62,    63,    64,    65,    66,    67,    68,    69,    30,
      -1,    -1,    33,    -1,    -1,    76,    77,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    48,    49,    50,
      51,    52,    53,    -1,    -1,    56,    57,    58,    59,    60,
      61,    62,    63,    64,    65,    66,    67,    68,    69,    30,
      -1,    -1,    33,    -1,    -1,    76,    77,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    48,    49,    50,
      51,    52,    53,    -1,    -1,    56,    57,    58,    59,    60,
      61,    62,    63,    64,    65,    66,    67,    68,    69,    33,
      -1,    -1,    -1,    -1,    -1,    76,    77,    -1,    -1,    -1,
      -1,    -1,    -1,    47,    48,    49,    50,    51,    52,    53,
      -1,    -1,    56,    57,    58,    59,    60,    61,    62,    63,
      64,    65,    66,    67,    68,    69,    33,    -1,    -1,    -1,
      -1,    -1,    76,    77,    -1,    -1,    -1,    -1,    -1,    -1,
      47,    48,    49,    50,    51,    52,    53,    -1,    33,    56,
      57,    58,    59,    60,    61,    62,    63,    64,    65,    66,
      67,    68,    69,    48,    49,    50,    51,    52,    53,    76,
      77,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    -1,    -1,    -1,    -1,    -1,
      -1,    76,    77,    35,    36,    37,    38,    39,    40,    41,
      42,    43,    44,    45,    46,    50,    51,    52,    53,    -1,
      -1,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    -1,    -1,    -1,    -1,    71,
      72,    76,    77,    75,    76,    77,    48,    49,    50,    51,
      52,    53,    -1,    -1,    56,    57,    58,    59,    60,    61,
      62,    63,    64,    65,    66,    67,    68,    69,    -1,    49,
      50,    51,    52,    53,    76,    77,    56,    57,    58,    59,
      60,    61,    62,    63,    64,    65,    66,    67,    68,    69,
      -1,    -1,    -1,    51,    52,    53,    76,    77,    56,    57,
      58,    59,    60,    61,    62,    63,    64,    65,    66,    67,
      68,    69,    -1,    -1,    -1,    -1,    52,    53,    76,    77,
      56,    57,    58,    59,    60,    61,    62,    63,    64,    65,
      66,    67,    68,    69,    -1,    -1,    -1,    -1,    -1,    -1,
      76,    77
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,     4,     5,     7,     9,    10,    11,    12,    15,
      16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    30,    31,    65,    70,    71,    72,    73,    75,
      76,    80,    81,    82,    83,    84,    85,    90,    92,    97,
      98,    99,   102,   103,   104,   108,   109,   112,   113,    75,
      75,    75,    31,    82,    83,    91,    75,    30,    30,     4,
      75,     4,    88,    89,    16,    30,    31,    83,    75,    84,
      85,   104,    85,     3,     4,    81,   110,   111,    83,    83,
      85,    85,    83,    83,    28,    83,    87,     0,    82,    83,
      30,    33,    48,    49,    50,    51,    52,    53,    56,    57,
      58,    59,    60,    61,    62,    63,    64,    65,    66,    67,
      68,    69,    76,    77,    35,    36,    37,    38,    39,    40,
      41,    42,    43,    44,    45,    46,    71,    72,    75,    76,
      77,    75,    83,    17,    30,    83,    85,    93,    96,    83,
      32,     9,    83,    75,     4,   105,   106,    46,    30,    33,
       4,     3,     4,    30,    83,    75,    75,    75,    30,    47,
      47,    32,    32,    33,    29,    28,    33,    83,    83,    83,
      83,    83,    83,    83,    83,    83,    83,    83,    83,    83,
      83,    83,    83,    83,    83,    83,    83,    83,    83,     4,
      83,    83,    83,    83,    83,    83,    83,    83,    83,    83,
      83,    83,    86,    87,    83,     4,   105,    29,    88,    30,
      83,    94,     8,    29,    75,    29,   105,    29,    33,    83,
      89,    29,    86,    86,    86,    83,    83,   111,    75,    83,
      47,    28,    75,    29,    28,    29,    91,    30,    30,    83,
      91,    83,    31,    29,    31,   107,     4,    75,    29,    29,
      29,    86,    83,    75,    86,   107,     6,    83,    95,    29,
      29,    13,    14,    32,   100,   101,   107,    32,    81,    86,
      29,    86,    29,    91,    29,    91,    83,    47,    32,   101,
      32,    29,    29,    91,    47,    81,    81
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
      yyerror (&yylloc, parser_state, YY_("syntax error: cannot back up")); \
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
# define YYLEX yylex (&yylval, &yylloc, parser_state)
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
		  Type, Value, Location, parser_state); \
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
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp, tyran_parser_state* parser_state)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep, yylocationp, parser_state)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
    YYLTYPE const * const yylocationp;
    tyran_parser_state* parser_state;
#endif
{
  if (!yyvaluep)
    return;
  YYUSE (yylocationp);
  YYUSE (parser_state);
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
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp, tyran_parser_state* parser_state)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep, yylocationp, parser_state)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
    YYLTYPE const * const yylocationp;
    tyran_parser_state* parser_state;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  YY_LOCATION_PRINT (yyoutput, *yylocationp);
  YYFPRINTF (yyoutput, ": ");
  yy_symbol_value_print (yyoutput, yytype, yyvaluep, yylocationp, parser_state);
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
yy_reduce_print (YYSTYPE *yyvsp, YYLTYPE *yylsp, int yyrule, tyran_parser_state* parser_state)
#else
static void
yy_reduce_print (yyvsp, yylsp, yyrule, parser_state)
    YYSTYPE *yyvsp;
    YYLTYPE *yylsp;
    int yyrule;
    tyran_parser_state* parser_state;
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
		       , &(yylsp[(yyi + 1) - (yynrhs)])		       , parser_state);
      fprintf (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, yylsp, Rule, parser_state); \
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
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep, YYLTYPE *yylocationp, tyran_parser_state* parser_state)
#else
static void
yydestruct (yymsg, yytype, yyvaluep, yylocationp, parser_state)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
    YYLTYPE *yylocationp;
    tyran_parser_state* parser_state;
#endif
{
  YYUSE (yyvaluep);
  YYUSE (yylocationp);
  YYUSE (parser_state);

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
int yyparse (tyran_parser_state* parser_state);
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
yyparse (tyran_parser_state* parser_state)
#else
int
yyparse (parser_state)
    tyran_parser_state* parser_state;
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
#line 192 "tyran_parser.y"
    {
		parser_state->opcodes = 0;
	;}
    break;

  case 3:
#line 195 "tyran_parser.y"
    {
		parser_state->opcodes = (struct tyran_opcodes*)(yyvsp[(1) - (1)]);
	;}
    break;

  case 4:
#line 198 "tyran_parser.y"
    {
		parser_state->opcodes = tyran_opcodes_merge3((struct tyran_opcodes*)(yyvsp[(1) - (2)]), (struct tyran_opcodes*)(yyvsp[(2) - (2)]), tyran_opcodes_insert_return(1));
	;}
    break;

  case 5:
#line 201 "tyran_parser.y"
    {
		parser_state->opcodes = tyran_opcodes_merge((struct tyran_opcodes*)(yyvsp[(1) - (1)]), tyran_opcodes_insert_return(1));
	;}
    break;

  case 6:
#line 209 "tyran_parser.y"
    {
		(yyval) = (yyvsp[(1) - (1)]);
	;}
    break;

  case 7:
#line 212 "tyran_parser.y"
    {
		(yyval) = tyran_opcodes_merge((struct tyran_opcodes*)(yyvsp[(1) - (2)]), (struct tyran_opcodes*)(yyvsp[(2) - (2)]));
	;}
    break;

  case 8:
#line 218 "tyran_parser.y"
    {
	;}
    break;

  case 9:
#line 220 "tyran_parser.y"
    {
		(yyval) = tyran_opcodes_merge((struct tyran_opcodes*)(yyvsp[(1) - (2)]), tyran_opcodes_insert_pop(1));
	;}
    break;

  case 10:
#line 223 "tyran_parser.y"
    {
		(yyval) = (yyvsp[(2) - (3)]);
	;}
    break;

  case 11:
#line 226 "tyran_parser.y"
    {
		(yyval) = tyran_opcodes_insert_mark_for_resolve(tyran_resolve_break);
	;}
    break;

  case 12:
#line 229 "tyran_parser.y"
    {
		(yyval) = tyran_opcodes_insert_mark_for_resolve(tyran_resolve_continue);
	;}
    break;

  case 13:
#line 232 "tyran_parser.y"
    {
		(yyval) = tyran_opcodes_merge((struct tyran_opcodes*)(yyvsp[(2) - (3)]), tyran_opcodes_insert_return(1));
	;}
    break;

  case 14:
#line 235 "tyran_parser.y"
    {
		(yyval) = tyran_opcodes_insert_return(0);
	;}
    break;

  case 15:
#line 238 "tyran_parser.y"
    {
		(yyval) = (yyvsp[(2) - (3)]);
	;}
    break;

  case 16:
#line 241 "tyran_parser.y"
    {
		(yyval) = (yyvsp[(1) - (1)]);
	;}
    break;

  case 17:
#line 244 "tyran_parser.y"
    {
		(yyval) = (yyvsp[(1) - (1)]);
	;}
    break;

  case 18:
#line 247 "tyran_parser.y"
    {
		(yyval) = (yyvsp[(1) - (1)]);
	;}
    break;

  case 19:
#line 250 "tyran_parser.y"
    {
		(yyval) = (yyvsp[(1) - (1)]);
	;}
    break;

  case 20:
#line 253 "tyran_parser.y"
    {
		(yyval) = (yyvsp[(1) - (1)]);
	;}
    break;

  case 21:
#line 256 "tyran_parser.y"
    {
		(yyval) = (yyvsp[(1) - (1)]);
	;}
    break;

  case 22:
#line 259 "tyran_parser.y"
    {
		(yyval) = (yyvsp[(1) - (1)]);
	;}
    break;

  case 23:
#line 267 "tyran_parser.y"
    {
		(yyval) = (yyvsp[(1) - (1)]);
	;}
    break;

  case 24:
#line 270 "tyran_parser.y"
    { 
		if (((struct tyran_opcodes *)(yyvsp[(1) - (1)]))->lvalue_flag == tyran_assign_object) {
			(yyval) = tyran_opcodes_merge((struct tyran_opcodes*)(yyvsp[(1) - (1)]), tyran_opcodes_insert_subscript(1));
		}
		else {
			(yyval) = (yyvsp[(1) - (1)]);
		}
	;}
    break;

  case 25:
#line 278 "tyran_parser.y"
    {
		if (((struct tyran_opcodes *)(yyvsp[(1) - (2)]))->lvalue_flag == tyran_assign_object) {
			(yyval) = tyran_opcodes_merge3((struct tyran_opcodes*)(yyvsp[(1) - (2)]), tyran_opcodes_insert_subscript(0), tyran_opcodes_insert_increase(1));
		} else {
			(yyval) = tyran_opcodes_merge((struct tyran_opcodes*)(yyvsp[(1) - (2)]), tyran_opcodes_insert_increase(1));
		}
	;}
    break;

  case 26:
#line 285 "tyran_parser.y"
    {
		if (((struct tyran_opcodes *)(yyvsp[(1) - (2)]))->lvalue_flag == tyran_assign_object) {
			(yyval) = tyran_opcodes_merge3((struct tyran_opcodes*)(yyvsp[(1) - (2)]), tyran_opcodes_insert_subscript(0), tyran_opcodes_insert_decrease(1));
		} else {
			(yyval) = tyran_opcodes_merge((struct tyran_opcodes*)(yyvsp[(1) - (2)]), tyran_opcodes_insert_decrease(1));
		}
	;}
    break;

  case 27:
#line 292 "tyran_parser.y"
    {
		if (((struct tyran_opcodes *)(yyvsp[(2) - (2)]))->lvalue_flag == tyran_assign_object) {
			(yyval) = tyran_opcodes_merge3((struct tyran_opcodes*)(yyvsp[(2) - (2)]), tyran_opcodes_insert_subscript(0), tyran_opcodes_insert_increase(0));
		} else {
			(yyval) = tyran_opcodes_merge((struct tyran_opcodes*)(yyvsp[(2) - (2)]), tyran_opcodes_insert_increase(0));
		}
	;}
    break;

  case 28:
#line 299 "tyran_parser.y"
    { 
		if (((struct tyran_opcodes *)(yyvsp[(2) - (2)]))->lvalue_flag == tyran_assign_object) {
			(yyval) = tyran_opcodes_merge3((struct tyran_opcodes*)(yyvsp[(2) - (2)]), tyran_opcodes_insert_subscript(0), tyran_opcodes_insert_decrease(0));
		} else {
			(yyval) = tyran_opcodes_merge((struct tyran_opcodes*)(yyvsp[(2) - (2)]), tyran_opcodes_insert_decrease(0));
		}
	;}
    break;

  case 29:
#line 306 "tyran_parser.y"
    {
		(yyval) = (yyvsp[(1) - (1)]);
	;}
    break;

  case 30:
#line 309 "tyran_parser.y"
    {
		(yyval) = (yyvsp[(1) - (1)]);
	;}
    break;

  case 31:
#line 312 "tyran_parser.y"
    {
		(yyval) = tyran_opcodes_merge((struct tyran_opcodes*)(yyvsp[(2) - (2)]), tyran_opcodes_insert_negate());
	;}
    break;

  case 32:
#line 315 "tyran_parser.y"
    {
		(yyval) = tyran_opcodes_merge((struct tyran_opcodes*)(yyvsp[(2) - (2)]), tyran_opcodes_insert_not());
	;}
    break;

  case 33:
#line 318 "tyran_parser.y"
    {
		(yyval) = tyran_opcodes_merge3((struct tyran_opcodes*)(yyvsp[(1) - (3)]), (struct tyran_opcodes*)(yyvsp[(3) - (3)]), tyran_opcodes_insert_multiply());
	;}
    break;

  case 34:
#line 321 "tyran_parser.y"
    {
		(yyval) = tyran_opcodes_merge3((struct tyran_opcodes*)(yyvsp[(1) - (3)]), (struct tyran_opcodes*)(yyvsp[(3) - (3)]), tyran_opcodes_insert_divide());
	;}
    break;

  case 35:
#line 324 "tyran_parser.y"
    {
		(yyval) = tyran_opcodes_merge3((struct tyran_opcodes*)(yyvsp[(1) - (3)]), (struct tyran_opcodes*)(yyvsp[(3) - (3)]), tyran_opcodes_insert_modulus());
	;}
    break;

  case 36:
#line 327 "tyran_parser.y"
    {
		(yyval) = tyran_opcodes_merge3((struct tyran_opcodes*)(yyvsp[(1) - (3)]), (struct tyran_opcodes*)(yyvsp[(3) - (3)]), tyran_opcodes_insert_add());
	;}
    break;

  case 37:
#line 330 "tyran_parser.y"
    {
		(yyval) = tyran_opcodes_merge3((struct tyran_opcodes*)(yyvsp[(1) - (3)]), (struct tyran_opcodes*)(yyvsp[(3) - (3)]), tyran_opcodes_insert_subtract());
	;}
    break;

  case 38:
#line 333 "tyran_parser.y"
    {
		(yyval) = (yyvsp[(2) - (3)]);
	;}
    break;

  case 39:
#line 336 "tyran_parser.y"
    {
		struct tyran_opcodes* expression = tyran_opcodes_merge(tyran_opcodes_insert_pop(1), (struct tyran_opcodes*)(yyvsp[(3) - (3)]));
		(yyval) = tyran_opcodes_merge3((struct tyran_opcodes*)(yyvsp[(1) - (3)]), tyran_opcodes_insert_jump_false(expression->code_len + 1), expression);
	;}
    break;

  case 40:
#line 340 "tyran_parser.y"
    {
		struct tyran_opcodes* expression = tyran_opcodes_merge(tyran_opcodes_insert_pop(1), (struct tyran_opcodes*)(yyvsp[(3) - (3)]));
		(yyval) = tyran_opcodes_merge3((struct tyran_opcodes*)(yyvsp[(1) - (3)]), tyran_opcodes_insert_jump_true(expression->code_len + 1), expression);
	;}
    break;

  case 41:
#line 344 "tyran_parser.y"
    {
		(yyval) = tyran_opcodes_merge3((struct tyran_opcodes*)(yyvsp[(1) - (3)]), (struct tyran_opcodes*)(yyvsp[(3) - (3)]), tyran_opcodes_insert_compare_less());
	;}
    break;

  case 42:
#line 347 "tyran_parser.y"
    {
		(yyval) = tyran_opcodes_merge3((struct tyran_opcodes*)(yyvsp[(1) - (3)]), (struct tyran_opcodes*)(yyvsp[(3) - (3)]), tyran_opcodes_insert_compare_greater());
	;}
    break;

  case 43:
#line 350 "tyran_parser.y"
    {
		(yyval) = tyran_opcodes_merge3((struct tyran_opcodes*)(yyvsp[(1) - (3)]), (struct tyran_opcodes*)(yyvsp[(3) - (3)]), tyran_opcodes_insert_compare_less_equal());
	;}
    break;

  case 44:
#line 353 "tyran_parser.y"
    {
		(yyval) = tyran_opcodes_merge3((struct tyran_opcodes*)(yyvsp[(1) - (3)]), (struct tyran_opcodes*)(yyvsp[(3) - (3)]), tyran_opcodes_insert_compare_greater_equal());
	;}
    break;

  case 45:
#line 356 "tyran_parser.y"
    {
		(yyval) = tyran_opcodes_merge3((struct tyran_opcodes*)(yyvsp[(1) - (3)]), (struct tyran_opcodes*)(yyvsp[(3) - (3)]), tyran_opcodes_insert_compare_equal());
	;}
    break;

  case 46:
#line 359 "tyran_parser.y"
    {
		(yyval) = tyran_opcodes_merge3((struct tyran_opcodes*)(yyvsp[(1) - (3)]), (struct tyran_opcodes*)(yyvsp[(3) - (3)]), tyran_opcodes_insert_compare_not_equal());
	;}
    break;

  case 47:
#line 362 "tyran_parser.y"
    {
		(yyval) = tyran_opcodes_merge((struct tyran_opcodes*)(yyvsp[(2) - (2)]), tyran_opcodes_insert_bitwise_not());
	;}
    break;

  case 48:
#line 365 "tyran_parser.y"
    {
		(yyval) = tyran_opcodes_merge3((struct tyran_opcodes*)(yyvsp[(1) - (3)]), (struct tyran_opcodes*)(yyvsp[(3) - (3)]), tyran_opcodes_insert_bitwise_and());
	;}
    break;

  case 49:
#line 368 "tyran_parser.y"
    {
		(yyval) = tyran_opcodes_merge3((struct tyran_opcodes*)(yyvsp[(1) - (3)]), (struct tyran_opcodes*)(yyvsp[(3) - (3)]), tyran_opcodes_insert_bitwise_or());
	;}
    break;

  case 50:
#line 371 "tyran_parser.y"
    {
		(yyval) = tyran_opcodes_merge3((struct tyran_opcodes*)(yyvsp[(1) - (3)]), (struct tyran_opcodes*)(yyvsp[(3) - (3)]), tyran_opcodes_insert_bitwise_xor());
	;}
    break;

  case 51:
#line 374 "tyran_parser.y"
    {
		(yyval) = tyran_opcodes_merge3((struct tyran_opcodes*)(yyvsp[(1) - (3)]), (struct tyran_opcodes*)(yyvsp[(3) - (3)]), tyran_opcodes_insert_bitwise_shift(tyran_shift_left));
	;}
    break;

  case 52:
#line 377 "tyran_parser.y"
    {
		(yyval) = tyran_opcodes_merge3((struct tyran_opcodes*)(yyvsp[(1) - (3)]), (struct tyran_opcodes*)(yyvsp[(3) - (3)]), tyran_opcodes_insert_bitwise_shift(tyran_shift_right));
	;}
    break;

  case 53:
#line 380 "tyran_parser.y"
    {
		(yyval) = tyran_opcodes_merge3((struct tyran_opcodes*)(yyvsp[(1) - (3)]), (struct tyran_opcodes*)(yyvsp[(3) - (3)]), tyran_opcodes_insert_bitwise_shift(tyran_shift_right_unsigned));
	;}
    break;

  case 54:
#line 383 "tyran_parser.y"
    {
		(yyval) = tyran_opcodes_merge3((struct tyran_opcodes*)(yyvsp[(1) - (3)]), (struct tyran_opcodes*)(yyvsp[(3) - (3)]), tyran_opcodes_insert_assign(((struct tyran_opcodes *)(yyvsp[(1) - (3)]))->lvalue_flag));
	;}
    break;

  case 55:
#line 386 "tyran_parser.y"
    {
		(yyval) = tyran_operator_assign((struct tyran_opcodes*)(yyvsp[(1) - (3)]), (struct tyran_opcodes*)(yyvsp[(3) - (3)]), tyran_opcodes_insert_add());
	;}
    break;

  case 56:
#line 389 "tyran_parser.y"
    {
		(yyval) = tyran_operator_assign((struct tyran_opcodes*)(yyvsp[(1) - (3)]), (struct tyran_opcodes*)(yyvsp[(3) - (3)]), tyran_opcodes_insert_subtract());
	;}
    break;

  case 57:
#line 392 "tyran_parser.y"
    {
		(yyval) = tyran_operator_assign((struct tyran_opcodes*)(yyvsp[(1) - (3)]), (struct tyran_opcodes*)(yyvsp[(3) - (3)]), tyran_opcodes_insert_multiply());
	;}
    break;

  case 58:
#line 395 "tyran_parser.y"
    {
		(yyval) = tyran_operator_assign((struct tyran_opcodes*)(yyvsp[(1) - (3)]), (struct tyran_opcodes*)(yyvsp[(3) - (3)]), tyran_opcodes_insert_modulus());
	;}
    break;

  case 59:
#line 398 "tyran_parser.y"
    {
		(yyval) = tyran_operator_assign((struct tyran_opcodes*)(yyvsp[(1) - (3)]), (struct tyran_opcodes*)(yyvsp[(3) - (3)]), tyran_opcodes_insert_bitwise_shift(tyran_shift_left));
	;}
    break;

  case 60:
#line 401 "tyran_parser.y"
    {
		(yyval) = tyran_operator_assign((struct tyran_opcodes*)(yyvsp[(1) - (3)]), (struct tyran_opcodes*)(yyvsp[(3) - (3)]), tyran_opcodes_insert_bitwise_shift(tyran_shift_right));
	;}
    break;

  case 61:
#line 404 "tyran_parser.y"
    {
		(yyval) = tyran_operator_assign((struct tyran_opcodes*)(yyvsp[(1) - (3)]), (struct tyran_opcodes*)(yyvsp[(3) - (3)]), tyran_opcodes_insert_bitwise_shift(tyran_shift_right_unsigned));
	;}
    break;

  case 62:
#line 407 "tyran_parser.y"
    {
		(yyval) = tyran_operator_assign((struct tyran_opcodes*)(yyvsp[(1) - (3)]), (struct tyran_opcodes*)(yyvsp[(3) - (3)]), tyran_opcodes_insert_bitwise_and());
	;}
    break;

  case 63:
#line 410 "tyran_parser.y"
    {
		(yyval) = tyran_operator_assign((struct tyran_opcodes*)(yyvsp[(1) - (3)]), (struct tyran_opcodes*)(yyvsp[(3) - (3)]), tyran_opcodes_insert_bitwise_or());
	;}
    break;

  case 64:
#line 413 "tyran_parser.y"
    {
		(yyval) = tyran_operator_assign((struct tyran_opcodes*)(yyvsp[(1) - (3)]), (struct tyran_opcodes*)(yyvsp[(3) - (3)]), tyran_opcodes_insert_bitwise_xor());
	;}
    break;

  case 65:
#line 416 "tyran_parser.y"
    {
		(yyval) = tyran_operator_assign((struct tyran_opcodes*)(yyvsp[(1) - (3)]), (struct tyran_opcodes*)(yyvsp[(3) - (3)]), tyran_opcodes_insert_divide());
	;}
    break;

  case 66:
#line 419 "tyran_parser.y"
    {
		(yyval) = tyran_opcodes_merge3((struct tyran_opcodes*)(yyvsp[(1) - (3)]), tyran_opcodes_insert_pop(1), (struct tyran_opcodes*)(yyvsp[(3) - (3)]));
	;}
    break;

  case 67:
#line 422 "tyran_parser.y"
    {
		(yyval) = tyran_opcodes_merge3((struct tyran_opcodes*)(yyvsp[(1) - (4)]), (struct tyran_opcodes*)(yyvsp[(3) - (4)]), tyran_opcodes_insert_subscript(1));
	;}
    break;

  case 68:
#line 425 "tyran_parser.y"
    {
		(yyval) = tyran_opcodes_merge3((struct tyran_opcodes*)(yyvsp[(1) - (3)]), tyran_opcodes_insert_push_string((const tyran_string*)(yyvsp[(3) - (3)])), tyran_opcodes_insert_subscript(1));
	;}
    break;

  case 69:
#line 428 "tyran_parser.y"
    {
		(yyval) = tyran_opcodes_merge((struct tyran_opcodes*)(yyvsp[(2) - (2)]), tyran_opcodes_insert_new_call(0));
	;}
    break;

  case 70:
#line 431 "tyran_parser.y"
    { 
		if (((struct tyran_opcodes *)(yyvsp[(2) - (2)]))->lvalue_flag == tyran_assign_object) {
			(yyval) = tyran_opcodes_merge3((struct tyran_opcodes*)(yyvsp[(2) - (2)]), tyran_opcodes_insert_subscript(1), tyran_opcodes_insert_new_call(0));
		} else {
			(yyval) = tyran_opcodes_merge((struct tyran_opcodes*)(yyvsp[(2) - (2)]), tyran_opcodes_insert_new_call(0));
		}
	;}
    break;

  case 71:
#line 438 "tyran_parser.y"
    {
		(yyval) = tyran_opcodes_merge((struct tyran_opcodes*)(yyvsp[(3) - (4)]), tyran_opcodes_insert_new_call(0));
	;}
    break;

  case 72:
#line 441 "tyran_parser.y"
    {
		(yyval) = tyran_opcodes_merge((struct tyran_opcodes*)(yyvsp[(2) - (2)]), tyran_opcodes_insert_new_call(0));
	;}
    break;

  case 73:
#line 444 "tyran_parser.y"
    { 
		struct tyran_opcodes* expression_list = (struct tyran_opcodes*)(yyvsp[(4) - (5)]);
		int expression_count = expression_list ? expression_list->expression_count : 0;
		(yyval) = tyran_opcodes_merge3((struct tyran_opcodes*)(yyvsp[(2) - (5)]), expression_list, tyran_opcodes_insert_new_call(expression_count));
	;}
    break;

  case 74:
#line 449 "tyran_parser.y"
    {
		struct tyran_opcodes *expression_list = (struct tyran_opcodes*)(yyvsp[(4) - (5)]);
		int expression_count = expression_list ? expression_list->expression_count : 0;
		struct tyran_opcodes *lv = 0;

		if (((struct tyran_opcodes *)(yyvsp[(2) - (5)]))->lvalue_flag == tyran_assign_object)
			lv = tyran_opcodes_merge((struct tyran_opcodes*)(yyvsp[(2) - (5)]), tyran_opcodes_insert_subscript(1));
		else
			lv = (struct tyran_opcodes*)(yyvsp[(2) - (5)]);

		(yyval) = tyran_opcodes_merge3(lv, expression_list, tyran_opcodes_insert_new_call(expression_count));
	;}
    break;

  case 75:
#line 461 "tyran_parser.y"
    { 
		struct tyran_opcodes *expression_list = (struct tyran_opcodes*)(yyvsp[(6) - (7)]);
		int expression_count = expression_list ? expression_list->expression_count : 0;
		(yyval) = tyran_opcodes_merge3((struct tyran_opcodes*)(yyvsp[(3) - (7)]), expression_list, tyran_opcodes_insert_new_call(expression_count));
	;}
    break;

  case 76:
#line 466 "tyran_parser.y"
    {
		struct tyran_opcodes *expression_list = (struct tyran_opcodes*)(yyvsp[(4) - (5)]);
		int expression_count = expression_list ? expression_list->expression_count : 0;
		(yyval) = tyran_opcodes_merge3((struct tyran_opcodes*)(yyvsp[(2) - (5)]), expression_list, tyran_opcodes_insert_new_call(expression_count));
	;}
    break;

  case 77:
#line 471 "tyran_parser.y"
    {
		struct tyran_opcodes *expression = tyran_opcodes_merge((struct tyran_opcodes*)(yyvsp[(3) - (5)]), tyran_opcodes_insert_jump(((struct tyran_opcodes *)(yyvsp[(5) - (5)]))->code_len + 1));
		(yyval) = tyran_opcodes_merge4((struct tyran_opcodes*)(yyvsp[(1) - (5)]), tyran_opcodes_insert_jump_false_pop(expression->code_len + 1), expression, (struct tyran_opcodes*)(yyvsp[(5) - (5)]));
	;}
    break;

  case 78:
#line 478 "tyran_parser.y"
    {
		(yyval) = tyran_opcodes_insert_push_string((const tyran_string*)(yyvsp[(1) - (1)]));
	;}
    break;

  case 79:
#line 481 "tyran_parser.y"
    {
		(yyval) = (yyvsp[(1) - (1)]);
	;}
    break;

  case 80:
#line 484 "tyran_parser.y"
    {
		(yyval) = (yyvsp[(1) - (1)]);
	;}
    break;

  case 81:
#line 487 "tyran_parser.y"
    {
		(yyval) = tyran_opcodes_insert_push_undefined();
	;}
    break;

  case 82:
#line 490 "tyran_parser.y"
    {
		(yyval) = tyran_opcodes_insert_push_number((double*)(yyvsp[(1) - (1)]));
	;}
    break;

  case 83:
#line 493 "tyran_parser.y"
    {
		(yyval) = tyran_opcodes_insert_push_boolean(1);
	;}
    break;

  case 84:
#line 496 "tyran_parser.y"
    {
		(yyval) = tyran_opcodes_insert_push_boolean(0);
	;}
    break;

  case 85:
#line 499 "tyran_parser.y"
    {
		(yyval) = tyran_opcodes_insert_push_null();
	;}
    break;

  case 86:
#line 505 "tyran_parser.y"
    {
		(yyval) = tyran_opcodes_insert_push_variable((tyran_string*)(yyvsp[(1) - (1)])); 
		((struct tyran_opcodes *)(yyval))->lvalue_flag = tyran_assign_variable; 
		((struct tyran_opcodes *)(yyval))->lvalue_name = (const tyran_string*)(yyvsp[(1) - (1)]); 
	;}
    break;

  case 87:
#line 510 "tyran_parser.y"
    {
		if (((struct tyran_opcodes *)(yyvsp[(1) - (4)]))->lvalue_flag == tyran_assign_object)
			(yyval) = tyran_opcodes_merge3((struct tyran_opcodes*)(yyvsp[(1) - (4)]), tyran_opcodes_insert_subscript(1), (struct tyran_opcodes*)(yyvsp[(3) - (4)]));
		else
			(yyval) = tyran_opcodes_merge((struct tyran_opcodes*)(yyvsp[(1) - (4)]), (struct tyran_opcodes*)(yyvsp[(3) - (4)])); 
		((struct tyran_opcodes *)(yyval))->lvalue_flag = tyran_assign_object;
	;}
    break;

  case 88:
#line 517 "tyran_parser.y"
    {
		if (((struct tyran_opcodes *)(yyvsp[(1) - (3)]))->lvalue_flag == tyran_assign_object)
			(yyval) = tyran_opcodes_merge3((struct tyran_opcodes*)(yyvsp[(1) - (3)]), tyran_opcodes_insert_subscript(1), tyran_opcodes_insert_push_string((const tyran_string*)(yyvsp[(3) - (3)]))); 
		else
			(yyval) = tyran_opcodes_merge((struct tyran_opcodes*)(yyvsp[(1) - (3)]), tyran_opcodes_insert_push_string((const tyran_string*)(yyvsp[(3) - (3)])));
		((struct tyran_opcodes *)(yyval))->lvalue_flag = tyran_assign_object;
	;}
    break;

  case 89:
#line 524 "tyran_parser.y"
    {
		(yyval) = tyran_opcodes_insert_push_scope();
		((struct tyran_opcodes *)(yyval))->lvalue_flag = tyran_assign_variable;
	;}
    break;

  case 90:
#line 528 "tyran_parser.y"
    {
		(yyval) = tyran_opcodes_insert_push_this();
		((struct tyran_opcodes *)(yyval))->lvalue_flag = tyran_assign_variable;
	;}
    break;

  case 91:
#line 534 "tyran_parser.y"
    {
		(yyval) = 0;
	;}
    break;

  case 92:
#line 537 "tyran_parser.y"
    {
		(yyval) = (yyvsp[(1) - (1)]);
	;}
    break;

  case 93:
#line 543 "tyran_parser.y"
    {
		(yyval) = (yyvsp[(1) - (1)]);
		((struct tyran_opcodes *)(yyval))->expression_count = 1;
	;}
    break;

  case 94:
#line 547 "tyran_parser.y"
    {
		int expression_count = ((struct tyran_opcodes *)(yyvsp[(1) - (3)]))->expression_count + 1;
		(yyval) = tyran_opcodes_merge((struct tyran_opcodes*)(yyvsp[(1) - (3)]), (struct tyran_opcodes*)(yyvsp[(3) - (3)]));
		((struct tyran_opcodes *)(yyval))->expression_count = expression_count;
	;}
    break;

  case 95:
#line 557 "tyran_parser.y"
    {
		(yyval) = (yyvsp[(1) - (1)]);
	;}
    break;

  case 96:
#line 560 "tyran_parser.y"
    {
		(yyval) = tyran_opcodes_merge((struct tyran_opcodes*)(yyvsp[(1) - (3)]), (struct tyran_opcodes*)(yyvsp[(3) - (3)]));
	;}
    break;

  case 97:
#line 566 "tyran_parser.y"
    {
		struct tyran_opcodes *ret = tyran_opcodes_merge4(tyran_opcodes_insert_push_variable((tyran_string *)(yyvsp[(1) - (1)])), tyran_opcodes_insert_push_undefined(), tyran_opcodes_insert_assign(tyran_assign_variable), tyran_opcodes_insert_pop(1));
		tyran_parser_local_variable_scope_add((const tyran_string*)(yyvsp[(1) - (1)]));
		(yyval) = ret;
	;}
    break;

  case 98:
#line 571 "tyran_parser.y"
    {
		struct tyran_opcodes *ret = tyran_opcodes_merge4(tyran_opcodes_insert_push_variable((tyran_string*)(yyvsp[(1) - (3)])), (struct tyran_opcodes*)(yyvsp[(3) - (3)]), tyran_opcodes_insert_assign(tyran_assign_variable), tyran_opcodes_insert_pop(1));
		tyran_parser_local_variable_scope_add((const tyran_string*)(yyvsp[(1) - (3)]));
		(yyval) = ret;
	;}
    break;

  case 99:
#line 579 "tyran_parser.y"
    {
		int offset = ((struct tyran_opcodes *)(yyvsp[(5) - (5)]))->code_len;
		(yyval) = tyran_opcodes_merge3((struct tyran_opcodes*)(yyvsp[(3) - (5)]), tyran_opcodes_insert_jump_false_pop(offset + 1), (struct tyran_opcodes*)(yyvsp[(5) - (5)]));
	;}
    break;

  case 100:
#line 583 "tyran_parser.y"
    {
		int len_block2 = ((struct tyran_opcodes *)(yyvsp[(7) - (7)]))->code_len;
		struct tyran_opcodes *block1 = tyran_opcodes_merge((struct tyran_opcodes*)(yyvsp[(5) - (7)]), tyran_opcodes_insert_jump(len_block2 + 1));
		struct tyran_opcodes *condi = tyran_opcodes_merge((struct tyran_opcodes*)(yyvsp[(3) - (7)]), tyran_opcodes_insert_jump_false_pop(block1->code_len + 1));
		(yyval) = tyran_opcodes_merge3(condi, block1, (struct tyran_opcodes*)(yyvsp[(7) - (7)]));
	;}
    break;

  case 101:
#line 592 "tyran_parser.y"
    {
		(yyval) = (yyvsp[(1) - (1)]);
	;}
    break;

  case 102:
#line 595 "tyran_parser.y"
    {
		
	;}
    break;

  case 103:
#line 601 "tyran_parser.y"
    {
		struct tyran_opcodes* init = (struct tyran_opcodes*)(yyvsp[(3) - (8)]);
		struct tyran_opcodes* condition = (struct tyran_opcodes*)(yyvsp[(4) - (8)]);
		struct tyran_opcodes* step = ((yyvsp[(6) - (8)]) ? tyran_opcodes_merge((struct tyran_opcodes*)(yyvsp[(6) - (8)]), tyran_opcodes_insert_pop(1)) : 0);
		struct tyran_opcodes* statements = (struct tyran_opcodes*)(yyvsp[(8) - (8)]);
		struct tyran_opcodes* condition_jump = tyran_opcodes_insert_jump_false_pop(step->code_len + statements->code_len + 2);
		struct tyran_opcodes* step_jump = tyran_opcodes_insert_jump(-(condition->code_len + step->code_len + statements->code_len + 1));
		tyran_opcodes_resolve(statements, step->code_len + 1, 0, 0);
		(yyval) = tyran_opcodes_merge(tyran_opcodes_merge3(init, condition, condition_jump), tyran_opcodes_merge3(statements, step, step_jump));
	;}
    break;

  case 104:
#line 611 "tyran_parser.y"
    {
		struct tyran_variable_info* fv = (struct tyran_variable_info*)(yyvsp[(3) - (7)]);
		struct tyran_opcodes* lvalue;
		if (fv->variable_name) {
			lvalue = tyran_opcodes_insert_push_variable((tyran_string*)fv->variable_name);
		} else { 
			lvalue = fv->lvalue;
		}
		
		struct tyran_opcodes* ret = make_forin(lvalue, (struct tyran_opcodes*)(yyvsp[(5) - (7)]), (struct tyran_opcodes*)(yyvsp[(7) - (7)]));
		if (fv->variable_name && fv->local) {
			tyran_parser_local_variable_scope_add(fv->variable_name);
			tyran_opcodes_free(fv->local);
		}
		(yyval) = ret;
	;}
    break;

  case 105:
#line 630 "tyran_parser.y"
    {
		
	;}
    break;

  case 106:
#line 633 "tyran_parser.y"
    {
		(yyval) = tyran_opcodes_merge((struct tyran_opcodes*)(yyvsp[(1) - (2)]), tyran_opcodes_insert_pop(1));
	;}
    break;

  case 107:
#line 636 "tyran_parser.y"
    {
		(yyval) = (yyvsp[(2) - (3)]);
	;}
    break;

  case 108:
#line 641 "tyran_parser.y"
    {
		(yyval) = tyran_opcodes_insert_push_boolean(1);
	;}
    break;

  case 109:
#line 644 "tyran_parser.y"
    {
		(yyval) = (yyvsp[(1) - (1)]);
	;}
    break;

  case 110:
#line 649 "tyran_parser.y"
    {
		(yyval) = 0;
	;}
    break;

  case 111:
#line 652 "tyran_parser.y"
    {
		(yyval) = (yyvsp[(1) - (1)]);
	;}
    break;

  case 112:
#line 658 "tyran_parser.y"
    {
		if (((struct tyran_opcodes *)(yyvsp[(1) - (1)]))->lvalue_flag == 2) 
			(yyval) = tyran_variable_info_new(0, 0, tyran_opcodes_merge((struct tyran_opcodes*)(yyvsp[(1) - (1)]), tyran_opcodes_insert_subscript(0)));
		else
			(yyval) = tyran_variable_info_new(0, 0, (struct tyran_opcodes*)(yyvsp[(1) - (1)]));
	;}
    break;

  case 113:
#line 667 "tyran_parser.y"
    {
		struct tyran_opcodes* condition = (struct tyran_opcodes*)(yyvsp[(3) - (5)]);
		struct tyran_opcodes* statements = (struct tyran_opcodes*)(yyvsp[(5) - (5)]);
		tyran_opcodes_resolve(statements, 1, 0, 0);
		(yyval) = tyran_opcodes_merge4(condition, tyran_opcodes_insert_jump_false_pop(statements->code_len + 2), statements,
						   tyran_opcodes_insert_jump(-(statements->code_len + condition->code_len + 1)));
	;}
    break;

  case 114:
#line 677 "tyran_parser.y"
    {
		struct tyran_opcodes* statements = (struct tyran_opcodes*)(yyvsp[(2) - (6)]);
		struct tyran_opcodes* condition = (struct tyran_opcodes*)(yyvsp[(5) - (6)]);
		tyran_opcodes_resolve(statements, condition->code_len + 1, 0, 0);
		(yyval) = tyran_opcodes_merge3(statements, condition, tyran_opcodes_insert_jump_true_pop(-(statements->code_len + condition->code_len)));
	;}
    break;

  case 115:
#line 686 "tyran_parser.y"
    {
		(yyval) = tyran_opcodes_merge((struct tyran_opcodes*)(yyvsp[(3) - (6)]), tyran_opcodes_insert_pop(1));
	;}
    break;

  case 116:
#line 689 "tyran_parser.y"
    {
		tyran_case_info* case_info = (tyran_case_info*) (yyvsp[(6) - (7)]);
		struct tyran_opcodes* statements = tyran_opcodes_new(3);
		tyran_case_info* case_default = 0;
		tyran_case_info* head = 0;
		
		while (case_info) {
			case_info->offset = statements->code_len;
			statements = tyran_opcodes_merge(statements, case_info->switch_info->statements);

			tyran_case_info *t = case_info;
			case_info = case_info->next;
			
			if (t->switch_info->is_default) {
				if (case_default) yyerror(&(yylsp[(7) - (7)]), parser_state, "Extra default found");
				case_default = t;
			} else {
				t->next = head;
				head = t;
			}
		}
		tyran_opcodes_resolve(statements, 0, 1, 1);
		
		struct tyran_opcodes *operator_root = tyran_opcodes_insert_jump(statements->code_len + 1);
		if (case_default) {
			operator_root = tyran_opcodes_merge(tyran_opcodes_insert_jump(operator_root->code_len + case_default->offset + 1), operator_root);
			free(case_default);
		}
		while (head) {
			struct tyran_opcodes *e = tyran_opcodes_merge4(tyran_opcodes_insert_push_top(), head->switch_info->expression,  tyran_opcodes_insert_compare_equal(), tyran_opcodes_insert_jump_true_pop(operator_root->code_len + head->offset + 1));
			operator_root = tyran_opcodes_merge(e, operator_root);
			tyran_case_info *t = head;
			head = head->next;
			free(t);
		}
		(yyval) = tyran_opcodes_merge4(tyran_opcodes_merge((struct tyran_opcodes*)(yyvsp[(3) - (7)]), tyran_opcodes_insert_unreference()), operator_root, statements, tyran_opcodes_insert_pop(1));
	;}
    break;

  case 117:
#line 729 "tyran_parser.y"
    {
		(yyval) = tyran_case_info_new((tyran_switch_info*)(yyvsp[(1) - (1)]));
	;}
    break;

  case 118:
#line 732 "tyran_parser.y"
    {
		(yyval) = tyran_case_info_add((tyran_case_info*)(yyvsp[(1) - (2)]), (tyran_switch_info*)(yyvsp[(2) - (2)]));
	;}
    break;

  case 119:
#line 738 "tyran_parser.y"
    {
		(yyval) = tyran_switch_info_new((struct tyran_opcodes*)(yyvsp[(2) - (4)]), (struct tyran_opcodes*)(yyvsp[(4) - (4)]), 0);
	;}
    break;

  case 120:
#line 741 "tyran_parser.y"
    {
		(yyval) = tyran_switch_info_new(0, (struct tyran_opcodes*)(yyvsp[(3) - (3)]), 1);
	;}
    break;

  case 121:
#line 749 "tyran_parser.y"
    {
		struct tyran_opcodes *ret = tyran_opcodes_merge4(tyran_opcodes_insert_push_variable((tyran_string*)(yyvsp[(1) - (5)])), tyran_opcodes_insert_push_function(tyran_function_new((const tyran_string_array*)(yyvsp[(3) - (5)]), tyran_parser_local_variable_scope_names(), (struct tyran_opcodes*)(yyvsp[(5) - (5)]))), tyran_opcodes_insert_assign(tyran_assign_variable), tyran_opcodes_insert_pop(1));
		tyran_parser_local_variable_scope_pop();
		(yyval) = ret;
	;}
    break;

  case 122:
#line 757 "tyran_parser.y"
    {
		tyran_parser_local_variable_scope_add((const tyran_string*)(yyvsp[(2) - (2)]));
		(yyval) = (yyvsp[(2) - (2)]);
	;}
    break;

  case 123:
#line 764 "tyran_parser.y"
    {
		(yyval) = tyran_opcodes_insert_push_function(tyran_function_new((const tyran_string_array *)(yyvsp[(3) - (5)]), tyran_parser_local_variable_scope_names(), (struct tyran_opcodes*)(yyvsp[(5) - (5)])));
		tyran_parser_local_variable_scope_pop();
	;}
    break;

  case 124:
#line 768 "tyran_parser.y"
    {
		(yyval) = tyran_opcodes_insert_push_function(tyran_function_new((const tyran_string_array *)(yyvsp[(4) - (6)]), tyran_parser_local_variable_scope_names(), (struct tyran_opcodes*)(yyvsp[(6) - (6)])));
		tyran_parser_local_variable_scope_pop();
	;}
    break;

  case 125:
#line 774 "tyran_parser.y"
    {
		tyran_parser_local_variable_scope_push();
		(yyval) = tyran_string_array_new();
	;}
    break;

  case 126:
#line 778 "tyran_parser.y"
    {
		tyran_parser_local_variable_scope_push();
		tyran_argument_list *a = (tyran_argument_list*)(yyvsp[(1) - (1)]);
		tyran_string_array* s = tyran_string_array_new();
		while (a) {
			tyran_string_array_add(s, a->argument_name);
			a = a->next;
		}
		(yyval) = s;
	;}
    break;

  case 127:
#line 791 "tyran_parser.y"
    {
		(yyval) = tyran_argument_list_new((const tyran_string*)(yyvsp[(1) - (1)]));
	;}
    break;

  case 128:
#line 794 "tyran_parser.y"
    {
		(yyval) = tyran_argument_list_add((tyran_argument_list*)(yyvsp[(1) - (3)]), (const tyran_string*)(yyvsp[(3) - (3)]));
	;}
    break;

  case 129:
#line 800 "tyran_parser.y"
    {
		(yyval) = (yyvsp[(2) - (3)]);
	;}
    break;

  case 130:
#line 803 "tyran_parser.y"
    {
	;}
    break;

  case 131:
#line 808 "tyran_parser.y"
    {
		struct tyran_opcodes *ff = tyran_opcodes_merge4((struct tyran_opcodes*)(yyvsp[(1) - (6)]), tyran_opcodes_insert_push_string((const tyran_string*)(yyvsp[(3) - (6)])), tyran_opcodes_insert_toc_dup(), tyran_opcodes_insert_subscript(1));
		struct tyran_opcodes *expression_list = (struct tyran_opcodes*)(yyvsp[(5) - (6)]);
		int expression_count = expression_list ? expression_list->expression_count : 0;
		(yyval) = tyran_opcodes_merge3(ff, expression_list, tyran_opcodes_insert_call_set_this(expression_count));
	;}
    break;

  case 132:
#line 814 "tyran_parser.y"
    {
		struct tyran_opcodes *ff = tyran_opcodes_merge3((struct tyran_opcodes*)(yyvsp[(1) - (7)]), (struct tyran_opcodes*)(yyvsp[(3) - (7)]), tyran_opcodes_insert_subscript(1));
		struct tyran_opcodes *expression_list = (struct tyran_opcodes*)(yyvsp[(6) - (7)]);
		int expression_count = expression_list ? expression_list->expression_count : 0;
		(yyval) = tyran_opcodes_merge3(ff, expression_list, tyran_opcodes_insert_call(expression_count));
	;}
    break;

  case 133:
#line 820 "tyran_parser.y"
    {
		struct tyran_opcodes *expression_list = (struct tyran_opcodes*)(yyvsp[(5) - (6)]);
		int expression_count = expression_list ? expression_list->expression_count : 0;
		(yyval) = tyran_opcodes_merge3((struct tyran_opcodes*)(yyvsp[(2) - (6)]), expression_list, tyran_opcodes_insert_call(expression_count));
	;}
    break;

  case 134:
#line 825 "tyran_parser.y"
    {
		struct tyran_opcodes *expression_list = (struct tyran_opcodes*)(yyvsp[(3) - (4)]);
		int expression_count = expression_list ? expression_list->expression_count : 0;
		struct tyran_opcodes *pref;
		struct tyran_opcodes *lvalue = (struct tyran_opcodes*)(yyvsp[(1) - (4)]);
		if (lvalue->lvalue_flag == tyran_assign_object) {
			pref = tyran_opcodes_merge3((struct tyran_opcodes*)(yyvsp[(1) - (4)]), tyran_opcodes_insert_toc_dup(), tyran_opcodes_insert_subscript(1));
			(yyval) = tyran_opcodes_merge3(pref, expression_list, tyran_opcodes_insert_call_set_this(expression_count));
		} else {
			pref = (struct tyran_opcodes*)(yyvsp[(1) - (4)]);
			(yyval) = tyran_opcodes_merge3(pref, expression_list, tyran_opcodes_insert_call(expression_count));
		}
	;}
    break;

  case 135:
#line 841 "tyran_parser.y"
    {
		(yyval) = tyran_opcodes_merge((struct tyran_opcodes*)(yyvsp[(2) - (3)]), tyran_opcodes_insert_make_object(((struct tyran_opcodes *)(yyvsp[(2) - (3)]))->expression_count));
	;}
    break;

  case 136:
#line 846 "tyran_parser.y"
    { 
		((struct tyran_opcodes *)(yyval))->expression_count = 0;
	;}
    break;

  case 137:
#line 849 "tyran_parser.y"
    {
		(yyval) = (yyvsp[(1) - (1)]); ((struct tyran_opcodes *)(yyval))->expression_count = 1;
	;}
    break;

  case 138:
#line 852 "tyran_parser.y"
    {
		int cnt = ((struct tyran_opcodes *)(yyvsp[(1) - (3)]))->expression_count + 1;
		(yyval) = tyran_opcodes_merge((struct tyran_opcodes*)(yyvsp[(1) - (3)]), (struct tyran_opcodes*)(yyvsp[(3) - (3)]));
		((struct tyran_opcodes *)(yyval))->expression_count = cnt;
	;}
    break;

  case 139:
#line 860 "tyran_parser.y"
    {
		(yyval) = tyran_opcodes_merge(tyran_opcodes_insert_push_string((const tyran_string*)(yyvsp[(1) - (3)])), (struct tyran_opcodes*)(yyvsp[(3) - (3)]));
	;}
    break;

  case 140:
#line 863 "tyran_parser.y"
    {
		(yyval) = tyran_opcodes_merge(tyran_opcodes_insert_push_string((const tyran_string*)(yyvsp[(1) - (3)])), (struct tyran_opcodes*)(yyvsp[(3) - (3)]));
	;}
    break;

  case 141:
#line 869 "tyran_parser.y"
    {
		(yyval) = tyran_opcodes_merge((struct tyran_opcodes*)(yyvsp[(2) - (3)]), tyran_opcodes_insert_make_array(((struct tyran_opcodes *)(yyvsp[(2) - (3)]))->expression_count));
	;}
    break;

  case 142:
#line 872 "tyran_parser.y"
    {
		(yyval) = tyran_opcodes_insert_make_array(0);
	;}
    break;

  case 143:
#line 878 "tyran_parser.y"
    {
		if (((struct tyran_opcodes *)(yyvsp[(2) - (3)]))->lvalue_flag == tyran_assign_object) {
			(yyval) = tyran_opcodes_merge((struct tyran_opcodes*)(yyvsp[(2) - (3)]), tyran_opcodes_insert_delete(tyran_assign_object));
		} else {
			(yyval) = tyran_opcodes_insert_delete(tyran_assign_variable);
		}
	;}
    break;


/* Line 1267 of yacc.c.  */
#line 3305 "tyran_parser.c"
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
      yyerror (&yylloc, parser_state, YY_("syntax error"));
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
	    yyerror (&yylloc, parser_state, yymsg);
	  }
	else
	  {
	    yyerror (&yylloc, parser_state, YY_("syntax error"));
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
		      yytoken, &yylval, &yylloc, parser_state);
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
		  yystos[yystate], yyvsp, yylsp, parser_state);
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
  yyerror (&yylloc, parser_state, YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEOF && yychar != YYEMPTY)
     yydestruct ("Cleanup: discarding lookahead",
		 yytoken, &yylval, &yylloc, parser_state);
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp, yylsp, parser_state);
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


#line 887 "tyran_parser.y"


