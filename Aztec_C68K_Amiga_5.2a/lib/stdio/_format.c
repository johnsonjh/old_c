/* Copyright 1989 Manx Software Systems, Inc. All rights reserved */

/*
 *	Synopsis
 *
 *	int _format(FILE *stream, const char *format, va_list varg);
 *
 *
 *	Description
 *
 *		The format shall be a multibyte character sequence, beginning and
 *	ending in its initial shift state. The format is composed of zero or more
 *	directives: ordinary multibyte characters (not %), which are copied
 *	unchanged to the output stream; and conversion specifications, each of
 *	which results in fetching zero or more subsequent arguments. Each
 *	conversion specification is introduced by the character %. After the %, the
 *	following appear in sequence:
 *
 *	  - Zero or more flags that modify the meaning of the conversion
 *		specification.
 *
 *	  - An optional decimal integer specifying a minimum field width. If the
 *		converted value has fewer characters than the field width, it will be
 *		padded with spaces on the left (or right, if the left adjustment flag,
 *		described later, has been given) to the field width.
 *
 *	  - An optional precision that gives the minimum number of digits to appear
 *		for the d, i, o, u, x, and X conversions, the number of digits to
 *		appear after the decimal-point character for e, E, and f conversions,
 *		the maximum number of significant digits for the g and G conversions,
 *		or the maximum number of characters to be written from a string in s
 *		conversion. The precision takes the form of a period (.) followed by an
 *		optional decimal integer, if the integer is omitted, it is treated as
 *		zero.
 *
 *	  - An optional h specifying that a following d, i, o, u, x, or X
 *		conversion specifier applies to a short int or unsigned short int
 *		argument (the argument will have been promoted according to integral
 *		promotions, and its value shall be converted to short int or unsigned
 *		short int before printing); an optional h specifying that a following n
 *		conversion specifier applies to a pointer to a short int argument; an
 *		optional l (ell) specifying that a following d, i, o, u, x, or X
 *		conversion specifier applies to a long int or unsigned long int
 *		argument; an optional l specifying that a following n conversion
 *		specifier applies to a pointer to a long int argument; or an optional L
 *		specifying that a following e, E, f, g, or G conversion specifier
 *		applies to a long double argument. If an h, l, or L appears with any
 *		other conversion specifier, the behavior is undefined.
 *
 *	  - A character that specifies the type of conversion to be applied.
 *
 *		A field width or precision, or both, may be indicated by an asterisk *
 *	instead of a digit string. In this case, an int argument supplies the field
 *	width or precision. The arguments specifying field width or precision, or
 *	both, shall appear (in that order) before the argument (if any) to be
 *	converted. A negative field width argument is taken as a - flag followed by
 *	a positive field width. A negative precision argument is taken as if it
 *	were missing.
 *
 *		The flag characters and their meanings are:
 *
 *	-	The result of the conversion will be left-justified within the field.
 *
 *	+	The result of a signed conversion will always begin with a plus or
 *		minus sign.
 *
 *	space	If the first character of a signed conversion is not a sign, or if
 *			a signed conversion results in no characters, a space will be
 *			prepended to the result. If the space and + flags both appear, the
 *			space flag will be ignored.
 *
 *	#	The result is to be converted to an "alternate form." For o conversion,
 *		it increases the precision to force the first digit of the result to be
 *		a zero. For x (or X) conversion, a nonzero result will have 0x (or 0X)
 *		prepended to it. For e, E, f, g, and G conversions, the result will
 *		always contain a decimal-point character, even if no digits follow it
 *		(normally, a decimal-point character appears in the result of these
 *		conversions only if a digit follows it). For g and G conversions,
 *		trailing zeros will NOT be removed from the result. For other
 *		conversions, the behavior is undefined.
 *
 *	0	For d, i, o, u, x, X, e, E, f, g, and G conversions, leading zeros
 *		(following any indication of a sign or base) are used to pad to the
 *		field width; no space padding is performed. If the 0 and - flags both
 *		appear, the 0 flag will be ignored. For d, i, o, u, x, and X
 *		conversions, if a precision is specified, the 0 flag will be ignored.
 *		For other conversions, the behavior is undefined.
 *
 *		The conversion specifiers and their meanings are:
 *
 *	d,i	The int argument is converted to signed decimal (d or i), unsigned
 *	o,u	octal (o), unsigned decimal (u), or unsigned hexadecimal notation
 *	x,X	(x or X); The letters abcdef are used for x conversion and the
 *		letters ABCDEF for X conversion. The precision specifies the
 *		minimum number of digits to appear; if the value being converted
 *		can be represented in fewer digits, it will be expanded with
 *		leading zeros. The default precision is 1. The result of converting
 *		a zero value with an explicit precision of zero is no characters.
 *
 *	f	The double argument is converted to decimal notation in the style
 *		[-]ddd.ddd, where the number of digits after the decimal-point
 *		character is equal to the precision specification. If the precision is
 *		missing, it is taken as 6; if the precision is explicitly zero, no
 *		decimal-point character appears. If a decimal-point character appears,
 *		at least one digit appears before it. The value is rounded to the
 *		appropriate number of digits.
 *
 *	e,E	The double argument is converted in the style [-]d.ddde[+-]dd, where
 *		there is one digit before the decimal-point character (which is nonzero
 *		if the argument is nonzero) and the number of digits after it is equal
 *		to the precision; if the precision is missing, it is taken as 6; if the
 *		precision is zero, no decimal-point character appears. The value is
 *		rounded to the appropriate number of digits. The E conversion specifier
 *		will produce a number with E instead of e introducing the exponent. The
 *		exponent always contains at least two digits. If the value is zero, the
 *		exponent is zero.
 *
 *	g,G	The double argument is converted in style f or e (or in style E in the
 *		case of G conversion specifier), with the precision specifying the
 *		number of significant digits. If an explicit precisio is zero, it is
 *		taken as 1. The style used depends on the value converted; style e will
 *		be used only if the exponent resulting from such a conversion is less
 *		than -4 or greater than or equal to the precision. Trailing zeros are
 *		removed from the fractional portion of the result; a decimal-point
 *		character appears only if it is followed by a digit.
 *
 *	c	The int argument is converted to an unsigned char, and the resulting
 *		character is written.
 *
 *	s	The argument shall be a pointer to an array of character type.
 *		Characters from the array are written up to (but not including) a
 *		terminating null character; if the precision is specified, no more than
 *		that many characters are written. If the precision is not specified or
 *		is greater than the size of the array, the array shall contain a null
 *		character.
 *
 *	p	The argument shall be a pointer to void. The value of the pointer is
 *		converted to a sequence of printable characters, in an implementation-
 *		defined manner.
 *
 *	n	The argument shall be a pointer to an integer into which is written the
 *		number of characters written to the output stream so far by this call
 *		to _format. No argument is converted.
 *
 *	%	A % is written. No argument is converted. The complete conversion
 *		specification shall be %%.
 *
 *		If a conversion specification is invalid, the behavior is undefined.
 *
 *		If any argument is, or points to, a union or aggregate (except for an
 *	array of character type using %s conversion, or a pointer cast to be a
 *	pointer to void using %p converstion), the behavior is undefined.
 *
 *		In no case does a nonexistent or small field width cause truncation of
 *	a field; if the result of a conversion is wider than the field width, the
 *	field is expanded to contain the conversion result.
 *
 *
 *	Returns
 *
 *		The _format function returns the number of characters transmitted, or a
 *	negative value if an output error occurred.
 */


