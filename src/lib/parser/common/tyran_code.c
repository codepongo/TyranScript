#include <tyranscript/parser/tyran_label.h>
#include <tyranscript/parser/tyran_label_reference.h>
#include <tyranscript/parser/common/tyran_variable_scope.h>
#include <tyranscript/tyran_string.h>

#include <tyranscript/parser/common/tyran_code.h>
#include <tyranscript/tyran_constants.h>
#include <tyranscript/tyran_config.h>

tyran_code_state* tyran_code_new(tyran_memory_pool* string_pool, tyran_memory_pool* function_pool, tyran_memory_pool* code_state_pool, tyran_memory_pool* opcodes_pool, tyran_memory_pool* constants_pool, tyran_memory_pool* constant_values_pool, tyran_memory_pool* label_pool, tyran_memory_pool* label_reference_pool, tyran_memory_pool* variable_info_pool, tyran_memory_pool* register_pool, tyran_variable_scopes* variable_scopes, tyran_memory* memory)
{
	tyran_code_state* state = TYRAN_CALLOC_TYPE(code_state_pool, tyran_code_state);

	state->opcodes_pool = opcodes_pool;
	state->function_pool = function_pool;

	state->string_pool = string_pool;
	state->memory = memory;
	state->variable_info_pool = variable_info_pool;
	state->register_pool = register_pool;

	state->opcodes = tyran_opcodes_new(opcodes_pool, memory, 1024);
	state->constants = tyran_constants_new(constants_pool, constant_values_pool, 1024);
	
	state->scope = variable_scopes;
	state->labels = TYRAN_CALLOC_TYPE_COUNT(label_pool, 100, tyran_label);
	state->label_references = TYRAN_CALLOC_TYPE_COUNT(label_reference_pool, 100, tyran_label_reference);
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


void tyran_code_add_label(tyran_memory* memory, tyran_code_state* state, const char* name)
{
	tyran_label_id label_index = tyran_code_label_new(state);

	tyran_code_define_label(state, label_index);

	struct tyran_label* label = &state->labels[label_index];
	label->name = tyran_strdup(memory, name);
}

void tyran_code_add_label_index_reference(tyran_code_state* state, tyran_label_id label_index)
{
	TYRAN_LOG("Adding label reference");
	struct tyran_label_reference* label_reference = &state->label_references[state->label_reference_count++];
	label_reference->label_index = label_index;
	label_reference->opcode = &state->opcodes->codes[state->opcodes->code_len];
}


int tyran_code_get_label(struct tyran_label* labels, int count, const char* name)
{
	int i;
	for (i=0; i<count; ++i)
	{
		if (tyran_strcmp(labels[i].name, name) == 0) {
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



