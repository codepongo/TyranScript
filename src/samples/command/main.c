#include <tyranscript/tyran_api.h>
#include <tyranscript/parser/mocha/tyran_mocha_lexer.h>
#include <tyranscript/parser/mocha/tyran_mocha_lexer_debug.h>
#include <tyranscript/parser/mocha/tyran_mocha_parser.h>
#include <tyranscript/parser/common/tyran_generator.h>
#include <tyranscript/parser/common/tyran_code.h>

int main(int argc, char* argv[])
{
	TYRAN_LOG("Mocha command");

	const int max_size = 32 * 1024;
	char buf[max_size];
	
	FILE* file = fopen("/Users/peter/work/TyranScript/src/samples/executor/test.mocha", "r");
	
	int octets_read = fread(buf, 1, max_size, file);
	buf[octets_read] = 0;
	fclose(file);
	
	tyran_mocha_lexer* mocha_lexer = tyran_mocha_lexer_lex(buf, tyran_strlen(buf));
	tyran_mocha_lexer_debug(mocha_lexer);
	struct tyran_parser_node* parser_tree = tyran_mocha_parser_parse(mocha_lexer);
	tyran_parser_node_print("result", parser_tree, 0);
	struct tyran_code_state* code = tyran_code_new();
	tyran_generator_new(parser_tree, code);
	tyran_print_opcodes(code->opcodes, 0, code->constants);
	
	return 0;
}
