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
#include <tyranscript/tyran_array.h>

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

	api->value_pool = TYRAN_MEMORY_POOL_CONSTRUCT(memory, tyran_value, 10);
	api->mocha_function_pool = TYRAN_MEMORY_POOL_CONSTRUCT(memory, tyran_function, 1);

	struct tyran_memory_pool* runtime_pool = TYRAN_MEMORY_POOL_CONSTRUCT(api->memory, tyran_runtime, 1);
	struct tyran_memory_pool* runtime_stack_pool = TYRAN_MEMORY_POOL_CONSTRUCT(api->memory, tyran_runtime_stack, 1);
	struct tyran_memory_pool* function_object_pool = TYRAN_MEMORY_POOL_CONSTRUCT(api->memory, tyran_function_object, 10);
	struct tyran_memory_pool* object_key_pool = 0; //TYRAN_MEMORY_POOL_CONSTRUCT(api->memory, tyran_object_key, 10);


	struct tyran_memory_pool* object_iterator_pool = 0; //TYRAN_MEMORY_POOL_CONSTRUCT(api->memory, tyran_object_iterator, 10);
	api->string_pool = TYRAN_MEMORY_POOL_CONSTRUCT(api->memory, tyran_string, 10);

	struct tyran_memory_pool* array_node_pool = TYRAN_MEMORY_POOL_CONSTRUCT(api->memory, tyran_array_node, 10);
	api->default_runtime = tyran_runtime_new(runtime_pool, api->memory, api->string_pool, object_key_pool, object_iterator_pool, api->mocha_function_pool, function_object_pool, runtime_stack_pool, api->object_pool, value_registers_pool, api->value_pool, array_node_pool);

	api->object_key_pool = 0; //TYRAN_MEMORY_POOL_CONSTRUCT(api->memory, tyran_object_key, 10);

	tyran_memory_pool* scopes_pool = TYRAN_MEMORY_POOL_CONSTRUCT(api->memory, tyran_variable_scopes, 1);
	tyran_memory_pool* scope_pool = TYRAN_MEMORY_POOL_CONSTRUCT(api->memory, tyran_variable_scope, 1);
	api->default_variable_info_pool = TYRAN_MEMORY_POOL_CONSTRUCT(api->memory, tyran_variable_info, 1);
	api->default_register_pool = TYRAN_MEMORY_POOL_CONSTRUCT(api->memory, int, 1);
	api->default_variable_scopes = tyran_variable_scopes_new(scopes_pool, api->memory, scope_pool, api->default_variable_info_pool, api->default_register_pool, 1024);

}

void tyran_mocha_api_eval(tyran_mocha_api* api, tyran_value* context, const char* buf, size_t length)
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

	tyran_memory_pool* function_pool = TYRAN_MEMORY_POOL_CONSTRUCT(api->memory, tyran_function, 10);
	tyran_memory_pool* string_pool = TYRAN_MEMORY_POOL_CONSTRUCT(api->memory, tyran_string, 10);


	struct tyran_code_state* code = tyran_code_new(api->default_runtime, string_pool, function_pool, code_state_pool, opcodes_pool, constants_pool, constant_values_pool, label_pool,
									label_reference_pool, api->default_variable_info_pool, api->default_register_pool, api->default_variable_scopes, api->memory);

	tyran_memory_pool* generator_pool = TYRAN_MEMORY_POOL_CONSTRUCT(api->memory, tyran_generator, 1);
	tyran_generator_new(api->memory, generator_pool, parser_tree, code);

	tyran_print_opcodes(code->opcodes, 0, code->constants);

	tyran_value return_value;
	tyran_runtime_push_call(api->default_runtime, code->opcodes, code->constants, context);
	tyran_runtime_execute(api->default_runtime, &return_value, 0);
	struct tyran_memory_pool* object_iterator_pool = 0; // TYRAN_MEMORY_POOL_CONSTRUCT(api->memory, tyran_object_iterator, 10);
	tyran_print_value("return", &return_value, 1, code->constants->symbol_table, object_iterator_pool, api->string_pool, api->memory);
}

tyran_value tyran_mocha_api_create_object(tyran_mocha_api* api)
{
	tyran_value value;

	tyran_object* object = tyran_object_new(api->default_runtime);
	tyran_value_set_object(value, object);

	return value;
}

void tyran_mocha_api_add_function(tyran_mocha_api* api, tyran_value* target, const char* name, tyran_function_callback callback)
{
	tyran_value* value = tyran_function_object_new_callback(api->default_runtime, callback);
	tyran_value_object_insert_c_string_key(api->default_runtime, target, name, value);
}

