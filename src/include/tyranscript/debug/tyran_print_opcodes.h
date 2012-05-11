#ifndef _TYRAN_OPCODES_PRINT_H
#define _TYRAN_OPCODES_PRINT_H

#include "tyranscript/tyran_opcodes.h"

struct tyran_opcodes;

void tyran_print_opcode(const tyran_opcode* opcode, int ip, int highlight);
void tyran_print_opcodes(const struct tyran_opcodes* ops, const tyran_opcode* ip);

#endif
