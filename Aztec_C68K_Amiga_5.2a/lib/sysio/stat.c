/* Copyright (C) 1986,1987 by Manx Software Systems, Inc. */

#include <stat.h>
#include <exec/exec.h>
#include <libraries/dosextens.h>
#include <functions.h>

int
stat(char *name, struct stat *buf)
{
	BPTR l;
	struct FileInfoBlock *fp;

	if ((l=Lock((UBYTE *)name, (long)ACCESS_READ)) == 0)
		return(-1);
	if ((fp = AllocMem((long)sizeof *fp, 0L)) == 0) {
		UnLock(l);
		return(-1);
	}
	Examine(l, fp);
	buf->st_attr = fp->fib_Protection;
	buf->st_mtime = fp->fib_Date.ds_Days * 24 * 60 * 60 +
					fp->fib_Date.ds_Minute * 60 +
					fp->fib_Date.ds_Tick/TICKS_PER_SECOND;
	buf->st_size = fp->fib_Size;
	FreeMem(fp, (long) sizeof *fp);
	UnLock(l);
	return(0);
}

