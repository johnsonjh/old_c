/* Copyright 1989 Manx Software Systems, Inc. All rights reserved */

/*
 *	Synopsis
 *
 *	int printf(const char *format, ...);
 *
 *
 *	Description
 *
 *		The printf function is equivalent to fprintf with the argument stdout
 *	interposed before the arguments to printf.
 *
 *		See the _format function for a complete description of the format
 *	string.
 *
 *
 *	Returns
 *
 *		The printf function returns the number of characters transmitted, or a
 *	negative value if an output error occurred.
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
printf(const char *format, ...)
{
	register va_list vargs;
	register int ret;

	va_start(vargs, format);
	ret = _format(stdout, format, vargs);
	va_end(vargs);
	return(ret);
}

