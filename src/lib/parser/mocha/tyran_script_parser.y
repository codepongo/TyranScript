%{
	#include <tyranscript/parser/mocha/tyran_parser.h>	
%}

%pure-parser
%locations
%parse-param {tyran_parser* parser}
%lex-param {tyran_parser* parser}
%error-verbose

%token COMMENT
%token UNARY
%token COMPARE
%token FOROF
%token IDENTIFIER
%token TERMINATOR
%token INDEX_START
%token SHIFT
%token INDENT
%token SWITCH
%token PARAM_END
%token TYRAN_TOKEN_NULL
%token CALL_START
%token UNDEFINED
%token TYRAN_TOKEN_TRUE
%token TYRAN_TOKEN_FALSE
%token WHILE
%token INDEX_SOAK
%token OUTDENT
%token RETURN
%token INDEX_END
%token RELATION
%token CALL_END
%token MATH
%token WHEN
%token FOR
%token SUPER
%token LOGIC
%token POST_IF
%token FORIN
%token STRING
%token NUMBER
%token BY
%token IF
%token LEADING_WHEN
%token PARAM_START
%token UNTIL
%token OWN
%token STATEMENT
%token COMPOUND_ASSIGNMENT
%token ADD
%token SUBTRACT
%token MULTIPLY
%token DIVIDE
%token MEMBER
%token SOAK_MEMBER
%token SCOPING
%token INCREMENT
%token DECREMENT
%token EQUAL
%token COLON
%token COMMA
%token MEMBER_SOAK
%token _CLASS
%token FUNCTION_GLYPH
%token FUNCTION_GLYPH_BOUND
%token SELF
%token QUESTION_MARK
%token OBJECT_START
%token OBJECT_END
%token RANGE_INCLUSIVE
%token RANGE_EXCLUSIVE
%token BRACKET_LEFT
%token BRACKET_RIGHT
%token PARENTHESES_LEFT
%token PARENTHESES_RIGHT
%token MODULUS
%token NOT

%right POST_IF
%right IF ELSE FOR WHILE UNTIL LOOP SUPER CLASS
%right FORIN FOROF BY WHEN
%right EQUAL COLON COMPOUND_ASSIGNMENT RETURN EXTENDS
%nonassoc INDENT OUTDENT
%left LOGIC
%left COMPARE
%left RELATION
%left SHIFT
%left ADD SUBTRACT
%left MULTIPLY
%left MATH
%right UNARY
%left QUESTION_MARK
%nonassoc INCREMENT DECREMENT
%left CALL_START CALL_END

%expect 30

%%

root: 
	body { $$ = $1; tyran_parser_root(parser, $1); }

body:
	line { $$ = $1; }
	| body TERMINATOR line
	| body TERMINATOR

line: 
	expression
	| statement

statement: 
	return
	| comment

expression: 
	value
	| invocation
	| code
	| operation
	| assignment
	| if
	| while
	| switch
	| class

block: 
	INDENT OUTDENT { $$ = tyran_parser_block(0); }
	| INDENT body OUTDENT { $$ = tyran_parser_block($2); }

identifier: 
	IDENTIFIER { $$ = tyran_parser_literal_identifier($1); }

alpha_numeric: 
	NUMBER { $$ = tyran_parser_literal_number($1); }
	| STRING { $$ = tyran_parser_literal_string($1); }

literal: 
	alpha_numeric
	| UNDEFINED { $$ = tyran_parser_undefined(); }
	| TYRAN_TOKEN_NULL { $$ = tyran_parser_null(); }
	| TYRAN_TOKEN_TRUE { $$ = tyran_parser_bool(1); }
	| TYRAN_TOKEN_FALSE { $$ = tyran_parser_bool(0); }

assignment: 
	assignable EQUAL expression { $$ = tyran_parser_assignment($1, $3); }
	| assignable EQUAL TERMINATOR expression { $$ = tyran_parser_assignment($1, $4); }
	| assignable EQUAL INDENT expression OUTDENT { $$ = tyran_parser_assignment($1, $4); }

object_assignment:
	object_assignable {}
	| object_assignable COLON expression { $$ = tyran_parser_object_assignment(tyran_parser_value($1), $3); }
	| object_assignable COLON INDENT expression OUTDENT { $$ = tyran_parser_object_assignment(tyran_parser_value($1), $4); }
	| comment

