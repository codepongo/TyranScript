#ifndef _TYRAN_FUNCTION_PROTOTYPE_H
#define _TYRAN_FUNCTION_PROTOTYPE_H

extern struct tyran_value* tyran_function_prototype;

struct tyran_runtime;
struct tyran_memory_pool;

void tyran_function_prototype_init(struct tyran_memory_pool* function_pool, struct tyran_memory_pool* function_object_pool, struct tyran_memory_pool* object_pool, struct tyran_memory_pool* value_pool, const struct tyran_runtime* runtime, struct tyran_value* constructor_protoype);
int tyran_function_prototype_constructor(struct tyran_runtime* runtime, struct tyran_value* function, struct tyran_value* arguments, int argument_count, struct tyran_value* _this, struct tyran_value* return_value, int is_constructor);

#endif
