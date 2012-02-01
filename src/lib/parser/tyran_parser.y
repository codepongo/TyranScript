%{
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

static struct  tyran_opcodes* make_forin(struct tyran_opcodes* lvalue, struct tyran_opcodes* expression, struct tyran_opcodes* statements, const tyran_string* label)
{
	struct tyran_opcodes* init = tyran_opcodes_merge(expression, tyran_opcodes_insert_key());
	struct tyran_opcodes* condition = tyran_opcodes_merge3(lvalue, tyran_opcodes_insert_next(), tyran_opcodes_insert_jump_false_pop(statements->code_len + 2));
	struct tyran_opcodes* stat_jmp = tyran_opcodes_insert_jump(-(condition->code_len + statements->code_len));
	tyran_opcodes_resolve(statements, 1, 0, 2);
	return tyran_opcodes_merge3(tyran_opcodes_merge(init, condition), tyran_opcodes_merge(statements, stat_jmp), tyran_opcodes_insert_pop(2));
}

%}

/* --------------- Bison options --------------- */
%pure-parser

%locations
%parse-param	{tyran_parser_state* parser_state}
%lex-param	{tyran_parser_state* parser_state}
%error-verbose


/* --------------- Tokens --------------- */
%token TYRAN_TOKEN_STRING
%token TYRAN_TOKEN_IDENTIFIER

%token TYRAN_TOKEN_IF
%token TYRAN_TOKEN_ELSE

%token TYRAN_TOKEN_FOR
%token TYRAN_TOKEN_IN

%token TYRAN_TOKEN_WHILE
%token TYRAN_TOKEN_DO

%token TYRAN_TOKEN_SWITCH

%token TYRAN_TOKEN_CONTINUE
%token TYRAN_TOKEN_CASE
%token TYRAN_TOKEN_DEFAULT
%token TYRAN_TOKEN_BREAK

%token TYRAN_TOKEN_FUNCTION
%token TYRAN_TOKEN_LOCAL
%token TYRAN_TOKEN_RETURN

%token TYRAN_TOKEN_NEW
%token TYRAN_TOKEN_DELETE

%token TYRAN_TOKEN_ARGUMENTS

%token TYRAN_TOKEN_UNDEFINED
%token TYRAN_TOKEN_NUMBER
%token TYRAN_TOKEN_TRUE
%token TYRAN_TOKEN_FALSE
%token TYRAN_TOKEN_THIS

%token TYRAN_TOKEN_BRACKET_RIGHT
%token TYRAN_TOKEN_PARENTHESES_RIGHT
%token TYRAN_TOKEN_EOL
%token TYRAN_TOKEN_BLOCK_START
%token TYRAN_TOKEN_BLOCK_END

/* --------------- Operators --------------- */
%left TYRAN_TOKEN_COMMA
%left comma_precedence
%right TYRAN_TOKEN_ASSIGNMENT TYRAN_TOKEN_ADD_ASSIGNMENT TYRAN_TOKEN_SUBTRACT_ASSIGNMENT TYRAN_TOKEN_MULTIPLY_ASSIGNMENT TYRAN_TOKEN_MODULUS_ASSIGNMENT TYRAN_TOKEN_SHIFT_LEFT_ASSIGNMENT TYRAN_TOKEN_SHIFT_RIGHT_ASSIGNMENT TYRAN_TOKEN_UNSIGNED_SHIFT_RIGHT_ASSIGNMENT TYRAN_TOKEN_BITWISE_AND_ASSIGNMENT TYRAN_TOKEN_BITWISE_OR_ASSIGNMENT TYRAN_TOKEN_BITWISE_XOR_ASSIGNMENT TYRAN_TOKEN_DIVIDE_ASSIGNMENT
%left TYRAN_TOKEN_QUESTION_MARK TYRAN_TOKEN_COLON
%left TYRAN_TOKEN_OR
%left TYRAN_TOKEN_AND
%left TYRAN_TOKEN_BITWISE_OR
%left TYRAN_TOKEN_BITWISE_XOR
%left TYRAN_TOKEN_BITWISE_AND
%left TYRAN_TOKEN_EQUAL TYRAN_TOKEN_NOT_EQUAL TYRAN_TOKEN_STRICT_EQUAL TYRAN_TOKEN_STRICT_NOT_EQUAL
%left TYRAN_TOKEN_GREATER TYRAN_TOKEN_LESS TYRAN_TOKEN_LESS_EQUAL TYRAN_TOKEN_GREATER_EQUAL
%left TYRAN_TOKEN_SHIFT_LEFT TYRAN_TOKEN_SHIFT_RIGHT TYRAN_TOKEN_SHIFT_RIGHT_UNSIGNED
%left TYRAN_TOKEN_ADD TYRAN_TOKEN_SUBTRACT
%left TYRAN_TOKEN_MULTIPLY TYRAN_TOKEN_DIVIDE TYRAN_TOKEN_MODULUS
%left TYRAN_TOKEN_NEGATIVE TYRAN_TOKEN_NOT TYRAN_TOKEN_INCREASE TYRAN_TOKEN_DECREASE TYRAN_TOKEN_BITWISE_NOT
%left TYRAN_TOKEN_NEW
%left TYRAN_TOKEN_MEMBER TYRAN_TOKEN_BRACKET_LEFT TYRAN_TOKEN_PARENTHESES_LEFT
%left function_precedence
%%

/* --------------- Rules --------------- */

file: {
		parser_state->opcodes = 0;
	}
	| statements {
		parser_state->opcodes = (struct tyran_opcodes*)$1;
	}
	| statements expression {
		parser_state->opcodes = tyran_opcodes_merge3((struct tyran_opcodes*)$1, (struct tyran_opcodes*)$2, tyran_opcodes_insert_return(1));
	}
	| expression {
		parser_state->opcodes = tyran_opcodes_merge((struct tyran_opcodes*)$1, tyran_opcodes_insert_return(1));
	}
