#ifndef _TYRAN_PARSER_STATE_H
#define _TYRAN_PARSER_STATE_H

struct tyran_lexer;
struct tyran_opcodes;
struct tyran_constants;
struct tyran_label;
struct tyran_label_reference;
struct tyran_runtime;
struct tyran_code_state;

#include <tyranscript/tyran_value.h>

typedef struct tyran_parser_state {
	struct tyran_lexer* lexer;

	struct tyran_opcodes* opcodes;
	struct tyran_constants* constants;
	struct tyran_value context;
	struct tyran_runtime* runtime;
	struct tyran_label* labels;
	struct tyran_code_state* code;
	int label_count;
	struct tyran_label_reference* label_references;
	int label_reference_count;

	int inside_function;

	char function_name[512];

	struct tyran_memory_pool* object_pool;
	struct tyran_memory_pool* value_pool;

	int error_count;
} tyran_parser_state;

tyran_parser_state* tyran_parser_state_new(tyran_memory_pool* parser_state_pool,  struct tyran_runtime* runtime, struct tyran_value* context, const char* str, int length);
void tyran_parser_state_free(tyran_parser_state* parser_state);
void tyran_parser_state_reset(tyran_parser_state* parser_state);
#endif
