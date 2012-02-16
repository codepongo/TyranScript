#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <tyranscript/tyran_rb_tree.h>
#include <tyranscript/tyran_rb_tree_macros.h>
#include <tyranscript/tyran_config.h>

tree_node RBNIL;

static tree_node* new_rbtree_node(void* node) {
	tree_node *z = tyran_rb_tree_alloc(tree_node, 1);

	RBNIL.node = NULL;
	RBNIL.color = tyran_rb_tree_color_black;
	RBNIL.parent = &RBNIL;
	RBNIL.left = &RBNIL;
	RBNIL.right = &RBNIL;

	z->node = node;
	z->parent = &RBNIL;
	z->left = &RBNIL;
	z->right = &RBNIL;
	z->color = tyran_rb_tree_color_red;
	return z;
}

tree_root* new_simple_rbtree() {
	return new_rbtree(0, 0);  
}

tree_root* new_rbtree(void* (*key_function_pointer)(struct stree_node* node), int (*compare_function_pointer)(void* keyA, void* keyB)) {
	tree_root* r = tyran_rb_tree_alloc(tree_root, 1);
	r->root = &RBNIL;
	r->key = key_function_pointer;
	r->compare = compare_function_pointer;
	
	return r;
}

/*WARNNING left_rbrotate assumes that rbrotate_on->right is NOT &RBNIL and that root->parent IS &RBNIL*/
static void left_rbrotate(tree_root* root, tree_node* rbrotate_on) {
	tree_node* y = rbrotate_on->right;
	rbrotate_on->right = y->left;

	if(y->left != &RBNIL)
		y->left->parent = rbrotate_on;
  
	y->parent = rbrotate_on->parent;
 
	if(rbrotate_on->parent == &RBNIL)
		root->root = y;
	else
		if(rbrotate_on == rbrotate_on->parent->left)
			rbrotate_on->parent->left = y;
		else
			rbrotate_on->parent->right = y;

	y->left = rbrotate_on;
	rbrotate_on->parent = y;
}

/*WARNNING right_rbrotate assumes that rbrotate_on->left is NOT &RBNIL and that root->parent IS &RBNIL*/
static void right_rbrotate(tree_root* root, tree_node* rbrotate_on) {
	tree_node* y = rbrotate_on->left;
	rbrotate_on->left = y->right;

	if(y->right != &RBNIL)
		y->right->parent = rbrotate_on;
  
	y->parent = rbrotate_on->parent;
 
	if(rbrotate_on->parent == &RBNIL)
		root->root = y;
	else
		if(rbrotate_on == rbrotate_on->parent->right)
			rbrotate_on->parent->right = y;
		else
			rbrotate_on->parent->left = y;
 
	y->right = rbrotate_on;
	rbrotate_on->parent = y;
}