;

/* ------------------------------------------------- */

statements:
	statement {
		$$ = $1;
	}
	| statements statement {
		$$ = tyran_opcodes_merge((struct tyran_opcodes*)$1, (struct tyran_opcodes*)$2);
	}
;

statement:
	TYRAN_TOKEN_EOL {
	}
	| expression TYRAN_TOKEN_EOL {
		$$ = tyran_opcodes_merge((struct tyran_opcodes*)$1, tyran_opcodes_insert_pop(1));
	}
	| TYRAN_TOKEN_BLOCK_START statements TYRAN_TOKEN_BLOCK_END {
		$$ = $2;
	}
	| TYRAN_TOKEN_BREAK TYRAN_TOKEN_EOL {
		$$ = tyran_opcodes_insert_mark_for_resolve(tyran_resolve_break);
	}
	| TYRAN_TOKEN_CONTINUE TYRAN_TOKEN_EOL {
		$$ = tyran_opcodes_insert_mark_for_resolve(tyran_resolve_continue);
	}
	| TYRAN_TOKEN_RETURN expression TYRAN_TOKEN_EOL {
		$$ = tyran_opcodes_merge((struct tyran_opcodes*)$2, tyran_opcodes_insert_return(1));
	}
	| TYRAN_TOKEN_RETURN TYRAN_TOKEN_EOL {
		$$ = tyran_opcodes_insert_return(0);
	}
	| TYRAN_TOKEN_LOCAL variable_declarations TYRAN_TOKEN_EOL {
		$$ = $2;
	}
	| if_statement {
		$$ = $1;
	}
	| delete_statement {
		$$ = $1;
	}
	| function_statement {
		$$ = $1;
	}
	| for_statement {
		$$ = $1;
	}
	| while_statement {
		$$ = $1;
	}
	| do_statement {
		$$ = $1;
	}
	| switch_statement {
		$$ = $1;
	}	
;


