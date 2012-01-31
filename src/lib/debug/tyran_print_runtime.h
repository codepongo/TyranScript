#ifndef _TYRAN_PRINT_RUNTIME_H
#define _TYRAN_PRINT_RUNTIME_H

struct tyran_value;
struct tyran_opcode;

void tyran_print_runtime(const tyran_value* stack, int sp, const tyran_value* _this, const tyran_opcode* opcode, int ip);

#endif
