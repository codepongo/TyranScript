#include <tyranscript/tyran_mocha_api.h>
#include <tyranscript/tyran_config.h>
#include <tyranscript/parser/tyran_lexer.h>
#include <tyranscript/debug/mocha/tyran_mocha_lexer_debug.h>
#include <tyranscript/debug/parser/tyran_print_parser_tree.h>
#include <tyranscript/parser/mocha/tyran_mocha_parser.h>
#include <tyranscript/parser/mocha/tyran_mocha_lexer.h>

#include <tyranscript/parser/common/tyran_generator.h>
#include <tyranscript/parser/common/tyran_variable_scope.h>
#include <tyranscript/parser/tyran_label.h>
#include <tyranscript/parser/tyran_label_reference.h>
#include <tyranscript/tyran_constants.h>

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

	api->object_pool = TYRAN_MEMORY_POOL_CONSTRUCT(memory, tyran_object, 10);
	struct tyran_memory_pool* value_registers_pool = TYRAN_MEMORY_POOL_CONSTRUCT(memory, tyran_value, 10);

	api->mocha_function_pool = TYRAN_MEMORY_POOL_CONSTRUCT(memory, tyran_function, 1);

	struct tyran_memory_pool* runtime_pool = TYRAN_MEMORY_POOL_CONSTRUCT(api->memory, tyran_runtime, 1);
	struct tyran_memory_pool* runtime_stack_pool = TYRAN_MEMORY_POOL_CONSTRUCT(api->memory, tyran_runtime_stack, 1);
	api->default_runtime = tyran_runtime_new(runtime_pool, runtime_stack_pool, api->object_pool, value_registers_pool);
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

	
	struct tyran_parser_node* parser_tree =  tyran_mocha_parser_parse(api->memory, mocha_lexer, mocha_parser_pool, enclosure_stack_pool, enclosure_info_pool, parser_node_parameter_pool, mocha_token_pool);


	// tyran_parser_node_print("result", parser_tree, 0);
	tyran_memory_pool* code_state_pool = TYRAN_MEMORY_POOL_CONSTRUCT(api->memory, tyran_code_state, 1);
	tyran_memory_pool* opcodes_pool = TYRAN_MEMORY_POOL_CONSTRUCT(api->memory, tyran_opcodes, 10);
	tyran_memory_pool* constants_pool = TYRAN_MEMORY_POOL_CONSTRUCT(api->memory, tyran_constants, 1);
	tyran_memory_pool* constant_values_pool = TYRAN_MEMORY_POOL_CONSTRUCT(api->memory, tyran_value, 1);
	tyran_memory_pool* label_pool = TYRAN_MEMORY_POOL_CONSTRUCT(api->memory, tyran_label, 1);
	tyran_memory_pool* label_reference_pool = TYRAN_MEMORY_POOL_CONSTRUCT(api->memory, tyran_label_reference, 1);
	tyran_memory_pool* scopes_pool = TYRAN_MEMORY_POOL_CONSTRUCT(api->memory, tyran_variable_scopes, 1);
	tyran_memory_pool* scope_pool = TYRAN_MEMORY_POOL_CONSTRUCT(api->memory, tyran_variable_scope, 1);
	tyran_memory_pool* variable_info_pool = TYRAN_MEMORY_POOL_CONSTRUCT(api->memory, tyran_variable_info, 1);
	tyran_memory_pool* register_pool = TYRAN_MEMORY_POOL_CONSTRUCT(api->memory, int, 1);

	tyran_memory_pool* function_pool = TYRAN_MEMORY_POOL_CONSTRUCT(api->memory, tyran_function, 10);

	TYRAN_LOG("code new!");
	struct tyran_code_state* code = tyran_code_new(function_pool, code_state_pool, opcodes_pool, constants_pool, constant_values_pool, label_pool,
		label_reference_pool, scopes_pool, scope_pool, variable_info_pool, register_pool, api->memory);

	tyran_memory_pool* generator_pool = TYRAN_MEMORY_POOL_CONSTRUCT(api->memory, tyran_code_state, 1);
	TYRAN_LOG("generator new!");
	tyran_generator_new(api->memory, generator_pool, parser_tree, code);

	TYRAN_LOG("print_opcodes!");
	tyran_print_opcodes(code->opcodes, 0, code->constants);

/*	tyran_runtime* runtime = tyran_runtime_new();
	tyran_value return_value;
	tyran_runtime_push_call(runtime, code->opcodes, code->constants, 0);
	tyran_runtime_execute(runtime, &return_value, 0);
	tyran_print_value("Return", &return_value, 1);
*/
}

tyran_value tyran_mocha_api_create_object(tyran_mocha_api* api) {
	tyran_value value;

	tyran_object* object = tyran_object_new(api->object_pool, api->default_runtime);
	tyran_value_set_object(value, object);

	return value;
}

void tyran_mocha_api_add_function(tyran_mocha_api* api, tyran_value* target, const char* name, tyran_function_callback callback) {
	tyran_function* func = tyran_function_callback_new(api->mocha_function_pool, callback);
	tyran_value value;
	tyran_value_set_static_function(value, func);
	tyran_value_object_insert_c_string_key(target, name, &value);
}

