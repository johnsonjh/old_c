/* Copyright (C) 1986 by Manx Software Systems */
#include <fcntl.h>

void
scr_clear(void)
{
	write(1, "\x1b[H\x1b[J", (size_t) 6);
}

