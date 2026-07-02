/* Copyright (C) 1986,1987 by Manx Software Systems, Inc. */

#include <stdlib.h>
#include <functions.h>

void
_abort(void)
{
	Write(Output(), "^C\n", 4L);
	exit(1);
}

