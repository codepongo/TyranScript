#ifndef _TYRAN_PARSER_STATE_H
#define _TYRAN_PARSER_STATE_H

struct tyran_lexer;
struct tyran_opcodes;

typedef struct tyran_parser_state {
	struct tyran_lexer* lexer;
	struct tyran_opcodes* opcodes;
	int error_count;
} tyran_parser_state;

tyran_parser_state* tyran_parser_state_new(const char* str, int octets);
void tyran_parser_state_free(tyran_parser_state* state);

#endif
