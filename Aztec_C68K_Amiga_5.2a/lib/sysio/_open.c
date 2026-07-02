/* Copyright (C) 1986,1987 by Manx Software Systems, Inc. */

#include <errno.h>
#include <fcntl.h>
#include <libraries/dos.h>
#include <functions.h>

int
_creat(const char *name, int mode)
{
	return(_open(name, O_WRONLY|O_TRUNC|O_CREAT, mode));
}

int
_open(register const char *name, int flag, ...)
{
	register struct _dev *refp;
	register int fd, err;
	register BPTR flock;
	register BPTR file;
	register struct Library *lib;

	Chk_Abort();
	refp = _devtab;
	for (fd=0;fd<_numdev;fd++)
		if (refp[fd].fd == 0)
			goto found;
	err = EMFILE;
	goto xerr;
found:
	if (flag & O_TRUNC) {
		if (flock = Lock((UBYTE *)name, (long)ACCESS_WRITE)) {
			UnLock(flock);
			if (DeleteFile((UBYTE *)name) == 0 && (err=IoErr()) != 205)
				goto xerr;
		}
	}
	file = Open((UBYTE *)name, (long)MODE_OLDFILE);
	if (file == 0) {
		if ((flag&O_CREAT) == 0) {
			err = ENOENT;
			goto xerr;
		}
		if ((file = Open((UBYTE *)name, (long)MODE_NEWFILE)) == 0) {
			err = IoErr();
			goto xerr;
		}
	/*
	 *	this kludge is necessary till the RAM: driver gets fixed
	 */
	 	if (lib = OpenLibrary((UBYTE *)"dos.library", 33L))
			CloseLibrary(lib);
		else {
			Write(file, "", 1L);
			Seek(file, 0L, -1L);
		}
	}
	else if ((flag&(O_CREAT|O_EXCL)) == (O_CREAT|O_EXCL)) {
		Close(file);
		err = EEXIST;
xerr:
		errno = err;
		return(-1);
	}
	refp[fd].fd = file;
	refp[fd].mode = flag;
	if (flag & O_APPEND)
		Seek(file, 0L, (long)OFFSET_END);
	return(fd);
}

