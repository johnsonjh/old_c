/* Copyright 1989 Manx Software Systems, Inc. All rights reserved */

/*
 *	Synopsis
 *
 *	int sprintf(chra *s, const char *format, ...);
 *
 *
 *	Description
 *
 *		The sprintf function is equivalent to fprintf, except that the argument
 *	s specifies an array into which the generated output is to be written,
 *	rather than to a stream. A null character is written at the end of the
 *	characters written; it is not counted as part of the returned sum. If
 *	copying takes place between objects that overlap, the behavior is
 *	undefined.
 *
 *		See the _format function for a complete description of the format
 *	string.
 *
 *
 *	Returns
 *
 *		The sprintf function returns the number of characters written in the
 *	array, not counting the terminating null character.
 *
 *
 *	Environmental limit
 *
 *		The minimum value for the maximum number of characters produced by any
 *	single conversion shall be 509.
 */

#include <stdio.h>
#include <stdarg.h>

int _format(FILE *stream, const char *format, va_list vargs);

int
sprintf(register char *s, const char *format, ...)
{
	register va_list vargs;
	FILE iob;
	register int ret;

	va_start(vargs, format);
	iob._flags = _IOW | _IOSTRNG | _IODIRTY;
	iob._buff = iob._bp = (unsigned char *)s;
	iob._bend = (unsigned char *)s + 32767;
	ret = _format(&iob, format, vargs);
	s[ret] = 0;
	va_end(vargs);
	return(ret);
}

