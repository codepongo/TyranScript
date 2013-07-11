#include <tyranscript/tyran_constants.h>
#include <tyranscript/debug/tyran_print_value.h>
#include <tyranscript/tyran_value.h>

void tyran_print_constants(tyran_constants* constants)
{
	char buf[255];
	int i;

	for (i=0; i<constants->size; ++i) {
		tyran_snprintf(buf, 255, "%d", i);
		tyran_print_value(buf, &constants->values[i], 1, constants->symbol_table);
	}
}