/* ------------------------------------------------- */
expression:
	value {
		$$ = $1;
	}
	| lvalue { 
		if (((struct tyran_opcodes *)$1)->lvalue_flag == tyran_assign_object) {
			$$ = tyran_opcodes_merge((struct tyran_opcodes*)$1, tyran_opcodes_insert_subscript(1));
		}
		else {
			$$ = $1;
		}
	}
	| lvalue TYRAN_TOKEN_INCREASE {
		if (((struct tyran_opcodes *)$1)->lvalue_flag == tyran_assign_object) {
			$$ = tyran_opcodes_merge3((struct tyran_opcodes*)$1, tyran_opcodes_insert_subscript(0), tyran_opcodes_insert_increase(1));
		} else {
			$$ = tyran_opcodes_merge((struct tyran_opcodes*)$1, tyran_opcodes_insert_increase(1));
		}
	}
	| lvalue TYRAN_TOKEN_DECREASE {
		if (((struct tyran_opcodes *)$1)->lvalue_flag == tyran_assign_object) {
			$$ = tyran_opcodes_merge3((struct tyran_opcodes*)$1, tyran_opcodes_insert_subscript(0), tyran_opcodes_insert_decrease(1));
		} else {
			$$ = tyran_opcodes_merge((struct tyran_opcodes*)$1, tyran_opcodes_insert_decrease(1));
		}
	}
	| TYRAN_TOKEN_INCREASE lvalue {
		if (((struct tyran_opcodes *)$2)->lvalue_flag == tyran_assign_object) {
			$$ = tyran_opcodes_merge3((struct tyran_opcodes*)$2, tyran_opcodes_insert_subscript(0), tyran_opcodes_insert_increase(0));
		} else {
			$$ = tyran_opcodes_merge((struct tyran_opcodes*)$2, tyran_opcodes_insert_increase(0));
		}
	}
	| TYRAN_TOKEN_DECREASE lvalue { 
		if (((struct tyran_opcodes *)$2)->lvalue_flag == tyran_assign_object) {
			$$ = tyran_opcodes_merge3((struct tyran_opcodes*)$2, tyran_opcodes_insert_subscript(0), tyran_opcodes_insert_decrease(0));
		} else {
			$$ = tyran_opcodes_merge((struct tyran_opcodes*)$2, tyran_opcodes_insert_decrease(0));
		}
	}
	| function_call_expression {
		$$ = $1;
	}
	| function_expression {
		$$ = $1;
	}
	| TYRAN_TOKEN_SUBTRACT expression %prec TYRAN_TOKEN_NEGATIVE {
		$$ = tyran_opcodes_merge((struct tyran_opcodes*)$2, tyran_opcodes_insert_negate());
	}
	| TYRAN_TOKEN_NOT expression {
		$$ = tyran_opcodes_merge((struct tyran_opcodes*)$2, tyran_opcodes_insert_not());
	}
	| expression TYRAN_TOKEN_MULTIPLY expression {
		$$ = tyran_opcodes_merge3((struct tyran_opcodes*)$1, (struct tyran_opcodes*)$3, tyran_opcodes_insert_multiply());
	}
	| expression TYRAN_TOKEN_DIVIDE expression {
		$$ = tyran_opcodes_merge3((struct tyran_opcodes*)$1, (struct tyran_opcodes*)$3, tyran_opcodes_insert_divide());
	}
	| expression TYRAN_TOKEN_MODULUS expression {
		$$ = tyran_opcodes_merge3((struct tyran_opcodes*)$1, (struct tyran_opcodes*)$3, tyran_opcodes_insert_modulus());
	}
	| expression TYRAN_TOKEN_ADD expression {
		$$ = tyran_opcodes_merge3((struct tyran_opcodes*)$1, (struct tyran_opcodes*)$3, tyran_opcodes_insert_add());
	}
	| expression TYRAN_TOKEN_SUBTRACT expression {
		$$ = tyran_opcodes_merge3((struct tyran_opcodes*)$1, (struct tyran_opcodes*)$3, tyran_opcodes_insert_subtract());
	}
	| TYRAN_TOKEN_PARENTHESES_LEFT expression TYRAN_TOKEN_PARENTHESES_RIGHT {
		$$ = $2;
	}
	| expression TYRAN_TOKEN_AND expression {
		struct tyran_opcodes* expression = tyran_opcodes_merge(tyran_opcodes_insert_pop(1), (struct tyran_opcodes*)$3);
		$$ = tyran_opcodes_merge3((struct tyran_opcodes*)$1, tyran_opcodes_insert_jump_false(expression->code_len + 1), expression);
	}
	| expression TYRAN_TOKEN_OR expression {
		struct tyran_opcodes* expression = tyran_opcodes_merge(tyran_opcodes_insert_pop(1), (struct tyran_opcodes*)$3);
		$$ = tyran_opcodes_merge3((struct tyran_opcodes*)$1, tyran_opcodes_insert_jump_true(expression->code_len + 1), expression);
	}
	| expression TYRAN_TOKEN_LESS expression {
		$$ = tyran_opcodes_merge3((struct tyran_opcodes*)$1, (struct tyran_opcodes*)$3, tyran_opcodes_insert_compare_less());
	}
	| expression TYRAN_TOKEN_GREATER expression {
		$$ = tyran_opcodes_merge3((struct tyran_opcodes*)$1, (struct tyran_opcodes*)$3, tyran_opcodes_insert_compare_greater());
	}
	| expression TYRAN_TOKEN_LESS_EQUAL expression {
		$$ = tyran_opcodes_merge3((struct tyran_opcodes*)$1, (struct tyran_opcodes*)$3, tyran_opcodes_insert_compare_less_equal());
	}
	| expression TYRAN_TOKEN_GREATER_EQUAL expression {
		$$ = tyran_opcodes_merge3((struct tyran_opcodes*)$1, (struct tyran_opcodes*)$3, tyran_opcodes_insert_compare_greater_equal());
	}
	| expression TYRAN_TOKEN_EQUAL expression {
		$$ = tyran_opcodes_merge3((struct tyran_opcodes*)$1, (struct tyran_opcodes*)$3, tyran_opcodes_insert_compare_equal());
	}
	| expression TYRAN_TOKEN_NOT_EQUAL expression {
		$$ = tyran_opcodes_merge3((struct tyran_opcodes*)$1, (struct tyran_opcodes*)$3, tyran_opcodes_insert_compare_not_equal());
	}
	| TYRAN_TOKEN_BITWISE_NOT expression {
		$$ = tyran_opcodes_merge((struct tyran_opcodes*)$2, tyran_opcodes_insert_bitwise_not());
	}
	| expression TYRAN_TOKEN_BITWISE_AND expression {
		$$ = tyran_opcodes_merge3((struct tyran_opcodes*)$1, (struct tyran_opcodes*)$3, tyran_opcodes_insert_bitwise_and());
	}
	| expression TYRAN_TOKEN_BITWISE_OR expression {
		$$ = tyran_opcodes_merge3((struct tyran_opcodes*)$1, (struct tyran_opcodes*)$3, tyran_opcodes_insert_bitwise_or());
	}
	| expression TYRAN_TOKEN_BITWISE_XOR expression {
		$$ = tyran_opcodes_merge3((struct tyran_opcodes*)$1, (struct tyran_opcodes*)$3, tyran_opcodes_insert_bitwise_xor());
	}
	| expression TYRAN_TOKEN_SHIFT_LEFT expression {
		$$ = tyran_opcodes_merge3((struct tyran_opcodes*)$1, (struct tyran_opcodes*)$3, tyran_opcodes_insert_bitwise_shift(tyran_shift_left));
	}
	| expression TYRAN_TOKEN_SHIFT_RIGHT expression {
		$$ = tyran_opcodes_merge3((struct tyran_opcodes*)$1, (struct tyran_opcodes*)$3, tyran_opcodes_insert_bitwise_shift(tyran_shift_right));
	}
	| expression TYRAN_TOKEN_SHIFT_RIGHT_UNSIGNED expression {
		$$ = tyran_opcodes_merge3((struct tyran_opcodes*)$1, (struct tyran_opcodes*)$3, tyran_opcodes_insert_bitwise_shift(tyran_shift_right_unsigned));
	}
	| lvalue TYRAN_TOKEN_ASSIGNMENT expression {
		$$ = tyran_opcodes_merge3((struct tyran_opcodes*)$1, (struct tyran_opcodes*)$3, tyran_opcodes_insert_assign(((struct tyran_opcodes *)$1)->lvalue_flag));
	}
	| lvalue TYRAN_TOKEN_ADD_ASSIGNMENT expression {
		$$ = tyran_operator_assign((struct tyran_opcodes*)$1, (struct tyran_opcodes*)$3, tyran_opcodes_insert_add());
	}
	| lvalue TYRAN_TOKEN_SUBTRACT_ASSIGNMENT expression {
		$$ = tyran_operator_assign((struct tyran_opcodes*)$1, (struct tyran_opcodes*)$3, tyran_opcodes_insert_subtract());
	}
	| lvalue TYRAN_TOKEN_MULTIPLY_ASSIGNMENT expression {
		$$ = tyran_operator_assign((struct tyran_opcodes*)$1, (struct tyran_opcodes*)$3, tyran_opcodes_insert_multiply());
	}
	| lvalue TYRAN_TOKEN_MODULUS_ASSIGNMENT expression {
		$$ = tyran_operator_assign((struct tyran_opcodes*)$1, (struct tyran_opcodes*)$3, tyran_opcodes_insert_modulus());
	}
	| lvalue TYRAN_TOKEN_SHIFT_LEFT_ASSIGNMENT expression {
		$$ = tyran_operator_assign((struct tyran_opcodes*)$1, (struct tyran_opcodes*)$3, tyran_opcodes_insert_bitwise_shift(tyran_shift_left));
	}
	| lvalue TYRAN_TOKEN_SHIFT_RIGHT_ASSIGNMENT expression {
		$$ = tyran_operator_assign((struct tyran_opcodes*)$1, (struct tyran_opcodes*)$3, tyran_opcodes_insert_bitwise_shift(tyran_shift_right));
	}
	| lvalue TYRAN_TOKEN_UNSIGNED_SHIFT_RIGHT_ASSIGNMENT expression {
		$$ = tyran_operator_assign((struct tyran_opcodes*)$1, (struct tyran_opcodes*)$3, tyran_opcodes_insert_bitwise_shift(tyran_shift_right_unsigned));
	}
	| lvalue TYRAN_TOKEN_BITWISE_AND_ASSIGNMENT expression {
		$$ = tyran_operator_assign((struct tyran_opcodes*)$1, (struct tyran_opcodes*)$3, tyran_opcodes_insert_bitwise_and());
	}
	| lvalue TYRAN_TOKEN_BITWISE_OR_ASSIGNMENT expression {
		$$ = tyran_operator_assign((struct tyran_opcodes*)$1, (struct tyran_opcodes*)$3, tyran_opcodes_insert_bitwise_or());
	}
	| lvalue TYRAN_TOKEN_BITWISE_XOR_ASSIGNMENT expression {
		$$ = tyran_operator_assign((struct tyran_opcodes*)$1, (struct tyran_opcodes*)$3, tyran_opcodes_insert_bitwise_xor());
	}
	| lvalue TYRAN_TOKEN_DIVIDE_ASSIGNMENT expression {
		$$ = tyran_operator_assign((struct tyran_opcodes*)$1, (struct tyran_opcodes*)$3, tyran_opcodes_insert_divide());
	}
	| expression TYRAN_TOKEN_COMMA expression {
		$$ = tyran_opcodes_merge3((struct tyran_opcodes*)$1, tyran_opcodes_insert_pop(1), (struct tyran_opcodes*)$3);
	}
	| expression TYRAN_TOKEN_BRACKET_LEFT expression TYRAN_TOKEN_BRACKET_RIGHT {
		$$ = tyran_opcodes_merge3((struct tyran_opcodes*)$1, (struct tyran_opcodes*)$3, tyran_opcodes_insert_subscript(1));
	}
	| expression TYRAN_TOKEN_MEMBER TYRAN_TOKEN_IDENTIFIER {
		$$ = tyran_opcodes_merge3((struct tyran_opcodes*)$1, tyran_opcodes_insert_push_string((const tyran_string*)$3), tyran_opcodes_insert_subscript(1));
	}
	| TYRAN_TOKEN_NEW value {
		$$ = tyran_opcodes_merge((struct tyran_opcodes*)$2, tyran_opcodes_insert_new_call(0));
	}
	| TYRAN_TOKEN_NEW lvalue { 
		if (((struct tyran_opcodes *)$2)->lvalue_flag == tyran_assign_object) {
			$$ = tyran_opcodes_merge3((struct tyran_opcodes*)$2, tyran_opcodes_insert_subscript(1), tyran_opcodes_insert_new_call(0));
		} else {
			$$ = tyran_opcodes_merge((struct tyran_opcodes*)$2, tyran_opcodes_insert_new_call(0));
		}
	}
	| TYRAN_TOKEN_NEW TYRAN_TOKEN_PARENTHESES_LEFT expression TYRAN_TOKEN_PARENTHESES_RIGHT {
		$$ = tyran_opcodes_merge((struct tyran_opcodes*)$3, tyran_opcodes_insert_new_call(0));
	}
	| TYRAN_TOKEN_NEW function_expression {
		$$ = tyran_opcodes_merge((struct tyran_opcodes*)$2, tyran_opcodes_insert_new_call(0));
	}
	| TYRAN_TOKEN_NEW value TYRAN_TOKEN_PARENTHESES_LEFT expression_list_optional TYRAN_TOKEN_PARENTHESES_RIGHT { 
		struct tyran_opcodes* expression_list = (struct tyran_opcodes*)$4;
		int expression_count = expression_list ? expression_list->expression_count : 0;
		$$ = tyran_opcodes_merge3((struct tyran_opcodes*)$2, expression_list, tyran_opcodes_insert_new_call(expression_count));
	}
	| TYRAN_TOKEN_NEW lvalue TYRAN_TOKEN_PARENTHESES_LEFT expression_list_optional TYRAN_TOKEN_PARENTHESES_RIGHT {
		struct tyran_opcodes *expression_list = (struct tyran_opcodes*)$4;
		int expression_count = expression_list ? expression_list->expression_count : 0;
		struct tyran_opcodes *lv = 0;

		if (((struct tyran_opcodes *)$2)->lvalue_flag == tyran_assign_object)
			lv = tyran_opcodes_merge((struct tyran_opcodes*)$2, tyran_opcodes_insert_subscript(1));
		else
			lv = (struct tyran_opcodes*)$2;

		$$ = tyran_opcodes_merge3(lv, expression_list, tyran_opcodes_insert_new_call(expression_count));
	}
	| TYRAN_TOKEN_NEW TYRAN_TOKEN_PARENTHESES_LEFT expression TYRAN_TOKEN_PARENTHESES_RIGHT TYRAN_TOKEN_PARENTHESES_LEFT expression_list_optional TYRAN_TOKEN_PARENTHESES_RIGHT { 
		struct tyran_opcodes *expression_list = (struct tyran_opcodes*)$6;
		int expression_count = expression_list ? expression_list->expression_count : 0;
		$$ = tyran_opcodes_merge3((struct tyran_opcodes*)$3, expression_list, tyran_opcodes_insert_new_call(expression_count));
	}
	| TYRAN_TOKEN_NEW function_expression TYRAN_TOKEN_PARENTHESES_LEFT expression_list_optional TYRAN_TOKEN_PARENTHESES_RIGHT {
		struct tyran_opcodes *expression_list = (struct tyran_opcodes*)$4;
		int expression_count = expression_list ? expression_list->expression_count : 0;
		$$ = tyran_opcodes_merge3((struct tyran_opcodes*)$2, expression_list, tyran_opcodes_insert_new_call(expression_count));
	}
	| expression TYRAN_TOKEN_QUESTION_MARK expression TYRAN_TOKEN_COLON expression {
		struct tyran_opcodes *expression = tyran_opcodes_merge((struct tyran_opcodes*)$3, tyran_opcodes_insert_jump(((struct tyran_opcodes *)$5)->code_len + 1));
		$$ = tyran_opcodes_merge4((struct tyran_opcodes*)$1, tyran_opcodes_insert_jump_false_pop(expression->code_len + 1), expression, (struct tyran_opcodes*)$5);
	}
