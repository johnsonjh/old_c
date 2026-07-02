/* Copyright (C) 1986,1987 by Manx Software Systems, Inc. */

#include <libraries/dos.h>
#include <errno.h>
#include <functions.h>

int
_rename(char *old, char *new)
{
	BPTR l;

	if (l = Lock((UBYTE *)new, (long)ACCESS_READ)) {
		UnLock(l);
		errno = EEXIST;
		return(-1);
	}
	if (Rename((UBYTE *)old, (UBYTE *)new) == 0) {
		errno = IoErr();
		return(-1);
	}
	return(0);
}

