#ifndef _TYRAN_OBJECT_POOL_H
#define _TYRAN_OBJECT_POOL_H

struct tyran_object;

typedef struct tyran_object_pool {
	void* p;
} tyran_object_pool;

void tyran_object_pool_free(tyran_object_pool* pool, struct tyran_object* v);
struct tyran_object* tyran_object_pool_alloc(tyran_object_pool* pool);

#endif
