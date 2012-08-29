#include <tyranscript/tyran_mocha_api.h>
#include <tyranscript/tyran_config.h>
#include <tyranscript/tyran_mocha_lexer.h>
#include <tyranscript/tyran_lexer.h>

tyran_mocha_api* tyran_mocha_api_new(int hunk_size)
{
	u8t* start = tyran_malloc(hunk_size);
	tyran_memory* memory = (tyran_memory*)start;
	start += sizeof(tyran_memory);
	tyran_memory_construct(memory, start, hunk_size - sizeof(tyran_memory));

	tyran_mocha_api* api = TYRAN_CALLOC_TYPE(pool, tyran_mocha_api);
	api->mocha_lexer_pool = TYRAN_MEMORY_POOL_CONSTRUCT(memory, tyran_mocha_lexer, 1);
	api->mocha_token_pool = TYRAN_MEMORY_POOL_CONSTRUCT(memory, tyran_mocha_token, 1);
	api->lexer_pool = TYRAN_MEMORY_POOL_CONSTRUCT(memory, tyran_lexer, 1);
	api->memory = memory;
	return api;
}

void tyran_mocha_api_eval(tyran_mocha_api* api, const char* buf, size_t length)
{
/*
	tyran_mocha_lexer* mocha_lexer = tyran_mocha_lexer_lex(buf, tyran_strlen(buf));
	tyran_mocha_lexer_debug(mocha_lexer);
	struct tyran_parser_node* parser_tree = tyran_mocha_parser_parse(mocha_lexer);
	tyran_parser_node_print("result", parser_tree, 0);
	struct tyran_code_state* code = tyran_code_new();
	tyran_generator_new(parser_tree, code);
	tyran_print_opcodes(code->opcodes, 0, code->constants);
	tyran_runtime* runtime = tyran_runtime_new();
	tyran_value return_value;
	tyran_runtime_push_call(runtime, code->opcodes, code->constants, 0);
	tyran_runtime_execute(runtime, &return_value, 0);
	tyran_print_value("Return", &return_value, 1);
*/
}

