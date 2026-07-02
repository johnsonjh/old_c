CC=cc
AS=as
CFLAGS=
AFLAGS=
O=oss

.c.$O:
	$(CC) -o $@ $(CFLAGS) $*.c
.a68.$O:
	$(AS) -o $@ $(AFLAGS) $*.a68

MLIB=\
	floor.$O random.$O \
	acos.$O asin.$O atan.$O cos.$O \
	cosh.$O exp.$O fabs.$O fadd.$O fcmp.$O \
	fdiv.$O ffix.$O fflt.$O ffp.$O ffpabs.$O \
	fmul.$O fneg.$O fsub.$O ftst.$O log.$O \
	log10.$O lvo.$O math.$O modf.$O pow.$O \
	sin.$O sincos.$O sinh.$O sp.$O sqrt.$O \
	tan.$O tanh.$O tran.$O atan2.$O frexp.$O ldexp.$O

mflib:	$(MLIB)

arc:
	-delete /src/ami_ffp.lzh
	lharc a /src/ami_ffp.lzh makefile #?.c #?.a68
