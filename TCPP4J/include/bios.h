/*  bios.h

    Access to bios services.

*/

/*
 *      C/C++ Run Time Library - Version 6.02
 *
 *      Copyright (c) 1987, 1994 by Borland International
 *      All Rights Reserved.
 *
 */

#if !defined(__BIOS_H)
#define __BIOS_H


#if !defined(___DEFS_H)
#include <_defs.h>
#endif


#if !defined(RC_INVOKED)

#if defined(__STDC__)
#pragma warn -nak
#endif

#endif  /* !RC_INVOKED */


#ifdef __cplusplus
extern "C" {
#endif


#if !defined(_Windows)

/* _ibmpc_diskinfo_t structure for _ibmpc_bios_disk() */

struct _ibmpc_diskinfo_t
{
    unsigned drive, head, track, sector, nsectors;
    void __far *buffer;
};

/* cmd values for _ibmpc_bios_disk() */

#define _IBMPC_DISK_RESET     0   /* controller hard reset */
#define _IBMPC_DISK_STATUS    1   /* status of last operation */
#define _IBMPC_DISK_READ      2   /* read sectors */
#define _IBMPC_DISK_WRITE     3   /* write sectors */
#define _IBMPC_DISK_VERIFY    4   /* verify sectors */
#define _IBMPC_DISK_FORMAT    5   /* format track */

unsigned _RTLENTRY _ibmpc_bios_disk(unsigned __cmd, struct _ibmpc_diskinfo_t _FAR *__dinfo);
int      _RTLENTRY _ibmpc_biosdisk(int __cmd, int __drive, int __head, int __track,
                                   int __sector, int __nsects, void _FAR *__buffer);

#if defined(_BIOS_IBMPC)
#define _diskinfo_t             _ibmpc_diskinfo_t
#define diskinfo_t              _ibmpc_diskinfo_t
#define _DISK_RESET             _IBMPC_DISK_RESET
#define _DISK_STATUS            _IBMPC_DISK_STATUS
#define _DISK_READ              _IBMPC_DISK_READ
#define _DISK_WRITE             _IBMPC_DISK_WRITE
#define _DISK_VERIFY            _IBMPC_DISK_VERIFY
#define _DISK_FORMAT            _IBMPC_DISK_FORMAT
#define _bios_disk              _ibmpc_bios_disk
#define biosdisk                _ibmpc_biosdisk
#endif  /* _BIOS_IBMPC */

#endif  /* !_Windows */


#if !defined(_Windows) || defined(__DPMI16__) || defined(__DPMI32__)

/* cmd values for _ibmpc_bios_keybrd() */

#define _IBMPC_KEYBRD_READ            0       /* read key */
#define _IBMPC_NKEYBRD_READ           0x10    /* read key - enhanced */
#define _IBMPC_KEYBRD_READY           1       /* check key ready */
#define _IBMPC_NKEYBRD_READY          0x11    /* check key ready - enhanced */
#define _IBMPC_KEYBRD_SHIFTSTATUS     2       /* get shift status */
#define _IBMPC_NKEYBRD_SHIFTSTATUS    0x12    /* get shift status - enhanced */

/* cmd values for _ibmpc_bios_printer() */

#define _IBMPC_PRINTER_WRITE  0       /* send a byte to printer */
#define _IBMPC_PRINTER_INIT   1       /* initialize printer */
#define _IBMPC_PRINTER_STATUS 2       /* read printer status */

/* cmd values for _ibmpc_bios_serialcom() */

#define _IBMPC_COM_INIT       0       /* set communication parms to a byte */
#define _IBMPC_COM_SEND       1       /* send a byte to port */
#define _IBMPC_COM_RECEIVE    2       /* read character from port */
#define _IBMPC_COM_STATUS     3       /* get status of port */

/* byte values for _IBMPC_COM_INIT cmd of _ibmpc_bios_serialcom() */

#define _IBMPC_COM_CHR7       0x02    /* 7 data bits */
#define _IBMPC_COM_CHR8       0x03    /* 8 data bits */
#define _IBMPC_COM_STOP1      0x00    /* 1 stop bit */
#define _IBMPC_COM_STOP2      0x04    /* 2 stop bits */
#define _IBMPC_COM_NOPARITY   0x00    /* no parity */
#define _IBMPC_COM_EVENPARITY 0x18    /* even parity */
#define _IBMPC_COM_ODDPARITY  0x08    /* odd parity */
#define _IBMPC_COM_110        0x00    /* 110 baud */
#define _IBMPC_COM_150        0x20    /* 150 baud */
#define _IBMPC_COM_300        0x40    /* 300 baud */
#define _IBMPC_COM_600        0x60    /* 600 baud */
#define _IBMPC_COM_1200       0x80    /* 1200 baud */
#define _IBMPC_COM_2400       0xa0    /* 2400 baud */
#define _IBMPC_COM_4800       0xc0    /* 4800 baud */
#define _IBMPC_COM_9600       0xe0    /* 9600 baud */

unsigned _RTLENTRY _ibmpc_bios_keybrd(unsigned __cmd);
unsigned _RTLENTRY _ibmpc_bios_printer(unsigned __cmd, unsigned __port, unsigned __abyte);
unsigned _RTLENTRY _ibmpc_bios_serialcom(unsigned __cmd, unsigned __port, unsigned __abyte);

int      _RTLENTRY _ibmpc_bioscom(int __cmd, char __abyte, int __port);
int      _RTLENTRY _ibmpc_bioskey(int __cmd);
int      _RTLENTRY _ibmpc_biosprint(int __cmd, int __abyte, int __port);

#if defined(_BIOS_IBMPC)
#define _KEYBRD_READ            _IBMPC_KEYBRD_READ
#define _NKEYBRD_READ           _IBMPC_NKEYBRD_READ
#define _KEYBRD_READY           _IBMPC_KEYBRD_READY
#define _NKEYBRD_READY          _IBMPC_NKEYBRD_READY
#define _KEYBRD_SHIFTSTATUS     _IBMPC_KEYBRD_SHIFTSTATUS
#define _NKEYBRD_SHIFTSTATUS    _IBMPC_NKEYBRD_SHIFTSTATUS
#define _PRINTER_WRITE          _IBMPC_PRINTER_WRITE
#define _PRINTER_INIT           _IBMPC_PRINTER_INIT
#define _PRINTER_STATUS         _IBMPC_PRINTER_STATUS
#define _COM_INIT               _IBMPC_COM_INIT
#define _COM_SEND               _IBMPC_COM_SEND
#define _COM_RECEIVE            _IBMPC_COM_RECEIVE
#define _COM_STATUS             _IBMPC_COM_STATUS
#define _COM_CHR7               _IBMPC_COM_CHR7
#define _COM_CHR8               _IBMPC_COM_CHR8
#define _COM_STOP1              _IBMPC_COM_STOP1
#define _COM_STOP2              _IBMPC_COM_STOP2
#define _COM_NOPARITY           _IBMPC_COM_NOPARITY
#define _COM_EVENPARITY         _IBMPC_COM_EVENPARITY
#define _COM_ODDPARITY          _IBMPC_COM_ODDPARITY
#define _COM_110                _IBMPC_COM_110
#define _COM_150                _IBMPC_COM_150
#define _COM_300                _IBMPC_COM_300
#define _COM_600                _IBMPC_COM_600
#define _COM_1200               _IBMPC_COM_1200
#define _COM_2400               _IBMPC_COM_2400
#define _COM_4800               _IBMPC_COM_4800
#define _COM_9600               _IBMPC_COM_9600
#define _bios_keybrd            _ibmpc_bios_keybrd
#define _bios_printer           _ibmpc_bios_printer
#define _bios_serialcom         _ibmpc_bios_serialcom
#define bioscom                 _ibmpc_bioscom
#define bioskey                 _ibmpc_bioskey
#define biosprint               _ibmpc_biosprint
#endif  /* _BIOS_IBMPC */

#endif  /* !_Windows || __DPMI16__ || __DPMI32__ */


#if !defined(__WIN32__) || defined(__DPMI32__)

/* cmd values for _ibmpc_bios_timeofday() */

#define _IBMPC_TIME_GETCLOCK  0   /* get clock count */
#define _IBMPC_TIME_SETCLOCK  1   /* set clock count */

unsigned _RTLENTRY _ibmpc_bios_equiplist(void);
unsigned _RTLENTRY _ibmpc_bios_memsize(void);
unsigned _RTLENTRY _ibmpc_bios_timeofday(unsigned __cmd, long _FAR *__timeval);

int      _RTLENTRY _ibmpc_biosequip(void);
int      _RTLENTRY _ibmpc_biosmemory(void);
long     _RTLENTRY _ibmpc_biostime(int __cmd, long __newtime);

#if defined(_BIOS_IBMPC)
#define _TIME_GETCLOCK          _IBMPC_TIME_GETCLOCK
#define _TIME_SETCLOCK          _IBMPC_TIME_SETCLOCK
#define _bios_equiplist         _ibmpc_bios_equiplist
#define _bios_memsize           _ibmpc_bios_memsize
#define _bios_timeofday         _ibmpc_bios_timeofday
#define biosequip               _ibmpc_biosequip
#define biosmemory              _ibmpc_biosmemory
#define biostime                _ibmpc_biostime
#endif  /* _BIOS_IBMPC */

#endif  /* !__WIN32__ || __DPMI32__ */


#if !defined(_Windows)

/* _necpc_diskinfo_t structure for _necpc_bios_disk() */

struct _necpc_diskinfo_t {
    unsigned command;
    unsigned drive;
    unsigned head;
    unsigned cylinder;
    unsigned data_len;
    unsigned sector_len;
    unsigned sector;
    unsigned nsectors;
    void __far *buffer;
    void __far *result;
};

/* service values for _necpc_bios_disk() */

#define _NECPC_DISK_READ            0x06    /* disk read */
#define _NECPC_DISK_WRITE           0x05    /* disk write */
#define _NECPC_DISK_SEEK            0x10    /* seek disk sector */
#define _NECPC_DISK_RECALIBRATE     0x07    /* recalibrate */
#define _NECPC_DISK_FORMATTRACK     0x0D    /* format track */
#define _NECPC_DISK_INITIALIZE      0x03    /* initialize */
#define _NECPC_DISK_VERIFY          0x01    /* verify disk sector */
#define _NECPC_DISK_SENSE           0x04    /* sense disk sector */
#define _NECPC_DISK_READID          0x0A    /* read ID */
#define _NECPC_DISK_WRITEDDAM       0x09    /* write deleted data */
#define _NECPC_DISK_FORMATDRIVE     0x8D    /* format drive */
#define _NECPC_DISK_ALTERNATE       0x08    /* assign alternate track */
#define _NECPC_DISK_BADTRACK        0x0B    /* format bad track */
#define _NECPC_DISK_READDDAM        0x0C    /* read deleted data */
#define _NECPC_DISK_DIAGNOSTIC      0x02    /* read diagnostic */
#define _NECPC_DISK_RETRACT         0x0F    /* retract */
#define _NECPC_DISK_OPMODE          0x0E    /* set operation mode */

/* command values for _necpc_bios_disk() */

#define _NECPC_CMD_2HD          0x0090    /* 1MB flopy disk */
#define _NECPC_CMD_2DD          0x0070    /* 640KB flopy disk */
#define _NECPC_CMD_2D           0x0050    /* 320KB flopy disk */
#define _NECPC_CMD_HD           0x0080    /* hard disk */

#define _NECPC_CMD_SEEK         0x1000    /* seek operation */
#define _NECPC_CMD_MF           0x4000    /* double/single-density */
#define _NECPC_CMD_MT           0x8000    /* multi/single track */
#define _NECPC_CMD_RETRY        0x2000    /* retry operation */

/* service values for _necpc_bios_keybrd() */

#define _NECPC_KEYBRD_READ          0   /* read key */
#define _NECPC_KEYBRD_READY         1   /* check key ready */
#define _NECPC_KEYBRD_SHIFTSTATUS   2   /* get shift status */
#define _NECPC_KEYBRD_INITIALIZE    3   /* initialize interface */
#define _NECPC_KEYBRD_SENSE         4   /* sense key status */

/* service values for _necpc_bios_printer() */

#define _NECPC_PRN_INIT         0x10    /* initialize printer */
#define _NECPC_PRN_WRITE        0x11    /* send a character to printer */
#define _NECPC_PRN_STRING       0x30    /* send a strings to printer */
#define _NECPC_PRN_STATUS       0x12    /* read printer status */

/* com_t structure for _necpc_bios_serialcom() */

struct _necpc_com_t {
    unsigned buad;                      /* baud : MSC compatible */
    unsigned mode;
    unsigned command;
    unsigned tx_time;
    unsigned rx_time;
    unsigned size;
    void __far *buffer;
};

/* service values for _necpc_bios_serialcom() */

#define _NECPC_COM_INIT         0   /* init serial port */
#define _NECPC_COM_INITX        1   /* init serial port with X parameter */
#define _NECPC_COM_GETDTL       2   /* get data length */
#define _NECPC_COM_SEND         3   /* send a byte to port */
#define _NECPC_COM_RECEIVE      4   /* read character from port */
#define _NECPC_COM_COMMAND      5   /* get command status */
#define _NECPC_COM_STATUS       6   /* get status of port */

/* select port */

#define _NECPC_COM_CH1          1   /* default port */
#define _NECPC_COM_CH2          2   /* expansion board's port */
#define _NECPC_COM_CH3          3   /* expansion board's port */

/* byte values for _COM_INIT service of _necpc_bios_serialcom() */

#define _NECPC_COM_CHR7         0x08    /* 7 bits characters */
#define _NECPC_COM_CHR8         0x0C    /* 8 bits characters */
#define _NECPC_COM_NOPARITY     0x00    /* no parity */
#define _NECPC_COM_ODD          0x10    /* odd parity */
#define _NECPC_COM_EVEN         0x30    /* even parity */
#define _NECPC_COM_STOP1        0x40    /* 1 stop bit */
#define _NECPC_COM_STOP2        0xC0    /* 2 stop bit */
#define _NECPC_COM_DEFAULT      0xFF    /* default baud */
#define _NECPC_COM_75           0x00    /* 75 baud */
#define _NECPC_COM_150          0x01    /* 150 baud */
#define _NECPC_COM_300          0x02    /* 300 baud */
#define _NECPC_COM_600          0x03    /* 600 baud */
#define _NECPC_COM_1200         0x04    /* 1200 baud */
#define _NECPC_COM_2400         0x05    /* 2400 baud */
#define _NECPC_COM_4800         0x06    /* 4800 baud */
#define _NECPC_COM_9600         0x07    /* 9600 baud */

#define _NECPC_COM_TXEN         0x01    /* transmission enable */
#define _NECPC_COM_DTR          0x02    /* data terminal ready */
#define _NECPC_COM_RXEN         0x04    /* enable to receive */
#define _NECPC_COM_SBRK         0x08    /* send brake character */
#define _NECPC_COM_ER           0x10    /* error reset */
#define _NECPC_COM_RTS          0x20    /* request to send */
#define _NECPC_COM_IR           0x40    /* internal reset */

/* service values for _necpc_bios_timeofday() */

#define _NECPC_TIME_GETCLOCK    0   /* get clock count */
#define _NECPC_TIME_SETCLOCK    1   /* set clock count */


unsigned _Cdecl _necpc_bios_disk(unsigned __service, struct _necpc_diskinfo_t _FAR *__dinfo);
unsigned _Cdecl _necpc_bios_keybrd(unsigned __service, ... /* unsigned char _FAR *__keytable */);
unsigned _Cdecl _necpc_bios_printer(unsigned __service, ... /* unsigned char _FAR *__databyte */);
unsigned _Cdecl _necpc_bios_serialcom(unsigned __service, unsigned __port, struct _necpc_com_t *__serialcom);
unsigned _Cdecl _necpc_bios_equiplist(void);
unsigned _Cdecl _necpc_bios_memsize(void);
unsigned _Cdecl _necpc_bios_timeofday(unsigned __service, char _FAR *__timeval);

#if defined(_BIOS_NECPC)
#define _DISK_READ              _NECPC_DISK_READ
#define _DISK_WRITE             _NECPC_DISK_WRITE
#define _DISK_SEEK              _NECPC_DISK_SEEK
#define _DISK_RECALIBRATE       _NECPC_DISK_RECALIBRATE
#define _DISK_FORMATTRACK       _NECPC_DISK_FORMATTRACK
#define _DISK_INITIALIZE        _NECPC_DISK_INITIALIZE
#define _DISK_VERIFY            _NECPC_DISK_VERIFY
#define _DISK_SENSE             _NECPC_DISK_SENSE
#define _DISK_READID            _NECPC_DISK_READID
#define _DISK_WRITEDDAM         _NECPC_DISK_WRITEDDAM
#define _DISK_FORMATDRIVE       _NECPC_DISK_FORMATDRIVE
#define _DISK_ALTERNATE         _NECPC_DISK_ALTERNATE
#define _DISK_BADTRACK          _NECPC_DISK_BADTRACK
#define _DISK_READDDAM          _NECPC_DISK_READDDAM
#define _DISK_DIAGNOSTIC        _NECPC_DISK_DIAGNOSTIC
#define _DISK_RETRACT           _NECPC_DISK_RETRACT
#define _DISK_OPMODE            _NECPC_DISK_OPMODE
#define _CMD_2HD                _NECPC_CMD_2HD
#define _CMD_2DD                _NECPC_CMD_2DD
#define _CMD_2D                 _NECPC_CMD_2D
#define _CMD_HD                 _NECPC_CMD_HD
#define _CMD_SEEK               _NECPC_CMD_SEEK
#define _CMD_MF                 _NECPC_CMD_MF
#define _CMD_MT                 _NECPC_CMD_MT
#define _CMD_RETRY              _NECPC_CMD_RETRY
#define _KEYBRD_READ            _NECPC_KEYBRD_READ
#define _KEYBRD_READY           _NECPC_KEYBRD_READY
#define _KEYBRD_SHIFTSTATUS     _NECPC_KEYBRD_SHIFTSTATUS
#define _KEYBRD_INITIALIZE      _NECPC_KEYBRD_INITIALIZE
#define _KEYBRD_SENSE           _NECPC_KEYBRD_SENSE
#define _PRN_INIT               _NECPC_PRN_INIT
#define _PRN_WRITE              _NECPC_PRN_WRITE
#define _PRN_STRING             _NECPC_PRN_STRING
#define _PRN_STATUS             _NECPC_PRN_STATUS
#define _COM_INIT               _NECPC_COM_INIT
#define _COM_INITX              _NECPC_COM_INITX
#define _COM_GETDTL             _NECPC_COM_GETDTL
#define _COM_SEND               _NECPC_COM_SEND
#define _COM_RECEIVE            _NECPC_COM_RECEIVE
#define _COM_COMMAND            _NECPC_COM_COMMAND
#define _COM_STATUS             _NECPC_COM_STATUS
#define _COM_CH1                _NECPC_COM_CH1
#define _COM_CH2                _NECPC_COM_CH2
#define _COM_CH3                _NECPC_COM_CH3
#define _COM_CHR7               _NECPC_COM_CHR7
#define _COM_CHR8               _NECPC_COM_CHR8
#define _COM_NOPARITY           _NECPC_COM_NOPARITY
#define _COM_ODD                _NECPC_COM_ODD
#define _COM_EVEN               _NECPC_COM_EVEN
#define _COM_STOP1              _NECPC_COM_STOP1
#define _COM_STOP2              _NECPC_COM_STOP2
#define _COM_DEFAULT            _NECPC_COM_DEFAULT
#define _COM_75                 _NECPC_COM_75
#define _COM_150                _NECPC_COM_150
#define _COM_300                _NECPC_COM_300
#define _COM_600                _NECPC_COM_600
#define _COM_1200               _NECPC_COM_1200
#define _COM_2400               _NECPC_COM_2400
#define _COM_4800               _NECPC_COM_4800
#define _COM_9600               _NECPC_COM_9600
#define _COM_TXEN               _NECPC_COM_TXEN
#define _COM_DTR                _NECPC_COM_DTR
#define _COM_RXEN               _NECPC_COM_RXEN
#define _COM_SBRK               _NECPC_COM_SBRK
#define _COM_ER                 _NECPC_COM_ER
#define _COM_RTS                _NECPC_COM_RTS
#define _COM_IR                 _NECPC_COM_IR
#define _TIME_GETCLOCK          _NECPC_TIME_GETCLOCK
#define _TIME_SETCLOCK          _NECPC_TIME_SETCLOCK
#define _diskinfo_t             _necpc_diskinfo_t
#define _com_t                  _necpc_com_t
#define diskinfo_t              _necpc_diskinfo_t
#define com_t                   _necpc_com_t
#define _bios_disk              _necpc_bios_disk
#define _bios_keybrd            _necpc_bios_keybrd
#define _bios_printer           _necpc_bios_printer
#define _bios_serialcom         _necpc_bios_serialcom
#define _bios_equiplist         _necpc_bios_equiplist
#define _bios_memsize           _necpc_bios_memsize
#define _bios_timeofday         _necpc_bios_timeofday
#endif  /* _BIOS_NECPC */

#endif  /* !_Windows  */


#if !defined(__WIN32__) || defined(__DPMI32__)

/* register structure definitions for int86(), int86x() */

#ifndef _REG_DEFS
#define _REG_DEFS

struct WORDREGS
{
    unsigned int    ax, bx, cx, dx, si, di, cflag, flags;
};


struct BYTEREGS
{
    unsigned char   al, ah, bl, bh, cl, ch, dl, dh;
};

union  REGS
{
    struct  WORDREGS x;
    struct  BYTEREGS h;
};

struct  SREGS
{
    unsigned int    es;
    unsigned int    cs;
    unsigned int    ss;
    unsigned int    ds;
};

struct  REGPACK
{
    unsigned    r_ax, r_bx, r_cx, r_dx;
    unsigned    r_bp, r_si, r_di, r_ds, r_es, r_flags;
};

#endif /* _REG_DEFS */

int      _RTLENTRY int86(int __intno,
                         union REGS _FAR *__inregs,
                         union REGS _FAR *__outregs );
int      _RTLENTRY int86x(int __intno,
                          union  REGS  _FAR *__inregs,
                          union  REGS  _FAR *__outregs,
                          struct SREGS _FAR *__segregs );

#endif  /* !__WIN32__ || __DPMI32__ */


#ifdef __cplusplus
}
#endif


#if !defined(RC_INVOKED)

#if defined(__STDC__)
#pragma warn .nak
#endif

#endif  /* !RC_INVOKED */


#endif  /* __BIOS_H */

