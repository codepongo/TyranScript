#include <tyranscript/parser/common/tyran_parser_tree.h>
#include <tyranscript/parser/tyran_lexer.h>
#include <tyranscript/tyran_string.h>
#include <tyranscript/tyran_config.h>

tyran_parser_node_operand_binary* tyran_parser_binary_operator_cast(NODE node)
{
	if (!node || node->type != TYRAN_PARSER_NODE_TYPE_OPERAND_BINARY) {
		return 0;
	} else {
		tyran_parser_node_operand_binary* binary_operator = (tyran_parser_node_operand_binary*) node;
		return binary_operator;
	}
}

tyran_parser_node_operand_binary* tyran_parser_binary_operator_type_cast(NODE node, tyran_parser_binary_operand_type operator_type)
{
	tyran_parser_node_operand_binary* binary = tyran_parser_binary_operator_cast(node);
	if (binary && binary->operator_type == operator_type) {
		return binary;
	} else {
		return 0;
	}
}

tyran_parser_node_operand_unary* tyran_parser_unary_operator_cast(NODE node)
{
	if (!node || node->type != TYRAN_PARSER_NODE_TYPE_OPERAND_UNARY) {
		return 0;
	} else {
		tyran_parser_node_operand_unary* unary_operator = (tyran_parser_node_operand_unary*) node;
		return unary_operator;
	}
}

tyran_parser_node_operand_unary* tyran_parser_unary_operator_type_cast(NODE node, tyran_parser_unary_operand_type operator_type)
{
	tyran_parser_node_operand_unary* unary = tyran_parser_unary_operator_cast(node);
	if (unary && unary->operator_type == operator_type) {
		return unary;
	} else {
		return 0;
	}
}


tyran_parser* tyran_parser_new(tyran_memory_pool* parser_pool, tyran_memory_pool* lexer_pool, tyran_memory* memory, const char* buf)
{
	tyran_parser* parser = TYRAN_MALLOC_TYPE(parser_pool, tyran_parser);
	parser->position = 0;
	parser->lexer = tyran_lexer_new(lexer_pool, memory, buf);

	return parser;
}


NODE tyran_parser_block()
{
	TYRAN_LOG("block");
	return 0;
}

NODE tyran_parser_compound_assignment(tyran_memory* memory, int operator_type, NODE target, NODE source)
{
	tyran_parser_node_compound_assignment* node = TYRAN_MALLOC_NO_POOL_TYPE_COUNT(memory, tyran_parser_node_compound_assignment, 1);
	node->node.type = TYRAN_PARSER_NODE_TYPE_COMPOUND_ASSIGNMENT;
	node->operator_type = operator_type;
	node->target = target;
	node->source = source;

	return (tyran_parser_node*)node;
}

NODE tyran_parser_assignment(tyran_memory* memory, NODE target, NODE source)
{
	tyran_parser_node_assignment* node = TYRAN_MALLOC_NO_POOL_TYPE_COUNT(memory, tyran_parser_node_assignment, 1);
	node->node.type = TYRAN_PARSER_NODE_TYPE_ASSIGNMENT;
	node->target = target;
	node->source = source;

	return (tyran_parser_node*)node;
}

