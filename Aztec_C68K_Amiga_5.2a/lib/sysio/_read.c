/* Copyright (C) 1986,1987 by Manx Software Systems, Inc. */

#include <errno.h>
#include <fcntl.h>
#include <functions.h>

size_t
_read(register int fd, void *buf, size_t len)
{
	register struct _dev *refp;
	register long err;

	Chk_Abort();
	refp = _devtab + fd;
	if (fd < 0 || fd >= _numdev || refp->fd == 0) {
		errno = EBADF;
		return(-1);
	}
	if ((refp->mode & 3) == O_WRONLY) {
		errno = EINVAL;
		return(-1);
	}
	if ((err = Read(refp->fd, buf, (long)len)) == -1) {
		errno = IoErr();
		return(-1);
	}
	return(err);
}

