#include <tyranscript/debug/tyran_print_runtime_state.h>
#include <tyranscript/debug/tyran_print_opcodes.h>
#include <tyranscript/debug/tyran_print_value.h>

#include "tyranscript/tyran_opcodes.h"
#include <tyranscript/tyran_constants.h>

#include "tyranscript/tyran_value.h"
#include "tyranscript/tyran_runtime_stack.h"


void tyran_print_runtime_state(const tyran_opcode* pc, const struct tyran_runtime_stack* sp, const struct tyran_value* r)
{
	long pc_value = pc - sp->opcodes->codes;
#define MAX_SIZE 1024
	char tmp[MAX_SIZE];
	char result[MAX_SIZE];

	result[0] = 0;
	int reg_index;
	TYRAN_LOG("---");
	for (reg_index=0; reg_index <= 29; reg_index++) {
		if (reg_index != 0) {
			tyran_strncat(result, ", ", MAX_SIZE);
		}
		tyran_snprintf(tmp, MAX_SIZE,  "r%d:", reg_index);
		tyran_strncat(result, tmp, MAX_SIZE);
		tyran_value_to_c_string(sp->constants->symbol_table, &r[reg_index], tmp, 128, 1);
		tyran_strncat(result, tmp, MAX_SIZE);
	}

	TYRAN_LOG("%s", result);

	tyran_print_opcode(pc, sp->constants, pc_value, 1);
}
