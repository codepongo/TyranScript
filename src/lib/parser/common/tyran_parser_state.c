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

tyran_parser_state* tyran_parser_state_new(tyran_memory_pool* parser_state_pool,  struct tyran_runtime* runtime, struct tyran_value* context, const char *str, int length)
{
	return 0;
}

void tyran_parser_state_free(tyran_parser_state* parser_state)
{
}


void tyran_parser_state_reset(tyran_parser_state* parser_state)
{
}

