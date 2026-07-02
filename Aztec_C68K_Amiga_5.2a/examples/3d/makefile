CFLAGS= -ff -so -qv -pp -wc

.c.o:
        cc $(CFLAGS) -o $@ $*.c

all: cube test

test: test.o
        ln +Cd test.o -lmf -lc  

cube: cube.o
        ln +Cd cube.o -lmf -lc

