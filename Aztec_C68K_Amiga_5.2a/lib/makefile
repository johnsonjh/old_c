N=
TARG=clib
CC=cc
CFLAGS=-WPDLE -SO -M0B
AFLAGS=
O=oss

warn:
	@echo "usage: make [css | cls | csl | cll | mss |..| mfss |..| mass |..| m8ss]"

all:	c m ma mf m8 s

#
# make all c libraries:
#
c:		css cls csl cll
# make c16.lib:
css:
	make LIB=c16  CC=cc TARG=clib O=oss "CFLAGS=$(CFLAGS) -PS" \
										 AFLAGS= clib
# make c.lib:
cls:
	make LIB=c    CC=cc TARG=clib O=ols "CFLAGS=$(CFLAGS) -PL" \
										 AFLAGS=-EINT32 clib
# make cl16.lib:
csl:
	make LIB=cl16 CC=cc TARG=clib O=osl "CFLAGS=$(CFLAGS) -PS -MCD" \
										 AFLAGS=-CD clib
# make cl.lib:
cll:
	make LIB=cl   CC=cc TARG=clib O=oll "CFLAGS=$(CFLAGS) -PL -MCD" \
										"AFLAGS=-EINT32 -CD" clib
#
# make all Amiga ffp libraries:
#
mf:	mfss mfls mfsl mfll
# make mf16.lib:
mfss:
	make LIB=mf16  CC=cc TARG=mflib O=fss \
			"CFLAGS=$(CFLAGS) -D_FLT_FFP -FF -PS" AFLAGS= mflib
# make mf.lib:
mfls:
	make LIB=mf    CC=cc TARG=mflib O=fls \
			"CFLAGS=$(CFLAGS) -D_FLT_FFP -FF -PL" AFLAGS=-EINT32 mflib
# make mfl16.lib:
mfsl:
	make LIB=mfl16 CC=cc TARG=mflib O=fsl \
			"CFLAGS=$(CFLAGS) -D_FLT_FFP -FF -MCD -PS" AFLAGS=-CD mflib
# make mfl.lib:
mfll:
	make LIB=mfl   CC=cc TARG=mflib O=fll \
		"CFLAGS=$(CFLAGS) -D_FLT_FFP -FF -MCD -PL" "AFLAGS=-CD -EINT32" mflib

#
# make all Manx IEEE math libraries:
#
m:		mss mls msl mll
# make m16.lib:
mss:
	make LIB=m16   CC=cc TARG=mlib O=mss \
			"CFLAGS=$(CFLAGS) -D_FLT_MANX -FM -PS" AFLAGS= mlib
# make m.lib:
mls:
	make LIB=m     CC=cc TARG=mlib O=mls \
			"CFLAGS=$(CFLAGS) -D_FLT_MANX -FM -PL" AFLAGS=-EINT32 mlib
# make ml16.lib:
msl:
	make LIB=ml16  CC=cc TARG=mlib O=msl \
			"CFLAGS=$(CFLAGS) -D_FLT_MANX -FM -MCD -PS" AFLAGS=-CD mlib
# make ml.lib:
mll:
	make LIB=ml    CC=cc TARG=mlib O=mll \
		"CFLAGS=$(CFLAGS) -D_FLT_MANX -FM -MCD -PL" "AFLAGS=-CD -EINT32" mlib

#
# make all Amiga IEEE math libraries:
#
ma:	mass mals masl mall
# make ma16.lib:
mass:
	make LIB=ma16  CC=cc TARG=malib O=ass \
			"CFLAGS=$(CFLAGS) -D_FLT_AMIGA -FA -PS" AFLAGS= malib
# make ma.lib:
mals:
	make LIB=ma    CC=cc TARG=malib O=als \
			"CFLAGS=$(CFLAGS) -D_FLT_AMIGA -FA -PL" AFLAGS=-EINT32 malib
# make mal16.lib:
masl:
	make LIB=mal16 CC=cc TARG=malib O=asl \
			"CFLAGS=$(CFLAGS) -D_FLT_AMIGA -FA -MCD -PS" AFLAGS=-CD malib
# make mal.lib:
mall:
	make LIB=mal   CC=cc TARG=malib O=all \
		"CFLAGS=$(CFLAGS) -D_FLT_AMIGA -FA -MCD -PL" \
		"AFLAGS=-CD -EINT32" malib

#
# make all 68881 math libraries:
#
m8:	m8ss m8ls m8sl m8ll
# make m816.lib:
m8ss:
	make LIB=m816  CC=cc TARG=m8lib O=8ss \
			"CFLAGS=$(CFLAGS) -D_FLT_881 -F8 -PS" AFLAGS= m8lib
