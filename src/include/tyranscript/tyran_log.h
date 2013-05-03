#ifndef tyran_log_h
#define tyran_log_h

#include <tyranscript/tyran_clib.h>
#include <tyranscript/tyran_configuration.h>


#if defined TYRAN_CONFIGURATION_DEBUG

#define TYRAN_LOG(...) { tyran_fprintf(stderr, __VA_ARGS__); tyran_fprintf(stderr, "\n"); tyran_fflush(stderr); }
#define TYRAN_LOG_NO_LF(...) { tyran_fprintf(stderr, __VA_ARGS__); tyran_fflush(stderr); }
#define TYRAN_SOFT_ERROR(...) TYRAN_LOG(__VA_ARGS__);
#define TYRAN_BREAK abort()
#define TYRAN_ERROR(...) TYRAN_LOG(__VA_ARGS__); TYRAN_BREAK;
#define TYRAN_ASSERT(expression, ...) if (!(expression)) { TYRAN_LOG(__VA_ARGS__); TYRAN_BREAK; }

#else

#define TYRAN_LOG(...)
#define TYRAN_LOG_NO_LF(...)
#define TYRAN_SOFT_ERROR(...)
#define TYRAN_BREAK abort()
#define TYRAN_ERROR(...)
#define TYRAN_ASSERT(expression, ...)

#endif

#define TYRAN_OUTPUT(...) { tyran_fprintf(stdout, __VA_ARGS__); tyran_fprintf(stdout, "\n"); tyran_fflush(stdout); }
#define TYRAN_OUTPUT_NO_LF(...) { tyran_fprintf(stdout, __VA_ARGS__); tyran_fflush(stdout); }

#endif
