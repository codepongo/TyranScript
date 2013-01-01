#ifndef _TYRAN_FUNCTION_CALLBACK_H
#define _TYRAN_FUNCTION_CALLBACK_H

struct tyran_runtime;
struct tyran_value;

typedef int (*tyran_function_callback)(struct tyran_runtime* runtime, struct tyran_value* function, struct tyran_value* arguments, int argument_count, struct tyran_value* _this, struct tyran_value* return_value, int is_new_call);

#endif