NODE tyran_parser_object_assignment(tyran_memory* memory, NODE name, NODE source)
{
	tyran_parser_node_object_assignment* node = TYRAN_MALLOC_NO_POOL_TYPE_COUNT(memory, tyran_parser_node_object_assignment, 1);
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

tyran_parser_node_operand_binary* tyran_parser_concat(tyran_memory* memory, NODE left, NODE right)
{
	tyran_parser_node_operand_binary* binary = tyran_parser_operand_binary(memory, TYRAN_PARSER_CONCAT, left, right);

	return binary;
}

NODE tyran_parser_splat(NODE a)
{
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


NODE tyran_parser_class(tyran_memory* memory, NODE name, NODE extends, NODE block)
{
	tyran_parser_node_class* node = TYRAN_MALLOC_NO_POOL_TYPE_COUNT(memory, tyran_parser_node_class, 1);
	node->node.type = TYRAN_PARSER_NODE_TYPE_CLASS;
	node->name = name;
	node->extends = extends;
	node->block = block;

	return (tyran_parser_node*)node;
}

NODE tyran_parser_range(NODE a, NODE b, NODE c)
{
	TYRAN_LOG("range");
	return 0;
}

NODE tyran_parser_while(tyran_memory* memory, NODE condition, NODE block)
{
	tyran_parser_node_while* node = TYRAN_MALLOC_NO_POOL_TYPE_COUNT(memory, tyran_parser_node_while, 1);
	node->node.type = TYRAN_PARSER_NODE_TYPE_WHILE;
	node->condition = condition;
	node->block = block;
	return (tyran_parser_node*)node;
}

NODE tyran_parser_for(tyran_memory* memory, tyran_parser_node_identifier* key_variable, tyran_parser_node_identifier* value_variable, NODE collection, NODE block)
{
	tyran_parser_node_for* node = TYRAN_MALLOC_NO_POOL_TYPE_COUNT(memory, tyran_parser_node_for, 1);
	node->node.type = TYRAN_PARSER_NODE_TYPE_FOR;
	node->key_variable = key_variable;
	node->value_variable = value_variable;
	node->collection = collection;
	node->block = block;
	return (tyran_parser_node*)node;
}

NODE tyran_parser_case(tyran_memory* memory, NODE expression, tyran_parser_node_when** whens, int when_count)
{
	tyran_parser_node_case* node = TYRAN_MALLOC_NO_POOL_TYPE_COUNT(memory, tyran_parser_node_case, 1);
	node->node.type = TYRAN_PARSER_NODE_TYPE_CASE;
	node->expression = expression;
	node->when_count = when_count;
	node->whens = TYRAN_MALLOC_NO_POOL_TYPE_COUNT(memory, tyran_parser_node_when*, node->when_count);
	tyran_memcpy_type(tyran_parser_node_when*, node->whens, whens, when_count);
	return (tyran_parser_node*)node;
}

NODE tyran_parser_when(tyran_memory* memory, NODE expression, NODE block)
{
	tyran_parser_node_when* node = TYRAN_MALLOC_NO_POOL_TYPE_COUNT(memory, tyran_parser_node_when, 1);
	node->node.type = TYRAN_PARSER_NODE_TYPE_WHEN;
	node->expression = expression;
	node->block = block;
	return (tyran_parser_node*)node;
}

NODE tyran_parser_return(tyran_memory* memory, NODE expression)
{
	tyran_parser_node_return* node = TYRAN_MALLOC_NO_POOL_TYPE_COUNT(memory, tyran_parser_node_return, 1);
	node->node.type = TYRAN_PARSER_NODE_TYPE_RETURN;
	node->expression = expression;
	return (NODE)node;
}

NODE tyran_parser_function(tyran_memory* memory, NODE block, tyran_boolean bound)
{
	tyran_parser_node_function* node = TYRAN_MALLOC_NO_POOL_TYPE_COUNT(memory, tyran_parser_node_function, 1);
	node->node.type = TYRAN_PARSER_NODE_TYPE_FUNCTION;
	node->bound = bound;
	node->parameters = 0;
	TYRAN_ASSERT(block, "No block defined!");
	node->block = block;
	return (tyran_parser_node*)node;
}

NODE tyran_parser_if(tyran_memory* memory, NODE expression, NODE then_block, tyran_boolean invert)
{
	tyran_parser_node_if* node = TYRAN_MALLOC_NO_POOL_TYPE_COUNT(memory, tyran_parser_node_if, 1);
	node->node.type = TYRAN_PARSER_NODE_TYPE_IF;
	node->expression = expression;
	node->then_block = then_block;
	node->invert = invert;
	return (tyran_parser_node*)node;
}

NODE tyran_parser_if_else(tyran_memory* memory, NODE expression, NODE then_block, NODE else_block, tyran_boolean invert)
{
	tyran_parser_node_if_else* node = TYRAN_MALLOC_NO_POOL_TYPE_COUNT(memory, tyran_parser_node_if_else, 1);
	node->node.type = TYRAN_PARSER_NODE_TYPE_IF_ELSE;
	node->expression = expression;
	node->then_block = then_block;
	node->else_block = else_block;
	node->invert = invert;
	return (tyran_parser_node*)node;
}

NODE tyran_parser_else(tyran_memory* memory, NODE else_block)
{
	tyran_parser_node_else* node = TYRAN_MALLOC_NO_POOL_TYPE_COUNT(memory, tyran_parser_node_else, 1);
	node->node.type = TYRAN_PARSER_NODE_TYPE_ELSE;
	node->block = else_block;
	return (tyran_parser_node*)node;
}

tyran_parser_node_operand_unary* tyran_parser_operand_unary(tyran_memory* memory, int operator_type, NODE expression, tyran_boolean post)
{
	tyran_parser_node_operand_unary* node = TYRAN_MALLOC_NO_POOL_TYPE_COUNT(memory, tyran_parser_node_operand_unary, 1);
	node->node.type = TYRAN_PARSER_NODE_TYPE_OPERAND_UNARY;
	node->expression = expression;
	node->post = post;
	node->operator_type = operator_type;
	return node;
}

tyran_parser_node_operand_binary* tyran_parser_operand_binary(tyran_memory* memory, tyran_parser_binary_operand_type operator_type, NODE left, NODE right)
{
	tyran_parser_node_operand_binary* node = TYRAN_MALLOC_NO_POOL_TYPE_COUNT(memory, tyran_parser_node_operand_binary, 1);
	node->node.type = TYRAN_PARSER_NODE_TYPE_OPERAND_BINARY;
	node->left = left;
	node->right = right;
	node->operator_type = operator_type;
	return node;
}

NODE tyran_parser_bool(tyran_memory* memory, int boolean)
{
	tyran_parser_node_boolean* node = TYRAN_MALLOC_NO_POOL_TYPE_COUNT(memory, tyran_parser_node_boolean, 1);
	node->node.type = TYRAN_PARSER_NODE_TYPE_BOOLEAN;
	node->boolean = boolean;
	return (tyran_parser_node*)node;
}

NODE tyran_parser_self(tyran_memory* memory)
{
	tyran_parser_node_self* node = TYRAN_MALLOC_NO_POOL_TYPE_COUNT(memory, tyran_parser_node_self, 1);
	node->node.type = TYRAN_PARSER_NODE_TYPE_SELF;
	return (tyran_parser_node*)node;
}

NODE tyran_parser_break(tyran_memory* memory)
{
	tyran_parser_node_break* node = TYRAN_MALLOC_NO_POOL_TYPE_COUNT(memory, tyran_parser_node_break, 1);
	node->node.type = TYRAN_PARSER_NODE_TYPE_BREAK;
	return (NODE)node;
}

NODE tyran_parser_continue(tyran_memory* memory)
{
	tyran_parser_node_continue* node = TYRAN_MALLOC_NO_POOL_TYPE_COUNT(memory, tyran_parser_node_continue, 1);
	node->node.type = TYRAN_PARSER_NODE_TYPE_CONTINUE;
	return (NODE)node;
}

NODE tyran_parser_nil(tyran_memory* memory)
{
	tyran_parser_node_nil* node = TYRAN_MALLOC_NO_POOL_TYPE_COUNT(memory, tyran_parser_node_nil, 1);
	node->node.type = TYRAN_PARSER_NODE_TYPE_NIL;
	return (tyran_parser_node*)node;
}

NODE tyran_parser_literal_number(tyran_memory* memory, tyran_number* number)
{
	tyran_parser_node_number* node = TYRAN_MALLOC_NO_POOL_TYPE_COUNT(memory, tyran_parser_node_number, 1);
	node->node.type = TYRAN_PARSER_NODE_TYPE_NUMBER;
	node->number = *number;
	return (tyran_parser_node*)node;
}

NODE tyran_parser_literal_string(tyran_memory* memory, const char* string)
{
	tyran_parser_node_string* node = TYRAN_MALLOC_NO_POOL_TYPE_COUNT(memory, tyran_parser_node_string, 1);
	node->node.type = TYRAN_PARSER_NODE_TYPE_STRING;
	node->string = tyran_strdup(memory, string);
	node->length = strlen(node->string);
	return (tyran_parser_node*)node;
}

NODE tyran_parser_literal_identifier(tyran_memory* memory, const char* string)
{
	tyran_parser_node_identifier* node = TYRAN_MALLOC_NO_POOL_TYPE_COUNT(memory, tyran_parser_node_identifier, 1);
	node->node.type = TYRAN_PARSER_NODE_TYPE_IDENTIFIER;
	node->string = tyran_strdup(memory, string);
	node->length = strlen(node->string);
	return (tyran_parser_node*)node;
}

NODE tyran_parser_call_super(NODE a)
{
	TYRAN_LOG("super");
	return 0;
}

int tyran_parser_node_is_constant(NODE node)
{
	enum tyran_parser_type type = node->type;
	return (type == TYRAN_PARSER_NODE_TYPE_NUMBER  || type ==  TYRAN_PARSER_NODE_TYPE_BOOLEAN || type == TYRAN_PARSER_NODE_TYPE_NIL ||  type == TYRAN_PARSER_NODE_TYPE_STRING);
}

int tyran_parser_node_is_literal(NODE node)
{
	enum tyran_parser_type type = node->type;
	return (tyran_parser_node_is_constant(node) || type == TYRAN_PARSER_NODE_TYPE_IDENTIFIER);
}

NODE tyran_parser_member_assign(tyran_memory* memory, NODE target, NODE expression)
{
	tyran_parser_node_member_assign* node = TYRAN_MALLOC_NO_POOL_TYPE_COUNT(memory, tyran_parser_node_member_assign, 1);
	node->node.type = TYRAN_PARSER_NODE_TYPE_MEMBER_ASSIGN;
	node->identifier = target;
	node->expression = expression;
	return (NODE)node;
}

