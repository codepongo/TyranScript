#include <tyranscript/tyran_configuration.h>
#include <tyranscript/parser/common/tyran_errors.h>
#include <tyranscript/parser/tyran_lexer.h>


tyran_errors* tyran_errors_new(tyran_memory* memory)
{
	tyran_errors* errors = TYRAN_MALLOC_NO_POOL_TYPE(memory, tyran_errors);

	return errors;
}


int tyran_errors_add(tyran_errors* errors, enum tyran_error_code error, struct tyran_lexer* lexer)
{
#if defined TYRAN_CONFIGURATION_DEBUG
	static const char* error_string[TYRAN_ERROR_CODE_MAX] = {
		"String without end"
	};

	errors->last_error = error;
	TYRAN_LOG("error:%s", error_string[error]);

	return (int) error;
#else
	return 0;
#endif
}
