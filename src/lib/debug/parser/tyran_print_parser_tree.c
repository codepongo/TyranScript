#include <tyranscript/parser/common/tyran_parser_tree.h>

const char* tyran_parser_binary_operand_to_string[TYRAN_PARSER_BINARY_OPERAND_TYPE_MAX] = { "DIVIDE", "MULTIPLY", "MODULUS", "ASSIGNMENT", "ASSIGNMENT_ADD", "ASSIGNMENT_SUB", "ASSIGNMENT_MUL", "ASSIGNMENT_DIV", "ASSIGNMENT_MOD", "ADD", "SUBTRACT", "MEMBER", "INDEX", "COMMA", "EQUAL", "NOT_EQUAL", ">=", ">", "<=", "<", "THEN", "ELSE", "LINE", "WHILE", "CONCAT", "IN", "WHEN", "CASE", "RANGE", "RANGE_INCLUSIVE", "UNTIL", "AND", "OR", "CALL", "COLON"};
const char* tyran_parser_unary_operand_to_string[TYRAN_PARSER_UNARY_OPERAND_TYPE_MAX] = { "ADD", "SUBTRACT", "PARENTHESES", "BLOCK", "IF", "UNLESS", "BRACKET", "ARRAY", "OBJECT", "NOT"};

void tyran_parser_node_print_helper_output(const char* buf, const char* description, int tab_count)
{
	char tabs[200];
	int octet_count = tab_count * 5;
	tyran_memset_type_n(tabs, '.', octet_count);
	tabs[octet_count] = 0;

	TYRAN_LOG("%s%s: %s", tabs, description, buf);
}


void tyran_parser_node_array_print_helper(const char* description, tyran_parser_node** nodes, int count, tyran_parser_node** current_root, tyran_parser_node** next_to_overwrite, tyran_parser_node** node_to_highlight, int tab_count);

