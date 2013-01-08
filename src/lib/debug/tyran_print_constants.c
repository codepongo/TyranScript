#include <tyranscript/tyran_constants.h>
#include <tyranscript/debug/tyran_print_value.h>
#include <tyranscript/tyran_value.h>

void tyran_print_constants(tyran_constants* constants, struct tyran_memory_pool* object_iterator_pool, tyran_memory_pool* string_pool, tyran_memory* memory)
{
	char buf[255];
	int i;

	for (i=0; i<constants->size; ++i) {
		tyran_snprintf(buf, 255, "%d", i);
		tyran_print_value(buf, &constants->values[i], 1, constants->symbol_table, object_iterator_pool, string_pool, memory);
	}
}

