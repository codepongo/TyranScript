#include <tyranscript/tyran_constants.h>
#include <tyranscript/tyran_value.h>
#include <tyranscript/tyran_string.h>
#include <tyranscript/tyran_function.h>
#include <tyranscript/tyran_string_object.h>
#include <tyranscript/tyran_object_macros.h>
#include <tyranscript/tyran_symbol_table.h>
#include <tyranscript/tyran_runtime.h>

tyran_constants* tyran_constants_new(tyran_memory_pool* constants_pool, tyran_symbol_table* symbol_table, tyran_memory* memory, size_t size)
{
	tyran_constants* constants = TYRAN_CALLOC_TYPE(constants_pool, tyran_constants);
	constants->values = TYRAN_MALLOC_NO_POOL_TYPE_COUNT(memory, tyran_value, size);
	constants->symbol_table = symbol_table;
	return constants;
}

void tyran_constants_free(tyran_constants* constants)
{
	TYRAN_MALLOC_FREE(constants->values);
	TYRAN_MALLOC_FREE(constants);
}

tyran_constant_index tyran_constants_reserve_index(struct tyran_constants* constants, tyran_value* v)
{
	tyran_constant_index i;
	for (i=0; i<constants->size; ++i) {
		if (tyran_value_is_same(&constants->values[i], v)) {
			return i | TYRAN_OPCODE_CONSTANT_BIT;
		}
	}

	tyran_constant_index new_index = constants->size++;
	tyran_value_copy(constants->values[new_index], *v);
	return new_index | TYRAN_OPCODE_CONSTANT_BIT;
}

tyran_constant_index tyran_constants_add_number(tyran_constants* constants, tyran_number v)
{
	tyran_value value;
	tyran_value_set_number(value, v);
	return tyran_constants_reserve_index(constants, &value);
}

tyran_constant_index tyran_constants_add_string(tyran_constants* constants, struct tyran_runtime* runtime, const struct tyran_string* v)
{
	tyran_value value;

	tyran_string_object_new(&value, runtime, v);

	return tyran_constants_reserve_index(constants, &value);
}

tyran_constant_index tyran_constants_add_symbol_from_c_string(tyran_constants* constants, const char* v)
{
	tyran_symbol symbol;
	tyran_symbol_table_add(constants->symbol_table, &symbol, v);
	tyran_value value;
	tyran_value_set_symbol(value, symbol);

	return tyran_constants_reserve_index(constants, &value);
}

tyran_constant_index tyran_constants_add_boolean(tyran_constants* constants, tyran_boolean v)
{
	tyran_value value;
	tyran_value_set_boolean(value, v);
	return tyran_constants_reserve_index(constants, &value);
}

tyran_constant_index tyran_constants_add_nil(tyran_constants* constants)
{
	tyran_value value;
	tyran_value_set_nil(value);
	return tyran_constants_reserve_index(constants, &value);
}


tyran_constant_index tyran_constants_add_function(tyran_memory_pool* function_pool, tyran_constants* constants, tyran_constants* function_constants, tyran_opcodes* opcodes)
{
	tyran_value value;
	struct tyran_function* func = tyran_function_new(function_pool, opcodes, function_constants);
	tyran_value_set_static_function(value, func);
	return tyran_constants_reserve_index(constants, &value);
}
