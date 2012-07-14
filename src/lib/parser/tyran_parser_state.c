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
#include <tyranscript/tyran_runtime.h>
#include <tyranscript/tyran_string.h>
#include <tyranscript/tyran_object_macros.h>

#include <tyranscript/debug/tyran_print_value.h>

tyran_parser_state* tyran_parser_state_new(tyran_runtime* runtime, tyran_value* context, const char *str, int length)
{
	tyran_parser_state* parser_state = TYRAN_CALLOC(tyran_parser_state);
	tyran_lexer* lexer = TYRAN_CALLOC(tyran_lexer);
	parser_state->lexer = lexer;
	tyran_value_copy(parser_state->context, *context);
	parser_state->runtime = runtime;

	tyran_parser_state_reset(parser_state);

	int number_of_octets = sizeof(char) * length;
	lexer->buffer = TYRAN_MALLOC_TYPE(char, length + 1);
	tyran_memcpy(lexer->buffer, str, number_of_octets);
	lexer->buffer[length] = 0;
	lexer->line = 1;

	return parser_state;
}

void tyran_parser_state_reset(tyran_parser_state* parser_state)
{
	parser_state->opcodes = tyran_opcodes_new(1024);
	parser_state->constants = tyran_constants_new(1024);
	parser_state->labels = TYRAN_MALLOC_TYPE(tyran_label, 1024);
	parser_state->label_references = TYRAN_MALLOC_TYPE(tyran_label_reference, 1024);
	parser_state->label_reference_count = 0;
}

void tyran_parser_state_free(tyran_parser_state* parser_state)
{
	tyran_free(parser_state->opcodes);
	tyran_free(parser_state->lexer->buffer);
	tyran_free(parser_state->lexer);
	tyran_free(parser_state);
}