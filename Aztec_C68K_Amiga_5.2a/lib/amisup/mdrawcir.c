/* Copyright 1989 Manx Software Systems, Inc. All rights reserved */

#include <graphics/gfxmacros.h>
#include <functions.h>

#undef DrawCircle

void
DrawCircle(struct RastPort *rp, long cx, long cy, long r)
{
	DrawEllipse(rp,cx,cy,r,r);
}

