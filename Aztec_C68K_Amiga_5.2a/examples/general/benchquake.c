/* BenchQuake, by Oren Peli. Copyright (c) 1988 BazboSoft! */

/* Should be called automatically from the 'Startup-Sequence' of all California
	residents!  */

#include <exec/ports.h>
#include <exec/types.h>
#include <devices/inputevent.h>
#include <devices/input.h>
#include <graphics/view.h>
#include <graphics/rastport.h>
#include <intuition/intuition.h>
#include <intuition/screens.h>
#include <functions.h>
struct Screen *MyOpenWorkBench(void); /* problem w/ C='s 2.04 proto */

#define REGISTER register

#ifdef FOOP
extern long OpenDevice();

extern struct MsgPort *CreatePort();
extern struct IOStdReq *CreateStdIO();
#endif

struct MsgPort *port = NULL;
struct IOStdReq *req;

long errdev = 0;

struct InputEvent ie;

#ifdef FOOP
void *OpenLibrary() , *IntuitionBase , *GfxBase;
struct Screen *OpenWorkBench();
#else
struct IntuitionBase *IntuitionBase;
struct GfxBase *GfxBase;
#endif

main()
{
	REGISTER WORD q , i , x , y;

	REGISTER struct RastPort *rp;
	REGISTER struct ViewPort *vp;

	REGISTER struct Screen *scr;

	IntuitionBase = (struct IntuitionBase *) 
		OpenLibrary("intuition.library" , 33L);
	GfxBase = (struct GfxBase *)
		OpenLibrary("graphics.library" , 33L);

	if (NOT IntuitionBase || NOT GfxBase)
		bye();

	if (NOT (port = CreatePort(0L , 0L) ) )
		bye();

	if (NOT (req = CreateStdIO(port) ) )
		bye();

	if (errdev = OpenDevice("input.device",0L,(struct IORequest *)req,0L))
		bye();

	puts("BenchQuake, by Oren Peli. Copyright (c) 1988 BazboSoft!");

	scr = MyOpenWorkBench();

	vp = &scr->ViewPort;
	rp = &scr->RastPort;

	x = vp->DxOffset;
	y = vp->DyOffset;

	for (i = 0 ; i <= random(200) + 50 ; i++)
		RangeRand( (LONG) random(27441) );

	req->io_Command = IND_WRITEEVENT;
	req->io_Flags = 0;
	req->io_Length = (long) sizeof(struct InputEvent);
	req->io_Data = (void *) &ie;

	ie.ie_NextEvent = NULL;
	ie.ie_Class = IECLASS_RAWMOUSE;
	ie.ie_TimeStamp.tv_secs = 0;
	ie.ie_TimeStamp.tv_micro = 0;
	ie.ie_Code = NULL;
	ie.ie_Qualifier = IEQUALIFIER_RELATIVEMOUSE;

	for (q = 1 ; q != 45 ; q++)
	{
		for (i = 0 ; i != 25 ; i++)
		{
			vp->DxOffset = RangeRand( (LONG) q * 2L) - q;
			vp->DyOffset = RangeRand( (LONG) q) - (q / 2);

			MakeScreen(scr);

			RethinkDisplay();

			ShiverPointer(q);
		}

		ScrambleRP(rp , scr , q);
		ScrambleRP(rp , scr , q);
		ScrambleRP(rp , scr , q);
		ScrambleRP(rp , scr , q);
		ScrambleRP(rp , scr , q);
	}

	for ( ; q != 0 ; q--)
	{
		for (i = 0 ; i != 20 ; i++)
		{
			vp->DxOffset = RangeRand( (LONG) q * 2L) - q;
			vp->DyOffset = RangeRand( (LONG) q) - (q / 2);

			MakeScreen(scr);

			RethinkDisplay();

			ShiverPointer(q);
		}

		ScrambleRP(rp , scr , q);
	}

	vp->DxOffset = x;
	vp->DyOffset = y;

	MakeScreen(scr);

	RethinkDisplay();

	bye();
}

ShiverPointer(q)
REGISTER WORD q;
{
	if (q < 1)
		q = 1;

	ie.ie_X = 2 * (RangeRand( (LONG) q) - (q / 2) );
	ie.ie_Y = 2 * (RangeRand( (LONG) q) - (q / 2) );

	DoIO((struct IORequest *)req);
}

ScrambleRP(rp , scr , q)
REGISTER WORD q;
REGISTER struct Screen *scr;
REGISTER struct RastPort *rp;
{
	REGISTER WORD srcx , srcy , width , height , destx , desty;

	if (q < 5)
		return;

	width = RangeRand( (LONG) q * 2L);
	height = RangeRand( (LONG) q);

	if (width < 1)
		width = 1;

	if (height < 1)
		height = 1;

	srcx = RangeRand( (LONG) scr->Width - width);
	srcy = RangeRand( (LONG) scr->Height - height);

	destx = srcx + RangeRand( (LONG) q * 2L) - q;
	desty = srcy + RangeRand( (LONG) q) - (q / 2);

	if (srcx < 0)
		srcx = 0;

	if (srcy < 0)
		srcy = 0;

	if (destx < 0)
		destx = 0;

	if (desty < 0)
		desty = 0;

	if (destx + width >= scr->Width)
		destx = scr->Width - width - 1;

	if (desty + height >= scr->Height)
		desty = scr->Height - height - 1;

	ClipBlit(rp , (LONG) srcx , (LONG) srcy , rp , (LONG) destx , (LONG) desty ,
												(LONG) width , (LONG) height , 0xC0L);
}

random(max)
REGISTER WORD max;
{
	static ULONG num;
	ULONG sec , mic;

/* 1.3 prototype for CurrentTime is different than 2.04's */ 
#ifndef USE1_3	
	CurrentTime(&sec , &mic);
#else
	CurrentTime((long *)&sec , (long *)&mic);
#endif

	num *= sec;
	num += mic;

	while (num > 32000)
		num = num >> 1;

	return( (WORD) (num % (ULONG) max) );
}

bye()
{
	if (NOT errdev)
		CloseDevice((struct IORequest *)req);

	if (req)
		DeleteStdIO(req);

	if (port)
		DeletePort(port);

	if (GfxBase)
		CloseLibrary((struct Library *)GfxBase);

	if (IntuitionBase)
		CloseLibrary((struct Library *)IntuitionBase);
}

#asm
	public _OpenWorkBench
	public _MyOpenWorkBench
_MyOpenWorkBench:
	jsr	_OpenWorkBench
	rts
#endasm


