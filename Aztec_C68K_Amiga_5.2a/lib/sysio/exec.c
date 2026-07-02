/* Copyright (C) 1986,1987 by Manx Software Systems, Inc. */

#include <exec/types.h>
#include <exec/tasks.h>
#include <libraries/dosextens.h>
#include <functions.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>

static int execit(char *arg, char **argv, int flg);

int
execl(char *file, char *arg0, ...)
{
	return(execv(file, &arg0));
}

int
execv(char *arg, char **argv)
{
	return(execit(arg, argv, 0));
}

int
execlp(char *file, char *arg0, ...)
{
	return(execvp(file, &arg0));
}

int
execvp(char *arg, char **argv)
{
	return(execit(arg, argv, 1));
}

struct ex {
	long	dosbase;
	BPTR	seglist;
	long *	stack;
	long	savret;
	BPTR *	cliseg;
	BPTR *	cliseg2;
	long	cmdlen;
	char *	cmdstr;
	char *	cmdnam;
	long	dirlck;
};

static int
isfile(BPTR l)
{
	struct FileInfoBlock *fp;
	int ret = 0;

	if ((fp = (struct FileInfoBlock *)AllocMem((long)sizeof *fp, 0L)) == 0)
		return(-1);
	Examine(l, fp);
	if (fp->fib_DirEntryType < 0)
		ret = 1;
	FreeMem(fp, (long) sizeof *fp);
	return(ret);
}

static int
execit(char *arg, char **argv, int flg)
{
	register struct ex *ex;
	register struct CommandLineInterface *cli;
	struct Process *pp;
	register char **ap, *cp;
	size_t len;
	long *l, *k, *bcpl;
	BPTR flck, savdir;
	struct Library *savlib;
	union {
		long *lp;
		long ll;
		BPTR fl;
		BPTR *flp;
	} dir;
	extern char _exec, _exectab;
	extern long DOSBase;
	extern long _savsp;

	for (len=0,ap=argv+1;*ap;ap++)
		len += strlen(*ap) + 1;
	pp = (struct Process *)FindTask(0);
	cli = (struct CommandLineInterface *)((long)pp->pr_CLI <<  2);
	if (cli == 0)
		return(-1);
	if ((savlib = OpenLibrary((UBYTE *)"dos.library", 33L)) == 0) {

		bcpl = (long *)*((long *)*((long *)*((long *)*((long *)
										_savsp+2)+1)-3)-3)+107;
		if (*bcpl != cli->cli_Module)
			return(-1);
	}
	else {
		CloseLibrary(savlib);
		bcpl = 0;
	}
	len += &_exectab-&_exec + 1 + 8 + sizeof(struct ex);
	len = (len + 3) & ~3;
	if ((k = AllocMem((long)len, 0L)) == 0)
		return(-1);
	memmove(k, &_exec, len);
	*k = len;
	ex = (struct ex *)((char *)k + (long)(&_exectab-&_exec));

	dir.ll = 0;
	if ((flck = Lock((UBYTE *)arg, (long)ACCESS_READ)) && isfile(flck))
		goto found;
	if (flg == 0)
		return(-1);
	dir.lp = (long *) cli->cli_CommandDir;
	while (dir.lp) {
		dir.ll <<= 2;
		savdir = CurrentDir(dir.flp[1]);
		flck = Lock((UBYTE *)arg, (long)ACCESS_READ);
		CurrentDir(savdir);
		if (flck && isfile(flck)) {
			dir.fl = DupLock(dir.flp[1]);
			goto found;
		}
		dir.ll = *dir.lp;
	}
	dir.fl = Lock((UBYTE *)"c:", (long)ACCESS_READ);
	savdir = CurrentDir(dir.fl);
	flck = Lock((UBYTE *)arg, (long)ACCESS_READ);
	CurrentDir(savdir);
	if (flck && isfile(flck))
		goto found;
	return(-1);
found:
	UnLock(flck);

	cp = (char *)(ex + 1);
	strcpy(cp, " ");
	for (ap=argv+1;*ap;ap++) {
		strcat(cp, *ap);
		strcat(cp, " ");
	}
	strcat(cp, "\r");

	ex->dosbase = DOSBase;
	ex->seglist = cli->cli_Module;
	ex->stack = (long *)_savsp+1;
	l = ex->stack - 1;
	ex->savret = *l;
	*l = (long)(k + 2);
	ex->cliseg = &cli->cli_Module;
	ex->cliseg2 = bcpl;
	ex->cmdlen = strlen(cp);
	ex->cmdstr = cp;
	cp = (char *)((long)cli->cli_CommandName<<2);
	*cp++ = strlen(arg);
	strcpy(cp, arg);
	ex->cmdnam = cp;
	ex->dirlck = dir.ll;
	exit(0);
	return(0);
}

