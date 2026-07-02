# arp.lib and a.lib makefile

CFLAGS=-m0b -pc -sbo -wdepru
AFLAGS=
TARGET=/lib/


all: ss ls sl ll

ss:
    make lib L=16  O=oss B=s \
	"CFLAGS=$(CFLAGS) -ps" \
	"AFLAGS=$(AFLAGS)" \
	"NOTE=small code/data, 16 bit ints"

ls:
    make lib L=    O=ols B=s \
	"CFLAGS=$(CFLAGS) -pl" \
	"AFLAGS=$(AFLAGS) -eINT32" \
	"NOTE=small code/data, 32 bit ints"

sl:
    make lib L=16l O=osl B=l \
	"CFLAGS=$(CFLAGS) -mcd -ps" \
	"AFLAGS=$(AFLAGS) -cd" \
	"NOTE=large code/data, 16 bit ints"

ll:
    make lib L=l   O=oll B=l \
	"CFLAGS=$(CFLAGS) -mcd -pl" \
	"AFLAGS=$(AFLAGS) -cd -eINT32" \
	"NOTE=large code/data, 32 bit ints"


# variable bits

O=oss
L=16
B=s

# CFLAGS:
# -m0b - turns of .begin
# -pc  - permits extra characters after #ifdef, etc
# -sb  -
# -so  -
# -wd  -
# -we  - turn warnings into errors
# -wp  - complain about functions w/o prototypes
# -wu  -


# object module suffix: .o[IntSize][Model]

.c.$O:
	cc $(CFLAGS) -o $@ $*.c

.asm.$O:
	as $(AFLAGS) -o $@ $*.asm

.fd.ls:
	bind -rAztec -o$@ $*.fd

.fd.ll:
	bind -rAztecL -o$@ $*.fd


# a.lib - arp function glue (no startup code)

A_LIB=sprintf.$O fprintf.$O printf.$O tracker.$O toupper.$O arp_lib.l$B


# arp.lib - arp function glue, arp-ified c.lib functions, and startup code

ARP_LIB=\
scdir.$O dospkt.$O fmalloc.$O crt0.$O _main.$O cliparse.$O clitemp.$O \
clihelp.$O exit.$O _exit.$O vars.$O $(A_LIB)


lib: $(TARGET)arp$L.lib $(TARGET)a$L.lib $(TARGET)gads.$O $(TARGET)arpdetach.$O

$(TARGET)arp$L.lib: $(ARP_LIB)
	lb $@ $(ARP_LIB)
	@filenote $@ "full arp.  $(NOTE)"

$(TARGET)a$L.lib: $(A_LIB)
	lb $@ $(A_LIB)
	@filenote $@ "arp glue only.  $(NOTE)"


# special compilation

$(TARGET)gads.$O: gads.c
	cc $(CFLAGS) -o $@ gads.c
	@filenote $@ "GADS() version of _cli_parse().  $(NOTE)"

$(TARGET)arpdetach.$O: _main.c
	cc $(CFLAGS) -DDETACH -o $@ _main.c
	@filenote $@ "arp version of detach.$O.  $(NOTE)"

