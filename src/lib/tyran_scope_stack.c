#include <tyranscript/tyran_scope_stack.h>
#include <tyranscript/tyran_value.h>
#include <tyranscript/tyran_value_object.h>
#include <tyranscript/tyran_config.h>

tyran_scope_stack* tyran_scope_stack_new(int cnt)
{
	struct tyran_scope_stack* r = TYRAN_CALLOC(struct tyran_scope_stack);
	r->scopes = TYRAN_CALLOC_COUNT(cnt, tyran_value*);
	r->scope_count = cnt;
	return r;
}

void tyran_scope_stack_free(tyran_scope_stack* stack)
{
	int i;
	for (i = 0; i < stack->scope_count; ++i) {
		tyran_value_free(stack->scopes[i]);
	}
	tyran_free(stack->scopes);
	tyran_free(stack);
}

tyran_scope_stack* tyran_scope_stack_clone_and_add(const tyran_scope_stack* stack, const tyran_value* scope_to_add)
{
	int scope_count = 0;
	if (stack) {
		scope_count = stack->scope_count;
	}

	tyran_scope_stack* r = tyran_scope_stack_new(scope_count + 1);

	int i;
	for (i = 0; i < scope_count; ++i) {
		r->scopes[i] = tyran_value_new();
		tyran_value_copy(*(r->scopes[i]), *(stack->scopes[i]));
	}

	r->scopes[i] = tyran_value_new();

	tyran_value_copy(*(r->scopes[i]), *scope_to_add);

	r->scope_count = i + 1;

	return r;
}

tyran_value* tyran_scope_stack_lookup(const tyran_scope_stack* stack, const tyran_object_key* key)
{
	int i;
	tyran_value* found_value;
	
	tyran_object_key_flag_type flag;
	for (i = stack->scope_count - 1; i >= 0; --i) {
		found_value = tyran_value_object_lookup(stack->scopes[i], key, &flag);
		if (found_value) {
			return found_value;
		}
	}
	return 0;
}