;

value:
	TYRAN_TOKEN_STRING {
		$$ = tyran_opcodes_insert_push_string((const tyran_string*)$1);
	}
	| object {
		$$ = $1;
	}
	| array {
		$$ = $1;
	}
	| TYRAN_TOKEN_UNDEFINED {
		$$ = tyran_opcodes_insert_push_undefined();
	}
	| TYRAN_TOKEN_NUMBER {
		$$ = tyran_opcodes_insert_push_number((double*)$1);
	}
	| TYRAN_TOKEN_TRUE {
		$$ = tyran_opcodes_insert_push_boolean(1);
	}
	| TYRAN_TOKEN_FALSE {
		$$ = tyran_opcodes_insert_push_boolean(0);
	}
;

lvalue:
	TYRAN_TOKEN_IDENTIFIER {
		$$ = tyran_opcodes_insert_push_variable((tyran_string*)$1); 
		((struct tyran_opcodes *)$$)->lvalue_flag = tyran_assign_variable; 
		((struct tyran_opcodes *)$$)->lvalue_name = (const tyran_string*)$1; 
	}
	| lvalue TYRAN_TOKEN_BRACKET_LEFT expression TYRAN_TOKEN_BRACKET_RIGHT {
		if (((struct tyran_opcodes *)$1)->lvalue_flag == tyran_assign_object)
			$$ = tyran_opcodes_merge3((struct tyran_opcodes*)$1, tyran_opcodes_insert_subscript(1), (struct tyran_opcodes*)$3);
		else
			$$ = tyran_opcodes_merge((struct tyran_opcodes*)$1, (struct tyran_opcodes*)$3); 
		((struct tyran_opcodes *)$$)->lvalue_flag = tyran_assign_object;
	}
	| lvalue TYRAN_TOKEN_MEMBER TYRAN_TOKEN_IDENTIFIER {
		if (((struct tyran_opcodes *)$1)->lvalue_flag == tyran_assign_object)
			$$ = tyran_opcodes_merge3((struct tyran_opcodes*)$1, tyran_opcodes_insert_subscript(1), tyran_opcodes_insert_push_string((const tyran_string*)$3)); 
		else
			$$ = tyran_opcodes_merge((struct tyran_opcodes*)$1, tyran_opcodes_insert_push_string((const tyran_string*)$3));
		((struct tyran_opcodes *)$$)->lvalue_flag = tyran_assign_object;
	}
	| TYRAN_TOKEN_ARGUMENTS {
		$$ = tyran_opcodes_insert_push_scope();
		((struct tyran_opcodes *)$$)->lvalue_flag = tyran_assign_variable;
	}
	| TYRAN_TOKEN_THIS {
		$$ = tyran_opcodes_insert_push_this();
		((struct tyran_opcodes *)$$)->lvalue_flag = tyran_assign_variable;
	}
