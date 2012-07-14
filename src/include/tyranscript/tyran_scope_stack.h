#ifndef _TYRAN_SCOPE_STACK_H
#define _TYRAN_SCOPE_STACK_H

struct tyran_scope_stack;
struct tyran_value;
struct tyran_object_key;

typedef struct tyran_scope_stack {
	struct tyran_value** scopes;
	int scope_count;
} tyran_scope_stack;

tyran_scope_stack* tyran_scope_stack_new(int count);
void tyran_scope_stack_free(tyran_scope_stack* stack);

struct tyran_value* tyran_scope_stack_lookup(const struct tyran_scope_stack* scopes, const struct tyran_object_key* key);
tyran_scope_stack* tyran_scope_stack_clone_and_add(const struct tyran_scope_stack* scopes, const struct tyran_value* scope_to_add);

#endif
