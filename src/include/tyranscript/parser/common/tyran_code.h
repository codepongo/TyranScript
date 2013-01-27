#ifndef tyranscript_tyran_code_h
#define tyranscript_tyran_code_h

#include <tyranscript/tyran_opcodes.h>

typedef struct tyran_code_state {
	struct tyran_opcodes* opcodes;
	struct tyran_constants* constants;
	struct tyran_variable_scopes* scope;
	struct tyran_runtime* runtime;

	struct tyran_label* labels;
	int label_count;

	struct tyran_label_reference* label_references;
	int label_reference_count;
	tyran_memory_pool* opcodes_pool;
	tyran_memory_pool* function_pool;
	tyran_memory_pool* string_pool;
	tyran_memory_pool* variable_info_pool;
	tyran_memory_pool* register_pool;
	tyran_memory_pool* constants_pool;
	tyran_memory_pool* code_state_pool;
	tyran_memory* memory;

	tyran_reg_index last_self_index;
	tyran_boolean last_call_was_new;
} tyran_code_state;

typedef int tyran_label_id;



tyran_code_state* tyran_code_new(struct tyran_runtime* runtime, tyran_memory_pool* string_pool, tyran_memory_pool* function_pool, tyran_memory_pool* code_state_pool, tyran_memory_pool* opcodes_pool, tyran_memory_pool* constants_pool, tyran_memory_pool* variable_info_pool, tyran_memory_pool* register_pool, struct tyran_variable_scopes* variable_scopes, tyran_memory* memory);
tyran_code_state* tyran_code_clone(tyran_code_state* state);

tyran_label_id tyran_code_prepare_label(tyran_code_state* state);
void tyran_code_define_label(tyran_code_state* state, tyran_label_id label_index);
void tyran_code_add_label_index_reference(tyran_code_state* state, tyran_label_id label_index);
tyran_label_id tyran_code_get_label(struct tyran_label* labels, int count, const char* name);
void tyran_code_fixup_label_references(tyran_code_state* state);
void tyran_code_add_label(tyran_memory* memory, tyran_code_state* state, const char* name);

#endif
