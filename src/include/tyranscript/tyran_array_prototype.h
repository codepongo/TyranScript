#ifndef _TYRAN_ARRAY_PROTOTYPE_H
#define _TYRAN_ARRAY_PROTOTYPE_H

struct tyran_value;
struct tyran_runtime;
struct tyran_memory_pool;

void tyran_array_prototype_init(const struct tyran_runtime* runtime, struct tyran_value* constructor_prototype);
int tyran_array_prototype_constructor(struct tyran_runtime* runtime, struct tyran_value* static_function, struct tyran_value* arguments, struct tyran_value* _this, struct tyran_value* return_value, int is_constructor);

#endif
