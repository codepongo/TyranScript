#ifndef _TYRAN_RUNTIME_CALLBACKS_H
#define _TYRAN_RUNTIME_CALLBACKS_H

struct tyran_runtime;
struct tyran_value;

typedef void (*tyran_runtime_assign_callback)(struct tyran_runtime* runtime, struct tyran_value* _this, struct tyran_value* subscript, struct tyran_value* source);

typedef struct tyran_runtime_callbacks {
	tyran_runtime_assign_callback assign_callback;
} tyran_runtime_callbacks;

#endif