object_assignable: 
	identifier
	| alpha_numeric
	| self_member

return: 
	RETURN expression {$$ = tyran_parser_return($2);}
	| RETURN {$$ = tyran_parser_return(0);}

comment: 
	COMMENT {$$ = tyran_parser_comment($1);}

code: 
	PARAM_START parameter_list PARAM_END function_glyph block {$$ = tyran_parser_code($2, $5, $4);}
	| function_glyph block {$$ = tyran_parser_code(0, $2, $1);}

function_glyph: 
	FUNCTION_GLYPH {}
	| FUNCTION_GLYPH_BOUND {}


parameter_list: 
	COMMA
	| parameter { $$ = $1; }
	| parameter_list COMMA parameter {$$ = tyran_parser_concat($1, $3);}
	| parameter_list TERMINATOR parameter {$$ = tyran_parser_concat($1, $3);}
	| parameter_list INDENT parameter_list OUTDENT {$$ = tyran_parser_concat($1, $3);}
 
parameter: 
	parameter_variable {$$ = tyran_parser_parameter($1, 0, 0);}
	| parameter_variable RANGE_EXCLUSIVE {$$ = tyran_parser_parameter($1, 0, 0);}
	| parameter_variable EQUAL expression {$$ = tyran_parser_parameter($1, $3, 0);}

parameter_variable:
	identifier
	| self_member
	| array
	| object

splat: 
	expression RANGE_EXCLUSIVE { $$ = tyran_parser_splat($1); }

basic_assignable: 
	identifier  {$$ = tyran_parser_value($1);}
	| value accessor { $$ = tyran_parser_accessor($2); }
	| invocation accessor { $$ = tyran_parser_concat(tyran_parser_value($1), $2); }
	| self_member


assignable: 
	basic_assignable
	| array { $$ = tyran_parser_value($1); }
	| object { $$ = tyran_parser_value($1); }

value: 
	assignable
	| literal { $$ = tyran_parser_value($1); }
	| parenthetical { $$ = tyran_parser_value($1); }
	| range { $$ = tyran_parser_value($1); }

accessor:
	MEMBER  identifier { $$ = tyran_parser_accessor($2); }
	| MEMBER_SOAK identifier { $$ = tyran_parser_accessor($2); }
	| SCOPING identifier { $$ = tyran_parser_accessor($2); }
	| index {}

index: 
	INDEX_START index_value INDEX_END { $$ = $2; }
	| INDEX_SOAK index { tyran_parser_index_soak($2); }

index_value: 
	expression { $$ = tyran_parser_index($1); }
	| slice { $$ = tyran_parser_slice($1); }

object: 
	OBJECT_START assign_list OBJECT_END { $$ = tyran_parser_object($2); }

assign_list:
	COMMA {}
	| object_assignment { $$ = $1; }
	| assign_list COMMA object_assignment { $$ = tyran_parser_concat($1, $3); }
	| assign_list TERMINATOR object_assignment { $$ = tyran_parser_concat($1, $3); }
	| assign_list INDENT assign_list OUTDENT { $$ = tyran_parser_concat($1, $3); }

class: 
	_CLASS basic_assignable { $$ = tyran_parser_class(0, 0, 0); }
	| _CLASS basic_assignable block { $$ = tyran_parser_class($2, 0, $3); }
	| _CLASS basic_assignable "extends" expression { $$ = tyran_parser_class($2, $4, 0); }
	| _CLASS basic_assignable "extends" expression block { $$ = tyran_parser_class($2, $4, $5); }

invocation: 
	value IDENTIFIER arguments { $$ = tyran_parser_call($1, $3, $2); }
	| invocation IDENTIFIER arguments { $$ = tyran_parser_call($1, $3, $2); }
	| SUPER { $$ = tyran_parser_call_super(0); }
	| SUPER arguments { $$ = tyran_parser_call_super($2); }

arguments: 
	CALL_START CALL_END
	| CALL_START argument_list CALL_END { $$ = tyran_parser_arguments($2); }

self: 
	SELF { $$ = tyran_parser_self(); }

self_member: 
	self identifier { tyran_parser_self_identifier($2); }

array: 
	BRACKET_LEFT BRACKET_RIGHT { $$ = tyran_parser_array(0); }
	| BRACKET_LEFT argument_list BRACKET_RIGHT { $$ = tyran_parser_array($2); }

