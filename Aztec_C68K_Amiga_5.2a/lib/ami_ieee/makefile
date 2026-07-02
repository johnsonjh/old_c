CC=cc
AS=as
CFLAGS=
AFLAGS=
O=oss

.c.$O:
	$(CC) -o $@ $(CFLAGS) $*.c
.a68.$O:
	$(AS) -o $@ $(AFLAGS) $*.a68
.asm.$O:
	$(AS) -o $@ $(AFLAGS) $*.asm

MLIB=\
	fmod.$O \
	fabs.$O frexp.$O \
	ldexp.$O math.$O modf.$O pabs.$O padd.$O \
	pcmp.$O pdiv.$O pfix.$O pflt.$O pmul.$O \
	pneg.$O psub.$O ptst.$O lvoieee.$O ceil.$O \
	floor.$O floats.$O \
	atan2.$O random.$O \
	acos.$O asin.$O atan.$O cos.$O cosh.$O\
	dtof.$O exp.$O ftod.$O log.$O log10.$O\
	lvotrans.$O pow.$O sin.$O sinh.$O sqrt.$O\
	tan.$O tanh.$O trans.$O

malib:	$(MLIB)

arc:
	-delete /src/ami_ieee.lzh
	lharc a /src/ami_ieee.lzh makefile #?.c #?.a68
