/*  jstring.h

    Definitions for Japanese string functions.

*/

/*
 *      C/C++ Run Time Library - Version 6.02
 *
 *      Copyright (c) 1987, 1994 by Borland International
 *      All Rights Reserved.
 *
 */

#ifndef __JSTRING_H
#define __JSTRING_H

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

#if !defined(__MBCTYPE_H)
#include <mbctype.h>
#endif

#if !defined(__MBSTRING_H)
#include <mbstring.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif
char _FAR * _RTLENTRYF jstrncpy (char _FAR *__dest, const char _FAR *__src, size_t __maxlen);
char _FAR * _RTLENTRYF jstrncat (char _FAR *__dest, const char _FAR *__src, size_t __maxlen);
char _FAR * _RTLENTRYF jstrchr  (const char _FAR *__s, unsigned short __c);
char _FAR * _RTLENTRYF jstrrchr (const char _FAR *__s, unsigned short __c);
char _FAR * _RTLENTRYF jstrtok  (char _FAR *__s1, const char _FAR *__s2);
char _FAR * _RTLENTRYF jstradv  (const char _FAR *__s, int __n);
char _FAR * _RTLENTRYF jstrmatch(const char _FAR *__s1, const char _FAR *__s2);
char _FAR * _RTLENTRY  jstrskip (const char _FAR *__s1, const char _FAR *__s2);
char _FAR * _RTLENTRY  jstrrev  (char _FAR *__s);
char _FAR * _RTLENTRY  jstrstr  (const char _FAR *__s1, const char _FAR *__s2);
int         _RTLENTRYF jstrcmp  (const char _FAR *__s1, const char _FAR *__s2);
int         _RTLENTRYF jstricmp (const char _FAR *__s1, const char _FAR *__s2);
int         _RTLENTRYF jstrncmp (const char _FAR *__s1, const char _FAR *__s2, size_t __maxlen);
int         _RTLENTRYF jstrnicmp(const char _FAR *__s1, const char _FAR *__s2, size_t __maxlen);
size_t      _RTLENTRYF jstrlen  (const char _FAR *__s);
char _FAR * _RTLENTRYF jstrupr  (char _FAR *__s);
char _FAR * _RTLENTRYF jstrlwr  (char _FAR *__s);
size_t      _RTLENTRY  jstrcspn (const char _FAR *__s1, const char _FAR *__s2);
size_t      _RTLENTRY  jstrspn  (const char _FAR *__s1, const char _FAR *__s2);
char _FAR * _RTLENTRY  jstrset  (char _FAR *__s, unsigned short __c);
char _FAR * _RTLENTRY  jstrnset (char _FAR *__s, unsigned short __c, size_t __maxlen);
int         _RTLENTRYF btom     (const char _FAR *__s, int __nbyte);
int         _RTLENTRYF mtob     (const char _FAR *__s, int __nmoji);


#if !defined(__FLAT__)
#if !__STDC__
char far * _RTLENTRY _FARCALL _fjstrncpy (char far *__dest, const char far *__src, size_t __maxlen);
char far * _RTLENTRY _FARCALL _fjstrncat (char far *__dest, const char far *__src, size_t __maxlen);
char far * _RTLENTRY _FARCALL _fjstrchr  (const char far *__s, unsigned short __c);
char far * _RTLENTRY _FARCALL _fjstrrchr (const char far *__s, unsigned short __c);
char far * _RTLENTRY _FARCALL _fjstrtok  (char far *__s1, const char far *__s2);
char far * _RTLENTRY _FARCALL _fjstradv  (const char far *__s, int __n);
char far * _RTLENTRY _FARCALL _fjstrmatch(const char far *__s1, const char far *__s2);
char far * _RTLENTRY _FARCALL _fjstrskip (const char far *__s1, const char far *__s2);
char far * _RTLENTRY _FARCALL _fjstrrev  (char far *__s);
char far * _RTLENTRY _FARCALL _fjstrstr  (const char far *__s1, const char far *__s2);
int        _RTLENTRY _FARCALL _fjstrcmp  (const char far *__s1, const char far *__s2);
int        _RTLENTRY _FARCALL _fjstricmp (const char far *__s1, const char far *__s2);
int        _RTLENTRY _FARCALL _fjstrncmp (const char far *__s1, const char far *__s2, size_t __maxlen);
int        _RTLENTRY _FARCALL _fjstrnicmp(const char far *__s1, const char far *__s2, size_t __maxlen);
size_t     _RTLENTRY _FARCALL _fjstrlen  (const char far *__s);
char far * _RTLENTRY _FARCALL _fjstrupr  (char far *__s);
char far * _RTLENTRY _FARCALL _fjstrlwr  (char far *__s);
size_t     _RTLENTRY _FARCALL _fjstrcspn (const char far *__s1, const char far *__s2);
size_t     _RTLENTRY _FARCALL _fjstrspn  (const char far *__s1, const char far *__s2);
char far * _RTLENTRY _FARCALL _fjstrset  (char far *__s, unsigned short __c);
char far * _RTLENTRY _FARCALL _fjstrnset (char far *__s, unsigned short __c, size_t __maxlen);
int        _RTLENTRY _FARCALL _fbtom     (const char far *__s, int __nbyte);
int        _RTLENTRY _FARCALL _fmtob     (const char far *__s, int __nmoji);
#endif  /* ! __STDC__ */
#endif  /* ! __FLAT__ */
#ifdef __cplusplus
}
#endif

