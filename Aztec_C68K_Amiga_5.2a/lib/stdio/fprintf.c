/* Copyright 1989 Manx Software Systems, Inc. All rights reserved */

/*
 *	Synopsis
 *
 *	int fprintf(FILE *stream, const char *format, ...);
 *
 *
 *	Description
 *
 *		The fprintf function writes output to the stream pointed to by stream,
 *	under control of the string pointed to by format that specifies how
 *	subsequent arguments are converted for output. If there are insufficient
 *	arguments for the format, the behavior is undefined. If the format is
 *	exhausted while arguments remain, the excess arguments are evaluated (as
 *	always) but are otherwise ignored. The fprintf function returns when the
 *	end of the format string is encountered.
 *
 *		See the _format function for a complete description of the format
 *	string.
 *
 *
 *	Returns
 *
 *		The fprintf function returns the number of characters transmitted, or a
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
fprintf(FILE *stream, const char *format, ...)
{
	register va_list vargs;
	register int ret;

	va_start(vargs, format);
	ret = _format(stream, format, vargs);
	va_end(vargs);
	return(ret);
}

