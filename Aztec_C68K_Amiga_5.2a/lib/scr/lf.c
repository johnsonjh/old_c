/* Copyright (C) 1986 by Manx Software Systems */
#include <fcntl.h>

void
scr_lf(void)
{
	write(1, "\x1b[B", (size_t) 3);
}

