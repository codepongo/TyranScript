#include <tyranscript/tyran_api.h>
#include <tyranscript/parser/mocha/tyran_mocha_lexer.h>
#include <tyranscript/parser/mocha/tyran_mocha_lexer_debug.h>
#include <tyranscript/parser/mocha/tyran_mocha_parser.h>

int main(int argc, char* argv[])
{
	TYRAN_LOG("TyranScript console");

	char buf[512];
	while (1)
	{
		TYRAN_LOG_NO_LF("> ");
		char* p = fgets(buf, 512, stdin);
		if (!p) {
			break;
		}
		tyran_mocha_lexer* mocha_lexer = tyran_mocha_lexer_lex(buf, tyran_strlen(buf));
		tyran_mocha_lexer_debug(mocha_lexer);
		struct tyran_parser_node* mocha_parser_tree = tyran_mocha_parser_parse(mocha_lexer);
		
		tyran_parser_node_print("result", mocha_parser_tree, 0);
	}

	return 0;
}
