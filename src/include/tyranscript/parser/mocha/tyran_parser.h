#ifndef _TYRAN_PARSER_H_
#define _TYRAN_PARSER_H_

#include <tyranscript/parser/tyran_lexer.h>

struct tyran_parser_node;
#define NODE struct tyran_parser_node*

#define YYSTYPE void*
#define YYLTYPE struct tyran_lexer_position_info

struct tyran_string;
struct tyran_lexer;
struct tyran_lexer_position_info;

typedef struct tyran_parser {
	struct tyran_lexer* lexer;
	int position;
	NODE root;
} tyran_parser;


int TYRAN_PARSER_lex(YYSTYPE *lvalp, struct tyran_lexer_position_info* llocp, tyran_parser* parser);
void TYRAN_PARSER_error(struct tyran_lexer_position_info* lexer_position_info, tyran_parser* ps, const char* message);

struct tyran_parser* tyran_parser_new(const char* buf);
int tyran_parser_parse(tyran_parser* parser);


void tyran_parser_root(tyran_parser* parser, NODE root);
NODE tyran_parser_block(NODE b);
NODE tyran_parser_assignment(NODE target, NODE source);
NODE tyran_parser_object_assignment(NODE a, NODE b);
NODE tyran_parser_compound_assignment(int type, NODE b, NODE c);
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
NODE tyran_parser_operand_unary(int operator_type, NODE b, tyran_boolean post);
NODE tyran_parser_operand_binary(char operator_type, NODE b, NODE c);
NODE tyran_parser_extends(NODE a, NODE b);
NODE tyran_parser_null();
NODE tyran_parser_bool(int boolean);
NODE tyran_parser_undefined();
NODE tyran_parser_literal_number(float* a);
NODE tyran_parser_literal_string(const char* string);
NODE tyran_parser_literal_identifier(const char* string);
NODE tyran_parser_call_super(NODE a);

#endif