#ifndef __CHKCTYPE
#define __CHKCTYPE

/* values used in chkctype(), nthctype() */
#define CT_ANK          _MBC_SINGLE
#define CT_KJ1          _MBC_LEAD
#define CT_KJ2          _MBC_TRAIL
#define CT_ILGL         _MBC_ILLEGAL

#ifdef __cplusplus
extern "C" {
#endif
int _RTLENTRYF chkctype(char __c, int __mode);
int _RTLENTRYF nthctype(const char _FAR *__s, int __nbyte);
#if !defined(__FLAT__)
#if !__STDC__
int _RTLENTRY _FARCALL _fchkctype(char __c, int __mode);
int _RTLENTRY _FARCALL _fnthctype(const char far *__s, int __nbyte);
#endif  /* ! __STDC__ */
#endif  /* ! __FLAT__ */
#ifdef __cplusplus
}
#endif
#endif /* __CHKCTYPE */

#ifdef _MSC
#define jiszen      _ismbclegal
#define jisl0       _ismbcl0
#define jisl1       _ismbcl1
#define jisl2       _ismbcl2
#define jiskata     _ismbckata
#define jishira     _ismbchira
#define jiskigou    _ismbcsymbol
#define jisprint    _ismbcprint
#define jtohira     _mbctohira
#define jtokata     _mbctokata
#define zentohan    _mbctombb
#define hantozen    _mbbtombc
#define jistojms    _mbcjistojms
#define jmstojis    _mbcjmstojis
#define jisalpha    _ismbcalpha
#define jisupper    _ismbcupper
#define jislower    _ismbclower
#define jisdigit    _ismbcdigit
#define jisspace    _ismbcspace
#define jtolower    _mbctolower
#define jtoupper    _mbctoupper
#define jstrncpy    _mbsncpy
#define jstrncat    _mbsncat
#define jstrchr     _mbschr
#define jstrrchr    _mbsrchr
#define jstrtok     _mbstok
#define jstradv     _mbsninc
#define jstrmatch   _mbspbrk
#define jstrskip    _mbsspnp
#define jstrrev     _mbsrev
#define jstrstr     _mbsstr
#define jstrcmp     _mbscmp
#define jstrncmp    _mbsncmp
#define jstrlen     _mbslen
#define jstrcspn    _mbscspn
#define jstrspn     _mbsspn
#define jstrset     _mbsset
#define jstrnset    _mbsnset
#define btom        _mbsnccnt
#define mtob        _mbsnbcnt
#define jstricmp    _mbsicmp
#define jstrnicmp   _mbsnicmp
#define jstrupr     _mbsupr
#define jstrlwr     _mbslwr
#define chkctype    _mbbtype
#define nthctype    _mbsbtype
#if !defined(__FLAT__)
#if !__STDC__
#define _fjstrncpy  _fmbsncpy
#define _fjstrncat  _fmbsncat
#define _fjstrchr   _fmbschr
#define _fjstrrchr  _fmbsrchr
#define _fjstrtok   _fmbstok
#define _fjstradv   _fmbsninc
#define _fjstrmatch _fmbspbrk
#define _fjstrskip  _fmbsspnp
#define _fjstrrev   _fmbsrev
#define _fjstrstr   _fmbsstr
#define _fjstrcmp   _fmbscmp
#define _fjstrncmp  _fmbsncmp
#define _fjstrlen   _fmbslen
#define _fjstrcspn  _fmbscspn
#define _fjstrspn   _fmbsspn
#define _fjstrset   _fmbsset
#define _fjstrnset  _fmbsnset
#define _fbtom      _fmbsnccnt
#define _fmtob      _fmbsnbcnt
#define _fjstricmp  _fmbsicmp
#define _fjstrnicmp _fmbnicmp
#define _fjstrupr   _fmbupr
#define _fjstrlwr   _fmblwr
#define _fchkctype  _fmbbtype
#define _fnthctype  _fmbsbtype
#endif  /* ! __STDC__ */
#endif  /* ! __FLAT__ */
#endif  /* _MSC */


#endif /* __JSTRING_H */
