#ifndef _TYRAN_NUMBER_H
#define _TYRAN_NUMBER_H

#define MAXEXP	2047

#define EXP(a) ((((u16t *)(&a))[3] & 0x7ff0) >> 4)
#define FRAZERO(a) (((u32t *)(&a))[0] == 0 && (((u32t *)(&a))[1] & 0x0fffff) == 0)

#define tyran_number_is_normal(a) (EXP(a) != MAXEXP)

#if defined _MSC_VER
#include <float.h>
#define tyran_number_is_nan(x) _isnan(x)
#define tyran_number_is_infinity(x) !_finite(x)
#else
#include <math.h>
#define tyran_number_is_nan(a)		isnan(a)
#define tyran_number_is_infinity(a)	isinf(a)
#endif

#endif

