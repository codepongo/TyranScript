#include <tyranscript/tyran_number.h>
#include <tyranscript/tyran_string.h>

static const double pow10[] = {1, 10, 100, 1000, 10000, 100000, 1000000,
10000000, 100000000, 1000000000};

#ifndef _WIN32
#  include <stdint.h>
#else
/* win64 is llp64 so these are the same for 32/64bit
   so no check for _WIN64 is required.
 */
  typedef unsigned char uint8_t;
  typedef signed char int8_t;
  typedef unsigned short uint16_t;
  typedef signed short int16_t;
  typedef unsigned int uint32_t;
  typedef signed int int32_t;
  typedef unsigned __int64 uint64_t;
  typedef signed __int64 int64_t;
#endif


static void strreverse(char* begin, char* end)
{
	char aux;
	while (end > begin)
		aux = *end, *end-- = *begin, *begin++ = aux;
}

void modp_itoa10(int32_t value, char* str)
{
	char* wstr=str;
	/* Take care of sign */
	unsigned int uvalue = (value < 0) ? -value : value;
	/* Conversion. Number is reversed. */
	do *wstr++ = (char)(48 + (uvalue % 10)); while(uvalue /= 10);
	if (value < 0) *wstr++ = '-';
	*wstr='\0';

	/*  Reverse string */
	strreverse(str,wstr-1);
}

void tyran_number_integer_to_string(tyran_memory_pool* string_pool, tyran_memory* memory, int value, const tyran_string** str)
{
	char string_buffer[100];
	
	modp_itoa10(value, string_buffer);

	*str = tyran_string_from_c_str(string_pool, memory, string_buffer);
}



void tyran_modp_dtoa2(double value, char* str, int prec)
{
    /* Hacky test for NaN
     * under -fast-math this won't work, but then you also won't
     * have correct nan values anyways.  The alternative is
     * to link with libmath (bad) or hack IEEE double bits (bad)
     */
    if (! (value == value)) {
        str[0] = 'n'; str[1] = 'a'; str[2] = 'n'; str[3] = '\0';
        return;
    }

    /* if input is larger than thres_max, revert to exponential */
    const double thres_max = (double)(0x7FFFFFFF);

    int count;
    double diff = 0.0;
    char* wstr = str;

    if (prec < 0) {
        prec = 0;
    } else if (prec > 9) {
        /* precision of >= 10 can lead to overflow errors */
        prec = 9;
    }


    /* we'll work in positive values and deal with the
       negative sign issue later */
    int neg = 0;
    if (value < 0) {
        neg = 1;
        value = -value;
    }


    int whole = (int) value;
    double tmp = (value - whole) * pow10[prec];
    uint32_t frac = (uint32_t)(tmp);
    diff = tmp - frac;

    if (diff > 0.5) {
        ++frac;
        /* handle rollover, e.g.  case 0.99 with prec 1 is 1.0  */
        if (frac >= pow10[prec]) {
            frac = 0;
            ++whole;
        }
    } else if (diff == 0.5 && ((frac == 0) || (frac & 1))) {
        /* if halfway, round up if odd, OR
           if last digit is 0.  That last part is strange */
        ++frac;
    }

    /* for very large numbers switch back to native sprintf for exponentials.
       anyone want to write code to replace this? */
    /*
      normal printf behavior is to print EVERY whole number digit
      which can be 100s of characters overflowing your buffers == bad
    */
    if (value > thres_max) {
        tyran_snprintf(str, prec, "%e", neg ? -value : value);
        return;
    }

    if (prec == 0) {
        diff = value - whole;
        if (diff > 0.5) {
            /* greater than 0.5, round up, e.g. 1.6 -> 2 */
            ++whole;
        } else if (diff == 0.5 && (whole & 1)) {
            /* exactly 0.5 and ODD, then round up */
            /* 1.5 -> 2, but 2.5 -> 2 */
            ++whole;
        }

        /* vvvvvvvvvvvvvvvvvvv  Diff from modp_dto2 */
    } else if (frac) {
        count = prec;
        /* now do fractional part, as an unsigned number */
        /* we know it is not 0 but we can have leading zeros, these */
        /* should be removed */
        while (!(frac % 10)) {
            --count;
            frac /= 10;
        }
        /* ^^^^^^^^^^^^^^^^^^^  Diff from modp_dto2 */

        /* now do fractional part, as an unsigned number */
        do {
            --count;
            *wstr++ = (char)(48 + (frac % 10));
        } while (frac /= 10);
        /* add extra 0s */
        while (count-- > 0) *wstr++ = '0';
        /* add decimal */
        *wstr++ = '.';
    }

    /* do whole part */
    /* Take care of sign */
    /* Conversion. Number is reversed. */
    do *wstr++ = (char)(48 + (whole % 10)); while (whole /= 10);
    if (neg) {
        *wstr++ = '-';
    }
    *wstr='\0';
    strreverse(str, wstr-1);
}

void tyran_number_to_string(tyran_memory_pool* string_pool, tyran_memory* memory, double value, const tyran_string** str, int prec)
{
	char string_buffer[100];

	tyran_modp_dtoa2(value, string_buffer, prec);

	*str = tyran_string_from_c_str(string_pool, memory, string_buffer);
}
