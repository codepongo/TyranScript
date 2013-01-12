#ifndef tyran_iterator_object_h
#define tyran_iterator_object_h

struct tyran_runtime;
struct tyran_red_black_tree_iterator;
struct tyran_value;

struct tyran_value* tyran_iterator_object_new(struct tyran_runtime* runtime, struct tyran_red_black_tree_iterator* iterator);

#endif
