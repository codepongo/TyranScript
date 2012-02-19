#ifndef _TYRAN_OPCODES_PRINT_H
#define _TYRAN_OPCODES_PRINT_H

struct tyran_opcode;
struct tyran_opcodes;

void tyran_print_opcode(const struct tyran_opcode* opcode, int ip, int highlight);
void tyran_print_opcodes(const struct tyran_opcodes* ops, const struct tyran_opcode* ip);

#endif
