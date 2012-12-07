#include <tyranscript/tyran_mocha_api.h>

int mocha_print(struct tyran_runtime* runtime, struct tyran_value* function, struct tyran_value* arguments, struct tyran_value* _this, struct tyran_value* return_value, int is_new_call) {
	TYRAN_OUTPUT("PRINT");
	return 0;
}


int main(int argc, char* argv[])
{
	TYRAN_LOG("TyranScript console");

	tyran_mocha_api api;
	tyran_mocha_api_new(&api, 1024);

	tyran_value global = tyran_mocha_api_create_object(&api);
	tyran_mocha_api_add_function(&api, &global, "print", mocha_print);

	char buf[512];
	while (1)
	{
		TYRAN_LOG_NO_LF("> ");
		char* p = fgets(buf, 512, stdin);
		if (!p) {
			break;
		}

		tyran_mocha_api_eval(&api, buf, tyran_strlen(buf));		
		
//		tyran_parser_node_print("result", mocha_parser_tree, 0);
	}

	return 0;
}
