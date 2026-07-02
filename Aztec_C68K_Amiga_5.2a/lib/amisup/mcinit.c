/* Copyright 1989 Manx Software Systems, Inc. All rights reserved */

#include <graphics/gfxmacros.h>
#include <functions.h>

#undef CINIT

void
CINIT(struct UCopList *c, long n)
{
	UCopperListInit(c, n);
}

