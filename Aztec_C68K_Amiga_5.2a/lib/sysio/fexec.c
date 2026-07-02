/* Copyright (C) 1986,1987 by Manx Software Systems, Inc. */

#include <exec/types.h>
#include <exec/tasks.h>
#include <libraries/dosextens.h>
#include <functions.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

static long ret_val;
long _doexec(long len, ...);
int fexecv(char *cmd, char **argv);

int
wait(void)
{
	return(ret_val);
}

int
fexecl(char *file, ...)
{
	va_list varg;

	va_start(varg, file);
	return(fexecv(file, (char **)varg));
}

int
fexecv(char *cmd, char **argv)
{
	register struct CommandLineInterface *cli;
	struct Process *pp;
	struct FileHandle *fhp;
	APTR sav_ret;
	register char **ap, *cp, *arg;
	long len, seg, stksiz, sav;
	struct Library *savlib;
	BPTR savdir;
	char buf[40];
	long *bcpl;
	union {
		long *lp;
		long ll;
		BPTR fl;
		BPTR *flp;
	} l, stk;
	long oldcin, oldcout;
	extern long _savsp;

	pp = (struct Process *)FindTask(0);
	if ((cli = (struct CommandLineInterface *)((long)pp->pr_CLI << 2)) == 0) {
		return(-1);
	}
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
	if (seg = LoadSeg((UBYTE *)cmd))
		goto found;
	l.lp = (long *) cli->cli_CommandDir;
	while (l.ll) {
		l.ll <<= 2;
		savdir = CurrentDir(l.flp[1]);
		seg = LoadSeg((UBYTE *)cmd);
		CurrentDir(savdir);
		if (seg)
			goto found;
		l.ll = *l.lp;
	}
	strcpy(buf, "c:");
	strcat(buf, cmd);
	if (seg = LoadSeg((UBYTE *)buf))
		goto found;
	return(-1);
found:
	stksiz = 4 * cli->cli_DefaultStack;
	if ((stk.lp = AllocMem(stksiz+8, 0L)) == 0) {
		UnLoadSeg(seg);
		return(-1);
	}
	for (len=1,ap=argv+1;*ap;ap++)
		len += strlen(*ap) + 1;
	if ((cp = arg = AllocMem(len, 0L)) == 0) {
		UnLoadSeg(seg);
		FreeMem(stk.lp, stksiz+8);
		return(-1);
	}
	*stk.lp = stksiz + 8;
	stk.ll += stksiz;
	stk.lp[0] = stksiz;
	stk.lp[1] = ((long *)_savsp)[2];
	sav_ret = pp->pr_ReturnAddr;
	pp->pr_ReturnAddr = (APTR) stk.lp;

	sav = cli->cli_Module;
	cli->cli_Module = seg;
	if (bcpl)
		*bcpl = seg;

	for (ap=argv+1;*ap;ap++) {
		strcpy(cp, *ap);
		strcat(cp, " ");
		cp += strlen(cp);
	}
	arg[len-1] = '\n';

	cp = (char *)((long)cli->cli_CommandName << 2);
	memmove(buf, cp, (size_t)40);
	strcpy(cp+1, cmd);
	cp[0] = strlen(cmd);

	fhp = (struct FileHandle *)(pp->pr_CIS << 2);
	strncpy((char *)(fhp->fh_Buf<<2), arg, (size_t)(len < 200?len:199));
	fhp->fh_Pos = 0;
	fhp->fh_End = len < 200?len:199;
	oldcin = pp->pr_CIS;
	oldcout = pp->pr_COS;   	

	ret_val = _doexec(len, stksiz, stksiz+8, len, arg, (seg+1)<<2, stk.ll);

	pp->pr_CIS =  oldcin;
	pp->pr_COS =  oldcout;   	
	fhp->fh_Pos = fhp->fh_End;
/*	UnLoadSeg(cli->cli_Module);			now done in doexec jgII 6/17/88 */
	pp->pr_ReturnAddr = sav_ret;
	cli->cli_Module = sav;
	if (bcpl)
		*bcpl = sav;
	FreeMem(arg, len);
	memmove(cp, buf, (size_t)40);
	return(0);
}

long _mysp;

#asm
	xref	_geta4
	xdef	__doexec
__doexec:
	link	a5,#0
	movem.l	d1/a6,-(sp)
	movem.l	d2-d7/a2-a5,-(sp)		;save registers *jd 5/9/91 save d2 too
	move.l	sp,__mysp				;save our sp
	movem.l	8(a5),d0/d2/d3/d4/a0/a4/a7	;load params
	move.l	4(sp),a3				;get old sp from CLI
	movem.l	4(a3),a1/a2/a5/a6		;get BCPL environment
	move.l	d0,12(a1)				;set length
	move.l	a0,d1					;copy to dreg
	lsr.l	#2,d1					;convert to BPTR
	move.l	d1,8(a1)				;set ptr
	move.l	a0,d1					;copy to d1 as well
	jsr		(a4)					;call new program

	move.l	4,a6					;get ExecBase
	move.l	d0,d6					;save return value
	lea		dos_name,a1				;get DOS name
	jsr		-408(a6)				;call OpenLibrary
	move.l	d0,d7					;save DOSBase
	move.l	$114(a6),a0				;get task
	move.l	$ac(a0),a0				;get cli
	add.l	a0,a0
	add.l	a0,a0					;convert from BPTR
	move.l	$3c(a0),d1				;get cli->cli_module
	move.l	d7,a6					;get DOSBase
	jsr		-156(a6)				;UnLoadseg
	move.l	a6,a1					;copy DOSBase for closing
	move.l	$4,a6					;get ExecBase
	jsr		-414(a6)				;CloseLibrary

	movem.l	(sp)+,d2/d3				;get stk siz and old sp
	move.l	d2,d1					;get stk size to d1 *jd 5/9/91
	move.l	sp,a1					;save current sp
	jsr		(_geta4).l				;get a4
	move.l	__mysp,sp				;get back our sp
	move.l	d6,d0					;get back return code
	movem.l	(sp)+,d2-d7/a2-a5		;get back registers *jd and d2 too
	move.l	d0,-(sp)				;save return code
	sub.l	d1,a1					;back up a bit *jd 5/9/91 use d1 not d2
	sub.l	#8,a1					;back up over header
	move.l	(a1),d0					;get size to free
	move.l	4,a6					;get ExecBase
	jsr		-210(a6)				;free the memory
	move.l	(sp)+,d0				;get the return code
	movem.l	(sp)+,d1/a6				;*jd 5/9/91 restore d1 not d2
	unlk	a5
	rts

	cseg
dos_name:
	dc.b	'dos.library',0
#endasm

