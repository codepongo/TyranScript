#ifndef TYRAN_ERRORS_H
#define TYRAN_ERRORS_H

struct tyran_lexer;
struct tyran_memory;

enum tyran_error_code {
	TYRAN_ERROR_NO_END_STRING,
	TYRAN_ERROR_CODE_MAX
};


typedef struct tyran_errors {
	enum tyran_error_code last_error;
} tyran_errors;


tyran_errors* tyran_errors_new(struct tyran_memory* memory);

int tyran_errors_add(struct tyran_errors* errors, enum tyran_error_code error, struct tyran_lexer* lexer);

#endif
