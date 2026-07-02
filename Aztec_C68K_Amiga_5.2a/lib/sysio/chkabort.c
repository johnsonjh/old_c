/* Copyright (C) 1986,1987 by Manx Software Systems, Inc. */

#include <functions.h>

void _abort(void);

long
Chk_Abort(void)
{
	long x;
	extern int Enable_Abort;

	if ((x = SetSignal(0L, 0x1000L))&0x1000) {
		if (Enable_Abort == 0)
			return(x);
		_abort();
	}
	return(0);
}

