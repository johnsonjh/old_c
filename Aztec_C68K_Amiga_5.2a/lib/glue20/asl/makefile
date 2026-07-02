CC=cc
AS=as
CFLAGS=
AFLAGS=
O=oss

.a68.$O:
	$(AS) -o $@ $(AFLAGS) $*.a68

CLIB=\
	AllocAsl.$O AllocFil.$O AslReque.$O \
	FreeAslR.$O FreeFile.$O RequestF.$O \
	AlloAslT.$O AslReqT.$O


clib:	$(CLIB)

