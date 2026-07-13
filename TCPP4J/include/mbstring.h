/*  mbstring.h

    Definitions for MBCS string functions.

*/

/*
 *      C/C++ Run Time Library - Version 6.02
 *
 *      Copyright (c) 1992, 1994 by Borland International
 *      All Rights Reserved.
 *
 */

#ifndef __MBSTRING_H
#define __MBSTRING_H

#ifdef _MSC
#if !defined(__STRING_H)
#include <string.h>
#endif
#endif

#if !defined(___DEFS_H)
#include <_defs.h>
#endif

#ifndef NULL
#include <_null.h>
#endif

#ifndef _SIZE_T
#define _SIZE_T
typedef unsigned size_t;
#endif

#ifdef __cplusplus
extern "C" {
#endif

unsigned char _FAR * _RTLENTRYF _mbscpy   (unsigned char _FAR *__dest, const unsigned char _FAR *__src);
unsigned char _FAR * _RTLENTRYF _mbscat   (unsigned char _FAR *__dest, const unsigned char _FAR *__src);
unsigned char _FAR * _RTLENTRYF _mbsncpy  (unsigned char _FAR *__dest, const unsigned char _FAR *__src, size_t __maxlen);
unsigned char _FAR * _RTLENTRYF _mbsncat  (unsigned char _FAR *__dest, const unsigned char _FAR *__src, size_t __maxlen);
unsigned char _FAR * _RTLENTRYF _mbsnbcpy (unsigned char _FAR *__dest, const unsigned char _FAR *__src, size_t __maxlen);
unsigned char _FAR * _RTLENTRYF _mbsnbcat (unsigned char _FAR *__dest, const unsigned char _FAR *__src, size_t __maxlen);
void                 _RTLENTRYF _mbccpy   (unsigned char _FAR *__dest, const unsigned char _FAR *__src);
unsigned char _FAR * _RTLENTRYF _mbsdup   (const unsigned char _FAR *__s);
unsigned char _FAR * _RTLENTRYF _mbschr   (const unsigned char _FAR *__s, unsigned int __c);
unsigned char _FAR * _RTLENTRYF _mbsrchr  (const unsigned char _FAR *__s, unsigned int __c);
size_t               _RTLENTRY  _mbscspn  (const unsigned char _FAR *__s1, const unsigned char _FAR *__s2);
size_t               _RTLENTRY  _mbsspn   (const unsigned char _FAR *__s1, const unsigned char _FAR *__s2);
unsigned char _FAR * _RTLENTRYF _mbspbrk  (const unsigned char _FAR *__s1, const unsigned char _FAR *__s2);
unsigned char _FAR * _RTLENTRY  _mbsspnp  (const unsigned char _FAR *__s1, const unsigned char _FAR *__s2);
unsigned char _FAR * _RTLENTRYF _mbsinc   (const unsigned char _FAR *__p);
unsigned char _FAR * _RTLENTRYF _mbsninc  (const unsigned char _FAR *__p, size_t __n);
unsigned char _FAR * _RTLENTRYF _mbsdec   (const unsigned char _FAR *__s, const unsigned char _FAR *__p);
unsigned char _FAR * _RTLENTRYF _mbstok   (unsigned char _FAR *__s1, const unsigned char _FAR *__s2);
unsigned char _FAR * _RTLENTRY  _mbsrev   (unsigned char _FAR *__s);
unsigned char _FAR * _RTLENTRY  _mbsstr   (const unsigned char _FAR *__s1, const unsigned char _FAR *__s2);
int                  _RTLENTRYF _mbscmp   (const unsigned char _FAR *__s1, const unsigned char _FAR *__s2);
int                  _RTLENTRYF _mbsicmp  (const unsigned char _FAR *__s1, const unsigned char _FAR *__s2);
int                  _RTLENTRYF _mbsncmp  (const unsigned char _FAR *__s1, const unsigned char _FAR *__s2, size_t __maxlen);
int                  _RTLENTRYF _mbsnicmp (const unsigned char _FAR *__s1, const unsigned char _FAR *__s2, size_t __maxlen);
int                  _RTLENTRYF _mbsnbcmp (const unsigned char _FAR *__s1, const unsigned char _FAR *__s2, size_t __maxlen);
int                  _RTLENTRYF _mbsnbicmp(const unsigned char _FAR *__s1, const unsigned char _FAR *__s2, size_t __maxlen);
int                  _RTLENTRYF _mbccmp   (const unsigned char _FAR *__s1, const unsigned char _FAR *__s2);
size_t               _RTLENTRYF _mbslen   (const unsigned char _FAR *__s);
size_t               _RTLENTRYF _mbclen   (const unsigned char _FAR *__s);
unsigned char _FAR * _RTLENTRYF _mbsupr   (unsigned char _FAR *__s);
unsigned char _FAR * _RTLENTRYF _mbslwr   (unsigned char _FAR *__s);
unsigned char _FAR * _RTLENTRY  _mbsset   (unsigned char _FAR *__s, unsigned int __c);
unsigned char _FAR * _RTLENTRY  _mbsnset  (unsigned char _FAR *__s, unsigned int __c, size_t __maxlen);
unsigned char _FAR * _RTLENTRYF _mbsnbset (unsigned char _FAR *__s, unsigned int __c, size_t __maxlen);
size_t               _RTLENTRYF _mbsnccnt (const unsigned char _FAR *__s, size_t __nbyte);
size_t               _RTLENTRYF _mbsnbcnt (const unsigned char _FAR *__s, size_t __nmbc);
unsigned int         _RTLENTRYF _mbsnextc (const unsigned char _FAR *__p);
int                  _RTLENTRYF _mbbtype  (unsigned char __c, int __mode);
int                  _RTLENTRYF _mbsbtype (const unsigned char _FAR *__s, size_t __nbyte);

#ifndef __MBCS_LEADTRAIL
#define __MBCS_LEADTRAIL
int _RTLENTRY _ismbblead  (unsigned int __c);
int _RTLENTRY _ismbbtrail (unsigned int __c);
int _RTLENTRY _ismbslead  (const unsigned char _FAR *__s1, const unsigned char _FAR *__s2);
int _RTLENTRY _ismbstrail (const unsigned char _FAR *__s1, const unsigned char _FAR *__s2);
#if !defined(__FLAT__)
/* Model-independent functions */
#if !__STDC__
int _RTLENTRY _FARCALL _fismbslead (const unsigned char far *__s1, const unsigned char far *__s2);
int _RTLENTRY _FARCALL _fismbstrail(const unsigned char far *__s1, const unsigned char far *__s2);
#endif  /* ! __STDC__ */
#endif  /* ! __FLAT__ */
#endif  /* ! __MBCS_LEADTRAIL */

#define _mbccmp(__s1, __s2) _mbsncmp((__s1),(__s2),1)

#if !defined(__FLAT__)

/* Model-independent functions */
#if !__STDC__

unsigned char far * _RTLENTRY _FARCALL _fmbscpy   (unsigned char far *__dest, const unsigned char far *__src);
unsigned char far * _RTLENTRY _FARCALL _fmbscat   (unsigned char far *__dest, const unsigned char far *__src);
unsigned char far * _RTLENTRY _FARCALL _fmbsncpy  (unsigned char far *__dest, const unsigned char far *__src, size_t __maxlen);
unsigned char far * _RTLENTRY _FARCALL _fmbsncat  (unsigned char far *__dest, const unsigned char far *__src, size_t __maxlen);
unsigned char far * _RTLENTRY _FARCALL _fmbsnbcpy (unsigned char far *__dest, const unsigned char far *__src, size_t __maxlen);
unsigned char far * _RTLENTRY _FARCALL _fmbsnbcat (unsigned char far *__dest, const unsigned char far *__src, size_t __maxlen);
void                _RTLENTRY _FARCALL _fmbccpy   (unsigned char far *__dest, const unsigned char far *__src);
unsigned char far * _RTLENTRY _FARCALL _fmbsdup   (const unsigned char _FAR *__s);
unsigned char far * _RTLENTRY _FARCALL _fmbschr   (const unsigned char far *__s, unsigned int __c);
unsigned char far * _RTLENTRY _FARCALL _fmbsrchr  (const unsigned char far *__s, unsigned int __c);
size_t              _RTLENTRY _FARCALL _fmbscspn  (const unsigned char _FAR *__s1, const unsigned char _FAR *__s2);
size_t              _RTLENTRY _FARCALL _fmbsspn   (const unsigned char _FAR *__s1, const unsigned char _FAR *__s2);
unsigned char far * _RTLENTRY _FARCALL _fmbspbrk  (const unsigned char far *__s1, const unsigned char far *__s2);
unsigned char far * _RTLENTRY _FARCALL _fmbsspnp  (const unsigned char far *__s1, const unsigned char far *__s2);
unsigned char far * _RTLENTRY _FARCALL _fmbsinc   (const unsigned char far *__p);
unsigned char far * _RTLENTRY _FARCALL _fmbsninc  (const unsigned char far *__p, size_t __n);
unsigned char far * _RTLENTRY _FARCALL _fmbsdec   (const unsigned char far *__s, const unsigned char far *__p);
unsigned char far * _RTLENTRY _FARCALL _fmbstok   (unsigned char far *__s1, const unsigned char far *__s2);
unsigned char far * _RTLENTRY _FARCALL _fmbsrev   (unsigned char far *__s);
unsigned char far * _RTLENTRY _FARCALL _fmbsstr   (const unsigned char far *__s1, const unsigned char far *__s2);
int                 _RTLENTRY _FARCALL _fmbscmp   (const unsigned char far *__s1, const unsigned char far *__s2);
int                 _RTLENTRY _FARCALL _fmbsicmp  (const unsigned char far *__s1, const unsigned char far *__s2);
int                 _RTLENTRY _FARCALL _fmbsncmp  (const unsigned char far *__s1, const unsigned char far *__s2, size_t __maxlen);
int                 _RTLENTRY _FARCALL _fmbsnicmp (const unsigned char far *__s1, const unsigned char far *__s2, size_t __maxlen);
int                 _RTLENTRY _FARCALL _fmbsnbcmp (const unsigned char far *__s1, const unsigned char far *__s2, size_t __maxlen);
int                 _RTLENTRY _FARCALL _fmbsnbicmp(const unsigned char far *__s1, const unsigned char far *__s2, size_t __maxlen);
int                 _RTLENTRY _FARCALL _fmbccmp   (const unsigned char far *__s1, const unsigned char far *__s2);
size_t              _RTLENTRY _FARCALL _fmbslen   (const unsigned char far *__s);
size_t              _RTLENTRY _FARCALL _fmbclen   (const unsigned char far *__s);
unsigned char far * _RTLENTRY _FARCALL _fmbsupr   (unsigned char far *__s);
unsigned char far * _RTLENTRY _FARCALL _fmbslwr   (unsigned char far *__s);
unsigned char far * _RTLENTRY _FARCALL _fmbsset   (unsigned char far *__s, unsigned int __c);
unsigned char far * _RTLENTRY _FARCALL _fmbsnset  (unsigned char far *__s, unsigned int __c, size_t __maxlen);
unsigned char far * _RTLENTRY _FARCALL _fmbsnbset (unsigned char far *__s, unsigned int __c, size_t __maxlen);
size_t              _RTLENTRY _FARCALL _fmbsnccnt (const unsigned char far *__s, size_t __nbyte);
size_t              _RTLENTRY _FARCALL _fmbsnbcnt (const unsigned char far *__s, size_t __nmbc);
unsigned int        _RTLENTRY _FARCALL _fmbsnextc (const unsigned char far *__p);
int                 _RTLENTRY _FARCALL _fmbbtype  (unsigned char __c, int __mode);
int                 _RTLENTRY _FARCALL _fmbsbtype (const unsigned char far *__s, size_t __nbyte);

#define _fmbccmp(__s1, __s2) _fmbsncmp((__s1),(__s2),1)

#endif  /* ! __STDC__ */

#endif  /* ! __FLAT__ */

#ifdef __cplusplus
}
#endif