range_dots: 
	RANGE_INCLUSIVE {}
	| RANGE_EXCLUSIVE {}

range: 
	BRACKET_LEFT expression range_dots expression BRACKET_RIGHT { $$ = tyran_parser_range($1, $3, $2); }

slice: 
	expression range_dots expression { $$ = tyran_parser_range($1, $3, $2); }
	| expression range_dots {$$ = tyran_parser_range($1, 0, $2); }
	| range_dots expression {$$ = tyran_parser_range($0, $2, $1); }
	| range_dots { $$ = tyran_parser_range(0, 0, $1); }

argument_list: 
	argument { $$ = $1; }
	| argument_list COMMA argument { $$ = tyran_parser_concat($1, $3); }
	| argument_list TERMINATOR argument { $$ = tyran_parser_concat($1, $3); }
	| INDENT argument_list OUTDENT { $$ = $2; }
	| argument_list INDENT argument_list OUTDENT { $$ = tyran_parser_concat($1, $4); }

argument: 
	expression
	| splat

basic_arguments: 
	expression
	| basic_arguments COMMA expression { $$ = tyran_parser_concat($1, $3); }

parenthetical: 
	PARENTHESES_LEFT body PARENTHESES_RIGHT { $$ = tyran_parser_parens($2); }
	| PARENTHESES_LEFT INDENT body OUTDENT PARENTHESES_RIGHT { $$ = tyran_parser_parens($3); }

while_condition: 
	WHILE expression { $$ = tyran_parser_while($2); }

while: 
	while_condition block { $$ = tyran_parser_while_condition($1, $2); }


switch: 
	SWITCH expression INDENT whens OUTDENT { $$ = tyran_parser_switch($2, $4, 0); }
	| SWITCH expression INDENT whens ELSE block OUTDENT { $$ = tyran_parser_switch($2, $4, $6); }
	| SWITCH INDENT whens OUTDENT { $$ = tyran_parser_switch($2, $4, 0); }
	| SWITCH INDENT whens ELSE block OUTDENT { $$ = tyran_parser_switch($2, $4, 0); }

whens: 
	when
	| whens when { tyran_parser_concat($1, $2); }

when: 
	LEADING_WHEN basic_arguments block { tyran_parser_when($2, $3); }
	| LEADING_WHEN basic_arguments block TERMINATOR { tyran_parser_when($2, $3); }

if_block: 
	IF expression block { $$ = tyran_parser_if($2, $3); }
	| if_block ELSE IF expression block {tyran_parser_if_else($1, $3); }

if: 
	if_block
	| if_block ELSE block { tyran_parser_if_else($1, $3); }
	| statement POST_IF expression {}
	| expression POST_IF expression {}

operation: 
	ADD expression { $$ = tyran_parser_operand_unary(ADD, $2, 0); }
	| SUBTRACT expression { $$ = tyran_parser_operand_unary(SUBTRACT, $2, 0); }
	| DECREMENT basic_assignable { $$ = tyran_parser_operand_unary(DECREMENT, $2, 0); }
	| INCREMENT basic_assignable { $$ = tyran_parser_operand_unary(INCREMENT, $2, 0); }
	| basic_assignable DECREMENT {$$ = tyran_parser_operand_unary(DECREMENT, $1, 1); }
	| basic_assignable INCREMENT {$$ = tyran_parser_operand_unary(INCREMENT, $1, 1); }
	| expression QUESTION_MARK {$$ = tyran_parser_operand_unary(QUESTION_MARK, $1, 1); }
	| expression ADD expression { $$ = tyran_parser_operand_binary('+', $1, $3); }
	| expression SUBTRACT expression { $$ = tyran_parser_operand_binary('-', $1, $3); }
	| expression MULTIPLY expression { $$ = tyran_parser_operand_binary('*', $1, $3); }
	| expression DIVIDE expression { $$ = tyran_parser_operand_binary('/', $1, $3); }
	| basic_assignable COMPOUND_ASSIGNMENT expression { $$ = tyran_parser_compound_assignment($1, $3, $2); }
	| basic_assignable COMPOUND_ASSIGNMENT INDENT expression OUTDENT {$$ = tyran_parser_compound_assignment($1, $3, $2); }
	| basic_assignable EXTENDS expression { tyran_parser_extends($1, $3); }
%%
