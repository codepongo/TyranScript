#ifndef _TYRAN_PARSER_H_
#define _TYRAN_PARSER_H_

#define NODE void*

#define YYSTYPE void*


struct tyran_string;
struct tyran_lexer;

typedef struct tyran_parser {
	struct tyran_lexer* lexer;
	int position;
} tyran_parser;


struct tyran_parser* tyran_parser_alloc(const char* buf);
int tyran_parser_parse(tyran_parser* parser);

NODE tyran_parser_block(NODE b);
NODE tyran_parser_assignment(NODE target, NODE source);
NODE tyran_parser_object_assignment(NODE a, NODE b);
NODE tyran_parser_compound_assignment(NODE a, NODE b, NODE c);
NODE tyran_parser_value(NODE a);
NODE tyran_parser_return(NODE expression);
NODE tyran_parser_comment(NODE comment);
NODE tyran_parser_code(NODE a, NODE b, NODE c);
NODE tyran_parser_concat(NODE a, NODE b);
NODE tyran_parser_parameter(NODE a, NODE b, NODE c);
NODE tyran_parser_splat(NODE a);
NODE tyran_parser_accessor(NODE a);
NODE tyran_parser_index_soak(NODE a);
NODE tyran_parser_index(NODE a);
NODE tyran_parser_slice(NODE b);
NODE tyran_parser_object(NODE a);
NODE tyran_parser_class(NODE name, NODE extends, NODE block);
NODE tyran_parser_call(NODE a, NODE b, NODE c);
NODE tyran_parser_arguments(NODE a);
NODE tyran_parser_self();
NODE tyran_parser_self_identifier(NODE a);
NODE tyran_parser_array(NODE a);
NODE tyran_parser_range(NODE a, NODE b, NODE c);
NODE tyran_parser_parens(NODE a);
NODE tyran_parser_while(NODE a);
NODE tyran_parser_while_condition(NODE a, NODE b);
NODE tyran_parser_for(NODE a, NODE b);
NODE tyran_parser_for_body(NODE a);
NODE tyran_parser_for_start(NODE a, NODE b);
NODE tyran_parser_for_variables(NODE a);
NODE tyran_parser_switch(NODE a, NODE b, NODE block);
NODE tyran_parser_when(NODE a, NODE b);
NODE tyran_parser_if(NODE a, NODE b);
NODE tyran_parser_if_else(NODE a, NODE b);
NODE tyran_parser_operand(NODE a, NODE b);
NODE tyran_parser_operand_binary(NODE a, NODE b, NODE c);
NODE tyran_parser_extends(NODE a, NODE b);
NODE tyran_parser_null();
NODE tyran_parser_bool(int boolean);
NODE tyran_parser_undefined();
NODE tyran_parser_literal_number(NODE a);
NODE tyran_parser_literal_string(struct tyran_string* string);
NODE tyran_parser_literal_identifier(struct tyran_string* string);
NODE tyran_parser_call_super(NODE a);

#endif
