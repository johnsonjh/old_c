CC=cc
AS=as
CFLAGS=
AFLAGS=
O=oss

.a68.$O:
	$(AS) -o $@ $(AFLAGS) $*.a68

CLIB=\
	AllocIFF.$O AllocLoc.$O CloseCli.$O CloseIFF.$O Collect1.$O  \
	Collecti.$O CurrentC.$O EntryHan.$O ExitHand.$O FindColl.$O  \
	FindLoca.$O FindPro1.$O FindProp.$O FreeIFF.$O FreeLoca.$O  \
	GoodID.$O GoodType.$O IDtoStr.$O InitIFF.$O InitIFF1.$O  \
	InitIFFa.$O LocalIte.$O OpenClip.$O OpenIFF.$O ParentCh.$O  \
	ParseIFF.$O PopChunk.$O PropChu1.$O PropChun.$O PushChun.$O  \
	ReadChu1.$O ReadChun.$O SetLocal.$O StopChu1.$O StopChun.$O  \
	StopOnEx.$O StoreIte.$O StoreLoc.$O WriteCh1.$O WriteChu.$O

clib:	$(CLIB)

