#include <tyranscript/parser/mocha/tyran_parser.h>
#include <tyranscript/parser/tyran_lexer.h>
#include "tyran_script_parser.tab.h"
#include <tyranscript/tyran_string.h>

enum tyran_parser_type {
	TYRAN_PARSER_NODE_TYPE_NUMBER,
	TYRAN_PARSER_NODE_TYPE_BOOLEAN,
	TYRAN_PARSER_NODE_TYPE_STRING,
	TYRAN_PARSER_NODE_TYPE_RETURN,
	TYRAN_PARSER_NODE_TYPE_IDENTIFIER,
	TYRAN_PARSER_NODE_TYPE_ASSIGNMENT,
	TYRAN_PARSER_NODE_TYPE_COMPOUND_ASSIGNMENT,
	TYRAN_PARSER_NODE_TYPE_OPERAND_BINARY,
	TYRAN_PARSER_NODE_TYPE_OPERAND_UNARY,
	TYRAN_PARSER_NODE_TYPE_CLASS,
	TYRAN_PARSER_NODE_TYPE_OBJECT_ASSIGNMENT,
	TYRAN_PARSER_NODE_TYPE_OBJECT,
	TYRAN_PARSER_NODE_TYPE_CONCAT
};

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
	char operator_type;
	tyran_parser_node* left;
	tyran_parser_node* right;
} tyran_parser_node_operand_binary;

typedef struct tyran_parser_node_operand_unary
{
	tyran_parser_node node;
	char operator_type;
	tyran_parser_node* expression;
	tyran_boolean post;
} tyran_parser_node_operand_unary;

typedef struct tyran_parser_node_return
{
	tyran_parser_node node;
	tyran_parser_node* expression;
} tyran_parser_node_return;

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

typedef struct tyran_parser_node_concat
{
	tyran_parser_node node;
	tyran_parser_node** nodes;
	int length;
} tyran_parser_node_concat;


void TYRAN_PARSER_NODE_PRINT_HELPER_OUTPUT(const char* buf, const char* description, int tab_count)
{
	char tabs[200];
	tyran_memset_type_n(tabs, '\t', tab_count);
	tabs[tab_count] = 0;
	
	TYRAN_LOG("%s%s %s", tabs, description, buf);
}

