#ifndef tyranscript_tyran_mocha_api_h
#define tyranscript_tyran_mocha_api_h

#include <tyranscript/tyran_config.h>

typedef struct tyran_mocha_api {
	struct tyran_memory_pool* mocha_lexer_pool;
	struct tyran_memory_pool* mocha_token_pool;
	struct tyran_memory_pool* lexer_pool;
	struct tyran_memory* memory;
} tyran_mocha_api;


tyran_mocha_api* tyran_mocha_api_new(int hunk_size);
void tyran_mocha_api_eval(tyran_mocha_api* api, const char* s, size_t length);

#endif
