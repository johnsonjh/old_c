/*	float.h

	Defines implementation specific macros for dealing with
	floating point.

	Copyright (c) Borland International 1987
	All Rights Reserved.
*/
#if __STDC__
#define _Cdecl
#else
#define _Cdecl	cdecl
#endif

#define FLT_RADIX			2
#define FLT_ROUNDS			1
#define FLT_GUARD			1
#define FLT_NORMALIZE			1

#define DBL_DIG				14
#define FLT_DIG				6
#define LDBL_DIG			14

#define DBL_MANT_DIG			53
#define FLT_MANT_DIG			24
#define LDBL_MANT_DIG			53

#define DBL_EPSILON			2.2204460492503131E-16
#define FLT_EPSILON			1.19209290E-07F
#define LDBL_EPSILON			2.2204460492503131E-16

#define DBL_MIN				2.225073858507201E-16
#define FLT_MIN				1.17549435E-38F
#define LDBL_MIN			2.225073858507201E-16

#define DBL_MAX				1.797693134862316E+308
#define FLT_MAX				3.40282347E+38F
#define LDBL_MAX			1.797693134862316E+308

#define DBL_MAX_EXP			+1024
#define FLT_MAX_EXP			+128
#define LDBL_MAX_EXP			+1024

#define DBL_MAX_10_EXP			+308
#define FLT_MAX_10_EXP			+38
#define LDBL_MAX_10_EXP			+308

#define DBL_MIN_10_EXP			-307
#define FLT_MIN_10_EXP			-37
#define LDBL_MIN_10_EXP			-307

#define DBL_MIN_EXP			-1021
#define FLT_MIN_EXP			-125
#define LDBL_MIN_EXP			-1021

unsigned int _Cdecl _clear87(void);
unsigned int _Cdecl _control87(unsigned int new, unsigned int mask);
void	     _Cdecl _fpreset(void);
unsigned int _Cdecl _status87(void);

/* 8087/80287 Status Word format   */

#define SW_INVALID		0x0001	/* Invalid operation		*/
#define SW_DENORMAL		0x0002	/* Denormalized operand		*/
#define SW_ZERODIVIDE		0x0004	/* Zero divide			*/
#define SW_OVERFLOW		0x0008	/* Overflow			*/
#define SW_UNDERFLOW		0x0010	/* Underflow			*/
#define SW_INEXACT		0x0020	/* Precision (Inexact result)	*/

/* 8087/80287 Control Word format */

#define MCW_EM			0x003f	/* interrupt Exception Masks	*/
#define	    EM_INVALID		0x0001	/*   invalid			*/
#define	    EM_DENORMAL		0x0002	/*   denormal			*/
#define	    EM_ZERODIVIDE	0x0004	/*   zero divide		*/
#define	    EM_OVERFLOW		0x0008	/*   overflow			*/
#define	    EM_UNDERFLOW	0x0010	/*   underflow			*/
#define	    EM_INEXACT		0x0020	/*   inexact (precision)	*/

#define MCW_IC			0x1000	/* Infinity Control		*/
#define	    IC_AFFINE		0x1000	/*   affine			*/
#define	    IC_PROJECTIVE	0x0000	/*   projective			*/

#define MCW_RC			0x0c00	/* Rounding Control		*/
#define	    RC_CHOP		0x0c00	/*   chop			*/
#define	    RC_UP		0x0800	/*   up				*/
#define	    RC_DOWN		0x0400	/*   down			*/
#define	    RC_NEAR		0x0000	/*   near			*/

#define MCW_PC			0x0300	/* Precision Control		*/
#define	    PC_24		0x0000	/*    24 bits			*/
#define	    PC_53		0x0200	/*    53 bits			*/
#define	    PC_64		0x0300	/*    64 bits			*/

/* 8087/80287 Initial Control Word */
/* should be same as in rules.asi  */

#define CW_DEFAULT (RC_NEAR+PC_64+EM_DENORMAL+EM_UNDERFLOW+EM_INEXACT)
