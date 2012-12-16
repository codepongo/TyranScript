#include <tyranscript/tyran_mocha_api.h>

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
	tyran_value global = tyran_mocha_api_create_object(&api);
	tyran_mocha_api_eval(&api, &global, buf, tyran_strlen(buf));

	return 0;
}