#ifdef __cplusplus
extern "C" {
#endif
int _RTLENTRY _ismbclegal(unsigned int __c);
int _RTLENTRY _ismbcalpha(unsigned int __c);
int _RTLENTRY _ismbcdigit(unsigned int __c);
int _RTLENTRY _ismbcprint(unsigned int __c);
int _RTLENTRY _ismbcspace(unsigned int __c);
int _RTLENTRY _ismbclower(unsigned int __c);
int _RTLENTRY _ismbcupper(unsigned int __c);
unsigned int _RTLENTRYF _mbctolower(unsigned int __c);
unsigned int _RTLENTRYF _mbctoupper(unsigned int __c);
#ifdef __cplusplus
}
#endif


/* Japanese DBCS special functions */
#ifdef __cplusplus
extern "C" {
#endif
int _RTLENTRY _ismbchira  (unsigned int __c);
int _RTLENTRY _ismbckata  (unsigned int __c);
int _RTLENTRY _ismbcl0    (unsigned int __c);
int _RTLENTRY _ismbcl1    (unsigned int __c);
int _RTLENTRY _ismbcl2    (unsigned int __c);
int _RTLENTRY _ismbcsymbol(unsigned int __c);
unsigned int _RTLENTRYF _mbctohira  (unsigned int __c);
unsigned int _RTLENTRYF _mbctokata  (unsigned int __c);
unsigned int _RTLENTRYF _mbctombb   (unsigned int __c);
unsigned int _RTLENTRYF _mbbtombc   (unsigned int __c);
unsigned int _RTLENTRYF _mbcjistojms(unsigned int __c);
unsigned int _RTLENTRYF _mbcjmstojis(unsigned int __c);
#ifdef __cplusplus
}
#endif


#endif /* __MBSTRING_H */
