#include <tyranscript/tyran_api.h>
#include <tyranscript/parser/mocha/tyran_mocha_lexer.h>
#include <tyranscript/debug/mocha/tyran_mocha_lexer_debug.h>
#include <tyranscript/debug/parser/tyran_print_parser_tree.h>
#include <tyranscript/parser/mocha/tyran_mocha_parser.h>
#include <tyranscript/parser/common/tyran_generator.h>
#include <tyranscript/parser/common/tyran_code.h>

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
	
	return 0;
}