void tyran_parser_node_print_helper(const char* description, tyran_parser_node** pointer_to_node, tyran_parser_node** current_root, tyran_parser_node** next_to_overwrite, tyran_parser_node** node_to_hightlight, int tab_count)
{
	const int buf_size = 256;

	char buf[buf_size];

	buf[0] = 0;
	NODE node = *pointer_to_node;

	if (!node) {
		tyran_snprintf(buf, buf_size, "null");
		tyran_parser_node_print_helper_output(buf, description, tab_count);
	} else {
		if (pointer_to_node == current_root) {
			TYRAN_LOG(" ROOT =>");
		}

		if (pointer_to_node == next_to_overwrite) {
			TYRAN_LOG(" OVERWRITE =>");
		}

		if (pointer_to_node == node_to_hightlight) {
			TYRAN_LOG(" NODE =>");
		}


		switch (node->type) {
			case TYRAN_PARSER_NODE_TYPE_NUMBER: {
				tyran_parser_node_number* number = (tyran_parser_node_number*)node;
				tyran_snprintf(buf, buf_size, "number:%f", number->number);
				tyran_parser_node_print_helper_output(buf, description, tab_count);
			}
			break;
			case TYRAN_PARSER_NODE_TYPE_BOOLEAN: {
				tyran_parser_node_boolean* number = (tyran_parser_node_boolean*)node;
				tyran_snprintf(buf, buf_size, "bool:%d", number->boolean);
				tyran_parser_node_print_helper_output(buf, description, tab_count);
			}
			break;
			case TYRAN_PARSER_NODE_TYPE_SELF: {
				tyran_snprintf(buf, buf_size, "self");
				tyran_parser_node_print_helper_output(buf, description, tab_count);
			}
			break;
			case TYRAN_PARSER_NODE_TYPE_BREAK: {
				tyran_snprintf(buf, buf_size, "break");
				tyran_parser_node_print_helper_output(buf, description, tab_count);
			}
			break;
			case TYRAN_PARSER_NODE_TYPE_CONTINUE: {
				tyran_snprintf(buf, buf_size, "continue");
				tyran_parser_node_print_helper_output(buf, description, tab_count);
			}
			break;
			case TYRAN_PARSER_NODE_TYPE_NIL: {
				tyran_snprintf(buf, buf_size, "nil");
				tyran_parser_node_print_helper_output(buf, description, tab_count);
			}
			break;
			case TYRAN_PARSER_NODE_TYPE_STRING: {
				tyran_parser_node_string* string = (tyran_parser_node_string*)node;
				tyran_snprintf(buf, buf_size, "string: '%s'", string->string);
				tyran_parser_node_print_helper_output(buf, description, tab_count);
			}
			break;
			case TYRAN_PARSER_NODE_TYPE_IDENTIFIER: {
				tyran_parser_node_identifier* identifier = (tyran_parser_node_identifier*)node;
				tyran_snprintf(buf, buf_size, "identifier: '%s'", identifier->string);
				tyran_parser_node_print_helper_output(buf, description, tab_count);
			}
			break;
			case TYRAN_PARSER_NODE_TYPE_ASSIGNMENT: {
				tyran_snprintf(buf, buf_size, "assignment");
				tyran_parser_node_print_helper_output(buf, description, tab_count);
				tyran_parser_node_assignment* assignment = (tyran_parser_node_assignment*)node;
				tyran_parser_node_print_helper("assignment source", &assignment->source, current_root, next_to_overwrite, node_to_hightlight, tab_count+1);
				tyran_parser_node_print_helper("assignment target", &assignment->target, current_root, next_to_overwrite, node_to_hightlight, tab_count+1);
			}
			break;
			case TYRAN_PARSER_NODE_TYPE_COMPOUND_ASSIGNMENT: {
				tyran_parser_node_compound_assignment* assignment = (tyran_parser_node_compound_assignment*)node;
				tyran_snprintf(buf, buf_size, "compound assignment %d", assignment->operator_type);
				tyran_parser_node_print_helper_output(buf, description, tab_count);
				tyran_parser_node_print_helper("assignment source", &assignment->source, current_root, next_to_overwrite, node_to_hightlight, tab_count+1);
				tyran_parser_node_print_helper("assignment target", &assignment->target, current_root, next_to_overwrite, node_to_hightlight, tab_count+1);
			}
			break;
			case TYRAN_PARSER_NODE_TYPE_OPERAND_BINARY: {
				tyran_parser_node_operand_binary* operand = (tyran_parser_node_operand_binary*)node;
				tyran_snprintf(buf, buf_size, "operand binary '%s'", tyran_parser_binary_operand_to_string[operand->operator_type]);
				tyran_parser_node_print_helper_output(buf, description, tab_count);
				tyran_parser_node_print_helper("operand left", &operand->left, current_root, next_to_overwrite, node_to_hightlight, tab_count+1);
				tyran_parser_node_print_helper("operand right", &operand->right, current_root, next_to_overwrite, node_to_hightlight, tab_count+1);
			}
			break;
			case TYRAN_PARSER_NODE_TYPE_IF: {
				tyran_parser_node_if* operand = (tyran_parser_node_if*)node;
				tyran_snprintf(buf, buf_size, "if ");
				tyran_parser_node_print_helper_output(buf, description, tab_count);
				tyran_parser_node_print_helper("if expression", &operand->expression, current_root, next_to_overwrite, node_to_hightlight, tab_count+1);
				tyran_parser_node_print_helper("if then", &operand->then_block, current_root, next_to_overwrite, node_to_hightlight, tab_count+1);
			}
			break;
			case TYRAN_PARSER_NODE_TYPE_IF_ELSE: {
				tyran_parser_node_if_else* operand = (tyran_parser_node_if_else*)node;
				tyran_snprintf(buf, buf_size, "if ");
				tyran_parser_node_print_helper_output(buf, description, tab_count);
				tyran_parser_node_print_helper("if expression", &operand->expression, current_root, next_to_overwrite, node_to_hightlight, tab_count+1);
				tyran_parser_node_print_helper("if then", &operand->then_block, current_root, next_to_overwrite, node_to_hightlight, tab_count+1);
				tyran_parser_node_print_helper("if else", &operand->else_block, current_root, next_to_overwrite, node_to_hightlight, tab_count+1);
			}
			break;
			case TYRAN_PARSER_NODE_TYPE_FUNCTION: {
				tyran_parser_node_function* func_node = (tyran_parser_node_function*)node;
				tyran_snprintf(buf, buf_size, "function ");
				tyran_parser_node_print_helper_output(buf, description, tab_count);
				tyran_parser_node_parameter* parameters = func_node->parameters;
				tyran_parser_node_print_helper_output("", "parameters", tab_count+1);
				for (int i=0; i<func_node->parameter_count; ++i) {
					tyran_parser_node_parameter* param = &parameters[i];
					tyran_snprintf(buf, buf_size, "(%d) '%s'", i, param->identifier->string);
					tyran_parser_node_print_helper_output(buf, "parameter", tab_count+2);
					if (param->default_value) {
						tyran_parser_node_print_helper("default", &param->default_value, current_root, next_to_overwrite, node_to_hightlight, tab_count+3);
					}
				}
				tyran_parser_node_print_helper("func block", &func_node->block, current_root, next_to_overwrite, node_to_hightlight, tab_count+1);
			}
			break;
			case TYRAN_PARSER_NODE_TYPE_ELSE: {
				tyran_parser_node_else* operand = (tyran_parser_node_else*)node;
				tyran_snprintf(buf, buf_size, "else ");
				tyran_parser_node_print_helper_output(buf, description, tab_count);
				tyran_parser_node_print_helper("else block", &operand->block, current_root, next_to_overwrite, node_to_hightlight, tab_count+1);
			}
			break;
			case TYRAN_PARSER_NODE_TYPE_WHILE:
			case TYRAN_PARSER_NODE_TYPE_UNTIL: {
				tyran_parser_node_while* operand = (tyran_parser_node_while*)node;
				tyran_snprintf(buf, buf_size, "while ");
				tyran_parser_node_print_helper_output(buf, description, tab_count);
				tyran_parser_node_print_helper("while condition", &operand->condition, current_root, next_to_overwrite, node_to_hightlight, tab_count+1);
				tyran_parser_node_print_helper("while block", &operand->block, current_root, next_to_overwrite, node_to_hightlight, tab_count+1);
			}
			break;
			case TYRAN_PARSER_NODE_TYPE_RETURN: {
				tyran_parser_node_return* operand = (tyran_parser_node_return*)node;
				tyran_snprintf(buf, buf_size, "return ");
				tyran_parser_node_print_helper_output(buf, description, tab_count);
				tyran_parser_node_print_helper("return expression", &operand->expression, current_root, next_to_overwrite, node_to_hightlight, tab_count+1);
			}
			break;
			case TYRAN_PARSER_NODE_TYPE_FOR: {
				tyran_parser_node_for* operand = (tyran_parser_node_for*)node;
				tyran_snprintf(buf, buf_size, "for ");
				tyran_parser_node_print_helper_output(buf, description, tab_count);
				//tyran_parser_node_print_helper("for key", &((NODE)(operand->key_variable)), current_root, next_to_overwrite, tab_count+1);
				//tyran_parser_node_print_helper("for value", &operand->value_variable, current_root, next_to_overwrite, tab_count+1);
				tyran_parser_node_print_helper("for collection", &operand->collection, current_root, next_to_overwrite, node_to_hightlight, tab_count+1);
				tyran_parser_node_print_helper("for block", &operand->block, current_root, next_to_overwrite, node_to_hightlight, tab_count+1);
			}
			break;
			case TYRAN_PARSER_NODE_TYPE_WHEN: {
				tyran_parser_node_when* operand = (tyran_parser_node_when*)node;
				tyran_snprintf(buf, buf_size, "when ");
				tyran_parser_node_print_helper_output(buf, description, tab_count);
				tyran_parser_node_print_helper("when expression", &operand->expression, current_root, next_to_overwrite, node_to_hightlight, tab_count+1);
				tyran_parser_node_print_helper("when block", &operand->block, current_root, next_to_overwrite, node_to_hightlight, tab_count+1);
			}
			break;
			case TYRAN_PARSER_NODE_TYPE_CASE: {
				tyran_parser_node_case* operand = (tyran_parser_node_case*)node;
				tyran_snprintf(buf, buf_size, "case ");
				tyran_parser_node_print_helper_output(buf, description, tab_count);
				tyran_parser_node_print_helper("case expression", &operand->expression, current_root, next_to_overwrite, node_to_hightlight, tab_count+1);
				for (int i=0; i<operand->when_count; ++i) {
					NODE when_node = (NODE) operand->whens[i];
					tyran_parser_node_print_helper("when", &when_node, current_root, next_to_overwrite, node_to_hightlight, tab_count+1);
				}
			}
			break;
			case TYRAN_PARSER_NODE_TYPE_OPERAND_UNARY: {
				tyran_parser_node_operand_unary* operand = (tyran_parser_node_operand_unary*)node;
				tyran_snprintf(buf, buf_size, "operand unary '%s' [%d] (%d)", tyran_parser_unary_operand_to_string[operand->operator_type], operand->operator_type, operand->post);
				tyran_parser_node_print_helper_output(buf, description, tab_count);
				tyran_parser_node_print_helper("operand expression", &operand->expression, current_root, next_to_overwrite, node_to_hightlight, tab_count+1);
			}
			break;
			case TYRAN_PARSER_NODE_TYPE_CLASS: {
				tyran_parser_node_class* operand = (tyran_parser_node_class*)node;
				tyran_snprintf(buf, buf_size, "class");
				tyran_parser_node_print_helper_output(buf, description, tab_count);
				tyran_parser_node_print_helper("class name", &operand->name, current_root, next_to_overwrite, node_to_hightlight, tab_count+1);
				tyran_parser_node_print_helper("class extends", &operand->extends, current_root, next_to_overwrite, node_to_hightlight, tab_count+1);
				tyran_parser_node_print_helper("class block", &operand->block, current_root, next_to_overwrite, node_to_hightlight, tab_count+1);
			}
			break;
			case TYRAN_PARSER_NODE_TYPE_OBJECT: {
				tyran_parser_node_object* object = (tyran_parser_node_object*)node;
				tyran_snprintf(buf, buf_size, "object");
				tyran_parser_node_print_helper_output(buf, description, tab_count);
				tyran_parser_node_print_helper("object assignments", &object->assignment_list, current_root, next_to_overwrite, node_to_hightlight, tab_count+1);
			}
			break;
			case TYRAN_PARSER_NODE_TYPE_OBJECT_ASSIGNMENT: {
				tyran_parser_node_object_assignment* object = (tyran_parser_node_object_assignment*)node;
				tyran_snprintf(buf, buf_size, "object_assignment");
				tyran_parser_node_print_helper_output(buf, description, tab_count);
				tyran_parser_node_print_helper("object_assignment name", &object->name, current_root, next_to_overwrite, node_to_hightlight, tab_count+1);
				tyran_parser_node_print_helper("object_assignment source", &object->source, current_root, next_to_overwrite, node_to_hightlight, tab_count+1);
			}
			break;
			case TYRAN_PARSER_NODE_TYPE_MEMBER_ASSIGN: {
				tyran_parser_node_member_assign* object = (tyran_parser_node_member_assign*)node;
				tyran_snprintf(buf, buf_size, "member_assign");
				tyran_parser_node_print_helper_output(buf, description, tab_count);
				tyran_parser_node_print_helper("member_assign identifier", &object->identifier, current_root, next_to_overwrite, node_to_hightlight, tab_count+1);
				tyran_parser_node_print_helper("member_assign expression", &object->expression, current_root, next_to_overwrite, node_to_hightlight, tab_count+1);

			}
			break;
			default:
				TYRAN_ERROR("unknown parser node type:%d", node->type);
		}
	}
}

void tyran_parser_node_array_print_helper(const char* description, tyran_parser_node** nodes, int count, tyran_parser_node** current_root, tyran_parser_node** next_to_overwrite, tyran_parser_node** node_to_highlight, int tab_count)
{
	for (int i=0; i<count; ++i) {
		tyran_parser_node_print_helper(description, &nodes[i], current_root, next_to_overwrite, 0, tab_count);
	}
}

void tyran_parser_node_print(const char* description, tyran_parser_node** node, tyran_parser_node** current_root)
{
	tyran_parser_node_print_helper(description, node, current_root, 0, 0, 0);
}

