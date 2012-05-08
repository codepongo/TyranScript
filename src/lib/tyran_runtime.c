#include "tyran_runtime_macros.h"

struct tyran_context
{
	uint32* pc;
	tyran_value* r;
	tyran_value* c;
};

void tyran_runtime_execute(tyran_runtime* runtime, struct tyran_value* return_value, const struct tyran_runtime_callbacks* event_callbacks)
{
	// Parameters
	uint8 a;
	uint8 x;
	uint8 y;

	tyran_value rcx;
	tyran_value rcy;

	// Context
	uint32* pc = 0;
	tyran_value[] r;
	tyran_value[] c;

	tyran_context[] sp;

	TYRAN_STACK_POP;

	uint32 instruction;

	uint32 instruction = *pc++;
	uint32 opcode = instruction & 0x3f;
	instruction >>= 6;

	switch (opcode)
	{
		case TYRAN_OPCODE_LD:
			TYRAN_REGISTER_A_X;
			r[a] = r[x];
			TYRAN_ADD_REF(r[a]);
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
			TYRAN_DEC_REF_RANGE(&r[a], x);
			memcpy(&r[a], 0, sizeof(uint32) * x);
			break;
		case TYRAN_OPCODE_ADD:
			TYRAN_REGISTER_A_RCX_RCY;
			r[a].number = rcx.data.number + rcy.data.number;
			break;
		case TYRAN_OPCODE_DIV:
			TYRAN_REGISTER_A_RCX_RCY;
			r[a].number = rcx.data.number / rcy.data.number;
			break;
		case TYRAN_OPCODE_MOD:
			TYRAN_REGISTER_A_RCX_RCY;
			r[a].number = rcx.data.number % rcy.data.number;
			break;
		case TYRAN_OPCODE_MUL:
			TYRAN_REGISTER_A_RCX_RCY;
			r[a].number = rcx.data.number * rcy.data.number;
			break;
		case TYRAN_OPCODE_NEG:
			TYRAN_REGISTER_A_RCX;
			r[a].number = -rcx.data.number;
			break;
		case TYRAN_OPCODE_NOT:
			TYRAN_REGISTER_A_RCX;
			r[a].boolean = !rcx.data.boolean;
			break;
		case TYRAN_OPCODE_POW:
			TYRAN_REGISTER_A_RCX_RCY;
			r[a].number = rcx.data.number ^ rcy.data.number;
			break;
		case TYRAN_OPCODE_SUB:
			TYRAN_REGISTER_A_RCX_RCY;
			r[a].number = rcx.data.number - rcy.data.number;
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
			bool match;
			if (rcx.type == TYRAN_VALUE_TYPE_STRING) {
				match = strcmp(rcx.data.str, rcy.data.str) == 0;
			} else {
				match = (rcx.data.raw == rcy.data.raw);
			}
			if (match != a) {
				pc++;
			}
			break;
		case TYRAN_OPCODE_JLT:
			TYRAN_REGISTER_A_RCX_RCY;
			bool match;
			if (rcx.type == TYRAN_VALUE_TYPE_STRING) {
				match = strcmp(rcx.data.str, rcy.data.str) < 0;
			} else {
				match = (rcx.data.raw < rcy.data.raw);
			}
			if (match != a) {
				pc++;
			}
			break;
		case TYRAN_OPCODE_JLE:
			TYRAN_REGISTER_A_RCX_RCY;
			bool match;
			if (rcx.type == TYRAN_VALUE_TYPE_STRING) {
				match = strcmp(rcx.data.str, rcy.data.str) <= 0;
			} else {
				match = (rcx.data.raw <= rcy.data.raw);
			}
			if (match != a) {
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
		case TYRAN_OPCODE_CALL:
			TYRAN_CONTEXT_PUSH;
			TYRAN_REGISTER_A_X;
			tyran_function* function = r[a].object.function;
			if (y == TYRAN_CALL_NEW) {
				r[a] = object_pool_alloc();
			}
			r = &r[a];
			pc = function->instructions;
			c = function->constants;
			break;
		case TYRAN_OPCODE_SET:
			TYRAN_REGISTER_A_RCX_RCY;
			hash = TYRAN_CALC_HASH(rcx);
			tyran_tree_set(r[a].data.object.tree, hash, rcy);
			break;
		case TYRAN_OPCODE_GET:
			TYRAN_REGISTER_A_RCX_RCY;
			hash = TYRAN_CALC_HASH(rcy);
			r[a] = tyran_tree_get(rcx.data.object.tree, hash);
			TYRAN_ADD_REF(r[a]);
			break;
		case TYRAN_OPCODE_DEBUG:
			return;
			break;
	}
}
