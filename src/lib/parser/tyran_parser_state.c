#include <tyranscript/tyran_config.h>
#include <tyranscript/parser/tyran_parser_state.h>
#include <tyranscript/parser/tyran_lexer.h>
#include <tyranscript/parser/tyran_label.h>
#include <tyranscript/parser/tyran_label_reference.h>

#include <tyranscript/tyran_config.h>
#include <tyranscript/parser/tyran_parser_state.h>
#include <tyranscript/parser/tyran_lexer.h>
#include <tyranscript/tyran_opcodes.h>
#include <tyranscript/tyran_constants.h>

tyran_parser_state* tyran_parser_state_new(const char *str, int length)
{
	tyran_parser_state* parser_state = TYRAN_CALLOC(tyran_parser_state);
	tyran_lexer* lexer = TYRAN_CALLOC(tyran_lexer);
	parser_state->lexer = lexer;

	parser_state->opcodes = tyran_opcodes_new(1024);
	parser_state->constants = tyran_constants_new(1024);
	parser_state->labels = TYRAN_MALLOC_TYPE(tyran_label, 1024);
	parser_state->label_references = TYRAN_MALLOC_TYPE(tyran_label_reference, 1024);

	int number_of_octets = sizeof(char) * length;
	lexer->buffer = TYRAN_MALLOC_TYPE(char, length + 1);
	tyran_memcpy(lexer->buffer, str, number_of_octets);
	lexer->buffer[length] = 0;
	lexer->line = 1;

	return parser_state;
}

void tyran_parser_state_free(tyran_parser_state* parser_state)
{
	tyran_free(parser_state->opcodes);
	tyran_free(parser_state->lexer->buffer);
	tyran_free(parser_state->lexer);
	tyran_free(parser_state);
}