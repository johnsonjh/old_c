/* Copyright (C) 1986,1987 by Manx Software Systems, Inc. */

#include <libraries/dosextens.h>
#include <functions.h>
#include <sgtty.h>
#include <fcntl.h>
#include <errno.h>

int
_ioctl(int fd, int cmd, struct sgttyb *arg)
{
	register struct _dev *refp;
	register struct FileHandle *fhp, *myfhp;
	struct Process *myProc;

	Chk_Abort();
	refp = _devtab + fd;
	if (fd < 0 || fd >= _numdev || refp->fd == 0) {
		errno = EBADF;
		return(-1);
	}
	switch (cmd) {
	case TIOCGETP:
		arg->sg_flags = (refp->mode&O_CONRAW)?RAW:0;
		break;
	case TIOCSETP:
		if (!IsInteractive(refp->fd))
			break;
		myProc = (struct Process *)FindTask(0L);
		myfhp = (struct FileHandle *)(refp->fd<<2);
		for (refp=_devtab;refp<_devtab+_numdev;refp++) {
			fhp = (struct FileHandle *)((long)refp->fd << 2);
			if (fhp == 0 || fhp->fh_Type != myfhp->fh_Type)
				continue;
			if (arg->sg_flags & RAW)
				refp->mode |= O_CONRAW;
			else
				refp->mode &= ~O_CONRAW;
		}
		dos_packet((struct MsgPort *)myfhp->fh_Type, 994L,
												arg->sg_flags&RAW?-1L:0L);
		break;
	}
	return(0);
}

