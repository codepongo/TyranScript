#ifndef _TYRAN_OPCODES_PRINT_H
#define _TYRAN_OPCODES_PRINT_H

struct tyran_opcode;
struct tyran_opcodes;

void tyran_opcodes_print_opcode(const struct tyran_opcode* opcode, int ip);
void tyran_opcodes_print(const struct tyran_opcodes* ops);

#endif
