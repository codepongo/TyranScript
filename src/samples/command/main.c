#include <tyranscript/tyran_mocha_api.h>

int mocha_print(struct tyran_runtime* runtime, struct tyran_value* function, struct tyran_value* arguments, int argument_count, struct tyran_value* _this, struct tyran_value* return_value, int is_new_call) {
	struct tyran_value* v = &arguments[0];
	const int buf_len = 100;
	char buf[buf_len];

	tyran_value_to_c_string(runtime->symbol_table, v, buf, buf_len, 0);

	puts(buf);

	tyran_value_set_number(*return_value, 16.0f);

	return 0;
}

int main(int argc, char* argv[])
{
	TYRAN_LOG("Mocha command");
	if (argc <= 1) {
		return -1;
	}
	const char* input_filename = argv[1];

	const int max_size = 32 * 1024;
	char buf[max_size];
	FILE* file = fopen(input_filename, "r");
	TYRAN_LOG("Reading '%s'", input_filename);
	int octets_read = fread(buf, 1, max_size, file);
	buf[octets_read] = 0;
	fclose(file);
	
	
	tyran_mocha_api api;
	
	tyran_mocha_api_new(&api, 1024);
	tyran_value* global = tyran_runtime_context(api.default_runtime);// tyran_mocha_api_create_object(&api);

	tyran_mocha_api_add_function(&api, global, "print", mocha_print);

	tyran_mocha_api_eval(&api, global, buf, tyran_strlen(buf));

	return 0;
}