# make m8.lib:
m8ls:
	make LIB=m8    CC=cc TARG=m8lib O=8ls \
			"CFLAGS=$(CFLAGS) -D_FLT_881 -F8 -PL" AFLAGS=-EINT32 m8lib
# make m8l16.lib:
m8sl:
	make LIB=m8l16 CC=cc TARG=m8lib O=8sl \
			"CFLAGS=$(CFLAGS) -D_FLT_881 -F8 -MCD -PS" AFLAGS=-CD m8lib
# make m8l.lib:
m8ll:
	make LIB=m8l   CC=cc TARG=m8lib O=8ll \
		"CFLAGS=$(CFLAGS) -D_FLT_881 -F8 -MCD -PL" "AFLAGS=-CD -EINT32" m8lib

#
# make all screen libraries:
#
s:		sss sls ssl sll
# make s16.lib:
sss:
	make LIB=s16  CC=cc TARG=clib O=oss "CFLAGS=$(CFLAGS) -PS" \
										 AFLAGS= scrlib
# make s.lib:
sls:
	make LIB=s    CC=cc TARG=clib O=ols "CFLAGS=$(CFLAGS) -PL" \
										 AFLAGS=-EINT32 scrlib
# make sl16.lib:
ssl:
	make LIB=sl16 CC=cc TARG=clib O=osl "CFLAGS=$(CFLAGS) -PS -MCD" \
										 AFLAGS=-CD scrlib
# make sl.lib:
sll:
	make LIB=sl   CC=cc TARG=clib O=oll "CFLAGS=$(CFLAGS) -PL -MCD" \
										"AFLAGS=-EINT32 -CD" scrlib

###########################################################################
#
# The following are called when make invokes a second copy of itself.
# you normally shouldn't try to directly make any of these
#
amilib:
	cd cia
	make $N CC=$(CC) "CFLAGS=$(CFLAGS)" "AFLAGS=$(AFLAGS)" O=$O $(TARG)
	cd /clist
	make $N CC=$(CC) "CFLAGS=$(CFLAGS)" "AFLAGS=$(AFLAGS)" O=$O $(TARG)
	cd /debug
	make $N CC=$(CC) "CFLAGS=$(CFLAGS)" "AFLAGS=$(AFLAGS)" O=$O $(TARG)
	cd /dos
	make $N CC=$(CC) "CFLAGS=$(CFLAGS)" "AFLAGS=$(AFLAGS)" O=$O $(TARG)
	cd /exec
	make $N CC=$(CC) "CFLAGS=$(CFLAGS)" "AFLAGS=$(AFLAGS)" O=$O $(TARG)
	cd /expand
	make $N CC=$(CC) "CFLAGS=$(CFLAGS)" "AFLAGS=$(AFLAGS)" O=$O $(TARG)
	cd /graphics
	make $N CC=$(CC) "CFLAGS=$(CFLAGS)" "AFLAGS=$(AFLAGS)" O=$O $(TARG)
	cd /icon
	make $N CC=$(CC) "CFLAGS=$(CFLAGS)" "AFLAGS=$(AFLAGS)" O=$O $(TARG)
	cd /intuit
	make $N CC=$(CC) "CFLAGS=$(CFLAGS)" "AFLAGS=$(AFLAGS)" O=$O $(TARG)
	cd /layers
	make $N CC=$(CC) "CFLAGS=$(CFLAGS)" "AFLAGS=$(AFLAGS)" O=$O $(TARG)
	cd /potluck
	make $N CC=$(CC) "CFLAGS=$(CFLAGS)" "AFLAGS=$(AFLAGS)" O=$O $(TARG)
	cd /

clib:
	cd amisup
	make $N CC=$(CC) "CFLAGS=$(CFLAGS)" "AFLAGS=$(AFLAGS)" O=$O $(TARG)
	cd /glue20
	make $N CC=$(CC) "CFLAGS=$(CFLAGS)" "AFLAGS=$(AFLAGS)" O=$O $(TARG)
	cd /misc
	make $N CC=$(CC) "CFLAGS=$(CFLAGS)" "AFLAGS=$(AFLAGS)" O=$O $(TARG)
	cd /stdio
	make $N CC=$(CC) "CFLAGS=$(CFLAGS)" "AFLAGS=$(AFLAGS)" O=$O $(TARG)
	cd /stdlib
	make $N CC=$(CC) "CFLAGS=$(CFLAGS)" "AFLAGS=$(AFLAGS)" O=$O $(TARG)
	cd /string
	make $N CC=$(CC) "CFLAGS=$(CFLAGS)" "AFLAGS=$(AFLAGS)" O=$O $(TARG)
	cd /sysio
	make $N CC=$(CC) "CFLAGS=$(CFLAGS)" "AFLAGS=$(AFLAGS)" O=$O $(TARG)
	cd /time
	make $N CC=$(CC) "CFLAGS=$(CFLAGS)" "AFLAGS=$(AFLAGS)" O=$O $(TARG)
	cd /inp
	-delete $(LIB).out
	make $N LIB=$(LIB)
	cd /

