#ifndef TYRAN_PRINT_RUNTIME_STATE_H
#define TYRAN_PRINT_RUNTIME_STATE_H

#include <tyranscript/tyran_opcodes.h>

struct tyran_runtime_stack;
struct tyran_value;

void tyran_print_runtime_state(const tyran_opcode* pc, const struct tyran_runtime_stack* sp, const struct tyran_value* r);

#endif
