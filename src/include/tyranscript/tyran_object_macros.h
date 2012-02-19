#ifndef _TYRAN_OBJECT_MACROS_H
#define _TYRAN_OBJECT_MACROS_H

#include <tyranscript/debug/tyran_print_value.h>

struct tyran_object;

void tyran_object_retain(struct tyran_object* o);
void tyran_object_release(struct tyran_object* o);

#define TYRAN_OBJECT_RETAIN(_object_) { tyran_object_retain(_object_);  }
#define TYRAN_OBJECT_RELEASE(object) { tyran_object_release(object); }
#define tyran_object_is_array(o) ((o)->type == TYRAN_OBJECT_TYPE_OBJECT && tyran_object_length(o) >= 0)
#define tyran_object_set_function(o, func) (o)->type = TYRAN_OBJECT_TYPE_FUNCTION; (o)->data.function = func;

#endif
