#define TYRAN_RUNTIME_REGISTER_ALL() \
	i = instruction; \
	a = i; \
	i >>= 8; \
	x = i; \
	i >>= 8; \
	xc = i & 0x01; \
	i >>= 1; \
	y = i; \
	i >>= 1; \
	yc = i & 0x01;

struct tyran_value
{
	union 
	{
		uint32 data;
		float32 number;
		tyran_string* characters;
		uint32 boolean;
	};

	enum tyran_type type;
};

struct tyran_context
{
	uint32* pc;
	tyran_value* r;
	tyran_value* c;
};

#define TYRAN_STACK_PUSH \
	sp->r = r; \
	sp->c = c; \
	sp->pc = pc; \
	sp++;

#define TYRAN_STACK_POP \
	sp--; \
	r = sp->r; \
	c = sp->c; \
	pc = sp->pc;

void tyran_runtime_execute(tyran_runtime* runtime, struct tyran_value* return_value, const struct tyran_runtime_callbacks* event_callbacks)
{
	// Parameters
	uint8 a;
	uint8 x;
	uint8 y;

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
			break;
		case TYRAN_OPCODE_LDC:
			TYRAN_REGISTER_A_X;
			r[a] = c[x];
			break;
		case TYRAN_OPCODE_LDB:
			TYRAN_REGISTER_A_X;
			r[a].type = TYRAN_TYPE_BOOLEAN;
			r[a].boolean = x;
			break;
		case TYRAN_OPCODE_LDN:
			TYRAN_REGISTER_A_X;
			memcpy(&r[a], 0, sizeof(uint32) * x);
			break;
		case TYRAN_OPCODE_ADD:
			TYRAN_REGISTER_RCX_RCY;
			r[a].number = rcx.number + rcy.number;
			break;
		case TYRAN_OPCODE_DIV:
			TYRAN_REGISTER_RCX_RCY;
			r[a].number = rcx.number / rcy.number;
			break;
		case TYRAN_OPCODE_MOD:
			TYRAN_REGISTER_RCX_RCY;
			r[a].number = rcx.number % rcy.number;
			break;
		case TYRAN_OPCODE_MUL:
			TYRAN_REGISTER_RCX_RCY;
			r[a].number = rcx.number * rcy.number;
			break;
		case TYRAN_OPCODE_NEG:
			TYRAN_REGISTER_RCX;
			r[a].number = -rcx.number;
			break;
		case TYRAN_OPCODE_NOT:
			TYRAN_REGISTER_RCX;
			r[a].boolean = !rcx.boolean;
			break;
		case TYRAN_OPCODE_POW:
			TYRAN_REGISTER_RCX_RCY;
			r[a].number = rcx.number ^ rcy.number;
			break;
		case TYRAN_OPCODE_SUB:
			TYRAN_REGISTER_RCX_RCY;
			r[a].number = rcx.number - rcy.number;
			break;
		case TYRAN_OPCODE_JB:
			TYRAN_REGISTER_RCX;
			if (rcx.boolean != a) {
				pc++;
			}
			break;
		case TYRAN_OPCODE_JBLD:
			if (rcx.boolean != y) {
				r[a] = rcx;
			} else {
				pc++;
			}
			break;
		case TYRAN_OPCODE_JEQ:
			TYRAN_REGISTER_RCX_RCY;
			bool match;
			if (rcx.type == TYRAN_STRING) {
				match = strcmp(rcx.characters, rcy.characters) == 0;
			} else {
				match = (rcx.data == rcy.data);
			}
			if (match != a) {
				pc++;
			}
			break;
		case TYRAN_OPCODE_JLT:
			TYRAN_REGISTER_RCX_RCY;
			bool match;
			if (rcx.type == TYRAN_STRING) {
				match = strcmp(rcx.characters, rcy.characters) < 0;
			} else {
				match = (rcx.data < rcy.data);
			}
			if (match != a) {
				pc++;
			}
			break;
		case TYRAN_OPCODE_JLE:
			TYRAN_REGISTER_RCX_RCY;
			bool match;
			if (rcx.type == TYRAN_STRING) {
				match = strcmp(rcx.characters, rcy.characters) <= 0;
			} else {
				match = (rcx.data <= rcy.data);
			}
			if (match != a) {
				pc++;
			}
			break;
		case TYRAN_OPCODE_JMP:
			TYRAN_REGISTER_BR;
			pc += br - 0x8000;
			break;
		case TYRAN_OPCODE_RET:
			TYRAN_CONTEXT_POP;
			break;
		case TYRAN_OPCODE_CALL:
			TYRAN_CONTEXT_PUSH;
			tyran_function* function = r[a].function;
			r = &r[a];
			pc = function->instructions;
			c = function->constants;
			break;
		case TYRAN_OPCODE_SET:
			TYRAN_REGISTER_RCX_RCY;
			hash = TYRAN_CALC_HASH(rcx);
			tyran_tree_add(r[a].object.tree, hash, rcy);
			break;
		case TYRAN_OPCODE_GET:
			TYRAN_REGISTER_RCX_RCY;
			hash = TYRAN_CALC_HASH(rcy);
			r[a] = tyran_tree_find(rcx.object.tree, hash);
			break;
		case TYRAN_OPCODE_DEBUG:
			return;
			break;
	}
}
