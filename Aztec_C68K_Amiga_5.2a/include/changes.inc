3/12/91: jd
	no registers specified for RawDoFmt() in pragmas.h
4/5/91 SCR 9: jd
	can't use a5 for reg args, so have to use glue routines for
	exec/alert, graphics/LockLayerRom, graphics/UnlockLayerRom,
	and graphics/AttemptLockLayerRom. Remove their pragmas from pragmas.h

9/3/91 
	changed amicall pragmas and function prototypes for Debug() and
	OpenResource() in the 1.3-compatible pragmas.h and functions.h
	to say that Debug takes an unsigned long in D0
	and OpenResource takes an unsigned char * in A1.

9/12/91
	added a #define TIME_MCH2AZTEC to time.h and stat.h for converting
	system time to time_t format. For example, to print out a file's
	time as returned by stat(), you can pass 
		TIME_MCH2AZTEC + st_mtime 
	to ctime().

9/24/91	ctype.h
	_toupper and _tolower macros were wrong

9/24/91 fcntl.h
	prototypes for fexecl() and execl() were wrong

	added prototypes for amisup/kputchar, amisup/kgetchar, amisup/cmpstr
		functions (debug.lib equivalents)

10/4/91 time.h
	changed CLOCKS_PER_SEC from 100 to 50 for Amiga
