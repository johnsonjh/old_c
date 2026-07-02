/* Copyright (C) 1986,1987 by Manx Software Systems, Inc. */

#include <errno.h>
#include <fcntl.h>
#include <functions.h>

int
_close(register int fd)
{
	register struct _dev *refp;

	refp = _devtab + fd;
	if (fd < 0 || fd >= _numdev || refp->fd == 0) {
		errno = EBADF;
		return(-1);
	}
	if ((refp->mode & O_STDIO) == 0)
		Close(refp->fd);
	refp->fd = 0;
	return(0);
}

