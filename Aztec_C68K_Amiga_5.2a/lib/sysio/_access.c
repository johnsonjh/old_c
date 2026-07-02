/* Copyright (C) 1986,1987 by Manx Software Systems, Inc. */

#include <errno.h>
#include <libraries/dos.h>
#include <functions.h>

int
_access(char *filename, int mode)
{
	BPTR l;
	int ret = -1;

	if ((l = Lock((UBYTE *)filename, (long)ACCESS_READ)) == 0) {
		errno = ENOENT;
		return(-1);
	}
	switch(mode) {
	case 2:			/* write */
		UnLock(l);
		if ((l = Lock((UBYTE *)filename, (long)ACCESS_WRITE)) == 0) {
			errno = EACCES;
			return(-1);
		}
		/* FALL THRU */
	case 0:			/* existence */
	case 1:			/* execute (if file) or search (if directory) */
	case 4:			/* read */
		ret = 0;
		break;
	}
	UnLock(l);
	return(ret);
}

