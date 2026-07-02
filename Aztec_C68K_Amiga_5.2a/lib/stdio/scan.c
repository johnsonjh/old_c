/* Copyright 1989 Manx Software Systems, Inc. All rights reserved */

/*
 *	Synopsis
 *
 *	int _scan(FILE *stream, const char *format, va_list varg);
 *
 *
 *	Description
 *
 *		The format shall be a multibyte character sequence, beginning and
 *	ending in its initial shift state. The format is composed of zero or more
 *	directives; one or more white-space characters; an ordinary multibyte
 *	character (not %); or a conversion specification. Each conversion
 *	specification is introduced by the character %. After the %, the following
 *	appear in sequence:
 *
 *	- An optional assignment-suppressing character *.
 *
 *	- An optional decimal integer that specifies the maximum field width.
 *
 *	- An optional h, l (ell) or L indicating the size of the receiving object.
 *		The conversion specifiers d, i, and n shall be preceded by h if the 
 *		corresponging argument is a pointer to short int rather than a pointer
 *		to int, or by l if it is a pointer to long int. Similarly, the
 *		conversion specifiers o, u, and x shall be preceded by h if the
 *		corresponding argument is a pointer to unsigned short int rather than a
 *		pointer to unsigned int, or by l if it is a pointer to unsigned long
 *		int. Finally, the conversion specifiers e, f, and g shall be preceded
 *		by l if the corresponding argument is a pointer to double rather than a
 *		pointer to float, or by L if it is a pointer to long double. If an h,
 *		l, or L appears with any other conversion specifier, the behavior is
 *		undefined.
 *
 *	- A character that specifies the type of conversion to be applied. The
 *		valid conversion specifiers are described below.
 *
 *		The _scan function executes each directive of the format in turn. If a
 *	directive fails, as detailed below, the _scan function returns. Failures
 *	are described as input failures (due to the unavailability or input
 *	characters), or matching failures (due to inappropriate input).
 *
 *		A directive composed of white space is executed by reading input up to
 *	the first non-white space character (which remains unread), or until no
 *	more characters can be read.
 *
 *		A directive that is an ordinary multibyte character is executed by
 *	reading the next characters of the stream. If one of the characters differs
 *	from one comprising the directive, the directive fails, and the differing
 *	and subsequent characters remain unread.
 *
 *		A directive that is a conversion specification defines a set of
 *	matching input sequences, as described below for each specifier. A
 *	conversion specification is executed in the following steps:
 *
 *		Input white-space characters (as specified by the isspace function) are
 *	skipped, unless the specification includes a [, c, or n specifier.
 *
 *		An input item is read from the stream, unless the specification
 *	includes an n specifier. An input item is defined as the longest sequence
 *	of input characters (up to any specified maximum field width) which is an
 *	initial subsequence of a matching sequence. The first character, if any,
 *	after the input item remains unread. If the length of the input item is
 *	zero, the execution of the directive fails: this condition is a matching
 *	failure, unless an error prevented input from the stream, in which case it
 *	is an input failure.
 *
 *		Except in the case of a % specifier, the input item (or, inthe case of
 *	a %n directive, the count of input characters) is converted to a type
 *	appropriate to the conversion specifier. If the input item is not a
 *	matching sequence, the execution of the directive fails: this condition is
 *	a matching failure. Unless assignment suppression was indicated by a *, the
 *	result of the conversion is placed in the object pointed to by the first
 *	argument following the format argument that has not already received a
 *	conversion result. If this object does not have an appropriate type, or if
 *	the result of the conversion cannot be represented in the space provided,
 *	the behavior is undefined.
 *
 *		The following conversion specifiers are valid:
 *
 *	d	Matches an optionally signed decimal integer, whose format is the same
 *		as expected for the subject sequence of the strtol function with the
 *		value 10 for the base argument. The corresponding argument shall be a
 *		pointer to integer.
 *
 *	i	Matches an optionally signed integer, whose format is the same as
 *		expected for the subject sequence fo the strtol function with the value
 *		0 for the base argument. The corresponding argument shall be a pointer
 *		to integer.
 *
 *	o	Matches an optionally signed octal integer, whose format is the same
 *		as expected for the subject sequence of the strtol function with the
 *		value 8 for the base argument. The corresponding argument shall be a
 *		pointer to unsigned integer.
 *
 *	u	Matches an optionally signed decimal integer, whose format is the same
 *		as expected for the subject sequence of the strtol function with the
 *		value 10 for the base argument. The corresponding argument shall be a
 *		pointer to unsigned integer.
 *
 *	x	Matches an optionally signed hexadecimal integer, whose format is the
 *		same as expected for the subject sequence of the strtol function with
 *		the value 10 for the base argument. The corresponding argument shall be
 *		a pointer to unsigned integer.
 *
 *	e,	Matches an optionally signed floating-point number, whose format is the
 *	f,	same as expected for the subject string of the strtod function. The
 *	g	corresponding argument shall be a pointer to floating.
 *
 *	s	Matches a sequence of non-white-space characters. The corresponding
 *		argument shall be a pointer to the initial character of an array large
 *		enough to accept the sequence and a terminating null character, which
 *		will be added automatically.
 *
 *	[	Matches a nonempty sequence of characters from a set of expected
 *		characters (the scanset). The corresponding argument shall be a pointer
 *		to the initial character of an array large enough to accept the
 *		sequence and a terminating null character, which will be added
 *		automatically. The conversion specifier includes all subsequent
 *		characters in the format string, up to and including the matching right
 *		bracket (]). The characters between the brackets (the scanlist)
 *		comprise the scanset, unless the character after the left bracket is a
 *		circumflex (^), in which case the scanset contains all characters that
 *		do not appear in the scanlist between the circumflex and the right
 *		bracket. As a special case, if the conversion specifier begins with []
 *		or [^], the right bracket character is in the scanlist and the NEXT
 *		right bracket character is the matching right bracket that ends the
 *		specification. If a - character is in the scanlist and is not the
 *		first, nor the second where the first character is a ^, nor the last
 *		character, the behavior is implementation-defined.
 *
 *	c	Matches a sequence of characters of the number specified by the field
 *		width (1 if no field width is present in the directive). The
 *		corresponding argument shall be a pointer to the initial character of
 *		an array large enough to accept the sequence. No null character is
 *		added.
 *
 *	p	Matches an implementation-defined set of sequences, which should be the
 *		same as the set of sequences that may be produced by the %p conversion
 *		of the _format function. The corresponding argument shall be a pointer
 *		to a pointer to void. The interpretation of the input item is 
 *		implementation-defined; however, for any input item other than a value
 *		converted earlier during the same program execution, the behavior of
 *		the %p conversion is undefined.
 *
 *	n	No input is consumed. The corresponding argument shall be a pointer to
 *		integer into which is written the number of characters read from the
 *		input stream so far by this call to the _scan function. Execution of a
 *		%n directive does not increment the assignment count returned at the
 *		completion of the _scan function.
 *
 *	%	Matches a single %; no conversion or assignment occurs. The complete
 *		conversion specification shall be %%.
 *
 *		If a conversion specification is invalid, the behavior is undefined.
 *
 *		The conversion specifiers, E, G, and X are also valid and behave the
 *	same as, respectively, e, g, and x.
 *
 *		If end-of-file is encountered during input, conversion is terminated.
 *	If end-of-file occurs before any characters matching the current directive
 *	have been read (other than leading white space, where permitted), execution
 *	of the current directive terminates with an input failure; otherwise,
 *	unless execution of the current directive is terminated with a matching
 *	failure, execution of the following directive (if any) is terminated with
 *	an input failure.
 *
 *		If conversion terminates on a conflicting input character, the
 *	offending input character is left unread in the input stream. Trailing
 *	white space (including new-line characters) is left unread unless matched
 *	by a directive. The success of literal matches and suppressed assignments
 *	is not directly determinable other than via the %n directive.
 *
 *
 *	Returns
 *
 *		The _scan function returns the value of the macro EOF if an input
 *	failure occurs before any conversion. Otherwise, the _scan function returns
 *	the number of input items assigned, which can be fewer than provided for,
 *	or even zero, in the event of an early matching failure.
 */

