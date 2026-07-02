/* Copyright 1989 Manx Software Systems, Inc. All rights reserved */

#include <graphics/gfxmacros.h>
#include <functions.h>

#undef CMOVE

void
CMOVE(struct UCopList *c, long a, long b)
{
	CMove(c,&a,b);
	CBump(c);
}

