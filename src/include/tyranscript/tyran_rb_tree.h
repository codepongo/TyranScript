#ifndef _TYRAN_RB_TREE_H
#define _TYRAN_RB_TREE_H

#include "tyran_rb_tree_macros.h"

typedef enum tyran_rb_tree_color {
	tyran_rb_tree_color_red = 1,
	tyran_rb_tree_color_black
} tyran_rb_tree_color;

typedef struct stree_node {
  void* node;

  tyran_rb_tree_color color;
  
  struct stree_node* parent;
  struct stree_node* left;
  struct stree_node* right;
} tree_node;

typedef struct sroot {
  struct stree_node* root;
  void* (*key)(struct stree_node* node);
  int (*compare)(void* keyA, void* keyB);
} tree_root;

typedef struct siterator{
  struct stree_node* current;
} tree_iterator;

extern tree_root* new_simple_rbtree();
extern tree_root* new_rbtree(void* (*key_function_pointer)(struct stree_node* node), int (*compare_function_pointer)(void* keyA, void* keyB));
extern void* rb_tree_insert(tree_root* root, void* node);
extern void* rb_tree_delete(tree_root* root, void* key);
extern void* search_rbtree(tree_root root, void* key);
extern void destroy_rbtree(tree_root* root);

extern tree_iterator* new_tree_iterator(tree_root* root);
extern int tree_iterator_has_next(tree_iterator* it);
extern void* tree_iterator_next(tree_iterator* it);
extern void destroy_iterator(tree_iterator* it);

#endif
