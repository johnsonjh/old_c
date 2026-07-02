N=
TARG=clib
CC=qcc
CFLAGS=-WPDLE -SO -M0B
AFLAGS=
O=oss
LIB=

warn:
	@echo "usage: make [a | al]"

final: liba

final16: liba

clib:
	cd asl
	make $N CC=$(CC) "CFLAGS=$(CFLAGS)" "AFLAGS=$(AFLAGS)" O=$O $(TARG)
	cd /battclock
	make $N CC=$(CC) "CFLAGS=$(CFLAGS)" "AFLAGS=$(AFLAGS)" O=$O $(TARG)
	cd /battmem
	make $N CC=$(CC) "CFLAGS=$(CFLAGS)" "AFLAGS=$(AFLAGS)" O=$O $(TARG)
	cd /commodities
	make $N CC=$(CC) "CFLAGS=$(CFLAGS)" "AFLAGS=$(AFLAGS)" O=$O $(TARG)
	cd /console
	make $N CC=$(CC) "CFLAGS=$(CFLAGS)" "AFLAGS=$(AFLAGS)" O=$O $(TARG)
	cd /diskfont
	make $N CC=$(CC) "CFLAGS=$(CFLAGS)" "AFLAGS=$(AFLAGS)" O=$O $(TARG)
	cd /dos
	make $N CC=$(CC) "CFLAGS=$(CFLAGS)" "AFLAGS=$(AFLAGS)" O=$O $(TARG)
	cd /exec
	make $N CC=$(CC) "CFLAGS=$(CFLAGS)" "AFLAGS=$(AFLAGS)" O=$O $(TARG)
	cd /expansion
	make $N CC=$(CC) "CFLAGS=$(CFLAGS)" "AFLAGS=$(AFLAGS)" O=$O $(TARG)
	cd /gadtools
	make $N CC=$(CC) "CFLAGS=$(CFLAGS)" "AFLAGS=$(AFLAGS)" O=$O $(TARG)
	cd /graphics
	make $N CC=$(CC) "CFLAGS=$(CFLAGS)" "AFLAGS=$(AFLAGS)" O=$O $(TARG)
	cd /icon
	make $N CC=$(CC) "CFLAGS=$(CFLAGS)" "AFLAGS=$(AFLAGS)" O=$O $(TARG)
	cd /iffparse
	make $N CC=$(CC) "CFLAGS=$(CFLAGS)" "AFLAGS=$(AFLAGS)" O=$O $(TARG)
	cd /input
	make $N CC=$(CC) "CFLAGS=$(CFLAGS)" "AFLAGS=$(AFLAGS)" O=$O $(TARG)
	cd /intuition
	make $N CC=$(CC) "CFLAGS=$(CFLAGS)" "AFLAGS=$(AFLAGS)" O=$O $(TARG)
	cd /keymap
	make $N CC=$(CC) "CFLAGS=$(CFLAGS)" "AFLAGS=$(AFLAGS)" O=$O $(TARG)
	cd /layers
	make $N CC=$(CC) "CFLAGS=$(CFLAGS)" "AFLAGS=$(AFLAGS)" O=$O $(TARG)
	cd /mathffp
	make $N CC=$(CC) "CFLAGS=$(CFLAGS)" "AFLAGS=$(AFLAGS)" O=$O $(TARG)
	cd /mathieeedoubbas
	make $N CC=$(CC) "CFLAGS=$(CFLAGS)" "AFLAGS=$(AFLAGS)" O=$O $(TARG)
	cd /mathieeedoubtrans
	make $N CC=$(CC) "CFLAGS=$(CFLAGS)" "AFLAGS=$(AFLAGS)" O=$O $(TARG)
	cd /mathieeesingbas
	make $N CC=$(CC) "CFLAGS=$(CFLAGS)" "AFLAGS=$(AFLAGS)" O=$O $(TARG)
	cd /mathieeesingtrans
	make $N CC=$(CC) "CFLAGS=$(CFLAGS)" "AFLAGS=$(AFLAGS)" O=$O $(TARG)
	cd /mathtrans
	make $N CC=$(CC) "CFLAGS=$(CFLAGS)" "AFLAGS=$(AFLAGS)" O=$O $(TARG)
	cd /misc
	make $N CC=$(CC) "CFLAGS=$(CFLAGS)" "AFLAGS=$(AFLAGS)" O=$O $(TARG)
	cd /potgo
	make $N CC=$(CC) "CFLAGS=$(CFLAGS)" "AFLAGS=$(AFLAGS)" O=$O $(TARG)
	cd /ramdrive
	make $N CC=$(CC) "CFLAGS=$(CFLAGS)" "AFLAGS=$(AFLAGS)" O=$O $(TARG)
	cd /timer
	make $N CC=$(CC) "CFLAGS=$(CFLAGS)" "AFLAGS=$(AFLAGS)" O=$O $(TARG)
	cd /translator
	make $N CC=$(CC) "CFLAGS=$(CFLAGS)" "AFLAGS=$(AFLAGS)" O=$O $(TARG)
	cd /utility
	make $N CC=$(CC) "CFLAGS=$(CFLAGS)" "AFLAGS=$(AFLAGS)" O=$O $(TARG)
	cd /wb
	make $N CC=$(CC) "CFLAGS=$(CFLAGS)" "AFLAGS=$(AFLAGS)" O=$O $(TARG)
	cd /
#	rm $(LIB).out
#	make $N LIB=$(LIB) libs

aclean:
	cd console
	rm #?.$O quiet
	cd /diskfont
	rm #?.$O quiet
	cd /dos
	rm #?.$O quiet
	cd /exec
	rm #?.$O quiet
	cd /expansion
	rm #?.$O quiet
	cd /graphics
	rm #?.$O quiet
	cd /icon
	rm #?.$O quiet
	cd /intuition
	rm #?.$O quiet
	cd /layers
	rm #?.$O quiet
	cd /potgo
	rm #?.$O quiet
	cd /romboot
	rm #?.$O quiet
	cd /timer
	rm #?.$O quiet
	cd /translator
	rm #?.$O quiet
	cd /

all:	liba

liba:		ass asll

asll:
	make LIB=al   CC=cc TARG=clib O=osl "CFLAGS=$(CFLAGS) -MCD" \
										 AFLAGS=-CD clib
ass:
	make LIB=a    CC=cc TARG=clib O=oss "CFLAGS=$(CFLAGS) -PS" \
										 AFLAGS= clib

all_clean:	a_clean

clean16:	assclean

a_clean:	assclean alsclean

assclean:
	make O=oss aclean
alsclean:
	make O=osl aclean

INSTALL=/libs/

.inp.out:
	ord $*.inp $*.out

libs:	$(LIB)

$(LIB):	$(LIB).out
	lb v:$(LIB).lib -f $(LIB).out
	cp v:$(LIB).lib $(LIB).lib
	rm v:$(LIB).lib $(INSTALL)$(LIB).lib
	mv $(LIB).lib $(INSTALL)$(LIB).lib

arc:
	-delete /src/glue20.lzh
	lharc -r -x a /src/glue20.lzh makefile #?.a68
