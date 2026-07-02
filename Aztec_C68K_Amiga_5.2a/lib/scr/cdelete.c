/* Copyright (C) 1986 by Manx Software Systems */
#include <fcntl.h>
void
scr_cdelete(void)
{
	write(1, "\x1b[P", (size_t) 3);
}

