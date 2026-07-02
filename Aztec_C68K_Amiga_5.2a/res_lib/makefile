CFLAGS=-so

.c.o:
	cc $(CFLAGS) -o $@ $*.c
.a68.o:
	as -o $@ $*.a68

OBJ = libstart.o libsup.o

all:	mylib.library test

mylib.library:	$(OBJ) mylib.o
	ln -gw -o mylib.library $(OBJ) mylib.o 

test:	test.o
	ln -gw test.o -lc

clean:
	delete mylib.library #?.dbg

SRC=libstart.asm libsup.c mylib.asm mylib.h test.c makefile readme

reslib.lzh: $(SRC)
	lharc a reslib.lzh $(SRC)

