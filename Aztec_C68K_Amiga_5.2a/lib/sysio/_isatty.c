/* Copyright (C) 1986,1987 by Manx Software Systems, Inc. */

#include <fcntl.h>
#include <errno.h>
#include <functions.h>

int
_isatty(int fd)
{
	register struct _dev *refp;

	refp = _devtab + fd;
	if (fd < 0 || fd >= _numdev || refp->fd == 0) {
		errno = EBADF;
		return(-1);
	}
	return(IsInteractive(_devtab[fd].fd) != 0);
}

