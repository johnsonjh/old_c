/* Copyright (C) 1986 by Manx Software Systems */
#include <fcntl.h>

void
scr_beep(void)
{
	write(1, "\x07", (size_t) 1);
}

