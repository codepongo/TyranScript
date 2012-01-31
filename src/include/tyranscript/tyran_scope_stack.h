#ifndef _TYRAN_SCOPE_STACK_H
#define _TYRAN_SCOPE_STACK_H

#include "tyran_object_key.h"

struct tyran_value;

typedef struct tyran_scope_stack {
	struct tyran_value** scopes;
	int scope_count;
} tyran_scope_stack;

tyran_scope_stack* tyran_scope_stack_new(int count);
void tyran_scope_stack_free(tyran_scope_stack* stack);

tyran_value* tyran_scope_stack_lookup(const tyran_scope_stack* scopes, const tyran_object_key* key);
tyran_scope_stack* tyran_scope_stack_clone_and_add(const tyran_scope_stack* scopes, const tyran_value* scope_to_add);

#endif
