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
	return state;
}

void tyran_code_add_label(tyran_code_state* state, tyran_string* name)
{
	struct tyran_label* label = &state->labels[state->label_count++];
	label->name = tyran_string_strdup(name);
	label->position = state->opcodes->code_len + 1;
	TYRAN_LOG("Adding label at pos:%d", label->position);
}

void tyran_code_add_label_reference(tyran_code_state* state, tyran_string* name)
{
	TYRAN_LOG("Adding label reference");
	struct tyran_label_reference* label_reference = &state->label_references[state->label_reference_count++];
	label_reference->name = tyran_string_strdup(name);
	label_reference->opcode = &state->opcodes->codes[state->opcodes->code_len];
}

tyran_label* tyran_code_get_label(tyran_label* labels, int count, const tyran_string* name)
{
	int i;
	for (i=0; i<count; ++i)
	{
		if (tyran_string_strcmp(labels[i].name, name) == 0) {
			return &labels[i];
		}
	}

	return 0;
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
		tyran_label* label = tyran_code_get_label(state->labels, state->label_count, ref->name);
		if (!label) {
			char buf[100];
			tyran_string_to_c_str(buf, 100, ref->name);
			TYRAN_SOFT_ERROR("Couldn't find label '%s'", buf);
		} else {
			int delta = label->position - (ref->opcode - state->opcodes->codes) - 2;
			tyran_code_change_opcode_branch(ref->opcode, delta);
		}
	}
}



