#ifndef _TYRAN_PARSER_STATE_H
#define _TYRAN_PARSER_STATE_H

struct tyran_lexer;
struct tyran_opcodes;
struct tyran_constants;
struct tyran_label;
struct tyran_label_reference;

typedef struct tyran_parser_state {
	struct tyran_lexer* lexer;
	struct tyran_opcodes* opcodes;
	struct tyran_constants* constants;
	struct tyran_label* labels;
	int label_count;
	struct tyran_label_reference* label_references;
	int label_reference_count;


	int error_count;
} tyran_parser_state;

tyran_parser_state* tyran_parser_state_new(const char *str, int length);
void tyran_parser_state_free(tyran_parser_state* parser_state);
#endif