;

expression_list_optional: {
		$$ = 0;
	}
	| expression_list {
		$$ = $1;
	}
;

expression_list:
	expression %prec comma_precedence {
		$$ = $1;
		((struct tyran_opcodes *)$$)->expression_count = 1;
	}
	| expression_list TYRAN_TOKEN_COMMA expression %prec comma_precedence {
		int expression_count = ((struct tyran_opcodes *)$1)->expression_count + 1;
		$$ = tyran_opcodes_merge((struct tyran_opcodes*)$1, (struct tyran_opcodes*)$3);
		((struct tyran_opcodes *)$$)->expression_count = expression_count;
	}
;


/* ------------------------------------------------- */
variable_declarations:
	variable_declaration {
		$$ = $1;
	}
	| variable_declarations TYRAN_TOKEN_COMMA variable_declaration {
		$$ = tyran_opcodes_merge((struct tyran_opcodes*)$1, (struct tyran_opcodes*)$3);
	}
;

variable_declaration:
	TYRAN_TOKEN_IDENTIFIER	{
		struct tyran_opcodes *ret = tyran_opcodes_merge4(tyran_opcodes_insert_push_variable((tyran_string *)$1), tyran_opcodes_insert_push_undefined(), tyran_opcodes_insert_assign(tyran_assign_variable), tyran_opcodes_insert_pop(1));
		tyran_parser_local_variable_scope_add((const tyran_string*)$1);
		$$ = ret;
	}
	| TYRAN_TOKEN_IDENTIFIER TYRAN_TOKEN_ASSIGNMENT expression {
		struct tyran_opcodes *ret = tyran_opcodes_merge4(tyran_opcodes_insert_push_variable((tyran_string*)$1), (struct tyran_opcodes*)$3, tyran_opcodes_insert_assign(tyran_assign_variable), tyran_opcodes_insert_pop(1));
		tyran_parser_local_variable_scope_add((const tyran_string*)$1);
		$$ = ret;
	}