#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <ctype.h>
#include <string.h>

#define GETCH(stream)	(chcnt++,getc(stream))
#define UNGETCH(c,stream) (chcnt--,ungetc(c,stream))

#ifdef FLOAT
static long double dpower(int n);
static long double strtold(const char *str, char **ep);
#endif

int
_scan(FILE *stream, register const char *fmt, register va_list varg)
{
	long lv;
	register int c, chcnt, count, base, cc;
	char suppress, lflag, widflg, pushback;
	int maxwidth;
	int savchcnt, off;
#ifdef FLOAT
	char decpt, exp;
#endif
	char sign;
	char *cp;
	auto char tlist[130];
	static char list[] = "ABCDEFabcdef9876543210";
	static char vals[] = {
			10,11,12,13,14,15,10,11,12,13,14,15,9,8,7,6,5,4,3,2,1,0
	};

	chcnt = count = 0;
	while (c = *fmt++) {
		if (c == '%') {
			widflg = lflag = suppress = 0;
			maxwidth = 127;
			if (*fmt == '*') {
				++fmt;
				suppress = 1;
			}
			if (isdigit(c=*fmt)) {
				maxwidth = 0;
				do {
					maxwidth = maxwidth*10 + c - '0';
				} while (isdigit(c=*++fmt));
				widflg = 1;
			}
			if (c == 'l' || c == 'h' || c == 'L') {
				lflag = c;
				++fmt;
			}
	
			switch (cc = *fmt++) {
			case '%':
				c = '%';
				goto matchit;

			case 'd':
			case 'u':
				base = 10;
				goto getval;

			case 'i':
				base = 0;
				goto getval;

			case 'o':
				base = 8;
				goto getval;

			case 'p':
				lflag = 'l';
			case 'X':
			case 'x':
				base = 16;
				goto getval;

getval:
				while (isspace(pushback=GETCH(stream)))
					;
				if (UNGETCH((int)pushback, stream) == EOF)
					goto stopscan;
				if (maxwidth <= 0)
					goto stopscan;
				savchcnt = chcnt;
				lv = sign = 0;
				if ((c = GETCH(stream)) == '-' || c == '+') {
					if (c == '-')
						sign = 1;
					c = GETCH(stream);
				}
				switch (base)
				{
				case 8:
					if (!isdigit (c) || (isdigit (c) && c-'0' > 7))
						goto stopscan;
					break;
				case 10: case 0:
					if (!isdigit (c))
						goto stopscan;
					break;
				case 16:
					if (!isxdigit (c))
						goto stopscan;
					break;
				}
				if (chcnt-savchcnt+1 < maxwidth &&
									(base == 16 || base == 0) && c == '0') {
					if (tolower(c = GETCH(stream)) == 'x') {
						c = GETCH(stream);		/* get next for ungetting */
						if (base == 0)
							base = 16;
					}
					else if (base != 16)
						base = 8;
				}
				if (base == 0)
					base = 10;
				UNGETCH(c, stream);

				off = 0;
				if (base == 10)
					off = 12;
				if (base == 8)
					off = 14;

				for ( ; chcnt-savchcnt < maxwidth ; ) {
					if ((cp = strchr(list+off, c = GETCH(stream))) == 0) {
						UNGETCH(c, stream);
						break;
					}
					lv *= base;
					lv += vals[cp-list];
				}
				if (sign)
					lv = -lv;
putval:
				if (!suppress) {
					if (lflag == 'h')
						*va_arg(varg, short *) = lv;
					else if (lflag == 'l')
						*va_arg(varg, long *) = lv;
					else
						*va_arg(varg, int *) = lv;
					++count;
				}
				break;

			case 'n':
				lv = chcnt;
				count--;
				goto putval;

#ifdef FLOAT
			case 'E':
			case 'e':
			case 'f':
			case 'g':
			case 'G':
				while (isspace(pushback=GETCH(stream)))
					;
				if (UNGETCH((int)pushback, stream) == EOF)
					goto stopscan;

				sign = exp = decpt = 0;

				for (cp = tlist ; maxwidth-- ; *cp++ = c) {
					c = GETCH(stream);
					if (!isdigit(c)) {
						if (!decpt && c == '.')
							decpt = 1;
						else if (!exp && (c == 'e' || c == 'E') &&
																cp != tlist) {
							sign = 0;
							exp = decpt = 1;
							continue;
						} else if (sign || (c != '-' && c != '+')) {
							UNGETCH(c, stream);
							break;
						}
					}
					sign = 1;
				}
				*cp = 0;
				if (cp == tlist)
					goto stopscan;

				if (!suppress) {
					if (lflag == 'l')
						*va_arg(varg, double *) = strtold(tlist, (char *)0);
					else if (lflag == 'L')
						*va_arg(varg, long double *) =
												strtold(tlist, (char *)0);
					else
						*va_arg(varg, float *) = strtold(tlist, (char *)0);
					++count;
				}
				break;
#endif
			case 's':
				while (isspace(pushback=GETCH(stream)))
					;
				if (UNGETCH((int)pushback, stream) == EOF)
					goto stopscan;
				lflag = 2;
				goto charstring;
			case 'c':
				if (!widflg)
					maxwidth = 1;
				lflag = 3;
				goto charstring;
			case '[':
				lflag = 0;
				if (*fmt == '^') {
					++fmt;
					lflag = 1;
				}
				cp = tlist;
				if (*fmt == ']')
					*cp++ = *fmt++;
				while ((c = *fmt++) && c != ']')
					*cp++ = c;
				*cp = 0;
charstring:
				if (!suppress)
					cp = va_arg(varg, char *);
				widflg = 0;
				while (maxwidth--) {
					if ((c = GETCH(stream)) == EOF)
						break;
					if (lflag == 2) {
						if (isspace(c)) {
							UNGETCH(c, stream);
							break;
						}
					}
					else if (lflag < 2 && lflag == (strchr(tlist, c) != 0)) {
						UNGETCH(c, stream);
						break;
					}
					if (!suppress)
						*cp++ = c;
					widflg = 1;
				}
				if (!widflg)
					goto stopscan;
				if (!suppress) {
					if (cc != 'c')
						*cp = 0;
					++count;
				}
				break;

			}
		} else if (isspace(c)) {
			while (isspace(pushback=GETCH(stream)))
				;
			if (UNGETCH((int)pushback, stream) == EOF)
				goto stopscan;
		} else {
matchit:
			if ((pushback=GETCH(stream)) != c) {
				UNGETCH((int)pushback, stream);
				goto stopscan;
			}
		}
	}

stopscan:
	if (count == 0) {
		if ((pushback=GETCH(stream)) == EOF)
			return(EOF);
		UNGETCH((int)pushback, stream);
	}
	return count;
}

