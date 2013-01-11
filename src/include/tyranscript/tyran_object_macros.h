#ifndef _TYRAN_OBJECT_MACROS_H
#define _TYRAN_OBJECT_MACROS_H

#include <tyranscript/debug/tyran_print_value.h>

struct tyran_object;

void tyran_object_retain(struct tyran_object* o);
void tyran_object_release(struct tyran_object* o);

#define TYRAN_OBJECT_RETAIN(_object_) { tyran_object_retain(_object_);  }
#define TYRAN_OBJECT_RELEASE(object) { tyran_object_release(object); }
#define tyran_object_is_array(o) ((o)->type == TYRAN_OBJECT_TYPE_ARRAY)

#define tyran_object_set_function(o, func) (o)->type = TYRAN_OBJECT_TYPE_FUNCTION; (o)->data.function = func;
#define tyran_object_set_string(o, string) (o)->type = TYRAN_OBJECT_TYPE_STRING; (o)->data.str = string;
#define tyran_object_set_array(o, NEWARRAY) (o)->type = TYRAN_OBJECT_TYPE_ARRAY; (o)->data.array = NEWARRAY;
#define tyran_object_set_array_iterator(o, ITERATOR) (o)->type = TYRAN_OBJECT_TYPE_ARRAY_ITERATOR; (o)->data.array_iterator = ITERATOR;

#define tyran_object_set_range(o, ITERATOR) (o)->type = TYRAN_OBJECT_TYPE_RANGE; (o)->data.range = ITERATOR;
#define tyran_object_set_range_iterator(o, ITERATOR) (o)->type = TYRAN_OBJECT_TYPE_RANGE_ITERATOR; (o)->data.range_iterator = ITERATOR;


#endif
