#ifndef tyranscript_tyran_print_parser_tree_h
#define tyranscript_tyran_print_parser_tree_h

struct tyran_parser_node;


void tyran_parser_node_print(const char* description, struct tyran_parser_node** current_root, struct tyran_parser_node** node);
void tyran_parser_node_print_helper(const char* description, struct tyran_parser_node** node, struct tyran_parser_node** current_root, struct tyran_parser_node** next_to_overwrite, struct tyran_parser_node** node_to_highlight, int tab_count);

#endif