#include <stdio.h>
#include <ctype.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>

#define PMISSING (32198)	/* unlikely precision */
#define SLEN 512
#define SLAST (SLEN-1)

#define LEFTJ		0x0001
#define SIGNED		0x0002
#define SPACED		0x0004
#define ALTERED		0x0008
#define SINTCONV	0x0010
#define NEGVAL		0x0020
#define LONGVAL		0x0040
#define SHORTVAL	0x0080
#define LONGDOUBLE	0x0100

#ifdef FLOAT
static void ldtoa(long double number, char *buffer, int maxwidth, int mode);
#endif

int
_format(register FILE *stream, const char *format, va_list varg)
{
	register short flags;
	register int i;
	register unsigned char c;
	int charcount;
	int fillc;
	int precision, width;
	auto char s[SLEN];
#ifdef FLOAT
	long double ld;
#endif

	charcount = 0;
	for (;;) {
		{
			register const char *fmt;

			if ((c = *(fmt=format)) == '\0')
				return(charcount);
			++fmt;
			if ( c != '%' ) {
				i = charcount;
				do {
					if (putc(c, stream) == EOF)
						goto errout;
					++i;
					if ((c = *fmt) == '\0')
						return(i);
					++fmt;
				} while (c != '%');
				charcount = i;
			}
			flags = 0;
			fillc = ' ';
parse_flags:
			switch (c = *fmt++) {
			case '-':
				flags |= LEFTJ;
				goto parse_flags;
			case '+':
				flags |= SIGNED;
				goto parse_flags;
			case ' ':
				flags |= SPACED;
				goto parse_flags;
			case '#':
				flags |= ALTERED;
				goto parse_flags;

/* field width */
			case '*':
				i = va_arg(varg, int);
				if (i < 0) {
					flags |= LEFTJ;
					i = -i;
				}
				c = *fmt++;
				break;
			case '0':
				fillc = '0';
				/*FALLTHROUGH*/
			default:
				for (i = 0 ; isdigit(c) ; c = *fmt++)
					i = (i*8+i+i) + c - '0';

			} /* endswitch */
			width = i;

/* precision */
			i = PMISSING;
			if (c == '.') {
				if ((c = *fmt++) == '*') {
					i = va_arg(varg, int);
					if (i < 0)
						i = PMISSING;
					c = *fmt++;
				} else {
					for (i = 0 ; isdigit(c) ; c = *fmt++)
						i = (i*8+i+i) + c - '0';
				}
			}
			precision = i;
			if (c == 'h') {
				flags |= SHORTVAL;
				goto skip_l;
			}
			if (c == 'l') {
				flags |= LONGVAL;
				goto skip_l;
			}
			if (c == 'L') {
				flags |= LONGDOUBLE;
skip_l:
				c = *fmt++;
			}
			format = fmt;
		}
		{
			register char *cp;

			switch ( c ) {
			default:
				goto errout;

			case 'n':
				if (flags & SHORTVAL)
					*va_arg(varg, short int *) = charcount;
				else if (flags & LONGVAL)
					*va_arg(varg, long int *) = charcount;
				else
					*va_arg(varg, int *) = charcount;
				i = 0;
				break;
#ifdef FLOAT
			case 'e':
			case 'f':
			case 'g':
			case 'E':
			case 'G':
				flags |= SINTCONV;
				cp = s;
				if (precision == PMISSING)
					precision = 6;
				i = tolower((int)c) - 'e';
				if (isupper(c))
					i |= 0x10;
				if (flags & ALTERED)
					i |= 0x20;
				if (flags & LONGDOUBLE)
					ld = va_arg(varg, long double);
				else
					ld = va_arg(varg, double);
				ldtoa(ld, cp, precision, i);
				if (*cp == '-') {
					++cp;
					flags |= NEGVAL;
				}
				precision = SLEN;
				goto ilencp;
#endif
			case 's':
				cp = va_arg(varg, char *);
ilencp:
				i = strlen(cp);
				if (precision != PMISSING && i > precision)
					i = precision;
				break;
			case 'c':
				c = va_arg(varg, int);
				/*FALLTHROUGH*/
			case '%':
				*(cp = s) = c;
				i = 1;
				break;
			case 'o':
				i = 8;
				goto do_conversion;
			case 'p':
				flags |= ALTERED|LONGVAL;
				c = 'x';
				/*FALLTHROUGH*/
			case 'X':
			case 'x':
				i = 16;
				goto do_conversion;
			case 'i':
			case 'd':
				flags |= SINTCONV;
				/*FALLTHROUGH*/
			case 'u':
				i = 10;
do_conversion:
				{
					register unsigned long val;
					char *digits;

					if (precision != PMISSING) 
						fillc = ' ';
					digits = (c == 'X' ) ? "0123456789ABCDEF" :
															"0123456789abcdef";
					if (flags & LONGVAL)
						val = va_arg(varg, long);
					else if (flags & SINTCONV) {
						val = va_arg(varg, int);
						if (flags & SHORTVAL)
							val = (short)val;
					}
					else {
						val = va_arg(varg, unsigned int);
						if (flags & SHORTVAL)
							val = (unsigned short)val;
					}
					if (flags & SINTCONV) {
						if ((long)val < 0) {
							val = -val;
							flags |= NEGVAL;
						}
					}

					cp = &s[SLAST+1];

/*	The default precision is 1 */

					if (precision == PMISSING)
						precision = 1;

/*	The result of converting a 0 value with a 0 precision is no characters */

					if (val != 0 || precision != 0) {
						do {
							*--cp = digits[(int)(val%i)];
						} while ((val /= i) != 0);
					}

					i = &s[SLAST+1] - cp;	/* # of characters in |value| */
					if (flags & ALTERED) {
/*
 *	For o conversion, increase the precision to force the first digit of the
 *	result to be a zero.  For x (or X) conversion, a nonzero result will have
 *	0x (or 0X) prepended to it.
 */
						if (c == 'o') {
							if (i == 0 || (*cp != '0' && i >= precision))
								 precision = i+1;
						} else if (c == 'x' || c == 'X') {
							if (i != 0 && *cp != '0') {
hexprex:
								while (i < precision && cp > &s[2]) {
									*--cp = '0';
									++i;
								}
								if(!(flags&LEFTJ) && fillc == '0' &&
																width > i+2) {
									precision = width - 2;
									goto hexprex;
								}
								*--cp = c;
								*--cp = '0';
								i += 2;
							}
						}
					}
							
					while (i < precision && cp > &s[0]) {
						*--cp = '0';
						++i;
					}
				} /* end of do_conversion block statement */

			} /* endswitch */

			if (flags & SINTCONV) {
				if (flags & NEGVAL)
			    	*--cp = '-';
				else if (flags & SIGNED)
					*--cp = '+';
				else if (flags & SPACED)
					*--cp = ' ';
				else
					--i;	/* nullify following ++i; */
				++i;
			} 
			charcount += i;
			if ( !(flags & LEFTJ) ) {
/*
 *	While the following may be reasonable (instead of 000-1 you get	-0001),
 *	it doesn't seem to be blessed by ANSI C.
 */
				if (fillc == '0') {
					if ((flags&SINTCONV) && (flags & (NEGVAL|SIGNED|SPACED))) {
						if (putc(*cp++, stream) == EOF)
							goto errout;
						--width;
						--i;
					}
				}
				for (; width-- > i ; ++charcount) {
					if (putc(fillc, stream) == EOF)
						goto errout;
				}
			}

/*	Output characters cp[0] through cp[i-1] of the converted value */

			precision = i;		/* save value of i in meaningless variable */
			while (i--)
				if (putc(*cp++, stream) == EOF)
					goto errout;

			if (flags & LEFTJ) {
				i = precision;	/* restore i */
		 		for (; width-- > i ; ++charcount)
					if (putc(' ', stream) == EOF)
						goto errout;
			}
		}
	}
errout:
	return(-1);
}

