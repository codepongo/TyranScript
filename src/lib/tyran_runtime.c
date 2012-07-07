#include "tyran_runtime_macros.h"
#include "tyranscript/tyran_value.h"
#include "tyranscript/tyran_runtime.h"
#include "tyranscript/tyran_opcode_ids.h"
#include "tyranscript/tyran_object_pool.h"
#include "tyranscript/tyran_config.h"
#include "tyranscript/tyran_function.h"
#include "tyranscript/tyran_function_object.h"
#include "tyranscript/tyran_opcodes.h"
#include "tyranscript/tyran_runtime_stack.h"
#include "tyranscript/tyran_value_object.h"
#include <tyranscript/debug/tyran_print_opcodes.h>

void tyran_runtime_execute(tyran_runtime* runtime, struct tyran_value* return_value, const struct tyran_runtime_callbacks* event_callbacks)
{
	TYRAN_LOG(" ");
	TYRAN_LOG("*** EXECUTE");
	// Parameters
	u8t a;
	u8t x;
	u8t y;
	u8t xc;
	u8t yc;

	int br;

	tyran_value rcx;
	tyran_value rcy;

	tyran_value_set_undefined(*return_value);

	// TYRAN_STACK_POP;
	runtime->stack_pointer--;

	tyran_runtime_stack* sp = &runtime->stack[runtime->stack_pointer];
	tyran_runtime_stack* base_sp = runtime->stack;

	// Context
	const tyran_opcode* pc = sp->pc;
	tyran_value* registers = TYRAN_MALLOC_TYPE(tyran_value, 128);
	registers[0] = sp->_this;

	tyran_value* r = registers;
	const tyran_value* c = sp->c;


	u32t i;
	int test;

	while (1)
	{
		long pc_value = pc - sp->opcodes->codes;

		char tmp[512];
		char result[512];

		result[0] = 0;

		for (int reg_index=0; reg_index < 4; reg_index++)
		{
			if (reg_index != 0) {
				tyran_strncat(result, ", ", 512);
			}
			tyran_snprintf(tmp, 512,  "r%d:", reg_index);
			tyran_strncat(result, tmp, 512);
			tyran_value_to_c_string(&r[reg_index], tmp, 512, 1);
			tyran_strncat(result, tmp, 512);
		}

		TYRAN_LOG("%s", result);

		tyran_print_opcode(pc, sp->constants, pc_value, 1);
		if (pc_value > 10) {
			return;
		}
	u32t instruction = *pc++;
	u32t opcode = instruction & 0x3f;
	instruction >>= 6;

	switch (opcode) {
		case TYRAN_OPCODE_LD:
			TYRAN_REGISTER_A_X;
			TYRAN_SET_REGISTER(a, x);
			TYRAN_ADD_REF(r[a]);
			break;
		case TYRAN_OPCODE_LDC:
			TYRAN_REGISTER_A_X;
			r[a] = c[x];
			TYRAN_ADD_REF(r[a]);
			break;
		case TYRAN_OPCODE_LDB:
			TYRAN_REGISTER_A_X;
			tyran_value_set_boolean(r[a], x);
			break;
		case TYRAN_OPCODE_LDN:
			TYRAN_REGISTER_A_X;
			// TYRAN_DEC_REF_RANGE(&runtime->object_pool, &r[a], x);
			tyran_memset_type_n(&r[a], 0, x);
			break;
		case TYRAN_OPCODE_ADD:
			TYRAN_REGISTER_A_RCX_RCY;
			tyran_value_set_number(r[a], rcx.data.number + rcy.data.number);
			break;
		case TYRAN_OPCODE_DIV:
			TYRAN_REGISTER_A_RCX_RCY;
			tyran_value_set_number(r[a], rcx.data.number / rcy.data.number);
			break;
		case TYRAN_OPCODE_MOD:
			TYRAN_REGISTER_A_RCX_RCY;
			tyran_value_set_number(r[a], tyran_fmod(rcx.data.number, rcy.data.number));
			break;
		case TYRAN_OPCODE_MUL:
			TYRAN_REGISTER_A_RCX_RCY;
			tyran_value_set_number(r[a], rcx.data.number * rcy.data.number);
			break;
		case TYRAN_OPCODE_NEG:
			TYRAN_REGISTER_A_RCX;
			tyran_value_set_number(r[a], -rcx.data.number);
			break;
		case TYRAN_OPCODE_NOT:
			TYRAN_REGISTER_A_RCX;
			tyran_value_set_boolean(r[a], !rcx.data.boolean);
			break;
		case TYRAN_OPCODE_POW:
			TYRAN_REGISTER_A_RCX_RCY;
			tyran_value_set_number(r[a], tyran_pow(rcx.data.number, rcy.data.number));
			break;
		case TYRAN_OPCODE_SUB:
			TYRAN_REGISTER_A_RCX_RCY;
			tyran_value_set_number(r[a], rcx.data.number - rcy.data.number);
			break;
		case TYRAN_OPCODE_JB:
			TYRAN_REGISTER_A_RCX;
			if (rcx.data.boolean != a) {
				pc++;
			}
			break;
		case TYRAN_OPCODE_JBLD:
			TYRAN_REGISTER_A_RCX_Y;
			if (rcx.data.boolean != y) {
				r[a] = rcx;
			} else {
				pc++;
			}
			break;
		case TYRAN_OPCODE_JEQ:
			TYRAN_REGISTER_A_RCX_RCY;
			if (rcx.type == TYRAN_VALUE_TYPE_STRING) {
				test = tyran_string_strcmp(rcx.data.str, rcy.data.str) == 0;
			} else {
				test = (rcx.data.data == rcy.data.data);
			}
			if (test != a) {
				pc++;
			}
			break;
		case TYRAN_OPCODE_JLT:
			TYRAN_REGISTER_A_RCX_RCY;
			if (rcx.type == TYRAN_VALUE_TYPE_STRING) {
				test = tyran_string_strcmp(rcx.data.str, rcy.data.str) < 0;
			} else {
				test = (rcx.data.data < rcy.data.data);
			}
			if (test != a) {
				pc++;
			}
			break;
		case TYRAN_OPCODE_JLE:
			TYRAN_REGISTER_A_RCX_RCY;
			if (rcx.type == TYRAN_VALUE_TYPE_STRING) {
				test = tyran_string_strcmp(rcx.data.str, rcy.data.str) <= 0;
			} else {
				test = (rcx.data.data <= rcy.data.data);
			}
			if (test != a) {
				pc++;
			}
			break;
		case TYRAN_OPCODE_JMP:
			TYRAN_REGISTER_BR;
			pc += br;
			break;
		case TYRAN_OPCODE_RET:
			if (sp == base_sp) {
				return;
			}
			TYRAN_STACK_POP;
			break;
		case TYRAN_OPCODE_CALL:
			TYRAN_STACK_PUSH;
			TYRAN_REGISTER_A_X;
			{
				TYRAN_ASSERT(tyran_value_is_function(&r[a]), "Must reference a function!");
				const tyran_function* function = r[a].data.object->data.function->static_function;
				sp->opcodes = function->data.opcodes;
				pc = sp->opcodes->codes;
				sp->constants = function->constants;
				c = sp->constants->values;
				r = &r[a] + 1;
			}
			break;
		case TYRAN_OPCODE_NEW:
			TYRAN_REGISTER_A;
			tyran_value_set_object(r[a], tyran_object_pool_alloc(&runtime->object_pool));
			break;
		case TYRAN_OPCODE_GET:
			TYRAN_REGISTER_A_RCX_RCY;
			TYRAN_ASSERT(tyran_value_is_string(&rcy), "Must use string to lookup. for now");
			tyran_object_key_flag_type flag = tyran_object_key_flag_normal;
			const tyran_object_key* key = tyran_object_key_new(rcy.data.str, flag);
			TYRAN_ASSERT(tyran_value_is_object(&rcx), "Must lookup object");
			tyran_value* v = tyran_value_object_lookup(&rcx, key, &flag);
			tyran_value_copy(r[a], *v);
			TYRAN_ADD_REF(r[a]);
			break;
		case TYRAN_OPCODE_SET:
			TYRAN_REGISTER_A_RCX_RCY;
			TYRAN_ASSERT(tyran_value_is_string(&rcx), "Must be string");
			tyran_value_object_insert_string_key(&r[a], rcx.data.str, &rcy);
			break;
		case TYRAN_OPCODE_DEBUG:
			return;
			break;
		}
	}
}
