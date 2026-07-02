CC=cc
AS=as
CFLAGS=
AFLAGS=
O=oss

.a68.$O:
	$(AS) -o $@ $(AFLAGS) $*.a68

CLIB=\
	SPAbs.$O SPAdd.$O SPCeil.$O SPCmp.$O SPDiv.$O \
	SPFix.$O SPFloor.$O SPFlt.$O SPMul.$O SPNeg.$O \
	SPSub.$O SPTst.$O

clib:	$(CLIB)

