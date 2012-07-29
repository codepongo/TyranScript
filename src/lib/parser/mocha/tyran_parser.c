#include <tyranscript/parser/mocha/tyran_parser.h>
#include <tyranscript/parser/tyran_lexer.h>
#include <tyranscript/tyran_string.h>


const char* g_buf;
int g_buf_size;
int g_buf_pos;

#define YY_INPUT(buf, result, max_size) \
	int remaining = (g_buf_size - g_buf_pos); \
	result = remaining < max_size ? remaining : max_size; \
	TYRAN_LOG("Tjoho:%d result:%d", max_size, result); \
	tyran_memcpy(buf, g_buf + g_buf_pos, result); \
	g_buf_pos += result;
	
#define YY_DEBUG 1
	

enum tyran_parser_type {
	TYRAN_PARSER_NODE_TYPE_NUMBER,
	TYRAN_PARSER_NODE_TYPE_BOOLEAN,
	TYRAN_PARSER_NODE_TYPE_NULL,
	TYRAN_PARSER_NODE_TYPE_UNDEFINED,
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
	TYRAN_PARSER_NODE_TYPE_ARGUMENTS,
	TYRAN_PARSER_NODE_TYPE_CALL,
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

typedef struct tyran_parser_node_arguments
{
	tyran_parser_node node;
	tyran_parser_node* argument_list;
} tyran_parser_node_arguments;

typedef struct tyran_parser_node_call
{
	tyran_parser_node node;
	tyran_parser_node* function_name;
	tyran_parser_node* arguments;
} tyran_parser_node_call;

typedef struct tyran_parser_node_concat
{
	tyran_parser_node node;
	tyran_parser_node** nodes;
	int length;
} tyran_parser_node_concat;

typedef struct tyran_parser_node_null
{
	tyran_parser_node node;
} tyran_parser_node_null;

typedef struct tyran_parser_node_undefined
{
	tyran_parser_node node;
} tyran_parser_node_undefined;

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
	case TYRAN_PARSER_NODE_TYPE_NULL:
		{
			tyran_snprintf(buf, buf_size, "null");
			TYRAN_PARSER_NODE_PRINT_HELPER_OUTPUT(buf, description, tab_count);
		}
	break;
	case TYRAN_PARSER_NODE_TYPE_UNDEFINED:
		{
			tyran_snprintf(buf, buf_size, "undefined");
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
			tyran_snprintf(buf, buf_size, "class");
			TYRAN_PARSER_NODE_PRINT_HELPER_OUTPUT(buf, description, tab_count);
			TYRAN_PARSER_NODE_PRINT_HELPER("class name", operand->name, tab_count+1);
			TYRAN_PARSER_NODE_PRINT_HELPER("class extends", operand->extends, tab_count+1);
			TYRAN_PARSER_NODE_PRINT_HELPER("class block", operand->block, tab_count+1);
		}
	break;
	case TYRAN_PARSER_NODE_TYPE_ARGUMENTS:
		{
			tyran_parser_node_arguments* arguments = (tyran_parser_node_arguments*)node;
			tyran_snprintf(buf, buf_size, "arguments");
			TYRAN_PARSER_NODE_PRINT_HELPER_OUTPUT(buf, description, tab_count);
			TYRAN_PARSER_NODE_PRINT_HELPER("arguments argument_list", arguments->argument_list, tab_count+1);
		}
	break;
	case TYRAN_PARSER_NODE_TYPE_CALL:
		{
			tyran_parser_node_call* call = (tyran_parser_node_call*)node;
			tyran_snprintf(buf, buf_size, "call");
			TYRAN_PARSER_NODE_PRINT_HELPER_OUTPUT(buf, description, tab_count);
			TYRAN_PARSER_NODE_PRINT_HELPER("call function_name", call->function_name, tab_count+1);
			TYRAN_PARSER_NODE_PRINT_HELPER("call arguments", call->arguments, tab_count+1);
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
void tyran_parser_root(tyran_parser* parser, NODE root)
{
	parser->root = root;
	TYRAN_PARSER_NODE_PRINT("root", parser->root);
}

int tyran_parser_parse(const char* buf, int length)
{
	g_buf = buf;
	g_buf_size = length;
	g_buf_pos = 0;
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
NODE tyran_parser_call(NODE previous_node, NODE function_name, NODE arguments)
{
	tyran_parser_node_call* node = TYRAN_MALLOC_TYPE(tyran_parser_node_call, 1);
	node->node.type = TYRAN_PARSER_NODE_TYPE_CALL;
	node->arguments = arguments;
	node->function_name = function_name;

	return (tyran_parser_node*)node;
}
NODE tyran_parser_arguments(NODE argument_list)
{
	tyran_parser_node_arguments* node = TYRAN_MALLOC_TYPE(tyran_parser_node_arguments, 1);
	node->node.type = TYRAN_PARSER_NODE_TYPE_ARGUMENTS;
	node->argument_list = argument_list;

	return (tyran_parser_node*)node;
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

NODE tyran_parser_null()
{
	tyran_parser_node_null* node = TYRAN_MALLOC_TYPE(tyran_parser_node_null, 1);
	node->node.type = TYRAN_PARSER_NODE_TYPE_NULL;
	return (tyran_parser_node*)node;
}
NODE tyran_parser_bool(int boolean)
{
	tyran_parser_node_boolean* node = TYRAN_MALLOC_TYPE(tyran_parser_node_boolean, 1);
	node->node.type = TYRAN_PARSER_NODE_TYPE_BOOLEAN;
	node->boolean = boolean;
	return (tyran_parser_node*)node;
}
NODE tyran_parser_undefined()
{
	tyran_parser_node_undefined* node = TYRAN_MALLOC_TYPE(tyran_parser_node_undefined, 1);
	node->node.type = TYRAN_PARSER_NODE_TYPE_UNDEFINED;
	return (tyran_parser_node*)node;
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
