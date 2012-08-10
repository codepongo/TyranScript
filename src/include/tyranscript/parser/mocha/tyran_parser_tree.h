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

enum tyran_parser_type {
	TYRAN_PARSER_NODE_TYPE_NUMBER,
	TYRAN_PARSER_NODE_TYPE_BOOLEAN,
	TYRAN_PARSER_NODE_TYPE_NULL,
	TYRAN_PARSER_NODE_TYPE_UNDEFINED,
	TYRAN_PARSER_NODE_TYPE_STRING,
	TYRAN_PARSER_NODE_TYPE_IDENTIFIER,
	TYRAN_PARSER_NODE_TYPE_ASSIGNMENT,
	TYRAN_PARSER_NODE_TYPE_COMPOUND_ASSIGNMENT,
	TYRAN_PARSER_NODE_TYPE_OPERAND_BINARY,
	TYRAN_PARSER_NODE_TYPE_OPERAND_UNARY,
	TYRAN_PARSER_NODE_TYPE_IF,
	TYRAN_PARSER_NODE_TYPE_IF_ELSE,
	TYRAN_PARSER_NODE_TYPE_WHILE,
	TYRAN_PARSER_NODE_TYPE_FOR,
	TYRAN_PARSER_NODE_TYPE_CLASS,
	TYRAN_PARSER_NODE_TYPE_WHEN,
	TYRAN_PARSER_NODE_TYPE_CASE,
	TYRAN_PARSER_NODE_TYPE_OBJECT_ASSIGNMENT,
	TYRAN_PARSER_NODE_TYPE_OBJECT,
	TYRAN_PARSER_NODE_TYPE_ARGUMENTS,
};

typedef enum tyran_parser_binary_operand_type {
	TYRAN_PARSER_DIVIDE,
	TYRAN_PARSER_MULTIPLY,
	TYRAN_PARSER_MODULUS,
	TYRAN_PARSER_ASSIGNMENT,
	TYRAN_PARSER_ADD,
	TYRAN_PARSER_SUBTRACT,
	TYRAN_PARSER_INDEX,
	TYRAN_PARSER_COMMA,
	TYRAN_PARSER_INVOKE,
	TYRAN_PARSER_EQUAL,
	TYRAN_PARSER_NOT_EQUAL,
	TYRAN_PARSER_GREATER_EQUAL,
	TYRAN_PARSER_GREATER,
	TYRAN_PARSER_LESS_EQUAL,
	TYRAN_PARSER_LESS,
	TYRAN_PARSER_THEN,
	TYRAN_PARSER_ELSE,
	TYRAN_PARSER_LINE,
	TYRAN_PARSER_WHILE,
	TYRAN_PARSER_CONCAT,
	TYRAN_PARSER_IN,
	TYRAN_PARSER_WHEN,
	TYRAN_PARSER_CASE,
	TYRAN_PARSER_RANGE,
	TYRAN_PARSER_RANGE_INCLUSIVE,
	TYRAN_PARSER_BINARY_OPERAND_TYPE_MAX
} tyran_parser_binary_operand_type;

typedef enum tyran_parser_unary_operand_type {
	TYRAN_PARSER_UNARY_OPERAND_ADD,
	TYRAN_PARSER_UNARY_OPERAND_SUBTRACT,
	TYRAN_PARSER_UNARY_PARENTHESES,
	TYRAN_PARSER_UNARY_BLOCK,
	TYRAN_PARSER_UNARY_IF,
	TYRAN_PARSER_UNARY_BRACKET,
	TYRAN_PARSER_UNARY_OPERAND_TYPE_MAX
} tyran_parser_unary_operand_type;

typedef struct tyran_parser_node
{
	enum tyran_parser_type type;
} tyran_parser_node;

typedef struct tyran_parser_node_value
{
	tyran_parser_node node;
} tyran_parser_node_value;

typedef struct tyran_parser_node_number
{
	tyran_parser_node node;
	tyran_number number;
} tyran_parser_node_number;

typedef struct tyran_parser_node_boolean
{
	tyran_parser_node node;
	tyran_boolean boolean;
} tyran_parser_node_boolean;

typedef struct tyran_parser_node_string
{
	tyran_parser_node node;
	const char* string;
	int length;
} tyran_parser_node_string;

typedef struct tyran_parser_node_identifier
{
	tyran_parser_node node;
	const char* string;
	int length;
} tyran_parser_node_identifier;

typedef struct tyran_parser_node_assignment
{
	tyran_parser_node node;
	tyran_parser_node* source;
	tyran_parser_node* target;
} tyran_parser_node_assignment;

typedef struct tyran_parser_node_compound_assignment
{
	tyran_parser_node node;
	int operator_type;
	tyran_parser_node* source;
	tyran_parser_node* target;
} tyran_parser_node_compound_assignment;

typedef struct tyran_parser_node_operand_binary
{
	tyran_parser_node node;
	int operator_type;
	tyran_parser_node* left;
	tyran_parser_node* right;
} tyran_parser_node_operand_binary;

typedef struct tyran_parser_node_operand_unary
{
	tyran_parser_node node;
	int operator_type;
	tyran_parser_node* expression;
	tyran_boolean post;
} tyran_parser_node_operand_unary;

