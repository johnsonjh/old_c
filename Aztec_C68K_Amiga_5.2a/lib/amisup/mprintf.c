/* Copyright (C) 1987 by Manx Software Systems */

#include <stdio.h>
#include <stdarg.h>

int _format(FILE *stream, const char *format, va_list vargs);
void kputs(const char *_s);

int
mprintf(const char *format, ...)
{
	char s[256];
	register int ret;
	register va_list vargs;

	va_start(vargs, format);
	ret = vsprintf(s, format, vargs);
	va_end(vargs);
	kputs(s);
	return(ret);
}

