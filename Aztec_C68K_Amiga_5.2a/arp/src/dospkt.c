/* arp'd dos_packet() */

#include <libraries/arpbase.h>
#include <functions.h>
#include <errno.h>
#include <stdarg.h>


/*doc dos_packet
NAME
    dos_packet -- Send an AmigaDOS packet

SYNOPSIS
    long dos_packet (struct MsgPort *port, long type, ...)

FUNCTION
    Sends a DOS packet to the specified handler.  This is a replacement
    for the Aztec C dos_packet() routine that calls Arp SendPacket().

    Other improvements over the MANX version (some are derivitive of
    SendPacket()'s implementation):
	. errno is set to Res2.
	. IoErr() can also be used to fetch Res2.
	. pr_PktWait() is called.

INPUTS
    port - Handler MsgPort
    type - Packet Action code
    args - Packet arguments

RESULTS
    Res1 from the Packet (return value from SendPacket())
    errno - Res2 from the Packet

MODULE
    dospkt.c
*end */

long
dos_packet(struct MsgPort *port, long type, ...)
{
    va_list arg;
    long ret;

    va_start(arg,type);
    ret = SendPacket (type, arg, port);
    va_end(arg);

    errno = IoErr();

    return ret;
}
