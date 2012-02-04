#include "tyran_print_runtime.h"

#include <tyranscript/tyran_config.h>
#include <tyranscript/tyran_value.h>

#include <tyranscript/debug/tyran_opcodes_print.h>
#include <tyranscript/debug/tyran_print_value.h>

void tyran_print_runtime(const tyran_value* stack, int sp, const tyran_value* _this, const struct tyran_opcode* opcode, int ip)
{
	int i;
	char stack_info[2048];

	tyran_sprintf(stack_info, "STACK%d: ", sp);
	for (i = sp - 1; i >= 0 && i >= sp - 10; --i) {
		if (i != sp - 1) {
			tyran_strcat(stack_info, ", ");
		}
		char some_info[2048];
		tyran_value_to_c_string(&stack[i], some_info, 2048, 1);
		tyran_strcat(stack_info, some_info);
	}

	tyran_strcat(stack_info, "   _this:");
	char other_info[2048];
	tyran_value_to_c_string(_this, other_info, 2048, 1);
	tyran_strcat(stack_info, other_info);

	TYRAN_LOG("%s", stack_info);
	tyran_opcodes_print_opcode(opcode, ip);
}
