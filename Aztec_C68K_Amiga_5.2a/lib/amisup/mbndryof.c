/* Copyright 1989 Manx Software Systems, Inc. All rights reserved */

#include <graphics/gfxmacros.h>
#include <functions.h>

#undef BNDRYOFF

void
BNDRYOFF(struct RastPort *rp)
{
	rp->Flags &= ~AREAOUTLINE;
}

