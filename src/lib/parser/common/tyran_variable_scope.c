#include <tyranscript/parser/common/tyran_variable_scope.h>
#include <tyranscript/tyran_config.h>

void tyran_variable_scopes_push_scope(tyran_variable_scopes* scopes)
{
	TYRAN_ASSERT(scopes->scope_count < scopes->allocated_scope_count, "Out of memory adding a scope");
	tyran_variable_scope* scope = &scopes->scopes[scopes->scope_count++];
	scope->allocated_variable_count = 1024;
	scope->variables = TYRAN_CALLOC_COUNT(scope->allocated_variable_count, tyran_variable_info);
	scope->register_count = 255;
	scope->registers = TYRAN_CALLOC_COUNT(scope->register_count, int);
}

void tyran_variable_scopes_pop_scope(tyran_variable_scopes* scopes)
{
	TYRAN_ASSERT(scopes->scope_count > 0, "Popped too much");
	scopes->scope_count --;
}

tyran_variable_scopes* tyran_variable_scopes_new(int max_count)
{
	tyran_variable_scopes* scopes = TYRAN_CALLOC(tyran_variable_scopes);
	scopes->allocated_scope_count = max_count;
	scopes->scopes = TYRAN_CALLOC_COUNT(scopes->allocated_scope_count, tyran_variable_scope);
	
	tyran_variable_scopes_push_scope(scopes);
	return scopes;
}

tyran_reg_index tyran_variable_scope_get_identifier(tyran_variable_scope* scope, const char* variable_name)
{
	int i;
	
	for (i=0; i<scope->variable_count; ++i) {
		if (tyran_strcmp(scope->variables[i].name, variable_name) == 0) {
			return scope->variables[i].register_index;
		}
	}
	
	return TYRAN_OPCODE_REGISTER_ILLEGAL;
}

tyran_variable_scope* tyran_variable_scopes_top(tyran_variable_scopes* scopes)
{
	return &scopes->scopes[scopes->scope_count - 1];
}

tyran_reg_index tyran_variable_scopes_get_identifier(tyran_variable_scopes* scopes, const char* string)
{
	return tyran_variable_scope_get_identifier(tyran_variable_scopes_top(scopes), string);
}

tyran_reg_index tyran_variable_scopes_define_identifier(tyran_variable_scopes* scopes, const char* string)
{
	return tyran_variable_scope_define_identifier(tyran_variable_scopes_top(scopes), string);
}

tyran_reg_index tyran_variable_scopes_define_temporary_variable(tyran_variable_scopes* scopes)
{
	return tyran_variable_scope_define_temporary_variable(tyran_variable_scopes_top(scopes));
}

void tyran_variable_scopes_undefine_variable(tyran_variable_scopes* scopes, tyran_reg_index index)
{
	tyran_variable_scope_undefine_variable(tyran_variable_scopes_top(scopes), index);
}

void tyran_variable_scope_add_identifier(tyran_variable_scope* scope, const char* variable_name, tyran_reg_index register_index)
{
	TYRAN_ASSERT(scope->variable_count < scope->allocated_variable_count, "Out of memory adding an identifier");
	TYRAN_LOG("Defining variable '%s' to register %d", variable_name, register_index);
	tyran_variable_info* info = &scope->variables[scope->variable_count++];
	info->name = tyran_strdup(variable_name);
	info->register_index = register_index;
}

void tyran_variable_scope_reserve_variable(tyran_variable_scope* scope, tyran_reg_index i, int status)
{
	if (i > scope->highest_register_used) {
		scope->highest_register_used = i;
	}
	scope->registers[i] = status;
}


tyran_reg_index tyran_variable_scope_top_free(tyran_variable_scope* scope, int return_count)
{
	int highest = scope->highest_register_used + 1;
	int i;
	for (i = highest; i < highest + return_count; ++i) {
		tyran_variable_scope_reserve_variable(scope, i, 1);
	}
	
	return highest;
}


tyran_reg_index tyran_variable_scopes_top_free(tyran_variable_scopes* scopes, int return_count)
{
	return tyran_variable_scope_top_free(tyran_variable_scopes_top(scopes), return_count);
}

tyran_reg_index tyran_variable_scope_find_and_reserve_variable(tyran_variable_scope* scope, int status)
{
	int i;

	for (i = 0; i < 255; ++i) {
		if (!scope->registers[i]) {
			tyran_variable_scope_reserve_variable(scope, i, status);
			return i;
		}
	}
	return TYRAN_OPCODE_REGISTER_ILLEGAL;
}

tyran_reg_index tyran_variable_scope_define_temporary_variable(tyran_variable_scope* scope)
{
	return tyran_variable_scope_find_and_reserve_variable(scope, 1);
}

void tyran_variable_scope_undefine_variable(tyran_variable_scope* scope, tyran_reg_index index)
{
	if (scope->registers[index] == 2) {
		return;
	}
	if (scope->highest_register_used == index) {
		scope->highest_register_used--;
	}
	scope->registers[index] = 0;
}

tyran_reg_index tyran_variable_scope_define_identifier(tyran_variable_scope* top_scope, const char* variable_name)
{
	tyran_reg_index current_index = tyran_variable_scope_get_identifier(top_scope, variable_name);
	if (current_index == TYRAN_OPCODE_REGISTER_ILLEGAL) {
		current_index = tyran_variable_scope_find_and_reserve_variable(top_scope, 2);
		tyran_variable_scope_add_identifier(top_scope, variable_name, current_index);
	}
	
	return current_index;
}
