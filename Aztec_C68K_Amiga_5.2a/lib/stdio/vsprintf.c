/* Copyright 1989 Manx Software Systems, Inc. All rights reserved */

/*
 *	Synopsis
 *
 *	int vsprintf(char *s, char *format, va_list arg);
 *
 *
 *	Description
 *
 *		The vsprintf function is equivalent to sprintf, with the variable
 *	argument list replaced by arg, which has been initialized by the va_start
 *	macro (and possibly subsequent va_arg calls). The vsprintf function does
 *	not invoke the va_end macro. If copying takes place between objects that
 *	overlap, the behavior is undefined.
 *
 *		See the _format function for a complete description of the format
 *	string.
 *
 *
 *	Returns
 *
 *		The vsprintf function returns the number of characters transmitted, or
 *	a negative value if an output error occurred.
 *
 *
 *	Environmental limit
 *
 *		The minimum value for the maximum number of characters produced by any
 *	single conversion shall be 509.
 */

#include <stdio.h>
#include <stdarg.h>

int
vsprintf(char *s, const char *format, va_list vargs)
{
	FILE iob;
	register int ret;

	iob._flags = _IOW | _IOSTRNG;
	iob._buff = iob._bp = (unsigned char *)s;
	iob._bend = (unsigned char *)s + 32767;
	ret = _format(&iob, format, vargs);
	s[ret] = 0;
	return(ret);
}

