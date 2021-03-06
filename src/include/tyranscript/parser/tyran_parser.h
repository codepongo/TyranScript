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
#define YYSTYPE void *

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