typedef struct tyran_parser_node_if
{
	tyran_parser_node node;
	tyran_parser_node* expression;
	tyran_parser_node* then_block;
} tyran_parser_node_if;


typedef struct tyran_parser_node_if_else
{
	tyran_parser_node node;
	tyran_parser_node* expression;
	tyran_parser_node* then_block;
	tyran_parser_node* else_block;
} tyran_parser_node_if_else;

typedef struct tyran_parser_node_while
{
	tyran_parser_node node;
	tyran_parser_node* condition;
	tyran_parser_node* block;
} tyran_parser_node_while;

typedef struct tyran_parser_node_for
{
	tyran_parser_node node;
	tyran_parser_node* variables;
	tyran_parser_node* collection;
	tyran_parser_node* block;
} tyran_parser_node_for;


typedef struct tyran_parser_node_when
{
	tyran_parser_node node;
	tyran_parser_node* expression;
	tyran_parser_node* block;
} tyran_parser_node_when;

typedef struct tyran_parser_node_case
{
	tyran_parser_node node;
	tyran_parser_node* expression;
	tyran_parser_node* block;
} tyran_parser_node_case;

typedef struct tyran_parser_node_class
{
	tyran_parser_node node;
	tyran_parser_node* name;
	tyran_parser_node* extends;
	tyran_parser_node* block;
} tyran_parser_node_class;

typedef struct tyran_parser_node_object
{
	tyran_parser_node node;
	tyran_parser_node* assignment_list;
} tyran_parser_node_object;

typedef struct tyran_parser_node_object_assignment
{
	tyran_parser_node node;
	tyran_parser_node* name;
	tyran_parser_node* source;
} tyran_parser_node_object_assignment;

typedef struct tyran_parser_node_arguments
{
	tyran_parser_node node;
	tyran_parser_node* argument_list;
} tyran_parser_node_arguments;

typedef struct tyran_parser_node_call
{
	tyran_parser_node node;
	tyran_parser_node* function_node;
	tyran_parser_node* arguments;
} tyran_parser_node_call;

typedef struct tyran_parser_node_null
{
	tyran_parser_node node;
} tyran_parser_node_null;

typedef struct tyran_parser_node_undefined
{
	tyran_parser_node node;
} tyran_parser_node_undefined;



void tyran_parser_node_print(const char* description, tyran_parser_node* current_root, tyran_parser_node* node);

struct tyran_parser* tyran_parser_new(const char* buf);
int tyran_parser_parse(const char* buf, int length);


void tyran_parser_root(tyran_parser* parser, NODE root);
NODE tyran_parser_block();
NODE tyran_parser_assignment(NODE target, NODE source);
NODE tyran_parser_object_assignment(NODE a, NODE b);
NODE tyran_parser_compound_assignment(int type, NODE b, NODE c);
NODE tyran_parser_value(NODE a);
NODE tyran_parser_return(NODE expression);
NODE tyran_parser_comment(NODE comment);
NODE tyran_parser_code(NODE a, NODE b, NODE c);
tyran_parser_node_operand_binary* tyran_parser_concat(NODE a, NODE b);
NODE tyran_parser_parameter(NODE a, NODE b, NODE c);
NODE tyran_parser_splat(NODE a);
NODE tyran_parser_accessor(NODE a);
NODE tyran_parser_index_soak(NODE a);
NODE tyran_parser_index(NODE a);
NODE tyran_parser_slice(NODE b);
NODE tyran_parser_object(NODE a);
NODE tyran_parser_class(NODE name, NODE extends, NODE block);
NODE tyran_parser_arguments(NODE a);
NODE tyran_parser_self();
NODE tyran_parser_self_identifier(NODE a);
NODE tyran_parser_array(NODE a);
NODE tyran_parser_range(NODE a, NODE b, NODE c);
NODE tyran_parser_parens(NODE a);
NODE tyran_parser_while(NODE condition, NODE block);
NODE tyran_parser_for(NODE variables, NODE expression, NODE block);
NODE tyran_parser_case(NODE expression, NODE block);
NODE tyran_parser_when(NODE a, NODE b);
NODE tyran_parser_if(NODE expression, NODE then_block);
NODE tyran_parser_if_else(NODE expression, NODE then_block, NODE else_block);
tyran_parser_node_operand_unary* tyran_parser_operand_unary(int operator_type, NODE b, tyran_boolean post);
tyran_parser_node_operand_binary* tyran_parser_operand_binary(tyran_parser_binary_operand_type operator_type, NODE b, NODE c);
NODE tyran_parser_null();
NODE tyran_parser_bool(int boolean);
NODE tyran_parser_undefined();
NODE tyran_parser_literal_number(float* a);
NODE tyran_parser_literal_string(const char* string);
NODE tyran_parser_literal_identifier(const char* string);
NODE tyran_parser_call_super(NODE a);


tyran_parser_node_operand_binary* tyran_parser_binary_operator_type_cast(NODE node, int operator_type);
tyran_parser_node_operand_binary* tyran_parser_binary_operator_cast(NODE node);


#endif
