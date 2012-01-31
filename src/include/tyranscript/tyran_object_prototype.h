#ifndef _TYRAN_OBJECT_PROTOTYPE_H
#define _TYRAN_OBJECT_PROTOTYPE_H

extern struct tyran_value* tyran_object_prototype;
struct tyran_runtime;

void tyran_object_prototype_init();
int tyran_object_prototype_constructor(tyran_runtime* runtime, tyran_value* function, tyran_value* arguments, tyran_value* _this, tyran_value* return_value, int is_constructor);

#endif
