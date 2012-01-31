#ifndef _TYRAN_ARRAY_PROTOTYPE_H
#define _TYRAN_ARRAY_PROTOTYPE_H

struct tyran_value;
struct tyran_runtime;

extern struct tyran_value* tyran_array_prototype;

void tyran_array_prototype_init();
int tyran_array_prototype_constructor(tyran_runtime* runtime, tyran_value* static_function, tyran_value* arguments, tyran_value* _this, tyran_value* return_value, int is_constructor);

#endif