void TYRAN_PARSER_NODE_PRINT_HELPER(const char* description, tyran_parser_node* node, int tab_count)
{

	const int buf_size = 256;
	char buf[buf_size];
	buf[0] = 0;
	if (!node) {
		tyran_snprintf(buf, buf_size, "null");
		TYRAN_PARSER_NODE_PRINT_HELPER_OUTPUT(buf, description, tab_count);
	} else {
	
	switch (node->type)
	{
	case TYRAN_PARSER_NODE_TYPE_NUMBER:
		{
			tyran_parser_node_number* number = (tyran_parser_node_number*)node;
			tyran_snprintf(buf, buf_size, "number:%f", number->number);
			TYRAN_PARSER_NODE_PRINT_HELPER_OUTPUT(buf, description, tab_count);
		}
	break;
	case TYRAN_PARSER_NODE_TYPE_BOOLEAN:
		{
			tyran_parser_node_boolean* number = (tyran_parser_node_boolean*)node;
			tyran_snprintf(buf, buf_size, "bool:%d", number->boolean);
			TYRAN_PARSER_NODE_PRINT_HELPER_OUTPUT(buf, description, tab_count);
		}
	break;
	case TYRAN_PARSER_NODE_TYPE_STRING:
		{
			tyran_parser_node_string* string = (tyran_parser_node_string*)node;
			tyran_snprintf(buf, buf_size, "string: '%s'", string->string);
			TYRAN_PARSER_NODE_PRINT_HELPER_OUTPUT(buf, description, tab_count);
		}
	break;
	case TYRAN_PARSER_NODE_TYPE_RETURN:
		{
			tyran_parser_node_return* ret = (tyran_parser_node_return*)node;
			tyran_snprintf(buf, buf_size, "return");
			TYRAN_PARSER_NODE_PRINT_HELPER_OUTPUT(buf, description, tab_count);
			TYRAN_PARSER_NODE_PRINT_HELPER("expression", ret->expression, tab_count + 1);
		}
	break;
	case TYRAN_PARSER_NODE_TYPE_IDENTIFIER:
		{
			tyran_parser_node_identifier* identifier = (tyran_parser_node_identifier*)node;
			tyran_snprintf(buf, buf_size, "identifier: '%s'", identifier->string);
			TYRAN_PARSER_NODE_PRINT_HELPER_OUTPUT(buf, description, tab_count);
		}
	break;
	case TYRAN_PARSER_NODE_TYPE_ASSIGNMENT:
		{
			tyran_snprintf(buf, buf_size, "assignment");
			TYRAN_PARSER_NODE_PRINT_HELPER_OUTPUT(buf, description, tab_count);
			tyran_parser_node_assignment* assignment = (tyran_parser_node_assignment*)node;
			TYRAN_PARSER_NODE_PRINT_HELPER("assignment source", assignment->source, tab_count+1);
			TYRAN_PARSER_NODE_PRINT_HELPER("assignment target", assignment->target, tab_count+1);
		}
	break;
	case TYRAN_PARSER_NODE_TYPE_COMPOUND_ASSIGNMENT:
		{
			tyran_parser_node_compound_assignment* assignment = (tyran_parser_node_compound_assignment*)node;
			tyran_snprintf(buf, buf_size, "compound assignment %d", assignment->operator_type);
			TYRAN_PARSER_NODE_PRINT_HELPER_OUTPUT(buf, description, tab_count);
			TYRAN_PARSER_NODE_PRINT_HELPER("assignment source", assignment->source, tab_count+1);
			TYRAN_PARSER_NODE_PRINT_HELPER("assignment target", assignment->target, tab_count+1);
		}
	break;
	case TYRAN_PARSER_NODE_TYPE_OPERAND_BINARY:
		{
			tyran_parser_node_operand_binary* operand = (tyran_parser_node_operand_binary*)node;
			tyran_snprintf(buf, buf_size, "operand binary '%c'", operand->operator_type);
			TYRAN_PARSER_NODE_PRINT_HELPER_OUTPUT(buf, description, tab_count);
			TYRAN_PARSER_NODE_PRINT_HELPER("operand left", operand->left, tab_count+1);
			TYRAN_PARSER_NODE_PRINT_HELPER("operand right", operand->right, tab_count+1);
		}
	break;
	case TYRAN_PARSER_NODE_TYPE_OPERAND_UNARY:
		{
			tyran_parser_node_operand_unary* operand = (tyran_parser_node_operand_unary*)node;
			tyran_snprintf(buf, buf_size, "operand unary '%d' (%d)", operand->operator_type, operand->post);
			TYRAN_PARSER_NODE_PRINT_HELPER_OUTPUT(buf, description, tab_count);
			TYRAN_PARSER_NODE_PRINT_HELPER("operand expression", operand->expression, tab_count+1);
		}
	break;
	case TYRAN_PARSER_NODE_TYPE_CLASS:
		{
			tyran_parser_node_class* operand = (tyran_parser_node_class*)node;
			tyran_snprintf(buf, buf_size, "* class");
			TYRAN_PARSER_NODE_PRINT_HELPER_OUTPUT(buf, description, tab_count);
			TYRAN_PARSER_NODE_PRINT_HELPER("class name", operand->name, tab_count+1);
			TYRAN_PARSER_NODE_PRINT_HELPER("class extends", operand->extends, tab_count+1);
			TYRAN_PARSER_NODE_PRINT_HELPER("class block", operand->block, tab_count+1);
		}
	break;
	case TYRAN_PARSER_NODE_TYPE_OBJECT:
		{
			tyran_parser_node_object* object = (tyran_parser_node_object*)node;
			tyran_snprintf(buf, buf_size, "object");
			TYRAN_PARSER_NODE_PRINT_HELPER_OUTPUT(buf, description, tab_count);
			TYRAN_PARSER_NODE_PRINT_HELPER("object assignments", object->assignment_list, tab_count+1);
		}
	break;
	case TYRAN_PARSER_NODE_TYPE_OBJECT_ASSIGNMENT:
		{
			tyran_parser_node_object_assignment* object = (tyran_parser_node_object_assignment*)node;
			tyran_snprintf(buf, buf_size, "object_assignment");
			TYRAN_PARSER_NODE_PRINT_HELPER_OUTPUT(buf, description, tab_count);
			TYRAN_PARSER_NODE_PRINT_HELPER("object_assignment name", object->name, tab_count+1);
			TYRAN_PARSER_NODE_PRINT_HELPER("object_assignment source", object->source, tab_count+1);
		}
	break;
	case TYRAN_PARSER_NODE_TYPE_CONCAT:
		{
			tyran_parser_node_concat* concat = (tyran_parser_node_concat*)node;
			tyran_snprintf(buf, buf_size, "concat");
			TYRAN_PARSER_NODE_PRINT_HELPER_OUTPUT(buf, description, tab_count);
			int i;
			for (i=0; i<concat->length; ++i)
			{
				TYRAN_PARSER_NODE_PRINT_HELPER(" ", concat->nodes[i], tab_count+1);
			}
		}
	break;
	
	}
	}
}

