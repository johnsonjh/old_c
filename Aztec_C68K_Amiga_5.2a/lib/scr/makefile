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
	beep.$O bs.$O cdelete.$O cinsert.$O clear.$O\
	cr.$O curs.$O cursrt.$O cursup.$O eol.$O\
	home.$O ldelete.$O lf.$O linsert.$O tab.$O

clib:	$(CLIB)

arc:
	-delete /src/scr.lzh
	lharc a /src/scr.lzh makefile #?.c #?.a68
