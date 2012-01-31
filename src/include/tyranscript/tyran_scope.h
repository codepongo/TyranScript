#ifndef _TYRAN_SCOPE_H
#define _TYRAN_SCOPE_H

struct tyran_value;
struct tyran_string_array;
struct tyran_function;

void tyran_scope_set_variable_names(tyran_value* arguments, const tyran_string_array* argument_names);
void tyran_scope_set_local_variables(tyran_value* arguments, const tyran_function* function);

#endif
