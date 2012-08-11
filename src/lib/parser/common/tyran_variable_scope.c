#include <tyranscript/parser/common/tyran_variable_scope.h>
#include <tyranscript/tyran_config.h>

void tyran_variable_scopes_add_scope(tyran_variable_scopes* scopes)
{
	TYRAN_ASSERT(scopes->scope_count < scopes->allocated_scope_count, "Out of memory adding a scope");
	tyran_variable_scope* scope = &scopes->scopes[scopes->scope_count++];
	scope->allocated_variable_count = 1024;
	scope->variables = TYRAN_CALLOC_COUNT(scope->allocated_variable_count, tyran_variable_info);
}

tyran_variable_scopes* tyran_variable_scopes_new(int max_count)
{
	tyran_variable_scopes* scopes = TYRAN_CALLOC(tyran_variable_scopes);
	scopes->register_count = 255;
	scopes->registers = TYRAN_CALLOC_COUNT(scopes->register_count, int);
	scopes->allocated_scope_count = max_count;
	scopes->scopes = TYRAN_CALLOC_COUNT(scopes->allocated_scope_count, tyran_variable_scope);
	
	tyran_variable_scopes_add_scope(scopes);
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

tyran_reg_index tyran_variable_scopes_get_identifier(tyran_variable_scopes* scopes, const char* variable_name)
{
	int i;
	
	for (i=scopes->scope_count - 1; i >= 0; --i) {
		tyran_reg_index variable_register = tyran_variable_scope_get_identifier(&scopes->scopes[i], variable_name);
		if (variable_register != TYRAN_OPCODE_REGISTER_ILLEGAL) {
			return variable_register;
		}
	}
	
	return TYRAN_OPCODE_REGISTER_ILLEGAL;
}

void tyran_variable_scope_add_identifier(tyran_variable_scope* scope, const char* variable_name, tyran_reg_index register_index)
{
	TYRAN_ASSERT(scope->variable_count < scope->allocated_variable_count, "Out of memory adding an identifier");
	TYRAN_LOG("Defining variable '%s' to register %d", variable_name, register_index);
	tyran_variable_info* info = &scope->variables[scope->variable_count++];
	info->name = tyran_strdup(variable_name);
	info->register_index = register_index;
}

tyran_reg_index tyran_variable_scopes_define_temporary_variable(tyran_variable_scopes* scopes)
{
	int i;

	for (i=0; i<255; ++i) {
		if (!scopes->registers[i]) {
			scopes->registers[i] = 1;
			return i;
		}
	}
	
	return -1;
}

void tyran_variable_scopes_undefine_variable(tyran_variable_scopes* scopes, tyran_reg_index index)
{
	scopes->registers[index] = 0;
}

tyran_reg_index tyran_variable_scopes_define_identifier(tyran_variable_scopes* scopes, const char* variable_name)
{
	tyran_variable_scope* top_scope = &scopes->scopes[0];
	
	tyran_reg_index current_index = tyran_variable_scope_get_identifier(top_scope, variable_name);
	if (current_index == TYRAN_OPCODE_REGISTER_ILLEGAL) {
		current_index = tyran_variable_scopes_define_temporary_variable(scopes);
		tyran_variable_scope_add_identifier(top_scope, variable_name, current_index);
	}
	
	return current_index;
}
