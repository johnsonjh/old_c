/* Copyright (C) 1986,1987 by Manx Software Systems, Inc. */

#include <exec/memory.h>
#include <libraries/dosextens.h>
#include <stdarg.h>
#include <functions.h>

long
dos_packet(struct MsgPort *port, long type, ...)
{
	register struct StandardPacket *sp;
	register struct MsgPort *rp;
	register va_list arg;
	long ret;

	if ((rp = CreatePort(0L, 0L)) == 0)
		return(0);
	if ((sp = AllocMem((long)sizeof(*sp), MEMF_PUBLIC|MEMF_CLEAR)) == 0) {
		DeletePort(rp);
		return(0);
	}
	sp->sp_Msg.mn_Node.ln_Name = (char *)&sp->sp_Pkt;
	sp->sp_Pkt.dp_Link = &sp->sp_Msg;
	sp->sp_Pkt.dp_Port = rp;
	sp->sp_Pkt.dp_Type = type;
	va_start(arg, type);
	sp->sp_Pkt.dp_Arg1 = va_arg(arg, long);
	sp->sp_Pkt.dp_Arg2 = va_arg(arg, long);
	sp->sp_Pkt.dp_Arg3 = va_arg(arg, long);
	sp->sp_Pkt.dp_Arg4 = va_arg(arg, long);
	sp->sp_Pkt.dp_Arg5 = va_arg(arg, long);
	sp->sp_Pkt.dp_Arg6 = va_arg(arg, long);
	sp->sp_Pkt.dp_Arg7 = va_arg(arg, long);
	va_end(arg);
	PutMsg(port, &sp->sp_Msg);
	WaitPort(rp);
	GetMsg(rp);
	ret = sp->sp_Pkt.dp_Res1;
	FreeMem(sp, (long)sizeof(*sp));
	DeletePort(rp);
	return(ret);
}

