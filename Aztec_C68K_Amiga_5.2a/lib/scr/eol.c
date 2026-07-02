/* Copyright (C) 1986 by Manx Software Systems */
#include <fcntl.h>

void
scr_eol(void)
{
	write(1, "\x1b[K", (size_t) 3);
}

