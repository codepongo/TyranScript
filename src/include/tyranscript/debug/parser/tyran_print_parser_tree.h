#ifndef tyranscript_tyran_print_parser_tree_h
#define tyranscript_tyran_print_parser_tree_h

struct tyran_parser_node;


void tyran_parser_node_print(const char* description, struct tyran_parser_node* current_root, struct tyran_parser_node* node);

#endif
