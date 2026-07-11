=X
I:
C: C:\BIN\COM020 -Qp32 %i %o
S: C:\BIN\ASM68 -lAQ %f
O: C:\BIN\LINK68 -QT0X5000 -x332 %f C:\LIB\~CRT332 %i \
#                       C:\LIB\LIBMS.332 \
                        C:\LIB\LIBC.332
+ABS: C:\BIN\ABS68
+LOAD: C:\BIN\SLDR
