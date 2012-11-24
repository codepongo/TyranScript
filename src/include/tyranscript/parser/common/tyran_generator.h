//
//  tyran_generator.h
//  tyranscript
//
//  Created by Peter Björklund on 2012-08-10.
//
//

#ifndef tyranscript_tyran_generator_h
#define tyranscript_tyran_generator_h

struct tyran_parser_node;
struct tyran_code_state;
struct tyran_memory_pool;
struct tyran_memory;

typedef struct tyran_generator {
	int dummy;
} tyran_generator;

tyran_generator* tyran_generator_new(struct tyran_memory* memory, struct tyran_memory_pool* generator_pool, struct tyran_parser_node* tree, struct tyran_code_state* code);

#endif
