/*  pc98.h

    Access to bios services and NEC PC-9801 series specific hardwares.

*/

/*
 *      C/C++ Run Time Library - Version 6.02
 *
 *      Copyright (c) 1987, 1994 by Borland International
 *      All Rights Reserved.
 *
 */

#if !defined(__PC98_H)
#define __PC98_H

#if !defined(___DEFS_H)
#include <_defs.h>
#endif


#if !defined(RC_INVOKED)

#if defined(__STDC__)
#pragma warn -nak
#endif

#pragma option -a-

#endif  /* !RC_INVOKED */


struct diskinfo {
    unsigned char   cmd;
    unsigned char   devtype;
    unsigned short  datalen;
    unsigned short  seclen;
    unsigned short  cylnum;
    unsigned char   headnum;
    unsigned char   secnum;
    char            _FAR *databuf;
};

struct mouseinfo {
    unsigned short  reg_ax;
    unsigned short  reg_bx;
    unsigned short  reg_cx;
    unsigned short  reg_dx;
    void            _FAR *shape;
    void            _RTLENTRY(*fptr)(unsigned __ax, unsigned __bx,
                                     unsigned __cx, unsigned __dx);
};

struct clockinfo {
    unsigned char   year;
    unsigned char   mon;
    unsigned char   wday;
    unsigned char   day;
    unsigned char   hour;
    unsigned char   min;
    unsigned char   sec;
    unsigned char   _filler;
};

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

void     _RTLENTRY pc98clock        (int __func,
                                     struct clockinfo _FAR *__clockdata);
int      _RTLENTRY pc98crt          (int __func, ...);
int      _RTLENTRY pc98disk         (struct diskinfo _FAR *__dp);
unsigned _RTLENTRY pc98equip        (void);
unsigned _RTLENTRY pc98key          (int __func, ...);
unsigned _RTLENTRY pc98mem          (void);
int      _RTLENTRY pc98mouse        (int __func, struct mouseinfo _FAR *__mp);
int      _RTLENTRY pc98print        (int __func, ...);
void _RTLENTRY(*_RTLENTRY pc98timer (unsigned __interval,
                                     void _RTLENTRY(*fptr)(void)))(void);
void     _RTLENTRY pc98getfont      (unsigned __code, void _FAR *__buffer);
void     _RTLENTRY pc98putuserfont  (unsigned __code, void _FAR *__buffer);
void     _RTLENTRY pc98fkeyon       (void);
void     _RTLENTRY pc98fkeyoff      (void);
int      _RTLENTRY pc98fkeychk      (void);
void     _RTLENTRY pc98getfkey      (int __id, void _FAR *__buffer);
void     _RTLENTRY pc98setfkey      (int __id, const void _FAR *__buffer);
int      _RTLENTRY pc98cominit      (const struct cominfo _FAR *__initdata);
int      _RTLENTRY pc98comterm      (void);
int      _RTLENTRY pc98comsend      (unsigned char __data);
int      _RTLENTRY pc98comrecv      (void _FAR *__buffer);
int      _RTLENTRY pc98comgetstat   (unsigned _FAR *__statbuf);
int      _RTLENTRY pc98comsetstat   (unsigned __stat);
int      _RTLENTRY pc98comchkbuf    (struct combufinfo _FAR *__bufdata);
int      _RTLENTRY pc98comsendbreak (void);
int      _RTLENTRY pc98comreset     (void);
int      _RTLENTRY pc98comcheckbaud (int __baud);
int      _RTLENTRY pc98cominitx     (int __chanel,
                                     const struct cominfo _FAR *__initdata);
int      _RTLENTRY pc98comtermx     (int __chanel);
int      _RTLENTRY pc98comsendx     (int __chanel, unsigned char __data);
int      _RTLENTRY pc98comrecvx     (int __chanel, void _FAR *__buffer);
int      _RTLENTRY pc98comgetstatx  (int __chanel, unsigned _FAR *__statbuf);
int      _RTLENTRY pc98comsetstatx  (int __chanel, unsigned __stat);
int      _RTLENTRY pc98comchkbufx   (int __chanel,
                                     struct combufinfo _FAR *__bufdata);
int      _RTLENTRY pc98comsendbreakx(int __chanel);
int      _RTLENTRY pc98comresetx    (int __chanel);
int      _RTLENTRY pc98comcheckbaudx(int __chanel, int __baud);

#ifdef __cplusplus
}
#endif

#if !defined(RC_INVOKED)

#pragma option -a.

#if defined(__STDC__)
#pragma warn .nak
#endif

#endif  /* !RC_INVOKED */


#endif /* __PC98_H */
