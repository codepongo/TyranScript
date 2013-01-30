#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <tyranscript/tyran_red_black_tree.h>
#include <tyranscript/tyran_red_black_tree_macros.h>
#include <tyranscript/tyran_config.h>

tyran_red_black_tree_node* tyran_red_black_tree_node_new(void* node)
{
	tyran_red_black_tree_node* z = tyran_red_black_tree_alloc(tyran_red_black_tree_node, 1);

	z->node = node;
	z->parent = 0;
	z->left = 0;
	z->right = 0;
	z->color = tyran_red_black_tree_color_red;
	return z;
}

tyran_red_black_tree* tyran_red_black_tree_new(void* (*key_function_pointer)(struct tyran_red_black_tree_node* node), int (*compare_function_pointer)(void* keyA, void* keyB))
{
	tyran_red_black_tree* r = tyran_red_black_tree_alloc(tyran_red_black_tree, 1);
	r->root = 0;
	r->key = key_function_pointer;
	r->compare = compare_function_pointer;

	return r;
}

/*WARNNING left_rbrotate assumes that rbrotate_on->right is NOT 0 and that root->parent IS 0*/
void tyran_red_black_tree_left_rotate(tyran_red_black_tree* root, tyran_red_black_tree_node* rbrotate_on)
{
	tyran_red_black_tree_node* y = rbrotate_on->right;
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
void tyran_red_black_tree_right_rotate(tyran_red_black_tree* root, tyran_red_black_tree_node* rbrotate_on)
{
	tyran_red_black_tree_node* y = rbrotate_on->left;
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

void tyran_red_black_tree_insert_fixup(tyran_red_black_tree* root, tyran_red_black_tree_node* z)
{
	tyran_red_black_tree_node* y;

	while (z->parent && z->parent->color == tyran_red_black_tree_color_red) {
		if (z->parent == z->parent->parent->left) {
			y = z->parent->parent->right;

			if (y->color == tyran_red_black_tree_color_red) {
				z->parent->color = tyran_red_black_tree_color_black;
				y->color = tyran_red_black_tree_color_black;
				z->parent->parent->color = tyran_red_black_tree_color_red;
				z = z->parent->parent;
			} else {
				if (z == z->parent->right) {
					z = z->parent;
					tyran_red_black_tree_left_rotate(root, z);
				}
				z->parent->color = tyran_red_black_tree_color_black;
				z->parent->parent->color = tyran_red_black_tree_color_red;
				tyran_red_black_tree_right_rotate(root, z->parent->parent);
			}
		} else {
			y = z->parent->parent->left;

			if (y && y->color == tyran_red_black_tree_color_red) {
				z->parent->color = tyran_red_black_tree_color_black;
				y->color = tyran_red_black_tree_color_black;
				z->parent->parent->color = tyran_red_black_tree_color_red;
				z = z->parent->parent;
			} else {
				if (z == z->parent->left) {
					z = z->parent;
					tyran_red_black_tree_right_rotate(root, z);
				}
				z->parent->color = tyran_red_black_tree_color_black;
				z->parent->parent->color = tyran_red_black_tree_color_red;
				tyran_red_black_tree_left_rotate(root, z->parent->parent);
			}
		}
	}

	root->root->color = tyran_red_black_tree_color_black;
}

void* tyran_red_black_tree_insert(tyran_red_black_tree* root, void* node)
{
	tyran_red_black_tree_node* y = 0, *x = root->root;

	tyran_red_black_tree_node* z = tyran_red_black_tree_node_new(node);

	while (x) {
		y = x;

		if (root->compare(root->key(z), root->key(x)) == 0) {
			void* holder = x->node;
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

	tyran_red_black_tree_insert_fixup(root, z);
	return 0;
}

tyran_red_black_tree_node* tyran_red_black_tree_search_node(tyran_red_black_tree root, void* key)
{
	tyran_red_black_tree_node* z = root.root;

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

void* tyran_red_black_tree_search(tyran_red_black_tree root, void* key)
{
	tyran_red_black_tree_node* z = tyran_red_black_tree_search_node(root, key);
	if (z) {
		return z->node;
	}

	return 0;
}

void tyran_red_black_tree_destroy_fixup(tyran_red_black_tree_node* root)
{
	tyran_red_black_tree_node* l, *r;

	if (!root) {
		return;
	}

	l = root->left;
	r = root->right;

	tyran_free(root);

	tyran_red_black_tree_destroy_fixup(l);
	tyran_red_black_tree_destroy_fixup(r);
}

void tyran_red_black_tree_destroy(tyran_red_black_tree* root)
{
	tyran_red_black_tree_destroy_fixup(root->root);
	tyran_free(root);
}

void tyran_red_black_tree_transplant(tyran_red_black_tree* root, tyran_red_black_tree_node* u, tyran_red_black_tree_node* v)
{
	if (!u->parent) {
		root->root = v;
	} else if (u == u->parent->left) {
		u->parent->left = v;
	} else {
		u->parent->right = v;
	}

	if (v) {
		v->parent = u->parent;
	}
}

tyran_red_black_tree_node* tyran_red_black_tree_minimum(tyran_red_black_tree_node* z)
{
	for(; z->left; z = z->left)
		;
	return z;
}

void tyran_red_black_tree_delete_fixup(tyran_red_black_tree* root, tyran_red_black_tree_node* x)
{
	tyran_red_black_tree_node* w;

	while (x != root->root && x->color == tyran_red_black_tree_color_black) {
		if (x == x->parent->left) {
			w = x->parent->right;
			if (w->color == tyran_red_black_tree_color_red) {
				w->color = tyran_red_black_tree_color_black;
				x->parent->color = tyran_red_black_tree_color_red;
				tyran_red_black_tree_left_rotate(root, x->parent);
				w = x->parent->right;
			}
			if (w->left->color == tyran_red_black_tree_color_black && w->right->color == tyran_red_black_tree_color_black) {
				w->color = tyran_red_black_tree_color_red;
				x = x->parent;
			} else {
				if (w->right->color == tyran_red_black_tree_color_black) {
					w->left->color = tyran_red_black_tree_color_black;
					w->color = tyran_red_black_tree_color_red;
					tyran_red_black_tree_right_rotate(root, w);
					w = w->parent->right;
				}
				w->color = x->parent->color;
				x->parent->color = tyran_red_black_tree_color_black;
				w->right->color = tyran_red_black_tree_color_black;
				tyran_red_black_tree_left_rotate(root, x->parent);
				x = root->root;
			}
		} else {
			w = x->parent->left;
			if (w->color == tyran_red_black_tree_color_red) {
				w->color = tyran_red_black_tree_color_black;
				x->parent->color = tyran_red_black_tree_color_red;
				tyran_red_black_tree_right_rotate(root, x->parent);
				w = x->parent->left;
			}
			if (w->right->color == tyran_red_black_tree_color_black && w->left->color == tyran_red_black_tree_color_black) {
				w->color = tyran_red_black_tree_color_red;
				x = x->parent;
			} else {
				if (w->left->color == tyran_red_black_tree_color_black) {
					w->right->color = tyran_red_black_tree_color_black;
					w->color = tyran_red_black_tree_color_red;
					tyran_red_black_tree_left_rotate(root, w);
					w = w->parent->left;
				}
				w->color = x->parent->color;
				x->parent->color = tyran_red_black_tree_color_black;
				w->left->color = tyran_red_black_tree_color_black;
				tyran_red_black_tree_right_rotate(root, x->parent);
				x = root->root;
			}
		}
	}
	if (x) {
		x->color = tyran_red_black_tree_color_black;
	}
}

void* tyran_red_black_tree_delete(tyran_red_black_tree* root, void* key)
{
	tyran_red_black_tree_node* y, *z, *x, *hold_node_to_delete;
	tyran_red_black_tree_color y_original_color;
	void* node_to_return;

	hold_node_to_delete = y = z = tyran_red_black_tree_search_node(*root, key);
	if (!hold_node_to_delete) {
		return 0;
	}

	node_to_return = y->node;

	y_original_color = y->color;
	if (!z->left) {
		x = z->right;
		tyran_red_black_tree_transplant(root, z, z->right);
	} else if (!z->right) {
		x = z->left;
		tyran_red_black_tree_transplant(root, z, z->left);
	} else {
		y = tyran_red_black_tree_minimum(z->right);
		y_original_color = y->color;
		x = y->right;
		if (y->parent == z) {
			if (x) {
				x->parent = y;
			}
		} else {
			tyran_red_black_tree_transplant(root, y, y->right);
			y->right = z->right;
			y->right->parent = y;
		}

		tyran_red_black_tree_transplant(root, z, y);
		y->left = z->left;
		y->left->parent = y;
		y->color = z->color;
	}

	if (x && (y_original_color == tyran_red_black_tree_color_black)) {
		tyran_red_black_tree_delete_fixup(root, x);
	}

	tyran_free(hold_node_to_delete);

	return node_to_return;
}

tyran_red_black_tree_iterator* tyran_red_black_tree_iterator_new(tyran_red_black_tree* root)
{
	tyran_red_black_tree_iterator* it = tyran_red_black_tree_alloc(tyran_red_black_tree_iterator, 1);

	it->current = root->root;
	it->previous = 0;

	return it;
}

void* tyran_red_black_tree_iterator_next(tyran_red_black_tree_iterator* it)
{
	struct tyran_red_black_tree_node* previous = it->previous;
	struct tyran_red_black_tree_node* current = it->current;

	if (!current) {
		return 0;
	}

	it->previous = current;

	if (previous == current->parent) {
		if (current->left) {
			it->current = current->left;
			if (it->current) {
				return tyran_red_black_tree_iterator_next(it);
			}
		} else {
			if (current->right) {
				it->current = current->right;
			} else {
				it->current = current->parent;
			}
		}
	} else if (previous == current->left) {
		if (current->right) {
			it->current = current->right;
		} else {
			it->current = current->parent;
		}
	} else {
		it->current = current->parent;
		return tyran_red_black_tree_iterator_next(it);
	}

	return current->node;
}

void tyran_red_black_tree_iterator_destroy(tyran_red_black_tree_iterator* it)
{
	tyran_free(it);
}
