#include <tyranscript/tyran_object_prototype.h>
#include <tyranscript/tyran_function_object.h>
#include <tyranscript/tyran_runtime.h>
#include <tyranscript/tyran_value.h>
#include <tyranscript/tyran_value_object.h>
/*

#include <tyranscript/parser/tyran_parser_state.h>
#include <tyranscript/tyran_value.h>
#include <tyranscript/tyran_string.h>
#include <tyranscript/tyran_function.h>

#include <tyranscript/tyran_object_prototype.h>
#include <tyranscript/tyran_function_prototype.h>

#include <tyranscript/tyran_value_object.h>
#include <tyranscript/tyran_object.h>
#include <tyranscript/tyran_object_macros.h>
#include <tyranscript/tyran_array.h>
*/

TYRAN_RUNTIME_CALL_FUNC(tyran_object_prototype_constructor) {
	return 0;
}

void tyran_object_prototype_init(const struct tyran_runtime* runtime, tyran_value* o) {
	TYRAN_MEMBER(o, "constructor", tyran_object_prototype_constructor);
}
