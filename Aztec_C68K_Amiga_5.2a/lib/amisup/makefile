CC=cc
AS=as
CFLAGS=
AFLAGS=
O=oss

.c.$O:
	$(CC) -o $@ $(CFLAGS) $*.c
.a68.$O:
	$(AS) -o $@ $(AFLAGS) $*.a68

ALIB=\
	address.$O beginio.$O fastrand.$O kcmpstr.$O kgetnum.$O \
	kputchar.$O \
	lvoasl.$O lvobclok.$O lvobmem.$O lvocia.$O lvoclist.$O \
	lvocommo.$O lvoconso.$O lvodiskf.$O lvodos.$O lvoexec.$O \
	lvoexpan.$O lvogadto.$O lvograph.$O lvoicon.$O lvoiffpa.$O \
	lvoinput.$O lvointui.$O lvokeyma.$O lvolayer.$O lvomatht.$O \
	lvomffp.$O lvomiedb.$O lvomiedt.$O lvomiesb.$O lvomiest.$O \
	lvomisc.$O lvopotgo.$O lvopotlu.$O lvoramdr.$O lvotimer.$O \
	lvotrans.$O lvoutili.$O lvowb.$O  \
	newlist.$O ableicr.$O addicrve.$O remicrve.$O \
	seticr.$O lvocia.$O allocunit.$O freeunit.$O getunit.$O \
	getunitid.$O giveunit.$O allocmisc.$O freemisc.$O execbase.$O


CLIB=\
	createex.$O createpo.$O createst.$O createta.$O \
	mareacir.$O mbndryof.$O mcend.$O mcinit.$O \
	mcmove.$O mcwait.$O mdrawcir.$O minitani.$O \
	mprintf.$O mrembob.$O msetafpt.$O msetdrpt.$O msetopen.$O \
	msetwrms.$O

clib:	$(ALIB) $(CLIB)

arc:
	-delete /src/amisup.lzh
	lharc a /src/amisup.lzh makefile #?.c #?.a68
