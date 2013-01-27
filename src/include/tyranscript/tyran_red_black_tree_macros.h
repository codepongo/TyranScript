#ifndef _TYRAN_RED_BLACK_TREE_MACROS_H
#define _TYRAN_RED_BLACK_TREE_MACROS_H

/*
 * Simple macro to malloc data and check if the allocation was successfull.
 * A simple use can be char* string = alloc(char, 5); which allocates a string with 5 characters.
 */
#define tyran_red_black_tree_alloc(type, how_many) (type *) (void *)tyran_malloc(how_many * sizeof(type));

#define tyran_red_black_tree_free(v) tyran_free(v);


#endif

