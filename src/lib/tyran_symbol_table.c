#include <tyranscript/tyran_symbol_table.h>
#include <tyranscript/tyran_config.h>
#include <tyranscript/tyran_symbol.h>

tyran_symbol_table* tyran_symbol_table_new(tyran_memory* memory)
{
	tyran_symbol_table* table = TYRAN_MALLOC_NO_POOL_TYPE(memory, tyran_symbol_table);
	table->entry_count = 0;
	table->memory = memory;

	return table;
}

void tyran_symbol_table_free(tyran_symbol_table* table)
{
	for (int i=0; i<table->entry_count; ++i) {
		tyran_free((void*)table->entries[i].string);
	}
	tyran_free(table);
}

int tyran_symbol_table_find(tyran_symbol_table* table, const char* str)
{
	for (int i=0; i<table->entry_count; ++i) {
		if (tyran_strcmp(table->entries[i].string, str) == 0) {
			return i;
		}
	}

	return -1;
}

void tyran_symbol_table_add(tyran_symbol_table* table, tyran_symbol* symbol, const char* str)
{
	int index = tyran_symbol_table_find(table, str);
	if (index == -1) {
		index = table->entry_count;
		TYRAN_ASSERT(table->entry_count < 100, "Out of memory");
		table->entry_count++;
		tyran_symbol_table_entry* entry = &table->entries[index];
		entry->string = tyran_strdup(table->memory, str);
	}

	symbol->hash = index;
}

const char* tyran_symbol_table_lookup(const tyran_symbol_table* table, const tyran_symbol* symbol)
{
	return table->entries[symbol->hash].string;
}
