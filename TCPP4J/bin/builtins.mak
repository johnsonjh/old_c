
#
# Borland Turbo C++ - (C) Copyright 1995 by Borland International
#

CC       = tcc
RC       = brcc
AS       = tasm

.asm.obj:
      $(AS) $(AFLAGS) $&.asm

.c.exe:
      $(CC) $(CFLAGS) $&.c

.c.obj:
      $(CC) $(CFLAGS) /c $&.c

.cpp.exe:
      $(CC) $(CFLAGS) $&.cpp

.cpp.obj:
      $(CC) $(CPPFLAGS) /c $&.cpp

.rc.res:
      $(RC) $(RFLAGS) /r $&

.SUFFIXES: .exe .obj .asm .c .res .rc

!if !$d(BCEXAMPLEDIR)
BCEXAMPLEDIR = $(MAKEDIR)\..\EXAMPLES
!endif
