#ifndef _TYRAN_OBJECT_MACROS_H
#define _TYRAN_OBJECT_MACROS_H

#define TYRAN_OBJECT_RETAIN(object) { (object)->retain_count++; }
#define TYRAN_OBJECT_RELEASE(object) { if (--((object)->retain_count) == 0) tyran_object_free((object)); }
#define tyran_object_is_array(o) ((o)->type == TYRAN_OBJECT_TYPE_OBJECT && tyran_object_length(o) >= 0)
#define tyran_object_set_function(o, func) (o)->type = TYRAN_OBJECT_TYPE_FUNCTION; (o)->data.function = func;

#endif
