#ifndef DOS_STDIO_H
#define DOS_STDIO_H
/*
**
**	$Filename: dos/stdio.h $
**	$Release: 2.04 $
**	$Revision: 36.5 $
**	$Date: 90/11/05 $
**
**	ANSI-like stdio defines for dos buffered I/O
**
**	(C) Copyright 1989,1990 Commodore-Amiga, Inc.
**	    All Rights Reserved
**
*/

#define ReadChar()		FGetC(Input())
#define WriteChar(c)		FPutC(Output(),(c))
#define UnReadChar(c)		UnGetC(Input(),(c))
/* next one is inefficient */
#define ReadChars(buf,num)	FRead(Input(),(buf),1,(num))
#define ReadLn(buf,len)		FGets(Input(),(buf),(len))
#define WriteStr(s)		FPuts(Output(),(s))
#define VWritef(format,argv)	VFWritef(Output(),(format),(argv))

/* types for SetVBuf */
#define BUF_LINE	0	/* flush on \n, etc */
#define BUF_FULL	1	/* never flush except when needed */
#define BUF_NONE	2	/* no buffering */

#endif	/* DOS_STDIO_H */
