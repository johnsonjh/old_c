/* Copyright 1989 Manx Software Systems, Inc. All rights reserved */

#include <graphics/gfxmacros.h>
#include <functions.h>

#undef SetWrMsk

void
SetWrMsk(struct RastPort *rp, long mask)
{
	rp->Mask = mask;
}

