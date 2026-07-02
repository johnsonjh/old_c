/* Copyright (C) 1986 by Manx Software Systems */
#include <fcntl.h>

void
scr_bs(void)
{
	write(1, "\x1b[D", (size_t) 3);
}

