/* Copyright (C) 1986 by Manx Software Systems */
#include <fcntl.h>

void
scr_cursrt(void)
{
	write(1, "\x1b[C", (size_t) 3);
}

