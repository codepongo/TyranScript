#ifndef _TYRAN_RB_TREE_H
#define _TYRAN_RB_TREE_H

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

typedef struct tree_root {
	struct stree_node* root;
	void* (*key)(struct stree_node* node);
	int (*compare)(void* keyA, void* keyB);
} tree_root;

typedef struct tree_iterator {
	struct stree_node* previous;
	struct stree_node* current;
} tree_iterator;

tree_root* new_simple_rbtree();
tree_root* new_rbtree(void* (*key_function_pointer)(struct stree_node* node), int (*compare_function_pointer)(void* keyA, void* keyB));
void* rb_tree_insert(tree_root* root, void* node);
void* rb_tree_delete(tree_root* root, void* key);
void* search_rbtree(tree_root root, void* key);
void destroy_rbtree(tree_root* root);

tree_iterator* new_tree_iterator(tree_root* root);
void* tree_iterator_next(tree_iterator* it);
void destroy_iterator(tree_iterator* it);

#endif
