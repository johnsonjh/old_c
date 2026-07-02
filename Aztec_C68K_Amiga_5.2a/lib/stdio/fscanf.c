/* Copyright 1989 Manx Software Systems, Inc. All rights reserved */

/*
 *	Synopsis
 *
 *	int fscanf(FILE *stream, const char *format, ...);
 *
 *
 *	Description
 *
 *		The fscanf function reads input from the stream pointed to by stream,
 *	under control of the string pointed to by format that specifies the
 *	admissible input sequences and how they are to be converted for assignment,
 *	using subsequent arguments as pointers to the objects to receive the
 *	converted input. If there are insufficient arguments for the format, the
 *	behavior is undefined. If the format is exhausted while arguments remain,
 *	the excess arguments are evaluated (as always) but are otherwise ignored.
 *
 *		See the _scan function for a complete description of the format
 *	string.
 *
 *
 *	Returns
 *
 *		The fscanf function returns the value of the macro EOF if an input
 *	failure occurs before any conversion. Otherwise, the fscanf function
 *	returns the number of input items assigned, which can be fewer than
 *	provided for, or even zero, in the event of an early matching failure.
 */

#include <stdio.h>
#include <stdarg.h>

int
fscanf(FILE *stream, const char *format, ...)
{
	register va_list vargs;
	register int ret;

	va_start(vargs, format);
	ret = _scan(stream, format, vargs);
	va_end(vargs);
	return(ret);
}

