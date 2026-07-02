/* Copyright 1989 Manx Software Systems, Inc. All rights reserved */

#include <graphics/gfxmacros.h>
#include <functions.h>

#undef CEND

void
CEND(struct UCopList *c)
{
	CWAIT(c, 10000L, 255L);
}