void TYRAN_PARSER_NODE_PRINT(const char* description, tyran_parser_node* node)
{
	TYRAN_PARSER_NODE_PRINT_HELPER(description, node, 0);
}


tyran_parser* tyran_parser_new(const char* buf)
{
	tyran_parser* parser = TYRAN_MALLOC_TYPE(tyran_parser, 1);
	parser->position = 0;
	parser->lexer = tyran_lexer_new(buf);

	return parser;
}

int tyran_parser_parse_operand(int c, tyran_lexer* lexer)
{
	tyran_lexer_push_character(c, lexer);
	typedef struct tyran_operand_info {
		const char* name;
		int len;
		int value;
	} tyran_operand_info;

	static tyran_operand_info operands[] = {
		{ "++", 2, INCREMENT },
		{ "--", 2, DECREMENT },
		{ "+=", 2, COMPOUND_ADD },
		{ "-=", 2, COMPOUND_SUBTRACT },
		{ "*=", 2, COMPOUND_MULTIPLY },
		{ "/=", 2, COMPOUND_DIVIDE },
		{ "%=", 2, COMPOUND_MODULUS },
		{ "|=", 2, 0 },
		{ "^=", 2, 0 },
		{ "<<", 2, 0 },
		{ ">>", 2, 0 },
		{ "<", 1, 0 },
		{ ">", 1, 0 },
		{ "&", 1, 0 },
		{ "|", 1, 0 },
		{ "^", 1, 0 },
		{ "/", 1, DIVIDE },
		{ "*", 1, MULTIPLY },
		{ "%", 1, MODULUS },
		{ "=", 1, EQUAL },
		{ "+", 1, ADD },
		{ "-", 1, SUBTRACT },
		{ "~", 1, 0 },
		{ "not", 3, NOT },
		{ ".", 1, MEMBER },
		{ "(", 1, PARENTHESES_LEFT },
		{ ")", 1, PARENTHESES_RIGHT },
		{ "[", 1, BRACKET_LEFT },
		{ "]", 1, BRACKET_RIGHT },
		{ ";", 1, TERMINATOR },
		{ "\n", 1, TERMINATOR },
		{ "{", 1, OBJECT_START },
		{ "}", 1, OBJECT_END },
		{ ":", 1, COLON },
		{ ",", 1, COMMA },
		{ "?", 1, 0 },
	};
	int index;
	char buf[5];
	size_t i;
	for (index = 0; index < 4; ++index) {
		char c = tyran_lexer_pop_character(lexer);
		if (c == 0 || c == '\n') {
			break;
		}
		buf[index] = c;
	}
	buf[index] = 0;
	if (!index) {
		return 0;
	}

	for (i = 0; i < sizeof(operands)/sizeof(tyran_operand_info); ++i) {
		if (index < operands[i].len) {
			continue;
		}

		if (tyran_strncmp(buf, operands[i].name, operands[i].len) == 0) {
			int j;
			for (j = index - 1; j >= operands[i].len; --j) {
				tyran_lexer_push_character(buf[j], lexer);
			}
			return operands[i].value;
		}
	}

	for (i = index - 1; i >= 1; --i) {
		tyran_lexer_push_character(buf[i], lexer);
	}
	return 0;
}


