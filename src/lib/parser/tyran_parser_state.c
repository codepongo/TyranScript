#include <tyranscript/tyran_config.h>
#include <tyranscript/parser/tyran_parser_state.h>
#include <tyranscript/parser/tyran_lexer.h>

extern int yyparse(tyran_parser_state *ps);

tyran_parser_state* tyran_parser_state_new(const char *str, int length)
{
	tyran_parser_state* parser_state = TYRAN_CALLOC(tyran_parser_state);
	tyran_lexer* lexer = TYRAN_CALLOC(tyran_lexer);
	parser_state->lexer = lexer;
	
	int number_of_octets = sizeof(char) * length;
	lexer->buffer = TYRAN_MALLOC_TYPE(char, length + 1);
	tyran_memcpy(lexer->buffer, str, number_of_octets);
	lexer->buffer[length] = 0;
	lexer->line = 1;

	yyparse(parser_state);

	return parser_state;
}

void tyran_parser_state_free(tyran_parser_state* parser_state)
{
	tyran_free(parser_state->opcodes);
	tyran_free(parser_state->lexer->buffer);
	tyran_free(parser_state->lexer);
	tyran_free(parser_state);
}
