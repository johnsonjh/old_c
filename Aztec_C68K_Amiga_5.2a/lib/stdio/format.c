/* Copyright (C) 1991 by Manx Software Systems */
#include <stdarg.h>
#include <stdio.h>

int
format(register int (*putsub)(int), const char *fmt, ...)
{
	va_list varg;
	int c;
	char buf[512];

	va_start(varg, fmt);
	c = vsprintf(buf, fmt, varg);
	va_end(varg);
	for (fmt = buf;*fmt;)
		if ((*putsub)((int)*fmt++) == -1)
			return -1;
	return c;
}
