#ifndef _TYRAN_RB_TREE_MACROS_H
#define _TYRAN_RB_TREE_MACROS_H

/*
 * Simple macro to malloc data and check if the allocation was successfull.
 * A simple use can be char* string = alloc(char, 5); which allocates a string with 5 characters.
 */
#define tyran_rb_tree_alloc(type, how_many)				\
  (type *) (void *)tyran_malloc(how_many * sizeof(type));

#endif

