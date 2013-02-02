#include <tyranscript/parser/common/tyran_variable_scope.h>
#include <tyranscript/tyran_config.h>

void tyran_variable_scopes_push_scope(tyran_variable_scopes* scopes, tyran_memory* memory, tyran_memory_pool* variable_info_pool, tyran_memory_pool* register_pool)
{
	TYRAN_LOG("PUSH SCOPE ***");
	TYRAN_ASSERT(scopes->scope_count < scopes->allocated_scope_count, "Out of memory adding a scope");
	tyran_variable_scope* scope = &scopes->scopes[scopes->scope_count++];
	scope->allocated_variable_count = 1024;
	scope->variables = TYRAN_MALLOC_NO_POOL_TYPE_COUNT(memory, tyran_variable_info, scope->allocated_variable_count);
	scope->variable_count = 0;
	scope->register_count = 255;
	scope->registers = TYRAN_MALLOC_NO_POOL_TYPE_COUNT(memory, int, scope->register_count);
}

void tyran_variable_scopes_pop_scope(tyran_variable_scopes* scopes)
{
	TYRAN_LOG("POP SCOPE ***");
	TYRAN_ASSERT(scopes->scope_count > 0, "Popped too much");
	scopes->scope_count --;
}

tyran_variable_scopes* tyran_variable_scopes_new(tyran_memory_pool* scopes_pool, tyran_memory* memory, tyran_memory_pool* scope_pool, tyran_memory_pool* variable_info_pool, tyran_memory_pool* register_pool, int max_count)
{
	TYRAN_LOG("NEW SCOPES....");
	tyran_variable_scopes* scopes = TYRAN_CALLOC_TYPE(scopes_pool, tyran_variable_scopes);
	scopes->allocated_scope_count = max_count;
	scopes->scopes = TYRAN_MALLOC_NO_POOL_TYPE_COUNT(memory, tyran_variable_scope, scopes->allocated_scope_count);

	tyran_variable_scopes_push_scope(scopes, memory, variable_info_pool, register_pool);
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

tyran_reg_index tyran_variable_scopes_define_identifier(tyran_memory* memory, tyran_variable_scopes* scopes, const char* string)
{
	return tyran_variable_scope_define_identifier(memory, tyran_variable_scopes_top(scopes), string);
}

tyran_reg_index tyran_variable_scopes_define_temporary_variable(tyran_variable_scopes* scopes)
{
	return tyran_variable_scope_define_temporary_variable(tyran_variable_scopes_top(scopes));
}


void tyran_variable_scope_add_identifier(tyran_memory* memory, tyran_variable_scope* scope, const char* variable_name, tyran_reg_index register_index)
{
	TYRAN_ASSERT(scope->variable_count < scope->allocated_variable_count, "Out of memory adding an identifier");
	TYRAN_LOG("Defining variable '%s' to register %d", variable_name, register_index);
	tyran_variable_info* info = &scope->variables[scope->variable_count++];
	info->name = tyran_strdup(memory, variable_name);
	info->register_index = register_index;
}

void tyran_variable_scope_reserve_variable(tyran_variable_scope* scope, tyran_reg_index i, int status)
{
	if (i > scope->highest_register_used) {
		scope->highest_register_used = i;
	}
	scope->registers[i] = status;
}


tyran_reg_index tyran_variable_scope_top_reserve_variables(tyran_variable_scope* scope, int return_count)
{
	int highest = scope->highest_register_used + 1;
	int i;
	for (i = highest; i < highest + return_count; ++i) {
		tyran_variable_scope_reserve_variable(scope, i, 1);
	}

	return highest;
}

void tyran_variable_scope_undefine_variable(tyran_variable_scope* scope, tyran_reg_index index)
{
	if (scope->highest_register_used == index) {
		scope->highest_register_used--;
	}
	TYRAN_LOG("Undefining register %d, highest is now %d", index, scope->highest_register_used);
	scope->registers[index] = 0;
}


tyran_reg_index tyran_variable_scopes_top_reserve_variables(tyran_variable_scopes* scopes, int return_count)
{
	return tyran_variable_scope_top_reserve_variables(tyran_variable_scopes_top(scopes), return_count);
}

void tyran_variable_scopes_undefine_variable(tyran_variable_scopes* scopes, tyran_reg_index index)
{
	tyran_variable_scope_undefine_variable(tyran_variable_scopes_top(scopes), index);
}

void tyran_variable_scope_undefine_variables(tyran_variable_scope* scope, tyran_reg_index start_index, int count)
{
	for (tyran_reg_index i=start_index+count-1; i>=start_index; --i) {
		tyran_variable_scope_undefine_variable(scope, i);
	}
}

void tyran_variable_scopes_top_undefine_variables(tyran_variable_scopes* scopes, tyran_reg_index start_index, int count)
{
	tyran_variable_scope_undefine_variables(tyran_variable_scopes_top(scopes), start_index, count);
}


tyran_reg_index tyran_variable_scope_find_and_reserve_variable(tyran_variable_scope* scope, int status)
{
	int i;

	for (i = 1; i < 255; ++i) {
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


tyran_reg_index tyran_variable_scope_define_identifier(tyran_memory* memory, tyran_variable_scope* top_scope, const char* variable_name)
{
	tyran_reg_index current_index = tyran_variable_scope_get_identifier(top_scope, variable_name);
	if (current_index == TYRAN_OPCODE_REGISTER_ILLEGAL) {
		current_index = tyran_variable_scope_find_and_reserve_variable(top_scope, 2);
		tyran_variable_scope_add_identifier(memory, top_scope, variable_name, current_index);
	}

	return current_index;
}