int tyran_parser_parse_token(int c, tyran_lexer* lexer)
{
	tyran_lexer_push_character(c, lexer);
	typedef struct tyran_operand_info {
		const char* name;
		int len;
		int value;
	} tyran_operand_info;

	static tyran_operand_info operands[] = {
		{ "if", 2, IF },
		{ "else", 4, ELSE },
		{ "true", 4, TYRAN_TOKEN_TRUE },
		{ "false", 5, TYRAN_TOKEN_FALSE },
		{ "class", 5, _CLASS },
		{ "extends", 7, EXTENDS },
		{ "return", 6, RETURN },
		{ "while", 5, WHILE },
		{ "switch", 6, SWITCH },
		{ "when", 4, WHEN },
		{ "for", 3, FOR },
		{ "super", 5, SUPER },
		{ "until", 5, UNTIL },
		{ "own", 3, OWN },
	};
	int index;
	const int max_characters = 7;
	char buf[max_characters + 1];
	size_t i;
	for (index = 0; index < max_characters; ++index) {
		char c = tyran_lexer_pop_character(lexer);
		if (c == 0 || c == '\n') {
			break;
		}
		buf[index] = c;
	}
	buf[index] = 0;
	if (!index) {
		return 0;
	}

	for (i = 0; i < sizeof(operands)/sizeof(tyran_operand_info); ++i) {
		if (index < operands[i].len) {
			continue;
		}

		if (tyran_strncmp(buf, operands[i].name, operands[i].len) == 0) {
			int j;
			for (j = index - 1; j >= operands[i].len; --j) {
				tyran_lexer_push_character(buf[j], lexer);
			}
			return operands[i].value;
		}
	}

	for (i = index - 1; i >= 1; --i) {
		tyran_lexer_push_character(buf[i], lexer);
	}
	return 0;
}


static int tyran_parser_next_token(tyran_lexer_token_data* token_data, tyran_lexer_position_info* lexer_position_info, tyran_lexer* lexer)
{
	tyran_lexer_set_begin(lexer_position_info, lexer);

	char c = tyran_lexer_next_character_skip_whitespace_except_newline(lexer);
	if (!c) {
		return 0;
	}

	if (tyran_lexer_is_alpha(c) || c == '_' || c == '$') {
		int len = 100;
		char* identifier = TYRAN_MALLOC_TYPE(char, len);
		int token = tyran_parser_parse_token(c, lexer);
		if (token) {
			return token;
		} else {
			tyran_lexer_parse_identifier(lexer, c, identifier, &len);
			*token_data = identifier;
			return IDENTIFIER;
		}
	} else if (tyran_lexer_is_digit(c)) {
		tyran_lexer_parse_number(lexer, c, lexer_position_info, token_data);
		return NUMBER;
	} else if (c == '"' || c == '\'') {
		tyran_lexer_parse_whole_string(lexer, c, lexer_position_info, token_data);
		return STRING;
	} else {
		int found = tyran_parser_parse_operand(c, lexer);
		if (found >=0) {
			return found;
		}
	}

	tyran_lexer_push_character(c, lexer);

	tyran_lexer_set_end(lexer_position_info, lexer);

	return 0;
}


int TYRAN_PARSER_lex(YYSTYPE *lvalp, struct tyran_lexer_position_info* llocp, tyran_parser* parser)
{
	tyran_lexer_token_data token_data = 0;
	tyran_lexer_position_info info;
	
	int ch = tyran_parser_next_token(&token_data, &info, parser->lexer);
	// TYRAN_LOG("Lex:%d", ch);
	*lvalp = token_data;
	return ch;
}

void TYRAN_PARSER_error(struct tyran_lexer_position_info* lexer_position_info, tyran_parser* ps, const char* message)
{
	TYRAN_LOG("Error:%s", message);
}

void tyran_parser_root(tyran_parser* parser, NODE root)
{
	parser->root = root;
	TYRAN_PARSER_NODE_PRINT("root", parser->root);
}

int tyran_parser_parse(tyran_parser* parser)
{
	TYRAN_PARSER_parse(parser);
	return 0;
}

