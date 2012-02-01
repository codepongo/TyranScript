#ifndef _TYRAN_PRINT_RUNTIME_H
#define _TYRAN_PRINT_RUNTIME_H

struct tyran_value;
struct tyran_opcode;

void tyran_print_runtime(const struct tyran_value* stack, int sp, const struct tyran_value* _this, const struct tyran_opcode* opcode, int ip);

#endif
