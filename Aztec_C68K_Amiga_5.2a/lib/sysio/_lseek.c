/* Copyright (C) 1986,1987 by Manx Software Systems, Inc. */

#include <errno.h>
#include <fcntl.h>
#include <functions.h>

long
_lseek(register int fd, long pos, int mode)
{
	register struct _dev *refp;
	register long err;

	Chk_Abort();
	refp = _devtab + fd;
	if (fd < 0 || fd >= _numdev || refp->fd == 0) {
		errno = EBADF;
		return(-1);
	}
	if ((err = Seek(refp->fd, pos, (long)mode-1)) == -1) {
		errno = IoErr();
		return(-1);
	}
	return(Seek(refp->fd, 0L, 0L));
}

