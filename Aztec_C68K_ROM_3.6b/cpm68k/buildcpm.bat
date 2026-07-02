c68 -o azcpm.r azcpm.c
copy ..\lib\c68mac.lib c68k.lib
lb68 c68k.lib -d mac
lb68 c68k.lib -d open close unlink lseek read isatty rename
lb68 c68k.lib -r write azcpm.r
lb68 c68k.lib -d pbwrite
copy c68K.lib c68kf.lib
lb68 c68kf.lib -r format ..\lib\misc\fformat.r
as68 cpm.asm -o cpm.r
