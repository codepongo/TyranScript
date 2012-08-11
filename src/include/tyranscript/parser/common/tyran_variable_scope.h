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
} tyran_variable_scope;

typedef struct tyran_variable_scopes {
	tyran_variable_scope* scopes;
	int* registers;
	int register_count;
	int scope_count;
	int allocated_scope_count;
} tyran_variable_scopes;


tyran_variable_scopes* tyran_variable_scopes_new(int max_count);

tyran_reg_index tyran_variable_scopes_get_identifier(tyran_variable_scopes* scope, const char* string);
tyran_reg_index tyran_variable_scopes_define_identifier(tyran_variable_scopes* scope, const char* string);
tyran_reg_index tyran_variable_scopes_define_temporary_variable(tyran_variable_scopes* scopes);
void tyran_variable_scopes_undefine_variable(tyran_variable_scopes* scopes, tyran_reg_index index);

#endif
