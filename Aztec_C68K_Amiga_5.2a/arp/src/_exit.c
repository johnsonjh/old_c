/* Created 11/08/87 by -=+SDB+=- from file provided by MANX */
/* Copyright (C) 1987 by Scott Ballantyne */
/* May be freely used by ARP supporters/users */
/* If somebody were to modify the libraries to use ARP tracking, this would
 * be even shorter (and so would the libraries)
 */

#include <libraries/arpbase.h>
#include <fcntl.h>
#include <functions.h>

extern int _argc;
extern char **_argv;
extern struct WBStartup *WBenchMsg;
extern void *MathBase, *MathTransBase;
extern void *MathIeeeDoubBasBase, *MathIeeeDoubTransBase;
extern void *_oldtrap, **_trapaddr;

void (*_cln)(void);

void _exit(int code)
{
	long ret = code;
	register int fd;

	if (_devtab) {
		for (fd = 0 ; fd < _numdev ; fd++)
			close(fd);
	}
	if (_cln)               /* needed to block loading 2 instances of _exit() if c.lib/malloc() gets loaded instead */
		(*_cln)();
#if 0	    /* is now Tracked */
	if (_detach_curdir)                             /* for DETACHed programs */
		UnLock(_detach_curdir);
#endif
	if (_trapaddr)                                  /* clean up signal handling */
		*_trapaddr = _oldtrap;
	if (MathTransBase)
		CloseLibrary(MathTransBase);
	if (MathBase)
		CloseLibrary(MathBase);
	if (MathIeeeDoubBasBase)
		CloseLibrary(MathIeeeDoubBasBase);
	if (MathIeeeDoubTransBase)
		CloseLibrary(MathIeeeDoubTransBase);
	{
#asm
	mc68881
	movem.l a5/a6,-(sp)
	move.l	4,a6				;get ExecBase
	btst.b	#4,$129(a6)                     ;check for 68881 flag in AttnFlags
	beq		1$					;skip if not
	lea		2$,a5
	jsr		-30(a6)                         ;do it in supervisor mode
	bra		1$
2$
	clr.l	-(sp)
	frestore (sp)+                          ;reset the ffp stuff
	rte							;and return
1$
	move.l	(sp)+,a5/a6
#endasm
	}
	if (WBenchMsg)
	{
		Forbid();
		ReplyMsg((struct Message *)WBenchMsg);
	}
	ArpExit( ret , 0L);     /* Exit, and free memory */
}
