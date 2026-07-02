/* Copyright 1989 Manx Software Systems, Inc. All rights reserved */

#include <graphics/gfxmacros.h>
#include <functions.h>

#undef SetDrPt

void
SetDrPt(struct RastPort *rp, long pattern)
{
	rp->LinePtrn = pattern;
	rp->Flags |= FRST_DOT;
	rp->linpatcnt = 15;
}

