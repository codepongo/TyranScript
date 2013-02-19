#include <tyranscript/tyran_mocha_api.h>

void print_value(tyran_runtime* runtime, tyran_value* v)
{
	const int buf_len = 100;
	char buf[buf_len];

	tyran_value_to_c_string(runtime->symbol_table, v, buf, buf_len, 1);

	puts(buf);

}


TYRAN_RUNTIME_CALL_FUNC(mocha_print)
{
	struct tyran_value* v = &arguments[0];
	print_value(runtime, v);
	tyran_value_set_number(*return_value, 16.0f);
	return 0;
}

int main(int argc, char* argv[])
{
	TYRAN_LOG("TyranScript console");

	tyran_mocha_api api;
	tyran_mocha_api_new(&api, 1024);

	tyran_value* global = tyran_runtime_context(api.default_runtime);
	tyran_mocha_api_add_function(&api, global, "print", mocha_print);

	char buf[512];
	while (1) {
		TYRAN_OUTPUT_NO_LF("> ");
		char* p = fgets(buf, 512, stdin);
		if (!p || strcmp(p, "quit\n") == 0) {
			break;
		}
		tyran_value return_value;
		tyran_mocha_api_eval(&api, global, &return_value, buf, tyran_strlen(buf));
		TYRAN_OUTPUT_NO_LF(" => ");
		print_value(api.default_runtime, &return_value);

	}

	return 0;
}
