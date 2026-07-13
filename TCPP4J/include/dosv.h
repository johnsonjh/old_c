/*  dosv.h

    Access to bios services and DOS/V specific hardwares.

*/

/*
 *      C/C++ Run Time Library - Version 6.02
 *
 *      Copyright (c) 1987, 1994 by Borland International
 *      All Rights Reserved.
 *
 */

#if !defined(__DOSV_H)
#define __DOSV_H

#if !defined(___DEFS_H)
#include <_defs.h>
#endif


#if !defined(RC_INVOKED)

#if defined(__STDC__)
#pragma warn -nak
#endif

#pragma option -a-

#endif  /* !RC_INVOKED */


#if !defined(__COMINFO_DEFS)
struct cominfo {
    unsigned short   baud;
    unsigned char    databit;
    unsigned char    stopbit;
    unsigned char    parity;
    unsigned char    flow;
    unsigned short   rbufsize;
    void             _FAR *rbuf;
    unsigned short   sbufsize;
    void             _FAR *sbuf;
};
struct combufinfo {
    unsigned short   rsize;
    int              rxoff;
    unsigned short   ssize;
    int              sxoff;
};

enum combaudlate {
    COM_B75 = 0, COM_B150, COM_B300, COM_B600,
    COM_B1200, COM_B2400, COM_B4800, COM_B9600,
    COM_B19200
};
enum comdatabitlength   { COM_L5 = 0, COM_L6, COM_L7, COM_L8 };
enum comstopbitlength   { COM_S1 = 0, COM_S15, COM_S2 };
enum comparitytype      { COM_PNONE = 0, COM_PEVEN, COM_PODD };
enum comflowtype        { COM_FNONE = 0, COM_FXONXOFF, COM_FRTSCTS };
#endif /* __COMINFO_DEFS */


#ifdef __cplusplus
extern "C" {
#endif
int        _RTLENTRY dosvcominitx      (int __chanel, const struct cominfo _FAR *__initdata);
int        _RTLENTRY dosvcomtermx      (int __chanel);
int        _RTLENTRY dosvcomsendx      (int __chanel, unsigned char __data);
int        _RTLENTRY dosvcomrecvx      (int __chanel, void _FAR *__buffer);
int        _RTLENTRY dosvcomgetstatx   (int __chanel, unsigned _FAR *__statbuf);
int        _RTLENTRY dosvcomsetstatx   (int __chanel, unsigned __stat);
int        _RTLENTRY dosvcomchkbufx    (int __chanel, struct combufinfo _FAR *__bufdata);
int        _RTLENTRY dosvcomsendbreakx (int __chanel);
int        _RTLENTRY dosvcomresetx     (int __chanel);
int        _RTLENTRY dosvcomcheckbaudx (int __chanel, int __baud);

#if !defined(__FLAT__)
void far * _RTLENTRY dosvgetvideoaddr(void);
void       _RTLENTRY dosvupdatescreen(const void __far *__ptr, int __length );
#endif

unsigned   _RTLENTRY dosvgetkbdid    (void);
unsigned   _RTLENTRY dosvgetiasstatus(void);
void       _RTLENTRY dosvsetiasstatus(unsigned __mode);
void       _RTLENTRY dosviasshifton  (void);
void       _RTLENTRY dosviasshiftoff (void);
int        _RTLENTRY dosviasshiftchk (void);

#if !defined(__FLAT__)
unsigned   _RTLENTRY dosvgetfont     (unsigned __code, char __width, char __height, unsigned __codepage, void __far *__buffer);
unsigned   _RTLENTRY dosvsetfont     (unsigned __code, char __width, char __height, unsigned __codepage, const void __far *__buffer);
#else
unsigned   _RTLENTRY dosvgetfont     (unsigned __code, char __width, char __height, unsigned __codepage, void *__buffer);
unsigned   _RTLENTRY dosvsetfont     (unsigned __code, char __width, char __height, unsigned __codepage, const void *__buffer);
#endif
unsigned   _RTLENTRY dosvgetdosenv   (void);

#ifdef __cplusplus
}
#endif

#if !defined(RC_INVOKED)

#pragma option -a.

#if defined(__STDC__)
#pragma warn .nak
#endif

#endif  /* !RC_INVOKED */


#endif /* __DOSV_H */
