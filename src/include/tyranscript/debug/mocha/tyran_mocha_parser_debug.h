#ifndef tyran_mocha_parser_debug_h
#define tyran_mocha_parser_debug_h

#include <tyranscript/parser/mocha/tyran_mocha_parser.h>
#include <tyranscript/debug/parser/tyran_print_parser_tree.h>

void tyran_mocha_parser_node_print_tree(tyran_mocha_parser* parser, const char* description, tyran_parser_node** node);

#endif
