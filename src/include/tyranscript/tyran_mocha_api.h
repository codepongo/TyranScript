#ifndef tyranscript_tyran_mocha_api_h
#define tyranscript_tyran_mocha_api_h

#include <tyranscript/tyran_config.h>
#include <tyranscript/tyran_api.h>

typedef struct tyran_mocha_api {
	struct tyran_memory_pool* mocha_lexer_pool;
	struct tyran_memory_pool* mocha_token_pool;
	struct tyran_memory_pool* lexer_pool;
	struct tyran_memory_pool* mocha_function_pool;
	struct tyran_memory_pool* object_pool;
	struct tyran_memory* memory;
	struct tyran_runtime* default_runtime;
} tyran_mocha_api;


void tyran_mocha_api_new(tyran_mocha_api* api, int hunk_size);
void tyran_mocha_api_eval(tyran_mocha_api* api, const char* s, size_t length);
tyran_value tyran_mocha_api_create_object(tyran_mocha_api* api);
void tyran_mocha_api_add_function(tyran_mocha_api* api, tyran_value* target, const char* name, tyran_function_callback callback);

#endif
