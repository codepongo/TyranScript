#include <tyranscript/parser/mocha/tyran_parser_tree.h>
#include <tyranscript/parser/tyran_lexer.h>
#include <tyranscript/tyran_string.h>

const char* tyran_parser_binary_operand_to_string[TYRAN_PARSER_BINARY_OPERAND_TYPE_MAX] = { "DIVIDE", "MULTIPLY", "MODULUS", "ASSIGNMENT", "ADD", "SUBTRACT", "INDEX", "COMMA", "INVOKE", "EQUAL", "NOT_EQUAL", "THEN", "ELSE", "LINE" };
const char* tyran_parser_unary_operand_to_string[TYRAN_PARSER_UNARY_OPERAND_TYPE_MAX] = { "ADD", "SUBTRACT", "PARENTHESES", "BLOCK", "IF", "BRACKET"};

void tyran_parser_node_print_helper_output(const char* buf, const char* description, int tab_count)
{
	char tabs[200];
	tyran_memset_type_n(tabs, '\t', tab_count);
	tabs[tab_count] = 0;
	
	TYRAN_LOG("%s%s %s", tabs, description, buf);
}

void tyran_parser_node_print_helper(const char* description, tyran_parser_node* node, int tab_count)
{
	const int buf_size = 256;

	char buf[buf_size];

	buf[0] = 0;

	if (!node) {
		tyran_snprintf(buf, buf_size, "null");
		tyran_parser_node_print_helper_output(buf, description, tab_count);
	} else {
	
	switch (node->type)
	{
	case TYRAN_PARSER_NODE_TYPE_NUMBER:
		{
			tyran_parser_node_number* number = (tyran_parser_node_number*)node;
			tyran_snprintf(buf, buf_size, "number:%f", number->number);
			tyran_parser_node_print_helper_output(buf, description, tab_count);
		}
	break;
	case TYRAN_PARSER_NODE_TYPE_BOOLEAN:
		{
			tyran_parser_node_boolean* number = (tyran_parser_node_boolean*)node;
			tyran_snprintf(buf, buf_size, "bool:%d", number->boolean);
			tyran_parser_node_print_helper_output(buf, description, tab_count);
		}
	break;
	case TYRAN_PARSER_NODE_TYPE_NULL:
		{
			tyran_snprintf(buf, buf_size, "null");
			tyran_parser_node_print_helper_output(buf, description, tab_count);
		}
	break;
	case TYRAN_PARSER_NODE_TYPE_UNDEFINED:
		{
			tyran_snprintf(buf, buf_size, "undefined");
			tyran_parser_node_print_helper_output(buf, description, tab_count);
		}
	break;
	case TYRAN_PARSER_NODE_TYPE_STRING:
		{
			tyran_parser_node_string* string = (tyran_parser_node_string*)node;
			tyran_snprintf(buf, buf_size, "string: '%s'", string->string);
			tyran_parser_node_print_helper_output(buf, description, tab_count);
		}
	break;
	case TYRAN_PARSER_NODE_TYPE_IDENTIFIER:
		{
			tyran_parser_node_identifier* identifier = (tyran_parser_node_identifier*)node;
			tyran_snprintf(buf, buf_size, "identifier: '%s'", identifier->string);
			tyran_parser_node_print_helper_output(buf, description, tab_count);
		}
	break;
	case TYRAN_PARSER_NODE_TYPE_ASSIGNMENT:
		{
			tyran_snprintf(buf, buf_size, "assignment");
			tyran_parser_node_print_helper_output(buf, description, tab_count);
			tyran_parser_node_assignment* assignment = (tyran_parser_node_assignment*)node;
			tyran_parser_node_print_helper("assignment source", assignment->source, tab_count+1);
			tyran_parser_node_print_helper("assignment target", assignment->target, tab_count+1);
		}
	break;
	case TYRAN_PARSER_NODE_TYPE_COMPOUND_ASSIGNMENT:
		{
			tyran_parser_node_compound_assignment* assignment = (tyran_parser_node_compound_assignment*)node;
			tyran_snprintf(buf, buf_size, "compound assignment %d", assignment->operator_type);
			tyran_parser_node_print_helper_output(buf, description, tab_count);
			tyran_parser_node_print_helper("assignment source", assignment->source, tab_count+1);
			tyran_parser_node_print_helper("assignment target", assignment->target, tab_count+1);
		}
	break;
	case TYRAN_PARSER_NODE_TYPE_OPERAND_BINARY:
		{
			tyran_parser_node_operand_binary* operand = (tyran_parser_node_operand_binary*)node;
			tyran_snprintf(buf, buf_size, "operand binary '%s'", tyran_parser_binary_operand_to_string[operand->operator_type]);
			tyran_parser_node_print_helper_output(buf, description, tab_count);
			tyran_parser_node_print_helper("operand left", operand->left, tab_count+1);
			tyran_parser_node_print_helper("operand right", operand->right, tab_count+1);
		}
	break;
	case TYRAN_PARSER_NODE_TYPE_IF:
		{
			tyran_parser_node_if* operand = (tyran_parser_node_if*)node;
			tyran_snprintf(buf, buf_size, "if ");
			tyran_parser_node_print_helper_output(buf, description, tab_count);
			tyran_parser_node_print_helper("if expression", operand->expression, tab_count+1);
			tyran_parser_node_print_helper("if then", operand->then_block, tab_count+1);
		}
	break;
	case TYRAN_PARSER_NODE_TYPE_IF_ELSE:
		{
			tyran_parser_node_if_else* operand = (tyran_parser_node_if_else*)node;
			tyran_snprintf(buf, buf_size, "if ");
			tyran_parser_node_print_helper_output(buf, description, tab_count);
			tyran_parser_node_print_helper("if expression", operand->expression, tab_count+1);
			tyran_parser_node_print_helper("if then", operand->then_block, tab_count+1);
			tyran_parser_node_print_helper("if else", operand->else_block, tab_count+1);
		}
	break;
	case TYRAN_PARSER_NODE_TYPE_OPERAND_UNARY:
		{
			tyran_parser_node_operand_unary* operand = (tyran_parser_node_operand_unary*)node;
			tyran_snprintf(buf, buf_size, "operand unary '%s' (%d)", tyran_parser_unary_operand_to_string[operand->operator_type], operand->post);
			tyran_parser_node_print_helper_output(buf, description, tab_count);
			tyran_parser_node_print_helper("operand expression", operand->expression, tab_count+1);
		}
	break;
	case TYRAN_PARSER_NODE_TYPE_CLASS:
		{
			tyran_parser_node_class* operand = (tyran_parser_node_class*)node;
			tyran_snprintf(buf, buf_size, "class");
			tyran_parser_node_print_helper_output(buf, description, tab_count);
			tyran_parser_node_print_helper("class name", operand->name, tab_count+1);
			tyran_parser_node_print_helper("class extends", operand->extends, tab_count+1);
			tyran_parser_node_print_helper("class block", operand->block, tab_count+1);
		}
	break;
	case TYRAN_PARSER_NODE_TYPE_ARGUMENTS:
		{
			tyran_parser_node_arguments* arguments = (tyran_parser_node_arguments*)node;
			tyran_snprintf(buf, buf_size, "arguments");
			tyran_parser_node_print_helper_output(buf, description, tab_count);
			tyran_parser_node_print_helper("arguments argument_list", arguments->argument_list, tab_count+1);
		}
	break;
	case TYRAN_PARSER_NODE_TYPE_OBJECT:
		{
			tyran_parser_node_object* object = (tyran_parser_node_object*)node;
			tyran_snprintf(buf, buf_size, "object");
			tyran_parser_node_print_helper_output(buf, description, tab_count);
			tyran_parser_node_print_helper("object assignments", object->assignment_list, tab_count+1);
		}
	break;
	case TYRAN_PARSER_NODE_TYPE_OBJECT_ASSIGNMENT:
		{
			tyran_parser_node_object_assignment* object = (tyran_parser_node_object_assignment*)node;
			tyran_snprintf(buf, buf_size, "object_assignment");
			tyran_parser_node_print_helper_output(buf, description, tab_count);
			tyran_parser_node_print_helper("object_assignment name", object->name, tab_count+1);
			tyran_parser_node_print_helper("object_assignment source", object->source, tab_count+1);
		}
	break;
	case TYRAN_PARSER_NODE_TYPE_CONCAT:
		{
			tyran_parser_node_concat* concat = (tyran_parser_node_concat*)node;
			tyran_snprintf(buf, buf_size, "concat");
			tyran_parser_node_print_helper_output(buf, description, tab_count);
			int i;
			for (i=0; i<concat->length; ++i)
			{
				tyran_parser_node_print_helper(" ", concat->nodes[i], tab_count+1);
			}
		}
	break;
	
	}
	}
}

void tyran_parser_node_print(const char* description, tyran_parser_node* node)
{
	tyran_parser_node_print_helper(description, node, 0);
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
	tyran_parser_node_print("root", parser->root);
}

NODE tyran_parser_block()
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

NODE tyran_parser_if(NODE expression, NODE then_block)
{
	tyran_parser_node_if* node = TYRAN_MALLOC_TYPE(tyran_parser_node_if, 1);
	node->node.type = TYRAN_PARSER_NODE_TYPE_IF;
	node->expression = expression;
	node->then_block = then_block;
	return (tyran_parser_node*)node;
}

NODE tyran_parser_if_else(NODE expression, NODE then_block, NODE else_block)
{
	tyran_parser_node_if_else* node = TYRAN_MALLOC_TYPE(tyran_parser_node_if_else, 1);
	node->node.type = TYRAN_PARSER_NODE_TYPE_IF_ELSE;
	node->expression = expression;
	node->then_block = then_block;
	node->else_block = else_block;
	return (tyran_parser_node*)node;
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

NODE tyran_parser_operand_binary(tyran_parser_binary_operand_type operator_type, NODE left, NODE right)
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