#ifdef FLOAT
static long double
strtold(register const char *str, register char **ep)
{
	register long double val, oldval;
	register const char *bp, *x, *op;
	int exp, oexp;
	char mflg = 0;

	for (bp=str;isspace(*bp);bp++)			/* scan past leading spaces */
		;
	if (*bp == '\0') {						/* return(0) if unable */
empty:
		if (ep != 0)
			*ep = (char *)str;
		return(0.0);
	}
	
	switch (*bp) {							/* may be preceded by '+' or '-' */
		case '-':
			mflg = 1;
			/* fall through */
		case '+':
			bp++;
			break;
		default:
			if (!isdigit(*bp) && *bp != '.')
				goto empty;
	}

	val = 0;
	for (x=bp;isdigit(*x);x++)				/* scan to end of first part */
		;
	op = x;
	val = 0;	
	for (x--;x>=bp;x--) {					/* calculate left of dec. pt. */
		oldval = val;
		val += (*x-'0') * dpower((int)(op-x-1));
		if (val < oldval) {					/*check for overflow*/
error:
			errno = ERANGE;
			if (mflg)
				return(-HUGE_VAL);
			return(HUGE_VAL);
		}
	}
	if (*op == '.') {
		for (x=op+1;isdigit(*x);x++)		/*calculate right of dec. pt.*/
			val += (*x-'0')/dpower((int)(x-op));
		op = x;
	}
	else
		x = op;
	if (*x == 'e' || *x == 'E') {			/* scientific notation? */
		if (*(x+1) == '-' || *(x+1) == '+')
			x++;
		if (isdigit(*(op=x+1))) {
			exp = 0;
			while (isdigit(*op)) {
				oexp = exp;
				exp = exp*10+*op-'0';
				if (exp < oexp) {
					if (*x == '-') {
						val = 0;
						exp = 0;
						errno = ERANGE;
						break;
					}
					else
						goto error;
				}
				op++;
			}
			if (*x == '-') {
				oldval = val;
				val /= dpower(exp);
				if ((oldval != 0.0)&&(val == 0.0)) /*underflow?*/
					errno = ERANGE;
			}
			else {
				oldval = val;
				val *= dpower(exp);
				if (val < oldval)		/*overflow?*/
					goto error;
			}
		}
	}
	if (ep != NULL)
		*ep = (char *)op;
	if (mflg)
		val = -val;
	return(val);
}

static long double
dpower(int n) 
{
	long double p;
	int i;
	p = 1;
	for (i=1; i<=n; ++i)
		p *=10.0;
	return(p); /* 10 to the nth power */
}
#endif

