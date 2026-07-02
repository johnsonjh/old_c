/* Copyright (C) 1986 by Manx Software Systems, Inc. */
#include <exec/io.h>
#include <exec/memory.h>
#include <functions.h>

struct IORequest *
CreateExtIO(struct MsgPort *mp, long size)
{
	register struct IORequest *iop;
	void *AllocMem();

	if (mp == 0)
		return(0);
	if ((iop = AllocMem(size, MEMF_PUBLIC|MEMF_CLEAR)) == 0)
		return(0);
	iop->io_Message.mn_Node.ln_Type = NT_MESSAGE;
	iop->io_Message.mn_Length = size;
	iop->io_Message.mn_ReplyPort = mp;
	return(iop);
}

void
DeleteExtIO(register struct IORequest *iop)
{
	if (iop == 0)
		return;
	iop->io_Message.mn_Node.ln_Type = -1;
	iop->io_Device = (struct Device *)-1;
	iop->io_Unit = (struct Unit *)-1;
	FreeMem(iop, (long)iop->io_Message.mn_Length);
}

