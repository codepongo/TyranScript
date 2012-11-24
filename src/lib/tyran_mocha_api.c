#include <tyranscript/tyran_mocha_api.h>
#include <tyranscript/tyran_config.h>
#include <tyranscript/parser/tyran_lexer.h>
#include <tyranscript/debug/mocha/tyran_mocha_lexer_debug.h>
#include <tyranscript/debug/parser/tyran_print_parser_tree.h>
#include <tyranscript/parser/mocha/tyran_mocha_parser.h>
#include <tyranscript/parser/mocha/tyran_mocha_lexer.h>

void tyran_mocha_api_new(tyran_mocha_api* api, int hunk_size)
{
	u8t* start = tyran_malloc(hunk_size);
	tyran_memory* memory = (tyran_memory*)start;
	start += sizeof(tyran_memory);
	tyran_memory_construct(memory, start, hunk_size - sizeof(tyran_memory));

	api->mocha_lexer_pool = TYRAN_MEMORY_POOL_CONSTRUCT(memory, tyran_mocha_lexer, 1);
	api->mocha_token_pool = TYRAN_MEMORY_POOL_CONSTRUCT(memory, tyran_mocha_token, 1);
	api->lexer_pool = TYRAN_MEMORY_POOL_CONSTRUCT(memory, tyran_lexer, 1);
	api->memory = memory;
}

void tyran_mocha_api_eval(tyran_mocha_api* api, const char* buf, size_t length)
{
	tyran_mocha_lexer* mocha_lexer = tyran_mocha_lexer_lex(api->mocha_lexer_pool, api->mocha_token_pool, api->lexer_pool, api->memory, buf, length);
	tyran_mocha_lexer_debug(mocha_lexer);
	

	tyran_memory_pool* mocha_parser_pool = TYRAN_MEMORY_POOL_CONSTRUCT(api->memory, tyran_mocha_parser, 1);
	tyran_memory_pool* enclosure_stack_pool = TYRAN_MEMORY_POOL_CONSTRUCT(api->memory, tyran_mocha_parser_enclosure_stack, 1);
	tyran_memory_pool* enclosure_info_pool = TYRAN_MEMORY_POOL_CONSTRUCT(api->memory, tyran_mocha_parser_enclosure_info, 1);
	tyran_memory_pool* parser_node_parameter_pool = TYRAN_MEMORY_POOL_CONSTRUCT(api->memory, tyran_parser_node_parameter, 1);
	tyran_memory_pool* mocha_token_pool = TYRAN_MEMORY_POOL_CONSTRUCT(api->memory, tyran_mocha_token, 1);
	
	struct tyran_parser_node* parser_tree = tyran_mocha_parser_parse(api->memory, mocha_lexer, mocha_parser_pool, enclosure_stack_pool, enclosure_info_pool, parser_node_parameter_pool, mocha_token_pool);

	tyran_parser_node_print("result", parser_tree, 0);
/*
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

