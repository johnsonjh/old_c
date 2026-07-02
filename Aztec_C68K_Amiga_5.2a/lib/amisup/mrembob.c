/* Copyright 1989 Manx Software Systems, Inc. All rights reserved */

#include <graphics/gels.h>
#include <functions.h>

#undef RemBob

void
RemBob(struct Bob *bob)
{
	bob->Flags |= BOBSAWAY;
}

