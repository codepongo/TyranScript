#ifndef _TYRAN_OBJECT_PROTOTYPE_H
#define _TYRAN_OBJECT_PROTOTYPE_H

struct tyran_runtime;
struct tyran_value;

void tyran_object_prototype_init(const struct tyran_runtime* runtime, struct tyran_value* o);

#endif
