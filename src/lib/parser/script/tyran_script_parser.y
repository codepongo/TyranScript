
%token COMMENT
%token UNARY
%token EXTENDS
%token COMPARE
%token FOROF
%token IDENTIFIER
%token TERMINATOR
%token INDEX_START
%token CLASS
%token ELSE
%token LOOP
%token COMPOUND ASSIGN
%token SHIFT
%token BOOL
%token INDENT
%token SWITCH
%token PARAM_END
%token NULL
%token CALL_START
%token UNDEFINED
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
%token COMPOUND_ASSIGN

%%

root: 
	body
	| block TERMINATOR

body:
	line {block_wrap $1}
	| body TERMINATOR line {$1.push $3}
	| body TERMINATOR

line: 
	expression
	| statement

statement: 
	return
	| comment
	| STATEMENT {new literal $1}

expression: 
	value
	| invocation
	| code
	| operation
	| assignment
	| if
	| while
	| for
	| switch
	| class

block: 
	INDENT OUTDENT {block_create}
	| INDENT body OUTDENT {$$ = $2;}

identifier: 
	IDENTIFIER {$$ = literal_create_identifier($1);}

alpha_numeric: 
	NUMBER {$$ = literal_create_number($1);}
	| STRING {$$ = literal_create_string($1);}

literal: 
	alpha_numeric
	| UNDEFINED {$$ = undefined_create();}
	| NULL {$$ = null_create();}
	| BOOL {$$ = bool_create($1);}

assignment: 
	assignable '=' expression {$$ = tyran_parser_assignment($1, $3);}
	| assignable '=' TERMINATOR expression {$$ = tyran_parser_assignment($1, $4);}
	| assignable '=' INDENT expression OUTDENT {$$ = tyran_parser_assignment($1, $4);}

object_assignment:
	object_assignable {new value $1}
	| object_assignable ':' expression {$$ = tyran_parser_assignment(tyran_parser_value($1), $3, "object");}
	| object_assignable ':' INDENT expression OUTDENT {$$ = tyran_parser_assignment(tyran_parser_value($1), $4, "object");}
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
	"->" {}
	| "=>" {}

optional_comma: 
	','

parameter_list: 
	','
	| parameter {$1}
	| parameter_list ',' parameter {$$ = tyran_parser_concat($1, $3);}
	| parameter_list optional_comma TERMINATOR parameter {$$ = tyran_parser_concat($1, $4);}
	| parameter_list optional_comma INDENT parameter_list optional_comma OUTDENT {$$ = tyran_parser_concat($1, $4);}

parameter: 
	parameter_variable {$$ = tyran_parser_parameter($1, 0, 0);}
	| parameter_variable "..." {$$ = tyran_parser_parameter($1, 0, 1);}
	| parameter_variable '=' expression {$$ = tyran_parser_parameter($1, $3, 0);}

parameter_variable:
	identifier
	| self_member
	| array
	| object

splat: 
	expression "..." {tyran_parser_splat($1)}

basic_assignable: 
	identifier  {$$ = tyran_parser_value($1);}
	| value accessor {$1.add $2}
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
	| self {}

accessor:
	'.'  identifier { $$ = tyran_parser_accessor($2); }
	| "?." identifier { $$ = tyran_parser_accessor($2); }
	| "::" identifier { $$ = tyran_parser_accessor(tyran_parser_accessor()); }
	| "::" { $$ = tyran_parser_accessor(tyran_parser_value('prototype')); }
	| index {}

index: 
	INDEX_START index_value INDEX_END {$2}
	| INDEX_SOAK index {extend $2, soak : yes}

index_value: 
	expression { $$ = tyran_parser_index($1); }
	| slice { $$ = tyran_parser_slice($1); }

object: 
	'{' assign_list '}' { $$ = tyran_parser_object($2); }

assign_list:
	',' {}
	| object_assignment {$1}
	| assign_list ',' object_assignment { $$ = tyran_parser_concat($1, $3); }
	| assign_list optional_comma TERMINATOR object_assignment { $$ = tyran_parser_concat($1, $4); }
	| assign_list optional_comma INDENT assign_list optional_comma OUTDENT { $$ = tyran_parser_concat($1, $4); }

class: 
	CLASS basic_assignable { $$ = tyran_parser_class(0, 0, 0); }
	| CLASS basic_assignable block { $$ = tyran_parser_class($2, null, $3); }
	| CLASS basic_assignable EXTENDS expression { $$ = tyran_parser_class($2, $4, 0); }
	| CLASS basic_assignable EXTENDS expression block { $$ = tyran_parser_class($2, $4, $5); }

invocation: 
	value IDENTIFIER arguments { $$ = tyran_parser_call($1, $3, $2); }
	| invocation IDENTIFIER arguments {new Call $1, $3, $2}
	| SUPER {new Call super, new splat new literal arguments}
	| SUPER arguments {new Call super, $2}

arguments: 
	CALL_START CALL_END
	| CALL_START argument_list optional_comma CALL_END {$2}

