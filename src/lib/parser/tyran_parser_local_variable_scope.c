#include <tyranscript/tyran_config.h>
#include <tyranscript/tyran_string.h>

#include "tyran_parser_local_variable_scope.h"
#include "../tyran_string_array.h"

#define  TYRAN_LOCAL_VARIABLE_SCOPE_MAX_DEPTH 1024

tyran_string_array* scopes[TYRAN_LOCAL_VARIABLE_SCOPE_MAX_DEPTH];
static int tyran_local_variable_scope_index;

void tyran_parser_local_variable_scope_push()
{
	TYRAN_ASSERT(tyran_local_variable_scope_index < TYRAN_LOCAL_VARIABLE_SCOPE_MAX_DEPTH, "Exceeded max depth");
	tyran_local_variable_scope_index++;
}

void tyran_parser_local_variable_scope_pop()
{
	TYRAN_ASSERT(tyran_local_variable_scope_index != 0, "Can not pop an empty stack");
	tyran_string_array* string_array_to_free = scopes[tyran_local_variable_scope_index];
	if (string_array_to_free != 0) {
		tyran_string_array_free(string_array_to_free);
	}
	scopes[tyran_local_variable_scope_index] = 0;
	tyran_local_variable_scope_index--;
}

void tyran_parser_local_variable_scope_add(const tyran_string* str)
{
	if (scopes[tyran_local_variable_scope_index] == 0) {
		scopes[tyran_local_variable_scope_index] = tyran_string_array_new();
	}
	
	int i;
	for (i = 0; i < scopes[tyran_local_variable_scope_index]->count; ++i) {
		if (tyran_string_strcmp(str, scopes[tyran_local_variable_scope_index]->strings[i]) == 0) {
			return;
		}
	}
	tyran_string_array_add(scopes[tyran_local_variable_scope_index], str);
}

tyran_string_array* tyran_parser_local_variable_scope_names()
{
	tyran_string_array* array_to_clone = scopes[tyran_local_variable_scope_index];
	if (array_to_clone == 0) {
		return tyran_string_array_new();
	}
	return tyran_string_array_clone(array_to_clone);
}
