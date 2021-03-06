#ifndef _TYRAN_PRINT_RUNTIME_H
#define _TYRAN_PRINT_RUNTIME_H

struct tyran_value;
struct tyran_scope_stack;
struct tyran_opcode;

void tyran_print_runtime(const struct tyran_value* stack, int sp, const struct tyran_value* _this, const struct tyran_opcode* opcode, int ip);
void tyran_print_scope_stack(const struct tyran_scope_stack* stack);

#endif
