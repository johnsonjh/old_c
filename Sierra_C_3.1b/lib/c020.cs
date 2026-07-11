=X
I:
C: C:\BIN\COM020 -Q %i %o
S: C:\BIN\ASM68 -lAQ %f
O: C:\BIN\LINK68 -QT0X5000 -x020 %f C:\LIB\~CRT133 %i \
#                       C:\LIB\LIBM.020 \
                        C:\LIB\LIBC.020
+ABS: C:\BIN\ABS68
+LOAD: C:\BIN\SLDR
