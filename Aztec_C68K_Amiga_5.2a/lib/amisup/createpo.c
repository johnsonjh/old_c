/* Copyright (C) 1986 by Manx Software Systems, Inc. */
#include <exec/ports.h>
#include <exec/memory.h>
#include <functions.h>

struct MsgPort *
CreatePort(UBYTE *name, long pri)
{
	register struct MsgPort *mp;
	register long sig;

	if ((sig = AllocSignal(-1L)) == -1)
		return(0);
	if ((mp = AllocMem((long)sizeof(*mp), MEMF_PUBLIC|MEMF_CLEAR)) == 0) {
		FreeSignal(sig);
		return(0);
	}
	mp->mp_Node.ln_Name = (char *)name;
	mp->mp_Node.ln_Pri = pri;
	mp->mp_Node.ln_Type = NT_MSGPORT;
	mp->mp_Flags = 0;
	mp->mp_SigBit = sig;
	mp->mp_SigTask = FindTask(0L);
	if (name)
		AddPort(mp);
	else
		NewList(&mp->mp_MsgList);
	return(mp);
}

void
DeletePort(register struct MsgPort *mp)
{
	if (mp->mp_Node.ln_Name)
		RemPort(mp);
	mp->mp_Node.ln_Type = -1;
	mp->mp_MsgList.lh_Head = (struct Node *)-1;
	FreeSignal((long)mp->mp_SigBit);
	FreeMem(mp, (long)sizeof(*mp));
}

