INSTALL=/libs/
LIB=

.inp.out:
	ord $*.inp $*.out

$(LIB):	$(LIB).out
	lb ram:$(LIB).lib -f $(LIB).out
	copy ram:$(LIB).lib $(LIB).lib
	delete ram:$(LIB).lib 
	-delete $(INSTALL)$(LIB).lib
	rename $(LIB).lib $(INSTALL)$(LIB).lib

arc:
	-delete /src/inp.lzh
	lharc a /src/inp.lzh makefile #?.inp
