/* Copyright 1989 Manx Software Systems, Inc. All rights reserved */

#include <graphics/gfxmacros.h>
#include <functions.h>

#undef SetOPen

void
SetOPen(struct RastPort *rp, long pen)
{
	rp->AOlPen = pen;
	rp->Flags |= AREAOUTLINE;
}

