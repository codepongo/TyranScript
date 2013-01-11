#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <tyranscript/tyran_rb_tree.h>
#include <tyranscript/tyran_rb_tree_macros.h>
#include <tyranscript/tyran_config.h>

tree_node* new_rbtree_node(void* node)
{
	tree_node* z = tyran_rb_tree_alloc(tree_node, 1);

	z->node = node;
	z->parent = 0;
	z->left = 0;
	z->right = 0;
	z->color = tyran_rb_tree_color_red;
	return z;
}

tree_root* new_simple_rbtree()
{
	return new_rbtree(0, 0);
}

tree_root* new_rbtree(void* (*key_function_pointer)(struct stree_node* node), int (*compare_function_pointer)(void* keyA, void* keyB))
{
	tree_root* r = tyran_rb_tree_alloc(tree_root, 1);
	r->root = 0;
	r->key = key_function_pointer;
	r->compare = compare_function_pointer;

	return r;
}

/*WARNNING left_rbrotate assumes that rbrotate_on->right is NOT 0 and that root->parent IS 0*/
void left_rbrotate(tree_root* root, tree_node* rbrotate_on)
{
	tree_node* y = rbrotate_on->right;
	rbrotate_on->right = y->left;

	if (y->left) {
		y->left->parent = rbrotate_on;
	}

	y->parent = rbrotate_on->parent;

	if (!rbrotate_on->parent) {
		root->root = y;
	} else if (rbrotate_on == rbrotate_on->parent->left) {
		rbrotate_on->parent->left = y;
	} else {
		rbrotate_on->parent->right = y;
	}

	y->left = rbrotate_on;
	rbrotate_on->parent = y;
}

/*WARNNING right_rbrotate assumes that rbrotate_on->left is NOT 0 and that root->parent IS 0*/
void right_rbrotate(tree_root* root, tree_node* rbrotate_on)
{
	tree_node* y = rbrotate_on->left;
	rbrotate_on->left = y->right;

	if (y->right) {
		y->right->parent = rbrotate_on;
	}

	y->parent = rbrotate_on->parent;

	if (!rbrotate_on->parent) {
		root->root = y;
	} else if (rbrotate_on == rbrotate_on->parent->right) {
		rbrotate_on->parent->right = y;
	} else {
		rbrotate_on->parent->left = y;
	}

	y->right = rbrotate_on;
	rbrotate_on->parent = y;
}

void rb_tree_insert_fixup(tree_root* root, tree_node* z)
{
	tree_node* y;

	while (z->parent && z->parent->color == tyran_rb_tree_color_red) {
		if (z->parent == z->parent->parent->left) {
			y = z->parent->parent->right;

			if (y->color == tyran_rb_tree_color_red) {
				z->parent->color = tyran_rb_tree_color_black;
				y->color = tyran_rb_tree_color_black;
				z->parent->parent->color = tyran_rb_tree_color_red;
				z = z->parent->parent;
			} else {
				if (z == z->parent->right) {
					z = z->parent;
					left_rbrotate(root, z);
				}
				z->parent->color = tyran_rb_tree_color_black;
				z->parent->parent->color = tyran_rb_tree_color_red;
				right_rbrotate(root, z->parent->parent);
			}
		} else {
			y = z->parent->parent->left;

			if (y && y->color == tyran_rb_tree_color_red) {
				z->parent->color = tyran_rb_tree_color_black;
				y->color = tyran_rb_tree_color_black;
				z->parent->parent->color = tyran_rb_tree_color_red;
				z = z->parent->parent;
			} else {
				if (z == z->parent->left) {
					z = z->parent;
					right_rbrotate(root, z);
				}
				z->parent->color = tyran_rb_tree_color_black;
				z->parent->parent->color = tyran_rb_tree_color_red;
				left_rbrotate(root, z->parent->parent);
			}
		}
	}

	root->root->color = tyran_rb_tree_color_black;
}

void* rb_tree_insert(tree_root* root, void* node)
{
	TYRAN_LOG("$$$ Insert:%p", node);
	tree_node* y = 0, *x = root->root;

	tree_node* z = new_rbtree_node(node);

	while (x) {
		y = x;

		if (root->compare(root->key(z), root->key(x)) == 0) {
			void* holder = x->node;
			free(z);
			x->node = node;
			return holder;
		}

		if (root->compare(root->key(z), root->key(x)) < 0) {
			x = x->left;
		} else {
			x = x->right;
		}
	}

	z->parent = y;

	if (!y) {
		root->root = z;
	} else {
		if (root->compare(root->key(z),root->key(y)) < 0) {
			y->left = z;
		} else {
			y->right = z;
		}
	}

	rb_tree_insert_fixup(root, z);
	return 0;
}

tree_node* __search_rbtree_node(tree_root root, void* key)
{
	tree_node* z = root.root;

	while (z) {
		if (root.compare(root.key(z), key) == 0) {
			return z;
		}

		if (root.compare(root.key(z), key) < 0) {
			z = z->right;
		} else {
			z = z->left;
		}
	}

	return 0;
}

void* search_rbtree(tree_root root, void* key)
{
	tree_node* z = __search_rbtree_node(root, key);
	if (z) {
		return z->node;
	}

	return 0;
}

void __destroy_rbtree(tree_node* root)
{
	tree_node* l, *r;

	if (!root) {
		return;
	}

	l = root->left;
	r = root->right;

	tyran_free(root);

	__destroy_rbtree(l);
	__destroy_rbtree(r);
}

