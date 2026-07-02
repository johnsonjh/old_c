/* Copyright (C) 1986 by Manx Software Systems */
#include <fcntl.h>
#include <string.h>
#include <stdio.h>

void
scr_curs(int lin, int col)
{
	char buf[80];
	sprintf(buf, "\x1b[%d;%dH", lin+1, col+1);
	write(1, buf, strlen(buf));
}

