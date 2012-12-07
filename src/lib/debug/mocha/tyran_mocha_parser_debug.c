#include <tyranscript/debug/mocha/tyran_mocha_parser_debug.h>

void tyran_mocha_parser_node_print_tree(tyran_mocha_parser* parser, const char* description, tyran_parser_node* node) {
	NODE* root = 0;

	root = parser->root;
	tyran_parser_node_print_helper(description, root, root, parser->next_node_to_overwrite, 0);
}