void destroy_rbtree(tree_root* root)
{
	__destroy_rbtree(root->root);
	tyran_free(root);
}

void __rb_transplant(tree_root* root, tree_node* u, tree_node* v)
{
	if (!u->parent) {
		root->root = v;
	} else if (u == u->parent->left) {
		u->parent->left = v;
	} else {
		u->parent->right = v;
	}

	v->parent = u->parent;
}

tree_node* __rb_tree_minimum(tree_node* z)
{
	for(; z->left; z = z->left)
		;
	return z;
}

void __rb_tree_delete_fixup(tree_root* root, tree_node* x)
{
	tree_node* w;

	while (x != root->root && x->color == tyran_rb_tree_color_black) {
		if (x == x->parent->left) {
			w = x->parent->right;
			if (w->color == tyran_rb_tree_color_red) {
				w->color = tyran_rb_tree_color_black;
				x->parent->color = tyran_rb_tree_color_red;
				left_rbrotate(root, x->parent);
				w = x->parent->right;
			}
			if (w->left->color == tyran_rb_tree_color_black && w->right->color == tyran_rb_tree_color_black) {
				w->color = tyran_rb_tree_color_red;
				x = x->parent;
			} else {
				if (w->right->color == tyran_rb_tree_color_black) {
					w->left->color = tyran_rb_tree_color_black;
					w->color = tyran_rb_tree_color_red;
					right_rbrotate(root, w);
					w = w->parent->right;
				}
				w->color = x->parent->color;
				x->parent->color = tyran_rb_tree_color_black;
				w->right->color = tyran_rb_tree_color_black;
				left_rbrotate(root, x->parent);
				x = root->root;
			}
		} else {
			w = x->parent->left;
			if (w->color == tyran_rb_tree_color_red) {
				w->color = tyran_rb_tree_color_black;
				x->parent->color = tyran_rb_tree_color_red;
				right_rbrotate(root, x->parent);
				w = x->parent->left;
			}
			if (w->right->color == tyran_rb_tree_color_black && w->left->color == tyran_rb_tree_color_black) {
				w->color = tyran_rb_tree_color_red;
				x = x->parent;
			} else {
				if (w->left->color == tyran_rb_tree_color_black) {
					w->right->color = tyran_rb_tree_color_black;
					w->color = tyran_rb_tree_color_red;
					left_rbrotate(root, w);
					w = w->parent->left;
				}
				w->color = x->parent->color;
				x->parent->color = tyran_rb_tree_color_black;
				w->left->color = tyran_rb_tree_color_black;
				right_rbrotate(root, x->parent);
				x = root->root;
			}
		}
	}
	x->color = tyran_rb_tree_color_black;
}

void* rb_tree_delete(tree_root* root, void* key)
{
	tree_node* y, *z, *x, *hold_node_to_delete;
	tyran_rb_tree_color y_original_color;
	void* node_to_return;

	hold_node_to_delete = y = z = __search_rbtree_node(*root, key);

	node_to_return = y->node;

	y_original_color = y->color;
	if (!z->left) {
		x = z->right;
		__rb_transplant(root, z, z->right);
	} else if (!z->right) {
		x = z->left;
		__rb_transplant(root, z, z->left);
	} else {
		y = __rb_tree_minimum(z->right);
		y_original_color = y->color;
		x = y->right;
		if (y->parent == z) {
			x->parent = y;
		} else {
			__rb_transplant(root, y, y->right);
			y->right = z->right;
			y->right->parent = y;
		}

		__rb_transplant(root, z, y);
		y->left = z->left;
		y->left->parent = y;
		y->color = z->color;
	}

	if (y_original_color == tyran_rb_tree_color_black) {
		__rb_tree_delete_fixup(root, x);
	}

	tyran_free(hold_node_to_delete);

	return node_to_return;
}

tree_iterator* new_tree_iterator(tree_root* root)
{
	tree_iterator* it = tyran_rb_tree_alloc(tree_iterator, 1);

	it->current = root->root;
	it->previous = 0;
	TYRAN_ASSERT(it->current->parent == 0, "BAD TREE");

	return it;
}


void* tree_iterator_next(tree_iterator* it)
{
	struct stree_node* previous = it->previous;
	struct stree_node* current = it->current;

	if (!current) {
		return 0;
	}

	it->previous = current;

	if (previous == current->parent) {
		if (current->left) {
			TYRAN_LOG("$$$ GOING LEFT");
			it->current = current->left;
			if (it->current) {
				return tree_iterator_next(it);
			}
		} else {
			if (current->right) {
				TYRAN_LOG("$$$ GOING RIGHT1");
				it->current = current->right;
			} else {
				TYRAN_LOG("$$$ GOING UP1");
				it->current = current->parent;
			}
		}
	} else if (previous == current->left) {
		if (current->right) {
			TYRAN_LOG("$$$ GOING RIGHT2");
			it->current = current->right;
		} else {
			TYRAN_LOG("$$$ GOING UP3");
			it->current = current->parent;
		}
	} else {
		TYRAN_LOG("$$$ GOING UP2");
		it->current = current->parent;
		return tree_iterator_next(it);
	}

	TYRAN_LOG("$$$ pointer:%p", current->node);
	return current->node;
}

void destroy_iterator(tree_iterator* it)
{
	tyran_free(it);
}