#ifdef FLOAT

#ifdef _FLT_FFP
static long lround[] = {
	0xa0000044L, 0x80000041L, 0xa0000043L,
	0x80000040L, 0xcccccd3cL, 0xa3d70a39L, 0x83126e36L,
	0xd1b71632L, 0xa7c5ab2fL, 0x8637bc2cL, 0xd6bf9328L,
	0xabcc7625L, 0x89705e22L, 0xdbe6fd1eL, 0xafebfe1bL,
	0x8cbccb18L, 0xe12e1214L, 0xb424db11L, 0x901d7c0eL,
};
#define MAXWIDTH 16
#else
static long double round[] = { 10, 1, 5,
	5e-1, 5e-2, 5e-3, 5e-4, 5e-5, 5e-6, 5e-7, 5e-8, 5e-9, 5e-10,
	5e-11, 5e-12, 5e-13, 5e-14, 5e-15, 5e-16, 5e-17, 5e-18, 5e-19, 5e-20 };
#define MAXWIDTH 20
#endif

static
void
ldtoa(long double number, register char *buffer, int maxwidth, int mode)
{
	register int i;
	register int exp, digit, decpos, ndig;
	register int flag;
#ifdef _FLT_FFP
	register float *round = (float *)lround;
#endif

#ifndef _FLT_FFP
#if _FLT_MANX || _FLT_881 || _FLT_SANE
	if ((*(short *)&number&0x7fff) == 0x7fff) {
#else	/* _FLT_AMIGA */
	if ((*(short *)&number&0x7ff0) == 0x7ff0) {
#endif
		exp = (*(short *)&number&0x8000) ? '-' : '+';
		while (maxwidth--)
			*buffer++ = exp;
		*buffer = 0;
		return;
	}
#endif	/* _FLT_FFP */

	/*
	 *	Convert the number to a number between 1 and 10 or 0. Calculate the
	 *	exponent at the same time.
	 */

	exp = 0;
	if (number < 0.0) {
		number = -number;
		*buffer++ = '-';
	}
	if (number > 0.0) {
		while (number < round[1]) {
			number *= round[0];
			--exp;
		}
		while (number >= round[0]) {
			number /= round[0];
			++exp;
		}
	}


	/*
	 *	The number of digits to display is equal to the number of digits
	 *	following the decimal point (maxwidth) + digits to the left (exp) +
	 *	a guaranteed digit since the number 10 > x >= 1. For E format, the
	 *	exp digits are not counted, while G format works differently.
	 */

	flag = mode & 3;
	if (flag == 2) {						/* 'g' format */
		if (maxwidth == 0)
			maxwidth = 1;
		if (exp < -4 || exp >= maxwidth)
			flag = -1;						/* switch to 'e' format */
		ndig = maxwidth;
	} else if (flag == 1)					/* 'f' format */
		ndig = maxwidth + exp + 1;
	else									/* 'e' format */
		ndig = maxwidth + 1;

	/*
	 *	Round the number up using 5e-x where x is one more than the
	 *	precision of the number.
	 */

	if (ndig >= 0) {
		if ((number += round[(ndig>MAXWIDTH?MAXWIDTH:ndig)+2]) >= round[0]) {
			number = round[1];
			++exp;
			if (flag > 0)
				++ndig;
		}
	}

	if (flag > 0) {
		if (exp < 0) {
			*buffer++ = '0';
			*buffer++ = '.';
			i = -exp - 1;
			if (ndig <= 0)
				i = maxwidth;
			while (i--)
				*buffer++ = '0';
			decpos = 0;
		} else {
			decpos = exp+1;
		}
	} else {
		decpos = 1;
	}

	if (ndig > 0) {
		for (i = 0 ; ; ++i) {
			if (i < MAXWIDTH) {
				digit = (int)number;
				*buffer++ = digit+'0';
				number = (number - digit) * round[0];
			} else
				*buffer++ = '0';
			if (--ndig == 0)
				break;
			if (decpos && --decpos == 0)
				*buffer++ = '.';
		}
	}

	if (decpos && (mode&0x20))
		*buffer++ = '.';
	if (decpos == 0 && (flag == 2 || flag == -1) && (mode&0x20) == 0) {
		while (*--buffer == '0')
			;
		if (*buffer != '.')
			++buffer;
	}
	if (flag <= 0) {
		*buffer++ = (mode&0x10)?'E':'e';
		if (exp < 0) {
			exp = -exp;
			*buffer++ = '-';
		} else
			*buffer++ = '+';
		if (exp/1000) {
			*buffer++ = exp/1000 + '0';
			exp %= 1000;
		}
		*buffer++ = exp/100 + '0';
		exp %= 100;
		*buffer++ = exp/10 + '0';
		*buffer++ = exp%10 + '0';
	}
	*buffer = 0;
}
#endif /* FLOAT */

