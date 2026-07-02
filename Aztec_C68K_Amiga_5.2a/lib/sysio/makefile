CC=cc
AS=as
CFLAGS=
AFLAGS=
O=oss

.c.$O:
	$(CC) -o $@ $(CFLAGS) $*.c
.a68.$O:
	$(AS) -o $@ $(AFLAGS) $*.a68

CLIB=\
	_main.$O _abort.$O _access.$O access.$O crt0.$O exec.$O fexec.$O\
	_open.$O open.$O _close.$O close.$O _read.$O read.$O _write.$O write.$O\
	_lseek.$O lseek.$O _ioctl.$O ioctl.$O _isatty.$O isatty.$O\
	setenv.$O _rename.$O stat.$O stkchk.$O stkover.$O\
	_unlink.$O unlink.$O segload.$O freeseg.$O dospkt.$O setcon.$O\
	_exit.$O chkabort.$O intman.$O cliparse.$O\
	wbparse.$O vars.$O detach.$O scdir.$O chdir.$O \
	getcwd.$O mkdir.$O mktemp.$O

clib:	$(CLIB)

detach.$O:	_main.c
	$(CC) -o $@ -DDETACH $(CFLAGS) _main.c
	-copy $@ /libs

arc:
	-delete /src/sysio.lzh
	lharc a /src/sysio.lzh makefile #?.c #?.a68
