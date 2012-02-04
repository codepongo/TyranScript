#include <tyranscript/tyran_api.h>

void expose_function(tyran_value* global, const char* name, tyran_function_callback static_function)
{
	tyran_value* function_object = tyran_function_object_new_callback(static_function);
	tyran_value_object_insert_string_key(global, tyran_string_from_c_str(name), function_object);
}

int read_file(const char* filename, char* buf, int max_length)
{
	FILE* fp = fopen(filename, "rb");
	int read = fread(buf, 1, max_length, fp);
	buf[read] = 0;
	return read;
}

tyran_parser_state* parse_file(const char* filename)
{
	const int max_length = 8192;
	char buf[max_length];

	int read_octets = read_file(filename, buf, max_length);

	tyran_parser_state* state = tyran_parser_state_new(buf, read_octets);
	printf("Error:%d\n", state->error_count);
	tyran_opcodes_print(state->opcodes);

	return state;
}

static int script_print(tyran_runtime* runtime, tyran_value* static_function, tyran_value* args, tyran_value* _this, tyran_value* ret, int is_constructor)
{
	tyran_value* str = tyran_value_object_lookup_array(args, 0, 0);
	char buf[2048];
	tyran_value_to_c_string(str, buf, 2048, 0);
	TYRAN_LOG_NO_LF("%s", buf);
	return 0;
}

tyran_value* create_context()
{
	tyran_value* global = tyran_value_new();
	tyran_value_set_object(*global, tyran_object_new());
	tyran_prototypes_init(global);

	expose_function(global, "print", script_print);

	return global;
}

void execute(tyran_opcodes* opcodes)
{
	tyran_value return_value;

	tyran_runtime_callbacks* callbacks = TYRAN_CALLOC(tyran_runtime_callbacks);

	tyran_runtime* runtime = tyran_runtime_new();

	tyran_value* global = create_context();

	tyran_scope_stack* global_scope_stack = tyran_scope_stack_clone_and_add(0, global);

	tyran_runtime_execute(runtime, opcodes, global_scope_stack, global, global, &return_value, callbacks);

	tyran_free(callbacks);

	tyran_runtime_free(runtime);

	tyran_print_value("\nresult", &return_value, 1);
}

int main(int argc, char* argv[])
{
	if (argc <= 1) {
		return -1;
	}


	tyran_parser_state* state = parse_file(argv[1]);
	execute(state->opcodes);
	tyran_parser_state_free(state);

	return 0;
}
