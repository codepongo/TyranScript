#include <tyranscript/parser/tyran_label.h>
#include <tyranscript/parser/tyran_label_reference.h>
#include <tyranscript/parser/common/tyran_variable_scope.h>
#include <tyranscript/tyran_string.h>

#include <tyranscript/parser/common/tyran_code.h>
#include <tyranscript/tyran_constants.h>

tyran_code_state* tyran_code_new()
{
	tyran_code_state* state = TYRAN_CALLOC(tyran_code_state);
	state->opcodes = tyran_opcodes_new(1024);
	state->constants = tyran_constants_new(1024);
	state->scope = tyran_variable_scopes_new(1024);
	state->labels = TYRAN_CALLOC_COUNT(100, tyran_label);
	state->label_references = TYRAN_CALLOC_COUNT(100, tyran_label_reference);
	return state;
}

tyran_label_id tyran_code_label_new(tyran_code_state* state)
{
	tyran_label_id label_index = state->label_count++;
	return label_index;
}

tyran_label_id tyran_code_prepare_label(tyran_code_state* state)
{
	return tyran_code_label_new(state);
}

void tyran_code_define_label(tyran_code_state* state, tyran_label_id label_index)
{
	struct tyran_label* label = &state->labels[label_index];
	label->position = state->opcodes->code_len + 1;
	TYRAN_LOG("defining label at pos:%d", label->position);
}


void tyran_code_add_label(tyran_code_state* state, tyran_string* name)
{
	tyran_label_id label_index = tyran_code_label_new(state);

	tyran_code_define_label(state, label_index);

	struct tyran_label* label = &state->labels[label_index];
	label->name = tyran_string_strdup(name);
}

void tyran_code_add_label_index_reference(tyran_code_state* state, tyran_label_id label_index)
{
	TYRAN_LOG("Adding label reference");
	struct tyran_label_reference* label_reference = &state->label_references[state->label_reference_count++];
	label_reference->label_index = label_index;
	label_reference->opcode = &state->opcodes->codes[state->opcodes->code_len];
}


int tyran_code_get_label(struct tyran_label* labels, int count, const tyran_string* name)
{
	int i;
	for (i=0; i<count; ++i)
	{
		if (tyran_string_strcmp(labels[i].name, name) == 0) {
			return i;
		}
	}

	return -1;
}

void tyran_code_change_opcode_branch(tyran_opcode* code, int position)
{
	u16t br = (position + 0x8000);
	*code = (*code & 0x3f) | (br << 6);
}

void tyran_code_fixup_label_references(tyran_code_state* state)
{
	int i;
	for (i=0; i<state->label_reference_count;++i)
	{
		tyran_label_reference* ref = &state->label_references[i];
		if (ref->label_index != -1) {
			tyran_label* label = &state->labels[ref->label_index];
			int delta = label->position - (ref->opcode - state->opcodes->codes) - 2;
			tyran_code_change_opcode_branch(ref->opcode, delta);
		} else {
			TYRAN_SOFT_ERROR("Couldn't find label");
		}
	}
	
	state->label_reference_count = 0;
}



