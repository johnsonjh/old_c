/* Copyright (C) 1986,1987 by Manx Software Systems, Inc. */

#include <errno.h>
#include <functions.h>

int
_unlink(char *name)
{
	if (DeleteFile((UBYTE *)name) == 0) {
		errno = IoErr();
		return(-1);
	}
	return(0);
}