;

if_statement:
	TYRAN_TOKEN_IF TYRAN_TOKEN_PARENTHESES_LEFT expression TYRAN_TOKEN_PARENTHESES_RIGHT statement_or_empty_block {
		int offset = ((struct tyran_opcodes *)$5)->code_len;
		$$ = tyran_opcodes_merge3((struct tyran_opcodes*)$3, tyran_opcodes_insert_jump_false_pop(offset + 1), (struct tyran_opcodes*)$5);
	}
	| TYRAN_TOKEN_IF TYRAN_TOKEN_PARENTHESES_LEFT expression TYRAN_TOKEN_PARENTHESES_RIGHT statement_or_empty_block TYRAN_TOKEN_ELSE statement_or_empty_block {
		int len_block2 = ((struct tyran_opcodes *)$7)->code_len;
		struct tyran_opcodes *block1 = tyran_opcodes_merge((struct tyran_opcodes*)$5, tyran_opcodes_insert_jump(len_block2 + 1));
		struct tyran_opcodes *condi = tyran_opcodes_merge((struct tyran_opcodes*)$3, tyran_opcodes_insert_jump_false_pop(block1->code_len + 1));
		$$ = tyran_opcodes_merge3(condi, block1, (struct tyran_opcodes*)$7);
	}
;

statement_or_empty_block:
	statement {
		$$ = $1;
	}
	| TYRAN_TOKEN_BLOCK_START TYRAN_TOKEN_BLOCK_END {
		
	}
;

for_statement:
	TYRAN_TOKEN_FOR TYRAN_TOKEN_PARENTHESES_LEFT for_init for_condition TYRAN_TOKEN_EOL expression_optional TYRAN_TOKEN_PARENTHESES_RIGHT statement_or_empty_block {
		struct tyran_opcodes* init = (struct tyran_opcodes*)$3;
		struct tyran_opcodes* condition = (struct tyran_opcodes*)$4;
		struct tyran_opcodes* step = ($6 ? tyran_opcodes_merge((struct tyran_opcodes*)$6, tyran_opcodes_insert_pop(1)) : 0);
		struct tyran_opcodes* statements = (struct tyran_opcodes*)$8;
		struct tyran_opcodes* condition_jump = tyran_opcodes_insert_jump_false_pop(step->code_len + statements->code_len + 2);
		struct tyran_opcodes* step_jump = tyran_opcodes_insert_jump(-(condition->code_len + step->code_len + statements->code_len + 1));
		tyran_opcodes_resolve(statements, step->code_len + 1, 0, 0);
		$$ = tyran_opcodes_merge(tyran_opcodes_merge3(init, condition, condition_jump), tyran_opcodes_merge3(statements, step, step_jump));
	}
	| TYRAN_TOKEN_FOR TYRAN_TOKEN_PARENTHESES_LEFT for_variable TYRAN_TOKEN_IN expression TYRAN_TOKEN_PARENTHESES_RIGHT statement_or_empty_block {
		struct tyran_variable_info* fv = (struct tyran_variable_info*)$3;
		struct tyran_opcodes* lvalue;
		if (fv->variable_name) {
			lvalue = tyran_opcodes_insert_push_variable((tyran_string*)fv->variable_name);
		} else { 
			lvalue = fv->lvalue;
		}
		
		struct tyran_opcodes* ret = make_forin(lvalue, (struct tyran_opcodes*)$5, (struct tyran_opcodes*)$7, 0);
		if (fv->variable_name && fv->local) {
			tyran_parser_local_variable_scope_add(fv->variable_name);
			tyran_opcodes_free(fv->local);
		}
		$$ = ret;
	}
;

for_init:
	TYRAN_TOKEN_EOL {
		
	}
	| expression TYRAN_TOKEN_EOL {
		$$ = tyran_opcodes_merge((struct tyran_opcodes*)$1, tyran_opcodes_insert_pop(1));
	}
	| TYRAN_TOKEN_LOCAL variable_declarations TYRAN_TOKEN_EOL {
		$$ = $2;
	}
;

for_condition: {
		$$ = tyran_opcodes_insert_push_boolean(1);
	}
	| expression {
		$$ = $1;
	}
;

expression_optional: {
		$$ = 0;
	}
	| expression {
		$$ = $1;
	}
;

for_variable:
	lvalue {
		if (((struct tyran_opcodes *)$1)->lvalue_flag == 2) 
			$$ = tyran_variable_info_new(0, 0, tyran_opcodes_merge((struct tyran_opcodes*)$1, tyran_opcodes_insert_subscript(0)));
		else
			$$ = tyran_variable_info_new(0, 0, (struct tyran_opcodes*)$1);
	}
;

while_statement:
	TYRAN_TOKEN_WHILE TYRAN_TOKEN_PARENTHESES_LEFT expression TYRAN_TOKEN_PARENTHESES_RIGHT statement_or_empty_block {
		struct tyran_opcodes* condition = (struct tyran_opcodes*)$3;
		struct tyran_opcodes* statements = (struct tyran_opcodes*)$5;
		tyran_opcodes_resolve(statements, 1, 0, 0);
		$$ = tyran_opcodes_merge4(condition, tyran_opcodes_insert_jump_false_pop(statements->code_len + 2), statements,
						   tyran_opcodes_insert_jump(-(statements->code_len + condition->code_len + 1)));
	}
