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
	i >>= 1; \
	yc = i & 0x01; \
	rcx = xc ? c[x] : r[x]; \
	rcy = yc ? c[y] : r[y];

#define TYRAN_REGISTER_BR \
	br = (instruction & 0xffff) - 0x8000;

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

#define TYRAN_ADD_REF(v) \
	if ((v).type == TYRAN_TYPE_OBJECT) { \
		((v)).object.ref_cnt++; \
	}

#define TYRAN_DEC_REF(memory_pool, v) \
	if (--(v).object.ref_cnt == 0) { \
		object_pool_free(memory_pool, (v).object); \
	}

#define TYRAN_DEC_REF_RANGE(memory_pool, v, n) { \
	for (int __i=0; __i < n; ++__i) { \
		TYRAN_DEC_REF(memory_pool, v[i]); \
	}
