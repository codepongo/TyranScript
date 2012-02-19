#ifndef _TYRAN_OBJECT_ARRAY_H
#define _TYRAN_OBJECT_ARRAY_H

struct tyran_value;
struct tyran_object;
struct tyran_runtime;

struct tyran_object* tyran_object_new_array(const struct tyran_runtime* runtime, const struct tyran_value* items, int count);

#endif
