#CFLAGS=-so -wc -dLIBRARY_VERSION=34L -dUSE1_3
CFLAGS=-so -wc -dLIBRARY_VERSION=34L 
.asm.o16:
	as -o $*.o16 $*.asm

.c.o16:
	cc $(CFLAGS) -ps -o $*.o16 $*.c

.c.of32:
	cc $(CFLAGS) -pl -ff $*.c -o $*.of32

.c.o32:
	cc $(CFLAGS) -pl $*.c -o $*.o32

all: watchman closeme benchquake biomorph ing gadget glow moire oing

# The I's have it!
watchman: watchman.o16
	ln watchman.o16 -lc16

# Catch the errant window
closeme: closeme.o32
	ln closeme.o32 -lc

# a MUST for Californians
benchquake: benchquake.o32
	ln benchquake.o32 -lc

# If you like fractals....
biomorph: biomorph.of32
	ln +Cd biomorph.of32 -lmf -lc

# Bouncing windows.
ing: ing.o16 rnd.o16
	ln +Cd ing.o16 rnd.o16 -lm16 -lc16

# Gadgets, gadgets everywhere.
gadget: gadget.o16
	ln +Cd gadget.o16 -lc16

# Possessed screen colors.
glow: glow.o16 
	ln +Cd glow.o16 -lc16

# What collection would be complete w/ a moire-pattern generator?
moire: moire.o16
	ln +Cd moire.o16 -lm16 -lc16

# The old favorite.
oing: oing.o16
	ln +Cd oing.o16 -lc16

