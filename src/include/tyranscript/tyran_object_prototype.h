#ifndef _TYRAN_OBJECT_PROTOTYPE_H
#define _TYRAN_OBJECT_PROTOTYPE_H

extern struct tyran_value* tyran_object_prototype;
struct tyran_runtime;

void tyran_object_prototype_init(const struct tyran_runtime* runtime, struct tyran_value* tyran_object_prototype);
int tyran_object_prototype_constructor(struct tyran_runtime* runtime, struct tyran_value* function, struct tyran_value* arguments, struct tyran_value* _this, struct tyran_value* return_value, int is_constructor);

#endif
