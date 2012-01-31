#ifndef _TYRAN_PARSER_LOCAL_VARIABLE_SCOPE_H
#define _TYRAN_PARSER_LOCAL_VARIABLE_SCOPE_H

#include <tyranscript/tyran_string.h>

struct tyran_string_array;

void tyran_parser_local_variable_scope_push();
void tyran_parser_local_variable_scope_pop();
void tyran_parser_local_variable_scope_add(const tyran_string* str);
struct tyran_string_array* tyran_parser_local_variable_scope_names();

#endif
