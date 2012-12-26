#include "tyran_print_runtime.h"

#include <tyranscript/tyran_config.h>
#include <tyranscript/tyran_value.h>

#include <tyranscript/debug/tyran_print_opcodes.h>
#include <tyranscript/debug/tyran_print_value.h>
#include <tyranscript/tyran_constants.h>

void tyran_print_runtime(const tyran_value* stack, int sp, const tyran_value* _this, const struct tyran_constants* constants, const tyran_opcode* opcode, int ip)
{
	int i;
	const int max_size = 2048;
	char stack_info[max_size];
	stack_info[0] = 0;

	int stack_info_length_left = max_size - 1;
	tyran_snprintf(stack_info, max_size, "STACK%d: ", sp - 1);
	for (i = sp - 1; i >= 0 && i >= sp - 10; --i) {
		if (i != sp - 1) {
			const char* seperator = ", ";
			tyran_strncat(stack_info, seperator, stack_info_length_left);
			stack_info_length_left -= tyran_strlen(seperator);
		}
		char some_info[max_size];
		tyran_value_to_c_string(constants->symbol_table, &stack[i], some_info, max_size, 1);
		stack_info_length_left -= tyran_strlen(some_info);
		tyran_strncat(stack_info, some_info, stack_info_length_left);
	}

	const char* this_seperator = "   _this:";
	tyran_strncat(stack_info, this_seperator, stack_info_length_left);
	stack_info_length_left -= tyran_strlen(this_seperator);

	char this_info[max_size];
	tyran_value_to_c_string(constants->symbol_table, _this, this_info, max_size, 1);
	tyran_strncat(stack_info, this_info, stack_info_length_left);

	TYRAN_LOG("%s", stack_info);
	tyran_print_opcode(opcode, constants, ip, 1);
}
