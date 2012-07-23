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

%left '.' "?." "::"
%left CALL_START CALL_END
%nonassoc "++" "--"
%left '?'
%right UNARY
%left MATH
%left '+' '-'
%left SHIFT
%left RELATION
%left COMPARE
%left LOGIC
%nonassoc INDENT OUTDENT
%right '=' ':' COMPOUND_ASSIGNMENT RETURN EXTENDS
%right FORIN FOROF BY WHEN
%right IF ELSE FOR WHILE UNTIL LOOP SUPER CLASS
%right POST_IF

%expect 19

%%

root: 
	body

body:
	line { $$ = $1; }

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
	assignable '=' expression { $$ = tyran_parser_assignment($1, $3); }
	| assignable '=' TERMINATOR expression { $$ = tyran_parser_assignment($1, $4); }
	| assignable '=' INDENT expression OUTDENT { $$ = tyran_parser_assignment($1, $4); }

object_assignment:
	object_assignable {}
	| object_assignable ':' expression { $$ = tyran_parser_object_assignment(tyran_parser_value($1), $3); }
	| object_assignable ':' INDENT expression OUTDENT { $$ = tyran_parser_object_assignment(tyran_parser_value($1), $4); }
	| comment

object_assignable: 
	identifier
	| alpha_numeric
	| self_member

return: 
	"return" expression {$$ = tyran_parser_return($2);}
	| "return" {$$ = tyran_parser_return(0);}

comment: 
	COMMENT {$$ = tyran_parser_comment($1);}

code: 
	PARAM_START parameter_list PARAM_END function_glyph block {$$ = tyran_parser_code($2, $5, $4);}
	| function_glyph block {$$ = tyran_parser_code(0, $2, $1);}

function_glyph: 
	"->" {}
	| "=>" {}

optional_comma: 
	','

parameter_list: 
	','
	| parameter { $$ = $1; }
	| parameter_list ',' parameter {$$ = tyran_parser_concat($1, $3);}
	| parameter_list optional_comma TERMINATOR parameter {$$ = tyran_parser_concat($1, $4);}
	| parameter_list optional_comma INDENT parameter_list optional_comma OUTDENT {$$ = tyran_parser_concat($1, $4);}
 
parameter: 
	parameter_variable {$$ = tyran_parser_parameter($1, 0, 0);}
	| parameter_variable "..." {$$ = tyran_parser_parameter($1, 0, 0);}
	| parameter_variable '=' expression {$$ = tyran_parser_parameter($1, $3, 0);}

parameter_variable:
	identifier
	| self_member
	| array
	| object

splat: 
	expression "..." { $$ = tyran_parser_splat($1); }

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
	'.'  identifier { $$ = tyran_parser_accessor($2); }
	| "?." identifier { $$ = tyran_parser_accessor($2); }
	| "::" identifier { $$ = tyran_parser_accessor($2); }
	| index {}

index: 
	INDEX_START index_value INDEX_END { $$ = $2; }
	| INDEX_SOAK index { tyran_parser_index_soak($2); }

index_value: 
	expression { $$ = tyran_parser_index($1); }
	| slice { $$ = tyran_parser_slice($1); }

object: 
	'{' assign_list '}' { $$ = tyran_parser_object($2); }

assign_list:
	',' {}
	| object_assignment { $$ = $1; }
	| assign_list ',' object_assignment { $$ = tyran_parser_concat($1, $3); }
	| assign_list optional_comma TERMINATOR object_assignment { $$ = tyran_parser_concat($1, $4); }
	| assign_list optional_comma INDENT assign_list optional_comma OUTDENT { $$ = tyran_parser_concat($1, $4); }

class: 
	"class" basic_assignable { $$ = tyran_parser_class(0, 0, 0); }
	| "class" basic_assignable block { $$ = tyran_parser_class($2, 0, $3); }
	| "class" basic_assignable "extends" expression { $$ = tyran_parser_class($2, $4, 0); }
	| "class" basic_assignable "extends" expression block { $$ = tyran_parser_class($2, $4, $5); }

invocation: 
	value IDENTIFIER arguments { $$ = tyran_parser_call($1, $3, $2); }
	| invocation IDENTIFIER arguments { $$ = tyran_parser_call($1, $3, $2); }
	| SUPER { $$ = tyran_parser_call_super(0); }
	| SUPER arguments { $$ = tyran_parser_call_super($2); }

