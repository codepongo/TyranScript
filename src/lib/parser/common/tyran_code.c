#include <tyranscript/parser/tyran_label.h>
#include <tyranscript/parser/tyran_label_reference.h>
#include <tyranscript/parser/common/tyran_variable_scope.h>
#include <tyranscript/tyran_string.h>
#include <tyranscript/tyran_runtime.h>

#include <tyranscript/parser/common/tyran_code.h>
#include <tyranscript/tyran_constants.h>
#include <tyranscript/tyran_config.h>

#include <tyranscript/tyran_memory_pool.h>

tyran_code_state* tyran_code_new(struct tyran_runtime* runtime, tyran_memory_pool* string_pool, tyran_memory_pool* function_pool, tyran_memory_pool* code_state_pool, tyran_memory_pool* opcodes_pool, tyran_memory_pool* constants_pool, tyran_memory_pool* variable_info_pool, tyran_memory_pool* register_pool, tyran_variable_scopes* variable_scopes, tyran_memory* memory)
{
	tyran_code_state* state = TYRAN_CALLOC_TYPE(code_state_pool, tyran_code_state);

	state->opcodes_pool = opcodes_pool;
	state->function_pool = function_pool;

	state->string_pool = string_pool;
	state->memory = memory;
	state->variable_info_pool = variable_info_pool;
	state->register_pool = register_pool;
	state->code_state_pool = code_state_pool;
	state->constants_pool = constants_pool;

	state->runtime = runtime;

	state->opcodes = tyran_opcodes_new(opcodes_pool, memory, 1024);
	state->constants = tyran_constants_new(constants_pool, runtime->symbol_table, memory, 1024);

	state->scope = variable_scopes;
	state->labels = TYRAN_MALLOC_NO_POOL_TYPE_COUNT(memory, tyran_label, 100);
	state->label_references = TYRAN_MALLOC_NO_POOL_TYPE_COUNT(memory, tyran_label_reference, 100);
	return state;
}

tyran_code_state* tyran_code_clone(tyran_code_state* state)
{
	tyran_code_state* cloned_state = tyran_code_new(state->runtime, state->string_pool, state->function_pool, state->code_state_pool, state->opcodes_pool, state->constants_pool, state->variable_info_pool, state->register_pool, state->scope, state->memory);
	return cloned_state;
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
}


void tyran_code_add_label(tyran_memory* memory, tyran_code_state* state, const char* name)
{
	tyran_label_id label_index = tyran_code_label_new(state);

	tyran_code_define_label(state, label_index);

	struct tyran_label* label = &state->labels[label_index];
	label->position = -1;
	label->name = tyran_strdup(memory, name);
}

void tyran_code_add_label_index_reference(tyran_code_state* state, tyran_label_id label_index)
{
	struct tyran_label_reference* label_reference = &state->label_references[state->label_reference_count++];
	label_reference->label_index = label_index;
	label_reference->opcode = &state->opcodes->codes[state->opcodes->code_len];
	TYRAN_LOG("Adding label reference:%d code_position:%d", label_index, state->opcodes->code_len);
}


int tyran_code_get_label(struct tyran_label* labels, int count, const char* name)
{
	int i;
	for (i=0; i<count; ++i) {
		if (tyran_strcmp(labels[i].name, name) == 0) {
			return i;
		}
	}

	return -1;
}

void tyran_code_fixup_label_references(tyran_code_state* state)
{
	int i;
	for (i=0; i<state->label_reference_count; ++i) {
		tyran_label_reference* ref = &state->label_references[i];
		TYRAN_ASSERT(state->label_count > ref->label_index, "Wrong label index:%d", ref->label_index);
		tyran_label* label = &state->labels[ref->label_index];
		if (label->position == -1) {
			TYRAN_SOFT_ERROR("Label:%d is not defined", i);
		} else {
			int absolute_position = (ref->opcode - state->opcodes->codes);
			TYRAN_ASSERT(absolute_position >= 0, "Wrong position for label");
			int delta = label->position - absolute_position - 2;
			tyran_opcodes_modify_branch(ref->opcode, delta);
		}
	}

	state->label_reference_count = 0;
}



