/* Copyright (C) 1986 by Manx Software Systems */
#include <fcntl.h>

void
scr_cr(void)
{
	write(1, "\x0d", (size_t) 1);
}