static void rb_tree_insert_fixup(tree_root* root, tree_node* z) {
	tree_node* y;

	while(z->parent->color == tyran_rb_tree_color_red) {
		if(z->parent == z->parent->parent->left) {
			y = z->parent->parent->right;

			if(y->color == tyran_rb_tree_color_red) {
				z->parent->color = tyran_rb_tree_color_black;
				y->color = tyran_rb_tree_color_black;
				z->parent->parent->color = tyran_rb_tree_color_red;
				z = z->parent->parent;
			} else {
				if(z == z->parent->right) {
					z = z->parent;
					left_rbrotate(root, z);
				}
				z->parent->color = tyran_rb_tree_color_black;
				z->parent->parent->color = tyran_rb_tree_color_red;
				right_rbrotate(root, z->parent->parent);
			}
		} else {
			y = z->parent->parent->left;

			if(y->color == tyran_rb_tree_color_red){
				z->parent->color = tyran_rb_tree_color_black;
				y->color = tyran_rb_tree_color_black;
				z->parent->parent->color = tyran_rb_tree_color_red;
				z = z->parent->parent;
			} else {
				if(z == z->parent->left) {
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

void* rb_tree_insert(tree_root* root, void* node) {
	tree_node *y = &RBNIL, *x = root->root;

	tree_node *z = new_rbtree_node(node);

	while(x != &RBNIL) {
		y = x;

		if(root->compare(root->key(z), root->key(x)) == 0) {
			void* holder = x->node;
			free(z);
			x->node = node;
			return holder;
		}

		if(root->compare(root->key(z), root->key(x)) < 0)
			x = x->left;
		else
			x = x->right;
	}

	z->parent = y;

	if (y == &RBNIL)
		root->root = z;
	else {
		if(root->compare(root->key(z),root->key(y)) < 0)
			y->left = z;
		else
			y->right = z;
	}

	rb_tree_insert_fixup(root, z);
	return 0;
}

static tree_node* __search_rbtree_node(tree_root root, void* key) {
	tree_node *z = root.root;

	while (z != &RBNIL) {
		if (root.compare(root.key(z), key) == 0)
			return z;

		if (root.compare(root.key(z), key) < 0)
	  		z = z->right;
		else
			z = z->left;
	}
	
	return 0;
}

void* search_rbtree(tree_root root, void* key) {
	tree_node *z = __search_rbtree_node(root, key);
	if(z)
		return z->node;
	
	return 0;
}

static void __destroy_rbtree(tree_node* root) {
	tree_node *l, *r;

	if(root == &RBNIL)
		return;

	l = root->left;
	r = root->right;

	tyran_free(root);

	__destroy_rbtree(l);
	__destroy_rbtree(r);
}

void destroy_rbtree(tree_root* root) {
	__destroy_rbtree(root->root);
	tyran_free(root);
}

static void __rb_transplant(tree_root* root, tree_node* u, tree_node* v) {
	if(u->parent == &RBNIL)
		root->root = v;
	else
		if(u == u->parent->left)
			u->parent->left = v;
		else
			u->parent->right = v;
	
	v->parent = u->parent;
}

static tree_node* __rb_tree_minimum(tree_node* z) {
	for(; z->left != &RBNIL; z = z->left)
		;
	return z;
}

static void __rb_tree_delete_fixup(tree_root* root, tree_node* x) {
	tree_node* w;
	while (x != root->root && x->color == tyran_rb_tree_color_black) {
		if(x == x->parent->left) {
			w = x->parent->right;
			if(w->color == tyran_rb_tree_color_red) {
				w->color = tyran_rb_tree_color_black;
				x->parent->color = tyran_rb_tree_color_red;
				left_rbrotate(root, x->parent);
				w = x->parent->right;
			}
			if(w->left->color == tyran_rb_tree_color_black && w->right->color == tyran_rb_tree_color_black){
				w->color = tyran_rb_tree_color_red;
				x = x->parent;
			} else {
				if(w->right->color == tyran_rb_tree_color_black) {
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
			if(w->color == tyran_rb_tree_color_red) {
				w->color = tyran_rb_tree_color_black;
				x->parent->color = tyran_rb_tree_color_red;
				right_rbrotate(root, x->parent);
				w = x->parent->left;
			}
			if(w->right->color == tyran_rb_tree_color_black && w->left->color == tyran_rb_tree_color_black){
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

void* rb_tree_delete(tree_root* root, void* key) {
	tree_node *y, *z, *x, *hold_node_to_delete;
	tyran_rb_tree_color y_original_color;
	void* node_to_return;

	hold_node_to_delete = y = z = __search_rbtree_node(*root, key);

	node_to_return = y->node;

	y_original_color = y->color;
	if(z->left == &RBNIL){
		x = z->right;
		__rb_transplant(root, z, z->right);
	} else if(z->right == &RBNIL) {
		x = z->left;
		__rb_transplant(root, z, z->left);
	} else {
		y = __rb_tree_minimum(z->right);
		y_original_color = y->color;
		x = y->right;
		if(y->parent == z)
			x->parent = y;
		else {
			__rb_transplant(root, y, y->right);
			y->right = z->right;
			y->right->parent = y;
		}
		
		__rb_transplant(root, z, y);
		y->left = z->left;
		y->left->parent = y;
		y->color = z->color;
	}

	if(y_original_color == tyran_rb_tree_color_black) {
		__rb_tree_delete_fixup(root, x);
	}

	tyran_free(hold_node_to_delete);

	return node_to_return;
}

tree_iterator* new_tree_iterator(tree_root* root) {
	tree_node* aux = root->root;
	tree_iterator* it = tyran_rb_tree_alloc(tree_iterator, 1);

	while(aux->left != &RBNIL || aux->right != &RBNIL) {
		while(aux->left != &RBNIL)
			aux = aux->left;
	
		if(aux->right != &RBNIL)
			aux = aux->right;
	}
	
	it->current = aux;

	return it;
}

int tree_iterator_has_next(tree_iterator* it) {
	if(it->current != &RBNIL)
		return 1;
	return 0;
}

void* tree_iterator_next(tree_iterator* it) {
	tree_node* aux;
	tree_node* tn = it->current;

	if(tn->parent != &RBNIL && tn->parent->right != &RBNIL && tn->parent->right != tn) {
		aux = tn->parent->right;
		while(aux->left != &RBNIL || aux->right != &RBNIL) {
			while(aux->left != &RBNIL)
				aux = aux->left;
	
			if(aux->right != &RBNIL)
				aux = aux->right;
		}
		it->current = aux;
	} else {
		it->current = it->current->parent;
	}
	
	return tn->node;
}

void destroy_iterator(tree_iterator* it){
	tyran_free(it);
}
