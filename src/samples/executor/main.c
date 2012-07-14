#include <tyranscript/tyran_api.h>
#include <tyranscript/parser/tyran_parser_assembler.h>
#include <tyranscript/tyran_constants.h>

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
}


void execute(tyran_runtime* runtime, const tyran_opcodes* opcodes, const struct tyran_constants* constants, tyran_value* global)
{
	tyran_value return_value;

	tyran_runtime_callbacks* callbacks = TYRAN_CALLOC(tyran_runtime_callbacks);

	runtime->delete_callback = object_deleted;

	tyran_runtime_push_call(runtime, opcodes, constants, global);
	tyran_runtime_execute(runtime, &return_value, callbacks);

	// tyran_value_release(*global);

	// tyran_free(callbacks);

	tyran_runtime_free(runtime);

	tyran_print_value("\nresult", &return_value, 1);
}

void execute_function(tyran_runtime* runtime, tyran_value* _this, const char* func_name)
{
	TYRAN_LOG(" ");
	TYRAN_LOG("Execute function '%s'", func_name);
	tyran_print_value("TJOHO", _this, 1);
	tyran_object_key_flag_type flag;
	tyran_value* value = tyran_value_object_lookup_string(_this, tyran_string_from_c_str(func_name), &flag);
	TYRAN_ASSERT(tyran_value_is_function(value), "Must be function!");
	
	const tyran_function* func = value->data.object->data.function->static_function;
	// tyran_print_opcodes(func->data.opcodes, 0, func->constants);
	execute(runtime, func->data.opcodes, func->constants, _this);
}

tyran_parser_state* parse_file(tyran_runtime* runtime, tyran_value* global, const char* filename)
{
	TYRAN_LOG("Parse file '%s'", filename);
	const int max_length = 8192;
	char buf[max_length];

	int read_octets = read_file(filename, buf, max_length);
	TYRAN_LOG("Read %d octets", read_octets);

	tyran_parser_state* state = tyran_parser_state_new(runtime, global, buf, read_octets);

	tyran_lexer_position_info position;
	tyran_lexer_assembler_parse(&position, state);
	if (state->error_count) {
		printf("Error:%d\n", state->error_count);
	}

	if (state->opcodes == 0) {
		return state;
	}
	// tyran_opcodes_print(state->opcodes, 0);

	return state;
}

int main(int argc, char* argv[])
{
	if (argc <= 1) {
		printf("usage: script_file [argument]\n");
		return -1;
	}

	tyran_runtime* runtime = tyran_runtime_new();
	tyran_value* global = create_context(runtime);
	tyran_parser_state* state = parse_file(runtime, global, argv[1]);
	if (state->opcodes) {
		execute_function(runtime, global, "main");
	}
	tyran_parser_state_free(state);

	return 0;
}