self: 
	'@' {new value new literal this}

self_member: 
	'@' identifier {new value new literal(this), new Access($2)], this}

array: 
	'[' ']' {new Arr}
	| '[' argument_list optional_comma ']' {new Arr $2}

range_dots: 
	".." {inclusive}
	| "..." {exclusive}

range: 
	'[' expression range_dots expression ']' {new range $1, $3, $2}

slice: 
	expression range_dots expression {new range $1, $3, $2}
	| expression range_dots {new range $1, null, $2}
	| range_dots expression {new range null, $2, $1}
	| range_dots {new range null, null, $1}

argument_list: 
	argument {$1}
	| argument_list ',' argument {$1.concat $3}
	| argument_list optional_comma TERMINATOR argument {$1.concat $4}
	| INDENT argument_list optional_comma OUTDENT {$2}
	| argument_list optional_comma INDENT argument_list optional_comma OUTDENT {$1.concat $4}

argument: 
	expression
	| splat

basic_arguments: 
	expression
	| basic_arguments ',' expression {concat $1, $3}

parenthetical: 
	'(' body ')' {new Parens $2}
	| '(' INDENT body OUTDENT ')' {new Parens $3}

while_condition: 
	WHILE expression {new While $2}
	| WHILE expression WHEN expression {new While $2, guard: $4}
	| UNTIL expression {new While $2, invert: true}
	| UNTIL expression WHEN expression {new While $2, invert: true, guard: $4}

while: 
	while_condition block {$1.addBody $2}
	| statement  while_condition {$2.addBody block.wrap $1}
	| expression while_condition {$2.addBody block.wrap $1}
	| loop {$1}

loop: 
	LOOP block {new While(new literal true).addBody $2}
	| LOOP expression {new While(new literal true).addBody block.wrap $2}

for: 
	statement for_body {new for $1, $2}
	| expression for_body {new for $1, $2}
	| for_body block {new for $2, $1}

for_body: 
	FOR range {source: new value($2)}
	| for_start for_source {}

for_start: 
	FOR for_variables {$2}
	| FOR OWN for_variables {$3.own = yes; $3}

for_value: 
	identifier
	| self_member
	| array {new value $1}
	| object {new value $1}

for_variables: 
	for_value {$1}
	| for_value ',' for_value {$1, $3}

for_source: 
	FORIN expression {source: $2}
	| FOROF expression {source: $2, object: yes}
	| FORIN expression WHEN expression {source: $2, guard: $4}
	| FOROF expression WHEN expression {source: $2, guard: $4, object: yes}
	| FORIN expression BY expression {source: $2, step: $4}
	| FORIN expression WHEN expression BY expression {source: $2, guard: $4, step: $6}
	| FORIN expression BY expression WHEN expression {source: $2, step:  $4, guard: $6}

switch: 
	SWITCH expression INDENT whens OUTDENT {new switch $2, $4}
	| SWITCH expression INDENT whens ELSE block OUTDENT {new switch $2, $4, $6}
	| SWITCH INDENT whens OUTDENT {new switch null, $3}
	| SWITCH INDENT whens ELSE block OUTDENT {new switch null, $3, $5}

whens: 
	when
	| whens when {$1.concat $2}

when: 
	LEADING_WHEN basic_arguments block {$2, $3}
	| LEADING_WHEN basic_arguments block TERMINATOR {$2, $3}

if_block: 
	IF expression block {new if $2, $3, type: $1}
	| if_block ELSE IF expression block {$1.addElse new if $4, $5, type: $3}

if: 
	if_block
	| if_block ELSE block {$1.addElse $3}
	| statement POST_IF expression {new if $3, block.wrap($1]), type: $2, statement: true}
	| expression POST_IF expression {new if $3, block.wrap($1]), type: $2, statement: true}

operation: 
	UNARY expression {new Op $1 , $2}
	| '-'     expression {new Op -, $2), prec: UNARY}
	| '+'    expression {new Op +, $2), prec: UNARY}
	| "--" basic_assignable {new Op --, $2}
	| "++" basic_assignable {new Op ++, $2}
	| basic_assignable "--" {new Op --, $1, null, true}
	| basic_assignable "++" {new Op ++, $1, null, true}
	| expression '?' {new Existence $1}
	| expression '+'  expression {new Op + , $1, $3}
	| expression '-'  expression {new Op - , $1, $3}

	| expression MATH     expression {new Op $2, $1, $3}
	| expression SHIFT    expression {new Op $2, $1, $3}
	| expression COMPARE  expression {new Op $2, $1, $3}
	| expression LOGIC    expression {new Op $2, $1, $3}
	| expression RELATION expression {if $2.charAt(0) is !new Op($2.., $1, $3).invert() else new Op $2, $1, $3}
	| basic_assignable COMPOUND_ASSIGN expression {new Assign $1, $3, $2}
	| basic_assignable COMPOUND_ASSIGN INDENT expression OUTDENT {new Assign $1, $4, $2}
	| basic_assignable EXTENDS expression {new Extends $1, $3}
%%
