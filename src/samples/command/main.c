#include <tyranscript/tyran_mocha_api.h>

void print_value(tyran_runtime* runtime, tyran_value* v)
{
	const int buf_len = 100;
	char buf[buf_len];
	tyran_value_to_c_string(runtime->symbol_table, v, buf, buf_len, 0);
	puts(buf);
}

void inspect_value(tyran_runtime* runtime, tyran_value* v)
{
	tyran_print_value("", v, 1, runtime->symbol_table, runtime->iterator_pool, runtime->string_pool, runtime->memory);
}


TYRAN_RUNTIME_CALL_FUNC(mocha_print)
{
	struct tyran_value* v = &arguments[0];
	print_value(runtime, v);
	tyran_value_set_number(*return_value, 16.0f);
	return 0;
}

tyran_value* load(tyran_mocha_api* api, tyran_value* global, const char* input_filename, tyran_value* return_object)
{
	const int max_size = 32 * 1024;
	char buf[max_size];
	FILE* file = fopen(input_filename, "r");
	TYRAN_LOG("Reading '%s'", input_filename);
	int octets_read = fread(buf, 1, max_size, file);
	buf[octets_read] = 0;
	fclose(file);


	tyran_value* new_object = tyran_value_object_new(api->default_runtime);
	tyran_value_object_set_prototype(new_object, global);

	tyran_value return_value;
	tyran_mocha_api_eval(api, new_object, &return_value, buf, tyran_strlen(buf));

	return new_object;
}

tyran_mocha_api api;
tyran_value* g_global;

TYRAN_RUNTIME_CALL_FUNC(mocha_load)
{
	struct tyran_value* v = &arguments[0];
	const tyran_string* filename = tyran_value_string(v);

	char c_filename[128];

	tyran_string_to_c_str(c_filename, 128, filename);

	tyran_value* created_object = load(&api, g_global, c_filename, return_value);

	tyran_value_copy(*return_value, *created_object);

	return 0;
}


int main(int argc, char* argv[])
{
	TYRAN_LOG("Mocha command");
	if (argc <= 1) {
		return -1;
	}
	const char* input_filename = argv[1];


	tyran_mocha_api_new(&api, 1024);
	tyran_value* global = tyran_runtime_context(api.default_runtime);

	g_global = global;
	tyran_mocha_api_add_function(&api, global, "print", mocha_print);
	tyran_mocha_api_add_function(&api, global, "load", mocha_load);

	tyran_value return_object;
	load(&api, global, input_filename, &return_object);

	return 0;
}
