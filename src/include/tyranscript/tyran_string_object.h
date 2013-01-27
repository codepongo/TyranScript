#ifndef _tyran_string_object_h
#define _tyran_string_object_h

struct tyran_runtime;
struct tyran_value;
struct tyran_string;

void tyran_string_object_new(struct tyran_value* value, struct tyran_runtime* runtime, const struct tyran_string* string);

#endif