NODE tyran_parser_block(NODE b)
{
	TYRAN_LOG("block");
	return 0;
}
NODE tyran_parser_compound_assignment(int operator_type, NODE target, NODE source)
{
	tyran_parser_node_compound_assignment* node = TYRAN_MALLOC_TYPE(tyran_parser_node_compound_assignment, 1);
	node->node.type = TYRAN_PARSER_NODE_TYPE_COMPOUND_ASSIGNMENT;
	node->operator_type = operator_type;
	node->target = target;
	node->source = source;

	return (tyran_parser_node*)node;
	return 0;
}
NODE tyran_parser_assignment(NODE target, NODE source)
{
	tyran_parser_node_assignment* node = TYRAN_MALLOC_TYPE(tyran_parser_node_assignment, 1);
	node->node.type = TYRAN_PARSER_NODE_TYPE_ASSIGNMENT;
	node->target = target;
	node->source = source;

	return (tyran_parser_node*)node;
}
NODE tyran_parser_object_assignment(NODE name, NODE source)
{
	tyran_parser_node_object_assignment* node = TYRAN_MALLOC_TYPE(tyran_parser_node_object_assignment, 1);
	node->node.type = TYRAN_PARSER_NODE_TYPE_OBJECT_ASSIGNMENT;
	node->name = name;
	node->source = source;

	return (tyran_parser_node*)node;
}

NODE tyran_parser_value(NODE a)
{
	TYRAN_LOG("value");
	return a;
}
NODE tyran_parser_return(NODE expression)
{
	tyran_parser_node_return* node = TYRAN_MALLOC_TYPE(tyran_parser_node_return, 1);
	node->node.type = TYRAN_PARSER_NODE_TYPE_RETURN;
	node->expression = expression;

	return (tyran_parser_node*)node;
}
NODE tyran_parser_comment(NODE comment)
{
	return 0;
}
NODE tyran_parser_code(NODE a, NODE b, NODE c)
{
	TYRAN_LOG("code");
	return 0;
}
NODE tyran_parser_concat(NODE a, NODE b)
{
	tyran_parser_node_concat* node;

	int new_node_count;
	if (a->type == TYRAN_PARSER_NODE_TYPE_CONCAT) {
		node = (tyran_parser_node_concat*)a;
		new_node_count = 1;
	} else {
		node = TYRAN_MALLOC_TYPE(tyran_parser_node_concat, 1);
		node->node.type = TYRAN_PARSER_NODE_TYPE_CONCAT;
		node->length = 0;
		node->nodes = 0;
		new_node_count = 2;
	}
	tyran_parser_node** new_nodes = TYRAN_MALLOC_TYPE(tyran_parser_node*, node->length + new_node_count);
	tyran_memcpy(new_nodes, node->nodes, (node->length) * sizeof(tyran_parser_node*));
	tyran_free(node->nodes);
	node->nodes = new_nodes;
	if (new_node_count == 2) {
		node->nodes[node->length] = a;
		node->length++;
	}
	node->nodes[node->length] = b;
	node->length++;

	return (tyran_parser_node*)node;
}
NODE tyran_parser_parameter(NODE a, NODE b, NODE c)
{
	TYRAN_LOG("parameter");
	return 0;
}
NODE tyran_parser_splat(NODE a)
{
	return 0;
}
NODE tyran_parser_accessor(NODE a)
{
	TYRAN_LOG("accessor");
	return 0;
}
NODE tyran_parser_index_soak(NODE a)
{
	TYRAN_LOG("index soak");
	return 0;
}
NODE tyran_parser_index(NODE a)
{
	TYRAN_LOG("index");
	return 0;
}
NODE tyran_parser_slice(NODE b)
{
	TYRAN_LOG("slice");
	return 0;
}
NODE tyran_parser_object(NODE assignment_list)
{
	tyran_parser_node_object* node = TYRAN_MALLOC_TYPE(tyran_parser_node_object, 1);
	node->node.type = TYRAN_PARSER_NODE_TYPE_OBJECT;
	node->assignment_list = assignment_list;
	return (tyran_parser_node*)node;
}
NODE tyran_parser_class(NODE name, NODE extends, NODE block)
{
	tyran_parser_node_class* node = TYRAN_MALLOC_TYPE(tyran_parser_node_class, 1);
	node->node.type = TYRAN_PARSER_NODE_TYPE_CLASS;
	node->name = name;
	node->extends = extends;
	node->block = block;

	return (tyran_parser_node*)node;
}
NODE tyran_parser_call(NODE a, NODE b, NODE c)
{
	TYRAN_LOG("call");
	return 0;
}
NODE tyran_parser_arguments(NODE a)
{
	TYRAN_LOG("arguments");
	return 0;
}
NODE tyran_parser_self()
{
	TYRAN_LOG("self");
	return 0;
}
NODE tyran_parser_self_identifier(NODE a)
{
	TYRAN_LOG("self identifier");
	return 0;
}
NODE tyran_parser_array(NODE a)
{
	TYRAN_LOG("array");
	return 0;
}
NODE tyran_parser_range(NODE a, NODE b, NODE c)
{
	TYRAN_LOG("range");
	return 0;
}
NODE tyran_parser_parens(NODE a)
{
	TYRAN_LOG("parens");
	return 0;
}
NODE tyran_parser_while(NODE a)
{
	TYRAN_LOG("while");
	return 0;
}
NODE tyran_parser_while_condition(NODE a, NODE b)
{
	TYRAN_LOG("while condition");
	return 0;
}
NODE tyran_parser_for(NODE a, NODE b)
{
	TYRAN_LOG("for");
	return 0;
}
NODE tyran_parser_for_body(NODE a)
{
	TYRAN_LOG("for body");
	return 0;
}
NODE tyran_parser_for_start(NODE a, NODE b)
{
	TYRAN_LOG("for start");
	return 0;
}
NODE tyran_parser_for_variables(NODE a)
{
	TYRAN_LOG("for var");
	return 0;
}
NODE tyran_parser_switch(NODE a, NODE b, NODE block)
{
	TYRAN_LOG("switch");
	return 0;
}
NODE tyran_parser_when(NODE a, NODE b)
{
	TYRAN_LOG("when");
	return 0;
}
NODE tyran_parser_if(NODE a, NODE b)
{
	TYRAN_LOG("if");
	return 0;
}
NODE tyran_parser_if_else(NODE a, NODE b)
{
	TYRAN_LOG("if else");
	return 0;
}
NODE tyran_parser_operand_unary(int operator_type, NODE expression, tyran_boolean post)
{
	tyran_parser_node_operand_unary* node = TYRAN_MALLOC_TYPE(tyran_parser_node_operand_unary, 1);
	node->node.type = TYRAN_PARSER_NODE_TYPE_OPERAND_UNARY;
	node->expression = expression;
	node->post = post;
	node->operator_type = operator_type;
	return (tyran_parser_node*)node;
}
NODE tyran_parser_operand_binary(char operator_type, NODE left, NODE right)
{
	tyran_parser_node_operand_binary* node = TYRAN_MALLOC_TYPE(tyran_parser_node_operand_binary, 1);
	node->node.type = TYRAN_PARSER_NODE_TYPE_OPERAND_BINARY;
	node->left = left;
	node->right = right;
	node->operator_type = operator_type;
	return (tyran_parser_node*)node;
}
NODE tyran_parser_extends(NODE a, NODE b)
{
	TYRAN_LOG("extends");
	return 0;
}

