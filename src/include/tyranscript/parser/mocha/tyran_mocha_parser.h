#ifndef tyranscript_tyran_mocha_parser_h
#define tyranscript_tyran_mocha_parser_h

#include <tyranscript/parser/common/tyran_parser_tree.h>
#include <tyranscript/parser/mocha/tyran_mocha_lexer.h>

struct tyran_mocha_lexer;


typedef struct tyran_mocha_parser_enclosure_info {
	tyran_mocha_token_id start_token_id;
	int top_precedence;
	NODE* root;
} tyran_mocha_parser_enclosure_info;


typedef struct tyran_mocha_parser_enclosure_stack {
	tyran_mocha_parser_enclosure_info* nodes;
	int alloc_size;
	int length;
} tyran_mocha_parser_enclosure_stack;



typedef struct tyran_mocha_parser {
	struct tyran_mocha_parser_enclosure_stack* enclosure_stack;
	tyran_mocha_token_id waiting_for_start_enclosure_id;
	int overwrite_precedence;
	NODE original_root;
	NODE* root;
	NODE* next_node_to_overwrite;
	struct tyran_memory_pool* parser_parameter_pool;
	struct tyran_memory_pool* mocha_token_pool;
} tyran_mocha_parser;


NODE tyran_mocha_parser_parse(tyran_memory* memory, tyran_mocha_lexer* lexer, tyran_memory_pool* mocha_parser_pool, tyran_memory_pool* enclosure_pool, tyran_memory_pool* enclosure_info_pool,  tyran_memory_pool* parser_parameter_pool, tyran_memory_pool* mocha_token_pool);

#endif
