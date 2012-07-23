#include <tyranscript/tyran_api.h>
#include <tyranscript/parser/mocha/tyran_parser.h>

int main(int argc, char* argv[])
{
	TYRAN_LOG("TyranScript console");

	char buf[512];
	while (1)
	{
		TYRAN_LOG_NO_LF("> ");
		scanf("%511s", buf);
		tyran_parser* parser = tyran_parser_alloc(buf);
		tyran_parser_parse(parser);
	}

	return 0;
}
