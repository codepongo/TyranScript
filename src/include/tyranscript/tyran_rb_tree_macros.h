#ifndef RB__MACROS_H__
#define RB__MACROS_H__

#include <stdlib.h>



/*
 * Simple macro to malloc data and check if the allocation was successfull.
 * A simple use can be char* string = alloc(char, 5); which allocates a string with 5 characters.
 */
#define rb_alloc(type, how_many)				\
  (type *) (void *)tyran_malloc(how_many * sizeof(type));

#endif

