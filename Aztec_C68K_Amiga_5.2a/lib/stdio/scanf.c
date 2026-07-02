/* Copyright 1989 Manx Software Systems, Inc. All rights reserved */

/*
 *	Synopsis
 *
 *	int scanf(const char *format, ...);
 *
 *
 *	Description
 *
 *		The scanf function is equivalent to fscanf with the argument stdin
 *	interposed before the arguments to scanf.
 *
 *		See the _scan function for a complete description of the format
 *	string.
 *
 *
 *	Returns
 *
 *		The scanf function returns the value of the macro EOF if an input
 *	failure occurs before any conversion. Otherwise, the fscanf function
 *	returns the number of input items assigned, which can be fewer than
 *	provided for, or even zero, in the event of an early matching failure.
 */

#include <stdio.h>
#include <stdarg.h>

int
scanf(const char *format, ...)
{
	register va_list vargs;
	register int ret;

	va_start(vargs, format);
	ret = _scan(stdin, format, vargs);
	va_end(vargs);
	return(ret);
}

