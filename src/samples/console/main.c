#include <tyranscript/tyran_api.h>
#include <tyranscript/parser/mocha/tyran_parser.h>

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
		tyran_parser* parser = tyran_parser_new(p);
		tyran_parser_parse(parser);
	}

	return 0;
}
