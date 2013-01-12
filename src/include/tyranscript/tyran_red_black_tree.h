#ifndef _TYRAN_RED_BLACK_TREE_H
#define _TYRAN_RED_BLACK_TREE_H

typedef enum tyran_red_black_tree_color {
	tyran_red_black_tree_color_red = 1,
	tyran_red_black_tree_color_black
} tyran_red_black_tree_color;

typedef struct tyran_red_black_tree_node {
	void* node;

	tyran_red_black_tree_color color;

	struct tyran_red_black_tree_node* parent;
	struct tyran_red_black_tree_node* left;
	struct tyran_red_black_tree_node* right;
} tyran_red_black_tree_node;

typedef struct tyran_red_black_tree {
	struct tyran_red_black_tree_node* root;
	void* (*key)(struct tyran_red_black_tree_node* node);
	int (*compare)(void* a, void* b);
} tyran_red_black_tree;

typedef struct tyran_red_black_tree_iterator {
	struct tyran_red_black_tree_node* previous;
	struct tyran_red_black_tree_node* current;
} tyran_red_black_tree_iterator;

tyran_red_black_tree* tyran_red_black_tree_new(void* (*key_function_pointer)(struct tyran_red_black_tree_node* node), int (*compare_function_pointer)(void* keyA, void* keyB));
void* tyran_red_black_tree_insert(tyran_red_black_tree* root, void* node);
void* tyran_red_black_tree_delete(tyran_red_black_tree* root, void* key);
void* tyran_red_black_tree_search(tyran_red_black_tree root, void* key);
void tyran_red_black_tree_destroy(tyran_red_black_tree* root);

tyran_red_black_tree_iterator* tyran_red_black_tree_iterator_new(tyran_red_black_tree* root);
void* tyran_red_black_tree_iterator_next(tyran_red_black_tree_iterator* it);
void tyran_red_black_tree_iterator_destroy(tyran_red_black_tree_iterator* it);

#endif