scrlib:
	cd scr
	make $N CC=$(CC) "CFLAGS=$(CFLAGS)" "AFLAGS=$(AFLAGS)" O=$O $(TARG)
	cd /inp
	-delete $(LIB).out
	make $N LIB=$(LIB)
	cd /

mflib:
	cd stdlib
	make $N CC=$(CC) "CFLAGS=$(CFLAGS)" "AFLAGS=$(AFLAGS)" O=$O $(TARG)
	cd /stdio
	make $N CC=$(CC) "CFLAGS=$(CFLAGS) -DFLOAT" "AFLAGS=$(AFLAGS)" O=$O $(TARG)
	cd /time
	make $N CC=$(CC) "CFLAGS=$(CFLAGS)" "AFLAGS=$(AFLAGS)" O=$O $(TARG)
	cd /ami_ffp
	make $N CC=$(CC) "CFLAGS=$(CFLAGS)" "AFLAGS=$(AFLAGS)" O=$O $(TARG)
	cd /inp
	-delete $(LIB).out
	make $N LIB=$(LIB)
	cd /

mlib:
	cd stdlib
	make $N CC=$(CC) "CFLAGS=$(CFLAGS)" "AFLAGS=$(AFLAGS)" O=$O $(TARG)
	cd /stdio
	make $N CC=$(CC) "CFLAGS=$(CFLAGS) -DFLOAT" "AFLAGS=$(AFLAGS)" O=$O $(TARG)
	cd /time
	make $N CC=$(CC) "CFLAGS=$(CFLAGS)" "AFLAGS=$(AFLAGS)" O=$O $(TARG)
	cd /mx_ieee
	make $N CC=$(CC) "CFLAGS=$(CFLAGS)" "AFLAGS=$(AFLAGS)" O=$O $(TARG)
	cd /inp
	-delete $(LIB).out
	make $N LIB=$(LIB)
	cd /

malib:
	cd stdlib
	make $N CC=$(CC) "CFLAGS=$(CFLAGS)" "AFLAGS=$(AFLAGS)" O=$O $(TARG)
	cd /stdio
	make $N CC=$(CC) "CFLAGS=$(CFLAGS) -DFLOAT" "AFLAGS=$(AFLAGS)" O=$O $(TARG)
	cd /time
	make $N CC=$(CC) "CFLAGS=$(CFLAGS)" "AFLAGS=$(AFLAGS)" O=$O $(TARG)
	cd /ami_ieee
	make $N CC=$(CC) "CFLAGS=$(CFLAGS)" "AFLAGS=$(AFLAGS)" O=$O $(TARG)
	cd /inp
	-delete $(LIB).out
	make $N LIB=$(LIB)
	cd /

m8lib:
	cd m881
	make $N CC=$(CC) "CFLAGS=$(CFLAGS)" "AFLAGS=$(AFLAGS)" O=$O $(TARG)
	cd /stdlib
	make $N CC=$(CC) "CFLAGS=$(CFLAGS)" "AFLAGS=$(AFLAGS)" O=$O $(TARG)
	cd /stdio
	make $N CC=$(CC) "CFLAGS=$(CFLAGS) -DFLOAT" "AFLAGS=$(AFLAGS)" O=$O $(TARG)
	cd /time
	make $N CC=$(CC) "CFLAGS=$(CFLAGS)" "AFLAGS=$(AFLAGS)" O=$O $(TARG)
	cd /inp
	-delete $(LIB).out
	make $N LIB=$(LIB)
	cd /

amiclean:
	cd cia
	-delete #?.$O quiet
	cd /clist
	-delete #?.$O quiet
	cd /debug
	-delete #?.$O quiet
	cd /dos
	-delete #?.$O quiet
	cd /exec
	-delete #?.$O quiet
	cd /expand
	-delete #?.$O quiet
	cd /graphics
	-delete #?.$O quiet
	cd /icon
	-delete #?.$O quiet
	cd /intuit
	-delete #?.$O quiet
	cd /layers
	-delete #?.$O quiet
	cd /potluck
	-delete #?.$O quiet
	cd /


