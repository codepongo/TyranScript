#ifndef _TYRAN_LABEL_REFERNCE_H
#define _TYRAN_LABEL_REFERNCE_H

#include <tyranscript/tyran_opcodes.h>

typedef struct tyran_label_reference {
	int label_index;
	tyran_opcode* opcode;
} tyran_label_reference;

#endif
