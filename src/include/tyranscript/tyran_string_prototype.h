#ifndef _TYRAN_STRING_PROTOTYPE_H
#define _TYRAN_STRING_PROTOTYPE_H

struct tyran_value;
struct tyran_runtime;

extern struct tyran_value* tyran_string_prototype;

void tyran_string_prototype_init(const struct tyran_runtime* runtime, struct tyran_value* constructor_prototype);
int tyran_string_prototype_constructor(struct tyran_runtime* runtime, struct tyran_value* function, struct tyran_value* arguments, struct tyran_value* _this, struct tyran_value* return_value, int is_constructor);

#endif