#asm
_LVOCurrentDir	equ	-126
_LVOUnLock		equ	-90
_LVOUnLoadSeg	equ	-156
_LVOLoadSeg		equ	-150
_LVOExit		equ	-144
_LVOPermit		equ	-138
_LVOForbid		equ	-132

	public	__exec
__exec
	dc.l	0					;len of segment
	dc.l	0					;pointer to next segment
	move.l	stack(pc),sp		;get a good stack location
	move.l	savret(pc),-(sp)	;set up for real return
	move.l	seglist(pc),d1		;get seglist of current program
	move.l	dosbase(pc),a6		;get pointer to library
	jsr		_LVOUnLoadSeg(a6)	;unload the program

	pea		-1					;push a -1 for no dir
	move.l	dirlck(pc),d1		;get lock for program directory
	beq		1$					;must be in current dir
	jsr		_LVOCurrentDir(a6)	;set to current dir
	move.l	d0,(sp)				;save old current dir
1$
	move.l	cmdnam(pc),d1		;get pointer to cmd name
	jsr		_LVOLoadSeg(a6)		;load the new program
	move.l	(sp)+,d1			;get current dir back
	bmi		3$					;if high bit set on BPTR, no dir
	move.l	d0,-(sp)			;save segment list
	jsr		_LVOCurrentDir(a6)	;put back the right current dir
	move.l	d0,d1
	jsr		_LVOUnLock(a6)		;get rid of the Lock on the program dir
	move.l	(sp)+,d0			;get back segment list
3$
	tst.l	d0					;check on load
	bne		2$					;skip if loaded okay
	jsr		fixlist				;add us to the seglist
	move.l	#1,d0				;do exit(1)
	move.l	stack(pc),a1		;get stack ptr
	sub.w	#4,a1				;point at return address
	move.l	a1,sp				;set up stack
	rts							;and return to real caller

2$
	jsr		fixlist
	move.l	cmdlen(pc),d0		;set up for program call
	move.l	cmdstr(pc),a0
	jmp		4(a1)				;and transfer to program

fixlist
	move.l	d0,-(sp)			;save our segment list
	move.l	4,a6				;get ExecBase
	jsr		_LVOForbid(a6)		;only one walker at a time
	move.l	(sp)+,d0
	move.l	cliseg(pc),a0		;pointer to CLI segment list
	move.l	d0,(a0)				;point CLI at new segment
fix1
	move.l	(a0),d0				;get chain to next
	beq		fix2				;at end, break out of loop
	lsl.l	#2,d0				;convert BPTR to real address
	move.l	d0,a0				;copy to a0
	bra		fix1				;and loop
fix2
	lea		__exec+4(pc),a2		;pointer to this segment
	move.l	a2,d0				;copy to d0
	lsr.l	#2,d0				;convert to BPTR
	move.l	d0,(a0)				;add us to list
	move.l	cliseg(pc),a0		;pointer to CLI segment list
	move.l	(a0),d0				;first hunk
	move.l	cliseg2(pc),a1		;pointer to BCPL copy of segment list
	move.l	a1,d1				;check for zero
	beq		1$					;skip if 1.2
	move.l	d0,(a1)				;point at new segment
1$
	lsl.l	#2,d0				;convert BPTR to real address
	move.l	d0,-(sp)			;save
	jsr		_LVOPermit(a6)		;turn on multi-tasking again
	move.l	(sp)+,a1			;save in a1 for jump
	rts

	public	__exectab
__exectab:

dosbase	dc.l	0				;address of DOS library
seglist	dc.l	0				;BPTR to seglist of current program
stack	dc.l	0				;Ptr to return address
savret	dc.l	0				;place to save real return address
cliseg	dc.l	0				;pointer to cli seg list
cliseg2	dc.l	0				;pointer to bcpl seg list
cmdlen	dc.l	0				;length of command string
cmdstr	dc.l	0				;pointer to command string
cmdnam	dc.l	0				;pointer to program name
dirlck	dc.l	0				;lock on program directory if non-zero

#endasm

