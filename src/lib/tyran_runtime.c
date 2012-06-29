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

typedef struct tyran_context
{
	u32t* pc;
	tyran_value* r;
	tyran_value* c;
} tyran_context;

void tyran_runtime_execute(tyran_runtime* runtime, struct tyran_value* return_value, const struct tyran_runtime_callbacks* event_callbacks)
{
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

	tyran_runtime_stack* stack = &runtime->stack[runtime->stack_pointer];


	// Context
	const u32t* pc = stack->pc;
	tyran_value registers[128];

	tyran_value* r = registers;
	tyran_value* c;

	tyran_context* sp;


	u32t i;
	int test;
	u32t instruction = *pc++;
	u32t opcode = instruction & 0x3f;
	instruction >>= 6;

	switch (opcode) {
		case TYRAN_OPCODE_LD:
			TYRAN_LOG("LD opcode");
			// TYRAN_REGISTER_A_X;
			// r[a] = r[x];
			// TYRAN_ADD_REF(r[a]);
			break;
		case TYRAN_OPCODE_LDC:
			TYRAN_REGISTER_A_X;
			r[a] = c[x];
			TYRAN_ADD_REF(r[a]);
			break;
		case TYRAN_OPCODE_LDB:
			TYRAN_REGISTER_A_X;
			r[a].type = TYRAN_VALUE_TYPE_BOOLEAN;
			r[a].data.boolean = x;
			break;
		case TYRAN_OPCODE_LDN:
			TYRAN_REGISTER_A_X;
			TYRAN_DEC_REF_RANGE(&runtime->object_pool, &r[a], x);
			tyran_memset_type_n(&r[a], 0, x);
			break;
		case TYRAN_OPCODE_ADD:
			TYRAN_REGISTER_A_RCX_RCY;
			r[a].data.number = rcx.data.number + rcy.data.number;
			break;
		case TYRAN_OPCODE_DIV:
			TYRAN_REGISTER_A_RCX_RCY;
			r[a].data.number = rcx.data.number / rcy.data.number;
			break;
		case TYRAN_OPCODE_MOD:
			TYRAN_REGISTER_A_RCX_RCY;
			r[a].data.number = tyran_fmod(rcx.data.number, rcy.data.number);
			break;
		case TYRAN_OPCODE_MUL:
			TYRAN_REGISTER_A_RCX_RCY;
			r[a].data.number = rcx.data.number * rcy.data.number;
			break;
		case TYRAN_OPCODE_NEG:
			TYRAN_REGISTER_A_RCX;
			r[a].data.number = -rcx.data.number;
			break;
		case TYRAN_OPCODE_NOT:
			TYRAN_REGISTER_A_RCX;
			r[a].data.boolean = !rcx.data.boolean;
			break;
		case TYRAN_OPCODE_POW:
			TYRAN_REGISTER_A_RCX_RCY;
			r[a].data.number = tyran_pow(rcx.data.number, rcy.data.number);
			break;
		case TYRAN_OPCODE_SUB:
			TYRAN_REGISTER_A_RCX_RCY;
			r[a].data.number = rcx.data.number - rcy.data.number;
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
			TYRAN_CONTEXT_POP;
			break;
		case TYRAN_OPCODE_NEW:
			TYRAN_REGISTER_A_X;
			r[a].data.object = tyran_object_pool_alloc(&runtime->object_pool); 
			r[a].type = TYRAN_VALUE_TYPE_OBJECT;
			if (x) {
				break;
			}
		case TYRAN_OPCODE_CALL:
			TYRAN_CONTEXT_PUSH;
			TYRAN_REGISTER_A_X;
			{
				const tyran_function* function = r[a].data.object->data.function->static_function;
				r = &r[a];
				pc = function->data.opcodes->codes;
				c = function->constants;
			}
			break;
/*
		case TYRAN_OPCODE_SET:
			TYRAN_REGISTER_A_RCX_RCY;
			i = TYRAN_CALC_HASH(rcx);
			tyran_tree_set(r[a].data.object.tree, i, rcy);
			break;
		case TYRAN_OPCODE_GET:
			TYRAN_REGISTER_A_RCX_RCY;
			i = TYRAN_CALC_HASH(rcy);
			r[a] = tyran_tree_get(rcx.data.object.tree, i);
			TYRAN_ADD_REF(r[a]);
			break;
*/
		case TYRAN_OPCODE_DEBUG:
			return;
			break;
		}
	}
}
