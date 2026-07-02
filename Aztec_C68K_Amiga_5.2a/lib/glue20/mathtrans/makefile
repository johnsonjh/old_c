CC=cc
AS=as
CFLAGS=
AFLAGS=
O=oss

.a68.$O:
	$(AS) -o $@ $(AFLAGS) $*.a68

CLIB=\
	SPAcos.$O SPAsin.$O SPAtan.$O SPCos.$O SPCosh.$O \
	SPExp.$O SPFieee.$O SPLog.$O SPLog10.$O SPPow.$O \
	SPSin.$O SPSincos.$O SPSinh.$O SPSqrt.$O SPTan.$O \
	SPTanh.$O SPTieee.$O

clib:	$(CLIB)

