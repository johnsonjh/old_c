/* Copyright 1989 Manx Software Systems, Inc. All rights reserved */

/*
 *	Synopsis
 *
 *	int sscanf(const char *s, const char *format, ...);
 *
 *
 *	Description
 *
 *		The sscanf function is equivalent to fscanf, except that the argument s
 *	specifies a string from which the input is to be obtained, rather than from
 *	a stream. Reaching the end of the string is equivalent to encountering
 *	end-of-file for the fscanf function. If copying takes place between objects
 *	that overlap, the behavior is undefined.
 *
 *		See the _scan function for a complete description of the format
 *	string.
 *
 *
 *	Returns
 *
 *		The sscanf function returns the value of the macro EOF if an input
 *	failure occurs before any conversion. Otherwise, the sscanf function
 *	returns the number of input items assigned, which can be fewer than
 *	provided for, or even zero, in the event of an early matching failure.
 */

#include <stdio.h>
#include <stdarg.h>
#include <string.h>

int
sscanf(register const char *s, const char *format, ...)
{
	register va_list vargs;
	FILE iob;
	register int ret;

	va_start(vargs, format);
	iob._flags = _IOR | _IOSTRNG | _IOMYBUF;
	iob._buff = iob._bp = (unsigned char *)s;
	iob._bend = (unsigned char *)s + strlen(s);
	ret = _scan(&iob, format, vargs);
	va_end(vargs);
	return(ret);
}

