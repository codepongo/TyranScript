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
} tyran_code_state;

tyran_code_state* tyran_code_new();

void tyran_code_add_label(tyran_code_state* state, tyran_string* name);
void tyran_code_add_label_reference(tyran_code_state* state, tyran_string* name);
struct tyran_label* tyran_code_get_label(struct tyran_label* labels, int count, const tyran_string* name);
void tyran_code_change_opcode_branch(tyran_opcode* code, int position);
void tyran_code_fixup_label_references(tyran_code_state* state);

#endif