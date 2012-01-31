#ifndef __MACROS_H__
#define __MACROS_H__

#include <stdlib.h>



/*
 * Simple macro to malloc data and check if the allocation was successfull.
 * A simple use can be char* string = alloc(char, 5); which allocates a string with 5 characters.
 */
#define alloc(type, how_many)				\
  (type *) __alloc(malloc(how_many * sizeof(type)));	

static inline void* __alloc(void* x){
  if(x)
    return x;
  exit(1);
  return 0;
}

#endif
    
