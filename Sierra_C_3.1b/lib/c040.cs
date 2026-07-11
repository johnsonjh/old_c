=X
I:
C: C:\BIN\COM020 -Qp40 %i %o
S: C:\BIN\ASM68 -lAQ %f
O: C:\BIN\LINK68 -QT0X5000 %f -x040 C:\LIB\~CRT167 %i \
#                       C:\LIB\LIBM.040 \
                        C:\LIB\LIBC.040
+ABS: C:\BIN\ABS68
+LOAD: C:\BIN\SLDR
