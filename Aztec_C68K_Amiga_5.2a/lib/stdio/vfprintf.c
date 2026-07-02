/* Copyright 1989 Manx Software Systems, Inc. All rights reserved */

/*
 *	Synopsis
 *
 *	int vfprintf(FILE *stream, const char *format, va_list arg);
 *
 *
 *	Description
 *
 *		The vfprintf function is equivalent to fprintf, with the variable
 *	argument list replaced by arg, which has been initialized by the va_start
 *	macro (and possibly subsequent va_arg calls). The vfprintf function does
 *	not invoke the va_end macro.
 *
 *		See the _format function for a complete description of the format
 *	string.
 *
 *
 *	Returns
 *
 *		The vfprintf function returns the number of characters transmitted, or
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
vfprintf(FILE *stream, const char *format, va_list vargs)
{
	return(_format(stream, format, vargs));
}

