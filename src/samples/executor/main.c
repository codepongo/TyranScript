#include <tyranscript/tyran_api.h>

void expose_function(const struct tyran_runtime* runtime, tyran_value* global, const char* name, tyran_function_callback static_function)
{
	tyran_value* function_object = tyran_function_object_new_callback(runtime, static_function);
	tyran_value_object_insert_string_key(global, tyran_string_from_c_str(name), function_object);
}

int read_file(const char* filename, char* buf, int max_length)
{
	FILE* fp;
	int read;
	tyran_fopen(&fp, filename, "rb");
	read = tyran_fread(buf, 1, max_length, fp);
	tyran_fclose(fp);
	buf[read] = 0;
	return read;
}

tyran_parser_state* parse_file(const char* filename)
{
	const int max_length = 8192;
	char buf[max_length];

	int read_octets = read_file(filename, buf, max_length);

	tyran_parser_state* state = tyran_parser_state_new(buf, read_octets);
	if (state->error_count) {
		printf("Error:%d\n", state->error_count);
	}
	if (state->opcodes == 0) {
		return state;
	}
	// tyran_opcodes_print(state->opcodes, 0);

	return state;
}

static int script_print(tyran_runtime* r, tyran_value* a, tyran_value* args, tyran_value* c, tyran_value* d, int is_constructor)
{
	tyran_object_key_flag_type flag;
	tyran_value* str = tyran_value_object_lookup_array(args, 0, &flag);
	char buf[2048];
	tyran_value_to_c_string(str, buf, 2048, 0);
	TYRAN_LOG_NO_LF("%s", buf);
	return 0;
}

tyran_value* create_context(const struct tyran_runtime* runtime)
{
	tyran_value* global = tyran_value_new();
	tyran_value_set_object(*global, tyran_object_new(runtime));
	tyran_prototypes_init(runtime, global);

	expose_function(runtime, global, "print", script_print);

	return global;
}

void object_deleted(const struct tyran_runtime* runtime, tyran_object* program_specific)
{
	tyran_value value;
	value.type = TYRAN_VALUE_TYPE_OBJECT;
	value.data.object = program_specific;
	// tyran_print_value("DELETED", &value, 1);
}

void execute(tyran_opcodes* opcodes, const char* numeric)
{
	tyran_value return_value;

	tyran_runtime_callbacks* callbacks = TYRAN_CALLOC(tyran_runtime_callbacks);

	tyran_runtime* runtime = tyran_runtime_new();
	runtime->delete_callback = object_deleted;

	tyran_value* global = create_context(runtime);

	tyran_scope_stack* global_scope_stack = tyran_scope_stack_clone_and_add(0, global);

	

	tyran_value* arguments = tyran_value_object_new(runtime);
	tyran_value argument;
	tyran_value_set_number(argument, atoi(numeric));
	tyran_value_object_insert_array(arguments, 0, &argument);
	tyran_value_set_object(*global, tyran_object_new(runtime));

	tyran_runtime_push_call(runtime, opcodes, global_scope_stack, arguments, global);
	tyran_runtime_execute(runtime, &return_value, callbacks);

	tyran_value_release(*global);

	tyran_free(callbacks);

	tyran_runtime_free(runtime);

	tyran_print_value("\nresult", &return_value, 1);
}

int main(int argc, char* argv[])
{
	if (argc <= 1) {
		printf("usage: script_file [argument]\n");
		return -1;
	}

	tyran_parser_state* state = parse_file(argv[1]);
	if (state->opcodes) {
		execute(state->opcodes, argc >= 3 ? argv[2] : "0");
	}
	tyran_parser_state_free(state);

	return 0;
}
