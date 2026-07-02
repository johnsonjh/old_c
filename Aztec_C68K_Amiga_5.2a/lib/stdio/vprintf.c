/* Copyright 1989 Manx Software Systems, Inc. All rights reserved */

/*
 *	Synopsis
 *
 *	int vprintf(char *format, va_list arg);
 *
 *
 *	Description
 *
 *		The vprintf function is equivalent to printf, with the variable
 *	argument list replaced by arg, which has been initialized by the va_start
 *	macro (and possibly subsequent va_arg calls). The vprintf function does
 *	not invoke the va_end macro.
 *
 *		See the _format function for a complete description of the format
 *	string.
 *
 *
 *	Returns
 *
 *		The vprintf function returns the number of characters transmitted, or
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
vprintf(const char *format, va_list vargs)
{
	return(_format(stdout, format, vargs));
}

