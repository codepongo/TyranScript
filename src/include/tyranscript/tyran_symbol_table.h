#ifndef tyran_symbol_table_h
#define tyran_symbol_table_h

struct tyran_memory;
struct tyran_symbol;


typedef struct tyran_symbol_table_entry {
	const char* string;
} tyran_symbol_table_entry;

typedef struct tyran_symbol_table {
	tyran_symbol_table_entry entries[100];
	int entry_count;
	struct tyran_memory* memory;
} tyran_symbol_table;

tyran_symbol_table* tyran_symbol_table_new(struct tyran_memory* memory);
void tyran_symbol_table_free(tyran_symbol_table* table);
void tyran_symbol_table_add(tyran_symbol_table* table, struct tyran_symbol* symbol, const char* str);
const char* tyran_symbol_table_lookup(const tyran_symbol_table* table, const struct tyran_symbol* symbol);

#endif
