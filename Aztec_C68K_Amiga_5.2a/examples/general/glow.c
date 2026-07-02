/*---------------------------------------------------------------*
 *	glow.c							08/31/89	Keith Young
 *
 *	This program shows an example 'C' VBlank Interrupt Server.  
 *
 *	In this example, the interrupt routine cycles a color register,
 *	but there are any number of other useful things it could do every
 *	time the screen is drawn ;-)
 *
 *	I wrote it not long ago (using information/code from various
 *	sources) and after a recent query about Interrupts on CIS, I
 *	decided to go ahead and post it. 
 *	
 *	I hereby place this code into the PUBLIC DOMAIN.  You may do
 *	with this code, anything you wish (whatever floats your boat).
 *
 *	Just keep in mind....
 *		a) this was a quick hack
 *		b) It is only meant as an example.
 *		c) I disclaim any and all responsibility for any ill-effects...
 * 
 *	This code was written using Manx 3.6a (where's that new
 *	version... ??)
 *
 *  compile:	1> cc glow
 *     link:	1> ln glow -lc
 *
 *	(if you get any warnings, you need to fix your functions.h
 *	file <grin> )
 *--------------------------------------------------------------*/

#include <intuition/intuitionbase.h>
#include <graphics/gfxbase.h>
#include <exec/interrupts.h>
#include <exec/memory.h>
#include <functions.h>

struct IntuitionBase	*IntuitionBase;
struct GfxBase			*GfxBase;

struct ViewPort			*VPort;			/* ViewPort for color changes */
struct Interrupt		VBlankServer;	/* our Interrupt Server */

unsigned long lag	= 1L;		/* lag time between color changes */
unsigned long count = 0L;		/* counter used with lag (above) */
unsigned long creg	= 0L;		/* color register to change */
unsigned long hue 	= 0L;		/* new color value */
unsigned long add	= 1L;		/* adding to color? or subracting? */

/*---------------------------------------------------------------*
 * GlowVBlank()
 *
 *	This is an example 'C' VBlank Interrupt routine. It first
 * gets the registers setup correctly by calling the Manx supplied
 * interrupt support routine 'int_start()'.  It then does it's thing
 * (notice that it has access to the program's global variables) and
 * resets the registers with 'int_end()'.
 *
 * Remember, keep it short, this is C, and gets called (roughly) 60
 * times a second <grin>.
 *--------------------------------------------------------------*/
void
GlowVBlank()
{
	int_start();				/* Manx Interrupt setup routine */

	if( lag )					/* don't want to "divide by zero" */
		count = ++count % lag;

	if( !count ) {				/* cycle color when counter wraps */
		if( add ) {				/* adding color ? */
			++hue;
			if( hue > 11 )
				add = 0;
		}
		else {					/* else subracting */
			--hue;
			if( !hue )
				add = 1;
		}
		SetRGB4(VPort, creg, 0L, hue+2L, hue);	/* set the new color */
	}

	int_end();					/* Manx Interrupt cleanup routine */
}

/*---------------------------------------------------------------*
 *	AddVBlankServer()
 *
 *	Fill in the VBlankServer structure, then add the server
 *--------------------------------------------------------------*/
void
AddVBlankServer()
{
	VBlankServer.is_Data		= (APTR)NULL;
	VBlankServer.is_Code		= GlowVBlank;	/* pointer to our C routine */
	VBlankServer.is_Node.ln_Succ= NULL;
	VBlankServer.is_Node.ln_Pred= NULL;
	VBlankServer.is_Node.ln_Type= NT_INTERRUPT;
	VBlankServer.is_Node.ln_Pri	= 0;
	VBlankServer.is_Node.ln_Name= "glow";

	AddIntServer(5L, &VBlankServer);
}

/*---------------------------------------------------------------*
 *	RemVBlankServer()
 *
 *	Remove the Interrupt Server
 *--------------------------------------------------------------*/
void
RemVBlankServer()
{
	RemIntServer(5L, &VBlankServer);
}

/*---------------------------------------------------------------*
 * main()
 *
 *	You know, where the program starts...
 * command line options:
 *
 *		1> glow [color register] [delay]
 *
 *		Where:
 *	[color register] =	a value from 0 to 32 (but heck, I don't
 *						actually check it) that tells the program
 *						which register to cycle.
 *	[delay]          =	is a value used to slow things down...
 *						0 = full speed, larger numbers = slower.
 *--------------------------------------------------------------*/
main(argc, argv)
int argc;
char *argv[];
{
extern unsigned long atol();
register int i, j;

	if( argv[1] )			/* first arg = color register to cycle */
		creg = atol( argv[1] );

	if( argv[2] )			/* second arg = delay value, bigger = slower */
		lag = atol(argv[2]);

	/* extern void *OpenLibrary(); */
	if(!(IntuitionBase = 
		(struct IntuitionBase *)
			OpenLibrary("intuition.library",LIBRARY_VERSION)))
		adios( 10, "No Intuition?" );

	if(!(GfxBase = 
		(struct GfxBase *) OpenLibrary("graphics.library",LIBRARY_VERSION)))
		adios( 20, "No GfxBase" );

	VPort = &IntuitionBase->FirstScreen->ViewPort;	/* get ViewPort ptr */

	AddVBlankServer();		/* add interrupt server */

	Delay( 1000L );			/* wait a while... */

	RemVBlankServer();		/* remove the server */

	Chk_Abort();			/* did the user hit ^C ? */

	adios( 0, "[1;32mDone.[0m" );
}

/*---------------------------------------------------------------*
 * adios()
 *
 *	print msg to console, free anything allocated, close anything
 * opened and exit() with supplied return code.
 *--------------------------------------------------------------*/
adios( rc, msg )
int rc;
char *msg;
{
	if( msg )
		puts( msg );

	if(IntuitionBase)
		CloseLibrary((struct Library *)IntuitionBase);

	if(GfxBase)
		CloseLibrary((struct Library *)GfxBase);

	exit( rc );
}

/*---------------------------------------------------------------*
 * _abort()
 *
 *	This over-rides the Manx _abort() function that is
 * called from Chk_Abort() when the user presses ^C in the CLI
 * after starting the program, it calls our own clean-up routine.
 *
 *	This is needed to keep the program from terminating before
 * we remove the interrupt server... otherwise, the interrupt
 * server chain will get badly munged when it tries to execute
 * code that is no longer there :).
 *
 *	As a side-note, it's a good idea to always include such a
 * replacement _abort() routine, so that you can do your normal
 * clean-up before exiting.
 *--------------------------------------------------------------*/
_abort()
{
	adios( 63, "[33;1m** BREAK[0m" );
}
