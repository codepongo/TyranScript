#ifndef tyranscript_tyran_variable_scope_h
#define tyranscript_tyran_variable_scope_h

#include <tyranscript/tyran_opcodes.h>

typedef struct tyran_variable_info {
	const char* name;
	tyran_reg_index register_index;
} tyran_variable_info;

typedef struct tyran_variable_scope {
	tyran_variable_info* variables;
	int variable_count;
	int allocated_variable_count;
	int* registers;
	int register_count;
	int highest_register_used;
} tyran_variable_scope;

typedef struct tyran_variable_scopes {
	tyran_variable_scope* scopes;
	int scope_count;
	int allocated_scope_count;
} tyran_variable_scopes;


tyran_variable_scopes* tyran_variable_scopes_new(tyran_memory_pool* scopes_pool, tyran_memory* memory, tyran_memory_pool* scope_pool, tyran_memory_pool* variable_info_pool, tyran_memory_pool* register_pool, int max_count);

tyran_reg_index tyran_variable_scope_get_identifier(tyran_variable_scope* scope, const char* string);
tyran_reg_index tyran_variable_scope_define_identifier(tyran_memory* memory, tyran_variable_scope* scope, const char* string);
tyran_reg_index tyran_variable_scope_define_temporary_variable(tyran_variable_scope* scope);
void tyran_variable_scope_undefine_variable(tyran_variable_scope* scope, tyran_reg_index index);


void tyran_variable_scope_undefine_variables(tyran_variable_scope* scope, tyran_reg_index start_index, int count);
void tyran_variable_scopes_top_undefine_variables(tyran_variable_scopes* scopes, tyran_reg_index start_index, int count);


tyran_reg_index tyran_variable_scopes_get_identifier(tyran_variable_scopes* scope, const char* string);
tyran_reg_index tyran_variable_scopes_define_identifier(tyran_memory* memory, tyran_variable_scopes* scope, const char* string);
tyran_reg_index tyran_variable_scopes_define_temporary_variable(tyran_variable_scopes* scope);
void tyran_variable_scopes_undefine_variable(tyran_variable_scopes* scope, tyran_reg_index index);

tyran_reg_index tyran_variable_scopes_top_reserve_variables(tyran_variable_scopes* scopes, int return_count);
tyran_reg_index tyran_variable_scope_top_reserve_variables(tyran_variable_scope* scope, int return_count);

void tyran_variable_scopes_push_scope(tyran_variable_scopes* scopes, tyran_memory* memory, tyran_memory_pool* variable_info_pool, tyran_memory_pool* register_pool);
void tyran_variable_scopes_pop_scope(tyran_variable_scopes* scopes);
#endif
