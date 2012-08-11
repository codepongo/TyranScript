#ifndef _TYRAN_LABEL_REFERNCE_H
#define _TYRAN_LABEL_REFERNCE_H

#include <tyranscript/tyran_opcodes.h>

typedef struct tyran_label_reference {
	const struct tyran_string* name;
	tyran_opcode* opcode;
} tyran_label_reference;

#endif
