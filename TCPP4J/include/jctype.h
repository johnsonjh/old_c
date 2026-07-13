/*  jctype.h

    Defines the jctype macros.

*/

/*
 *      C/C++ Run Time Library - Version 6.02
 *
 *      Copyright (c) 1987, 1994 by Borland International
 *      All Rights Reserved.
 *
 */

#ifndef __JCTYPE_H
#define __JCTYPE_H

#ifndef __CTYPE_H
#include <ctype.h>
#endif

#if !defined(___DEFS_H)
#include <_defs.h>
#endif

#if !defined(__MBCTYPE_H)
#include <mbctype.h>
#endif

#define _KNJ_M  __MBBS
#define _KNJ_P  __MBBP
#define _KNJ_1  __MBB1
#define _KNJ_2  __MBB2

#define _jctype _mbctype

#ifdef __cplusplus
extern "C" {
#endif
int _RTLENTRY iskmoji   (int __c);
int _RTLENTRY iskpun    (int __c);
int _RTLENTRY iskana    (int __c);
int _RTLENTRY iskata    (int __c);
int _RTLENTRY isalkana  (int __c);
int _RTLENTRY ispnkana  (int __c);
int _RTLENTRY isalnmkana(int __c);
int _RTLENTRY isprkana  (int __c);
int _RTLENTRY isgrkana  (int __c);
int _RTLENTRY iskanji   (int __c);
int _RTLENTRY iskanji2  (int __c);
#ifdef __cplusplus
}
#endif
#define iskmoji     _ismbbkalpha
#define iskpun      _ismbbkpunct
#define iskana      _ismbbkana
#define iskata      _ismbbkana
#define isalkana    _ismbbalpha
#define ispnkana    _ismbbpunct
#define isalnmkana  _ismbbalnum
#define isprkana    _ismbbprint
#define isgrkana    _ismbbgraph
#define iskanji     _ismbblead
#define iskanji2    _ismbbtrail

#ifndef _MSC

#ifdef __cplusplus
extern "C" {
#endif
int _RTLENTRY jiszen  (unsigned short __c);
int _RTLENTRY jisl0   (unsigned short __c);
int _RTLENTRY jisl1   (unsigned short __c);
int _RTLENTRY jisl2   (unsigned short __c);
int _RTLENTRY jisalpha(unsigned short __c);
int _RTLENTRY jisupper(unsigned short __c);
int _RTLENTRY jislower(unsigned short __c);
int _RTLENTRY jisdigit(unsigned short __c);
int _RTLENTRY jiskana (unsigned short __c);
int _RTLENTRY jiskata (unsigned short __c);
int _RTLENTRY jishira (unsigned short __c);
int _RTLENTRY jiskigou(unsigned short __c);
int _RTLENTRY jisspace(unsigned short __c);
int _RTLENTRY jisprint(unsigned short __c);
unsigned short _RTLENTRYF jtolower(unsigned short __c);
unsigned short _RTLENTRYF jtoupper(unsigned short __c);
unsigned short _RTLENTRYF jtohira (unsigned short __c);
unsigned short _RTLENTRYF jtokana (unsigned short __c);
unsigned short _RTLENTRYF jtokata (unsigned short __c);
unsigned short _RTLENTRYF zentohan(unsigned short __c);
unsigned short _RTLENTRYF hantozen(unsigned short __c);
unsigned short _RTLENTRYF jistojms(unsigned short __c);
unsigned short _RTLENTRYF jmstojis(unsigned short __c);
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

#endif /* ! _MSC */


#endif /* __JCTYPE_H */
