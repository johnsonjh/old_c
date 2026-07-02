/* Copyright 1989 Manx Software Systems, Inc. All rights reserved */

#include <graphics/gfxmacros.h>
#include <functions.h>

#undef SetAfPt

void
SetAfPt(struct RastPort *rp, unsigned short *pattern, long size)
{
	rp->AreaPtrn = pattern;
	rp->AreaPtSz = size;
}

