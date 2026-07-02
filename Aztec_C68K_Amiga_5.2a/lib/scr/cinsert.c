/* Copyright (C) 1986 by Manx Software Systems */
#include <fcntl.h>

void
scr_cinsert(void)
{
	write(1, "\x1b[@", (size_t) 3);
}