cclean:
	-delete amisup/#?.$O quiet
	-delete misc/#?.$O quiet
	-delete stdio/#?.$O quiet
	-delete stdlib/#?.$O quiet
	-delete string/#?.$O quiet
	-delete sysio/#?.$O quiet
	-delete time/#?.$O quiet
	-delete glue20/asl/#?.$O quiet
	-delete glue20/battclock/#?.$O quiet
	-delete glue20/battmem/#?.$O quiet
	-delete glue20/commodities/#?.$O quiet
	-delete glue20/console/#?.$O quiet
	-delete glue20/diskfont/#?.$O quiet
	-delete glue20/dos/#?.$O quiet
	-delete glue20/exec/#?.$O quiet
	-delete glue20/expansion/#?.$O quiet
	-delete glue20/gadtools/#?.$O quiet
	-delete glue20/graphics/#?.$O quiet
	-delete glue20/icon/#?.$O quiet
	-delete glue20/iffparse/#?.$O quiet
	-delete glue20/input/#?.$O quiet
	-delete glue20/intuition/#?.$O quiet
	-delete glue20/keymap/#?.$O quiet
	-delete glue20/layers/#?.$O quiet
	-delete glue20/mathffp/#?.$O quiet
	-delete glue20/mathieeedoubbas/#?.$O quiet
	-delete glue20/mathieeedoubtrans/#?.$O quiet
	-delete glue20/mathieeesingbas/#?.$O quiet
	-delete glue20/mathsingtrans/#?.$O quiet
	-delete glue20/mathtrans/#?.$O quiet
	-delete glue20/misc/#?.$O quiet
	-delete glue20/potgo/#?.$O quiet
	-delete glue20/ramdrive/#?.$O quiet
	-delete glue20/timer/#?.$O quiet
	-delete glue20/translator/#?.$O quiet
	-delete glue20/utility/#?.$O quiet
	-delete glue20/wb/#?.$O quiet

sclean:
	-delete scr/#?.$O quiet

mclean:
	-delete mx_ieee/#?.$O quiet
	-delete stdlib/#?.$O quiet
	-delete stdio/#?.$O quiet
	-delete time/#?.$O quiet

mfclean:
	-delete ami_ffp/#?.$O quiet
	-delete stdlib/#?.$O quiet
	-delete stdio/#?.$O quiet
	-delete time/#?.$O quiet

maclean:
	-delete ami_ieee/#?.$O quiet
	-delete stdlib/#?.$O quiet
	-delete stdio/#?.$O quiet
	-delete time/#?.$O quiet

m8clean:
	-delete m881/#?.$O quiet
	-delete stdlib/#?.$O quiet
	-delete stdio/#?.$O quiet
	-delete time/#?.$O quiet
#
# end of dependencies for make re-invocations
#
############################################################################

#
# delete all object modules:
#
all_clean:	c_clean m_clean mf_clean ma_clean m8_clean s_clean
#
# delete all object modules for all c libraries:
#
c_clean:	cssclean clsclean cslclean cllclean

cssclean:
	make O=oss cclean
clsclean:
	make O=ols cclean
cslclean:
	make O=osl cclean
cllclean:
	make O=oll cclean
#
# delete all object modules for Manx IEEE math libraries:
#
m_clean:	mssclean mlsclean mslclean mllclean

mssclean:
	make O=mss mclean
mslclean:
	make O=msl mclean
mlsclean:
	make O=mls mclean
mllclean:
	make O=mll mclean

#
# delete all object modules for Amiga FFP math libraries
#
mf_clean:	mfssclean mflsclean mfslclean mfllclean

mfssclean:
	make O=fss mfclean
mflsclean:
	make O=fls mfclean
mfslclean:
	make O=fsl mfclean
mfllclean:
	make O=fll mfclean

#
# delete all object modules for Amiga IEEE math libraries
#
ma_clean:	massclean malsclean maslclean mallclean

massclean:
	make O=ass maclean
malsclean:
	make O=als maclean
maslclean:
	make O=asl maclean
mallclean:
	make O=all maclean

#
# delete all object modules for 68881 math libraries
#
m8_clean:	m8ssclean m8lsclean m8slclean m8llclean

m8ssclean:
	make O=8ss m8clean
m8lsclean:
	make O=8ls m8clean
m8slclean:
	make O=8sl m8clean
m8llclean:
	make O=8ll m8clean
#
# delete all object modules for screen libraries
#
s_clean:	sssclean slsclean sslclean sllclean

sssclean:
	make O=oss sclean
slsclean:
	make O=ols sclean
sslclean:
	make O=osl sclean
sllclean:
	make O=oll sclean
#
# create source archives
#
arc:
	cd ami_ffp
	make arc
	cd /ami_ieee
	make arc
	cd /amisup
	make arc
	cd /glue20
	make arc
	cd /inp
	make arc
	cd /m881
	make arc
	cd /misc
	make arc
	cd /mx_ieee
	make arc
	cd /scr
	make arc
	cd /stdio
	make arc
	cd /stdlib
	make arc
	cd /string
	make arc
	cd /sysio
	make arc
	cd /time
	make arc
	cd /
	-delete src/libsrc52.lzh
	lharc a src/libsrc52.lzh makefile changes.lib