arguments: 
	CALL_START CALL_END
	| CALL_START argument_list CALL_END { $$ = tyran_parser_arguments($2); }

self: 
	'@' { $$ = tyran_parser_self(); }

self_member: 
	self identifier { tyran_parser_self_identifier($2); }

array: 
	'[' ']' { $$ = tyran_parser_array(0); }
	| '[' argument_list ']' { $$ = tyran_parser_array($2); }

range_dots: 
	".." {}
	| "..." {}

range: 
	'[' expression range_dots expression ']' { $$ = tyran_parser_range($1, $3, $2); }

slice: 
	expression range_dots expression { $$ = tyran_parser_range($1, $3, $2); }
	| expression range_dots {$$ = tyran_parser_range($1, 0, $2); }
	| range_dots expression {$$ = tyran_parser_range($0, $2, $1); }
	| range_dots { $$ = tyran_parser_range(0, 0, $1); }

argument_list: 
	argument { $$ = $1; }
	| argument_list ',' argument { $$ = tyran_parser_concat($1, $3); }
	| argument_list TERMINATOR argument { $$ = tyran_parser_concat($1, $3); }
	| INDENT argument_list OUTDENT { $$ = $2; }
	| argument_list INDENT argument_list OUTDENT { $$ = tyran_parser_concat($1, $4); }

argument: 
	expression
	| splat

basic_arguments: 
	expression
	| basic_arguments ',' expression { $$ = tyran_parser_concat($1, $3); }

parenthetical: 
	'(' body ')' { $$ = tyran_parser_parens($2); }
	| '(' INDENT body OUTDENT ')' { $$ = tyran_parser_parens($3); }

while_condition: 
	WHILE expression { $$ = tyran_parser_while($2); }

while: 
	while_condition block { $$ = tyran_parser_while_condition($1, $2); }


switch: 
	"switch" expression INDENT whens OUTDENT { $$ = tyran_parser_switch($2, $4, 0); }
	| "switch" expression INDENT whens ELSE block OUTDENT { $$ = tyran_parser_switch($2, $4, $6); }
	| "switch" INDENT whens OUTDENT { $$ = tyran_parser_switch($2, $4, 0); }
	| "switch" INDENT whens ELSE block OUTDENT { $$ = tyran_parser_switch($2, $4, 0); }

whens: 
	when
	| whens when { tyran_parser_concat($1, $2); }

when: 
	LEADING_WHEN basic_arguments block { tyran_parser_when($2, $3); }
	| LEADING_WHEN basic_arguments block TERMINATOR { tyran_parser_when($2, $3); }

if_block: 
	"if" expression block { $$ = tyran_parser_if($2, $3); }
	| if_block "else" "if" expression block {tyran_parser_if_else($1, $3); }

if: 
	if_block
	| if_block "else" block { tyran_parser_if_else($1, $3); }
	| statement POST_IF expression {}
	| expression POST_IF expression {}

operation: 
	UNARY expression { $$ = tyran_parser_operand($1, $2); }
	| '-' expression { $$ = tyran_parser_operand($1, $2); }
	| '+' expression { $$ = tyran_parser_operand($1, $2); }
	| "--" basic_assignable { $$ = tyran_parser_operand($1, $2); }
	| "++" basic_assignable { $$ = tyran_parser_operand($1, $2); }
	| basic_assignable "--" {$$ = tyran_parser_operand($1, $2); }
	| basic_assignable "++" {$$ = tyran_parser_operand($1, $2); }
	| expression '?' {$$ = tyran_parser_operand($1, $2); }
	| expression '+'  expression { $$ = tyran_parser_operand_binary($2, $1, $3); }
	| expression '-'  expression { $$ = tyran_parser_operand_binary($2, $1, $3); }

	| expression MATH expression { $$ = tyran_parser_operand_binary($2, $1, $3); }
	| expression SHIFT expression { $$ = tyran_parser_operand_binary($2, $1, $3); }
	| expression COMPARE expression { $$ = tyran_parser_operand_binary($2, $1, $3); }
	| expression LOGIC expression { $$ = tyran_parser_operand_binary($2, $1, $3); }
	| basic_assignable COMPOUND_ASSIGNMENT expression { $$ = tyran_parser_compound_assignment($1, $3, $2); }
	| basic_assignable COMPOUND_ASSIGNMENT INDENT expression OUTDENT {$$ = tyran_parser_compound_assignment($1, $3, $2); }
	| basic_assignable EXTENDS expression { tyran_parser_extends($1, $3); }
%%
