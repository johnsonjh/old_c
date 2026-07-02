CC=cc
AS=as
CFLAGS=
AFLAGS=
O=oss

.a68.$O:
	$(AS) -o $@ $(AFLAGS) $*.a68

CLIB=\
	Allocate.$O Amiga2Da.$O CallHook.$O CheckDat.$O CloneTag.$O \
	Date2Ami.$O FilterT1.$O FilterTa.$O FindTagI.$O FreeTagI.$O \
	GetTagDa.$O MapTags.$O NextTagI.$O PackBool.$O RefreshT.$O \
	SDivMod3.$O SMult32.$O TagInArr.$O UDivMod3.$O UMult32.$O \
	Stricmp.$O Strnicmp.$O ToUpper.$O ToLower.$O

clib:	$(CLIB)

