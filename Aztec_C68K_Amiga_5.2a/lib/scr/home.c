/* Copyright (C) 1986 by Manx Software Systems */
#include <fcntl.h>

void
scr_home(void)
{
	write(1, "\x1b[H", (size_t) 3);
}

