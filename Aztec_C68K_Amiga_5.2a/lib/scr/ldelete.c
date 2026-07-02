/* Copyright (C) 1986 by Manx Software Systems */
#include <fcntl.h>

void
scr_ldelete(void)
{
	write(1, "\x1b[M", (size_t) 3);
}

