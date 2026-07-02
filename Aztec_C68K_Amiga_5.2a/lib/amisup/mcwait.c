/* Copyright 1989 Manx Software Systems, Inc. All rights reserved */

#include <graphics/gfxmacros.h>
#include <functions.h>

#undef CWAIT

void
CWAIT(struct UCopList *c, long a, long b)
{
	CWait(c,a,b);
	CBump(c);
}

