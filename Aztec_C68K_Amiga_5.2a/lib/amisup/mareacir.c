/* Copyright 1989 Manx Software Systems, Inc. All rights reserved */

#include <graphics/gfxmacros.h>
#include <functions.h>

#undef AreaCircle

long
AreaCircle(struct RastPort *rp, long cx, long cy, long r)
{
	return(AreaEllipse(rp,cx,cy,r,r));
}

