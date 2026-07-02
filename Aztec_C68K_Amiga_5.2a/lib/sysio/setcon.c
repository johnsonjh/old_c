/* Copyright (C) 1986,1987 by Manx Software Systems, Inc. */

#include <libraries/dosextens.h>
#include <fcntl.h>
#include <functions.h>

void
set_raw(void)
{
	struct Process *mp;

	mp = (struct Process *)FindTask(0L);     
    if (mp->pr_Task.tc_Node.ln_Type == NT_PROCESS && mp->pr_ConsoleTask)
		dos_packet((struct MsgPort *)mp->pr_ConsoleTask, 994L, -1L);
}

void
set_con(void)
{
	struct Process *mp;

	mp = (struct Process *)FindTask(0L);     
    if (mp->pr_Task.tc_Node.ln_Type == NT_PROCESS && mp->pr_ConsoleTask)
		dos_packet((struct MsgPort *)mp->pr_ConsoleTask, 994L, 0L);
}

