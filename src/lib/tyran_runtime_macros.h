#define TYRAN_REGISTER_A \
	a = instruction;

#define TYRAN_REGISTER_A_X \
	i = instruction; \
	a = i; \
	i >>= 8; \
	x = i;

#define TYRAN_REGISTER_A_RCX \
	i = instruction; \
	a = i; \
	i >>= 8; \
	x = i; \
	i >>= 8; \
	xc = i & 0x01; \
	rcx = xc ? c[x] : r[x];

#define TYRAN_REGISTER_A_RCX_Y \
	i = instruction; \
	a = i; \
	i >>= 8; \
	x = i; \
	i >>= 8; \
	xc = i & 0x01; \
	i >>= 1; \
	y = i; \
	rcx = xc ? c[x] : r[x];

#define TYRAN_REGISTER_A_RCX_RCY \
	i = instruction; \
	a = i; \
	i >>= 8; \
	x = i; \
	i >>= 8; \
	xc = i & 0x01; \
	i >>= 1; \
	y = i; \
	i >>= 8; \
	yc = i & 0x01; \
	rcx = xc ? c[x] : r[x]; \
	rcy = yc ? c[y] : r[y];

#define TYRAN_REGISTER_A_B_RCX_RCY \
	i = instruction; \
	a = i; \
	i >>= 8; \
	x = i; \
	i >>= 8; \
	xc = i & 0x01; \
	i >>= 1; \
	y = i; \
	i >>= 8; \
	yc = i & 0x01; \
	rcx = xc ? c[x] : r[x]; \
	rcy = yc ? c[y] : r[y]; \
	i >>= 1; \
	b = i & 0x01;

#define TYRAN_REGISTER_BR \
	br = (instruction & 0xffff) - 0x8000;

#define TYRAN_STACK_PUSH \
	sp->r = r; \
	sp->c = c; \
	sp->pc = pc; \
	sp->argument_count = x; \
	sp++;

#define TYRAN_STACK_POP \
	sp--; \
	r = sp->r; \
	c = sp->c; \
	/* argument_count = sp->argument_count; */ \
	pc = sp->pc;

