=X
I:
C: C:\BIN\COM68 -Q %i %o
S: C:\BIN\ASM68 -lAQ %f
O: C:\BIN\LINK68 -QT0X5000 %f C:\LIB\~CRT105 %i \
#                       C:\LIB\LIBMS.68 \
                        C:\LIB\LIBC.68
+ABS: C:\BIN\ABS68
+LOAD: C:\BIN\SLDR
