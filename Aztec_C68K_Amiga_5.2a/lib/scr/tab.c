/* Copyright (C) 1986 by Manx Software Systems */
#include <fcntl.h>

void
scr_tab(void)
{
	write(1, "\x09", (size_t) 1);
}