;

do_statement:
	TYRAN_TOKEN_DO statement_or_empty_block TYRAN_TOKEN_WHILE TYRAN_TOKEN_PARENTHESES_LEFT expression TYRAN_TOKEN_PARENTHESES_RIGHT {
		struct tyran_opcodes* statements = (struct tyran_opcodes*)$2;
		struct tyran_opcodes* condition = (struct tyran_opcodes*)$5;
		tyran_opcodes_resolve(statements, condition->code_len + 1, 0, 0);
		$$ = tyran_opcodes_merge3(statements, condition, tyran_opcodes_insert_jump_true_pop(-(statements->code_len + condition->code_len)));
	}
;

switch_statement:
	TYRAN_TOKEN_SWITCH TYRAN_TOKEN_PARENTHESES_LEFT expression TYRAN_TOKEN_PARENTHESES_RIGHT TYRAN_TOKEN_BLOCK_START TYRAN_TOKEN_BLOCK_END {
		$$ = tyran_opcodes_merge((struct tyran_opcodes*)$3, tyran_opcodes_insert_pop(1));
	}
	| TYRAN_TOKEN_SWITCH TYRAN_TOKEN_PARENTHESES_LEFT expression TYRAN_TOKEN_PARENTHESES_RIGHT TYRAN_TOKEN_BLOCK_START cases TYRAN_TOKEN_BLOCK_END	{
		tyran_case_info* case_info = (tyran_case_info*) $6;
		struct tyran_opcodes* statements = tyran_opcodes_new(3);
		tyran_case_info* case_default = 0;
		tyran_case_info* head = 0;
		
		while (case_info) {
			case_info->offset = statements->code_len;
			statements = tyran_opcodes_merge(statements, case_info->switch_info->statements);

			tyran_case_info *t = case_info;
			case_info = case_info->next;
			
			if (t->switch_info->is_default) {
				if (case_default) yyerror(&@7, parser_state, "Extra default found");
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
		$$ = tyran_opcodes_merge4(tyran_opcodes_merge((struct tyran_opcodes*)$3, tyran_opcodes_insert_unreference()), operator_root, statements, tyran_opcodes_insert_pop(1));
	}
;

cases:
	case {
		$$ = tyran_case_info_new((tyran_switch_info*)$1);
	}
	| cases case {
		$$ = tyran_case_info_add((tyran_case_info*)$1, (tyran_switch_info*)$2);
	}
;

case:
	TYRAN_TOKEN_CASE expression TYRAN_TOKEN_COLON statements {
		$$ = tyran_switch_info_new((struct tyran_opcodes*)$2, (struct tyran_opcodes*)$4, 0);
	}
	| TYRAN_TOKEN_DEFAULT TYRAN_TOKEN_COLON statements {
		$$ = tyran_switch_info_new(0, (struct tyran_opcodes*)$3, 1);
	}
;


/* --------- Functions --------- */
function_statement:
	function_prefix TYRAN_TOKEN_PARENTHESES_LEFT arguments_optional TYRAN_TOKEN_PARENTHESES_RIGHT function_statement_block {
		struct tyran_opcodes *ret = tyran_opcodes_merge4(tyran_opcodes_insert_push_variable((tyran_string*)$1), tyran_opcodes_insert_push_function(tyran_function_new((const tyran_string_array*)$3, tyran_parser_local_variable_scope_names(), (struct tyran_opcodes*)$5)), tyran_opcodes_insert_assign(tyran_assign_variable), tyran_opcodes_insert_pop(1));
		tyran_parser_local_variable_scope_pop();
		$$ = ret;
	}
;

function_prefix:
	TYRAN_TOKEN_FUNCTION TYRAN_TOKEN_IDENTIFIER %prec function_precedence {
		tyran_parser_local_variable_scope_add((const tyran_string*)$2);
		$$ = $2;
	}
;

function_expression:
	TYRAN_TOKEN_FUNCTION TYRAN_TOKEN_PARENTHESES_LEFT arguments_optional TYRAN_TOKEN_PARENTHESES_RIGHT function_statement_block {
		$$ = tyran_opcodes_insert_push_function(tyran_function_new((const tyran_string_array *)$3, tyran_parser_local_variable_scope_names(), (struct tyran_opcodes*)$5));
		tyran_parser_local_variable_scope_pop();
	}
	| TYRAN_TOKEN_FUNCTION TYRAN_TOKEN_IDENTIFIER TYRAN_TOKEN_PARENTHESES_LEFT arguments_optional TYRAN_TOKEN_PARENTHESES_RIGHT function_statement_block {
		$$ = tyran_opcodes_insert_push_function(tyran_function_new((const tyran_string_array *)$4, tyran_parser_local_variable_scope_names(), (struct tyran_opcodes*)$6));
		tyran_parser_local_variable_scope_pop();
	}
;

arguments_optional: {
		tyran_parser_local_variable_scope_push();
		$$ = tyran_string_array_new();
	}
	| arguments {
		tyran_parser_local_variable_scope_push();
		tyran_argument_list *a = (tyran_argument_list*)$1;
		tyran_string_array* s = tyran_string_array_new();
		while (a) {
			tyran_string_array_add(s, a->argument_name);
			a = a->next;
		}
		$$ = s;
	}
;

arguments:
	TYRAN_TOKEN_IDENTIFIER	{
		$$ = tyran_argument_list_new((const tyran_string*)$1);
	}
	| arguments TYRAN_TOKEN_COMMA TYRAN_TOKEN_IDENTIFIER {
		$$ = tyran_argument_list_add((tyran_argument_list*)$1, (const tyran_string*)$3);
	}
;

function_statement_block:
	TYRAN_TOKEN_BLOCK_START statements TYRAN_TOKEN_BLOCK_END {
		$$ = $2;
	}
	| TYRAN_TOKEN_BLOCK_START TYRAN_TOKEN_BLOCK_END {
	}
;

function_call_expression:
	expression TYRAN_TOKEN_MEMBER TYRAN_TOKEN_IDENTIFIER TYRAN_TOKEN_PARENTHESES_LEFT expression_list_optional TYRAN_TOKEN_PARENTHESES_RIGHT {
		struct tyran_opcodes *ff = tyran_opcodes_merge4((struct tyran_opcodes*)$1, tyran_opcodes_insert_push_string((const tyran_string*)$3), tyran_opcodes_insert_load_this(), tyran_opcodes_insert_subscript(1));
		struct tyran_opcodes *expression_list = (struct tyran_opcodes*)$5;
		int expression_count = expression_list ? expression_list->expression_count : 0;
		$$ = tyran_opcodes_merge3(ff, expression_list, tyran_opcodes_insert_call(expression_count));
	}
	| expression TYRAN_TOKEN_BRACKET_LEFT expression TYRAN_TOKEN_BRACKET_RIGHT TYRAN_TOKEN_PARENTHESES_LEFT expression_list_optional TYRAN_TOKEN_PARENTHESES_RIGHT {
		struct tyran_opcodes *ff = tyran_opcodes_merge4((struct tyran_opcodes*)$1, (struct tyran_opcodes*)$3, tyran_opcodes_insert_load_this(), tyran_opcodes_insert_subscript(1));
		struct tyran_opcodes *expression_list = (struct tyran_opcodes*)$6;
		int expression_count = expression_list ? expression_list->expression_count : 0;
		$$ = tyran_opcodes_merge3(ff, expression_list, tyran_opcodes_insert_call(expression_count));
	}
	| TYRAN_TOKEN_PARENTHESES_LEFT expression TYRAN_TOKEN_PARENTHESES_RIGHT TYRAN_TOKEN_PARENTHESES_LEFT expression_list_optional TYRAN_TOKEN_PARENTHESES_RIGHT {
		struct tyran_opcodes *expression_list = (struct tyran_opcodes*)$5;
		int expression_count = expression_list ? expression_list->expression_count : 0;
		$$ = tyran_opcodes_merge3((struct tyran_opcodes*)$2, expression_list, tyran_opcodes_insert_call(expression_count));
	}
	| lvalue TYRAN_TOKEN_PARENTHESES_LEFT expression_list_optional TYRAN_TOKEN_PARENTHESES_RIGHT {
		struct tyran_opcodes *expression_list = (struct tyran_opcodes*)$3;
		int expression_count = expression_list ? expression_list->expression_count : 0;
		struct tyran_opcodes *pref;
		struct tyran_opcodes *lvalue = (struct tyran_opcodes*)$1;
		if (lvalue->lvalue_flag == tyran_assign_object) {
			pref = tyran_opcodes_merge3((struct tyran_opcodes*)$1, tyran_opcodes_insert_load_this(), tyran_opcodes_insert_subscript(1));
			$$ = tyran_opcodes_merge3(pref, expression_list, tyran_opcodes_insert_call(expression_count));
		} else {
			pref = (struct tyran_opcodes*)$1;
			$$ = tyran_opcodes_merge3(pref, expression_list, tyran_opcodes_insert_call(expression_count));
		}
	}
;

object:
	TYRAN_TOKEN_BLOCK_START object_items TYRAN_TOKEN_BLOCK_END {
		$$ = tyran_opcodes_merge((struct tyran_opcodes*)$2, tyran_opcodes_insert_make_object(((struct tyran_opcodes *)$2)->expression_count));
	}
;

object_items: { 
		((struct tyran_opcodes *)$$)->expression_count = 0;
	}
	| object_item {
		$$ = $1; ((struct tyran_opcodes *)$$)->expression_count = 1;
	}
	| object_items TYRAN_TOKEN_COMMA object_item {
		int cnt = ((struct tyran_opcodes *)$1)->expression_count + 1;
		$$ = tyran_opcodes_merge((struct tyran_opcodes*)$1, (struct tyran_opcodes*)$3);
		((struct tyran_opcodes *)$$)->expression_count = cnt;
	}
;

object_item:
	TYRAN_TOKEN_IDENTIFIER TYRAN_TOKEN_COLON expression {
		$$ = tyran_opcodes_merge(tyran_opcodes_insert_push_string((const tyran_string*)$1), (struct tyran_opcodes*)$3);
	}
	| TYRAN_TOKEN_STRING TYRAN_TOKEN_COLON expression	{
		$$ = tyran_opcodes_merge(tyran_opcodes_insert_push_string((const tyran_string*)$1), (struct tyran_opcodes*)$3);
	}
;

array:
	TYRAN_TOKEN_BRACKET_LEFT expression_list TYRAN_TOKEN_BRACKET_RIGHT {
		$$ = tyran_opcodes_merge((struct tyran_opcodes*)$2, tyran_opcodes_insert_make_array(((struct tyran_opcodes *)$2)->expression_count));
	}
	| TYRAN_TOKEN_BRACKET_LEFT TYRAN_TOKEN_BRACKET_RIGHT {
		$$ = tyran_opcodes_insert_make_array(0);
	}
;

delete_statement:
	TYRAN_TOKEN_DELETE lvalue TYRAN_TOKEN_EOL {
		if (((struct tyran_opcodes *)$2)->lvalue_flag == tyran_assign_object) {
			$$ = tyran_opcodes_merge((struct tyran_opcodes*)$2, tyran_opcodes_insert_delete(tyran_assign_object));
		} else {
			$$ = tyran_opcodes_insert_delete(tyran_assign_variable);
		}
	}
;

%%
