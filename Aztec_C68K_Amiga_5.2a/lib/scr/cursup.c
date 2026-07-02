/* Copyright (C) 1986 by Manx Software Systems */
#include <fcntl.h>

void
scr_cursup(void)
{
	write(1, "\x1b[A", (size_t) 3);
}