NODE tyran_parser_null()
{
	TYRAN_LOG("null");
	return 0;
}
NODE tyran_parser_bool(int boolean)
{
	TYRAN_LOG("bool");
	tyran_parser_node_boolean* node = TYRAN_MALLOC_TYPE(tyran_parser_node_boolean, 1);
	node->node.type = TYRAN_PARSER_NODE_TYPE_BOOLEAN;
	node->boolean = boolean;
	return (tyran_parser_node*)node;
}
NODE tyran_parser_undefined()
{
	TYRAN_LOG("undefined");
	return 0;
}
NODE tyran_parser_literal_number(float* number)
{
	tyran_parser_node_number* node = TYRAN_MALLOC_TYPE(tyran_parser_node_number, 1);
	node->node.type = TYRAN_PARSER_NODE_TYPE_NUMBER;
	node->number = *number;
	return (tyran_parser_node*)node;
}
NODE tyran_parser_literal_string(const char* string)
{
	tyran_parser_node_string* node = TYRAN_MALLOC_TYPE(tyran_parser_node_string, 1);
	node->node.type = TYRAN_PARSER_NODE_TYPE_STRING;
	node->string = tyran_strdup(string);
	node->length = strlen(node->string);
	return (tyran_parser_node*)node;
}
NODE tyran_parser_literal_identifier(const char* string)
{
	tyran_parser_node_identifier* node = TYRAN_MALLOC_TYPE(tyran_parser_node_identifier, 1);
	node->node.type = TYRAN_PARSER_NODE_TYPE_IDENTIFIER;
	node->string = tyran_strdup(string);
	node->length = strlen(node->string);
	return (tyran_parser_node*)node;
}
NODE tyran_parser_call_super(NODE a)
{
	TYRAN_LOG("super");
	return 0;
}
