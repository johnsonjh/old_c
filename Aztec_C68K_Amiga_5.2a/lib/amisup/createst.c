/* Copyright (C) 1986 by Manx Software Systems, Inc. */
#include <exec/io.h>
#include <functions.h>

struct IOStdReq *
CreateStdIO(struct MsgPort *mp)
{
	return((struct IOStdReq *)CreateExtIO(mp, (long)sizeof(struct IOStdReq)));
}

void
DeleteStdIO(struct IOStdReq *iop)
{
	DeleteExtIO((struct IORequest *)iop);
}

