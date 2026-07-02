/* Copyright (C) 1986,1987 by Manx Software Systems, Inc. */

/*
 *	This routine is called whenever the stack checking code detects an
 *	overrun of the bottom of the stack.
 */

#include <functions.h>

void _exit(int);

void
_stkover(void)
{
#asm
	move.l	__savsp#,d0
	sub.l	#16,d0
	move.l	d0,a7
#endasm
	Write(Output(), "Stack overflow!!\n", 17L);
	_exit(100);
}

