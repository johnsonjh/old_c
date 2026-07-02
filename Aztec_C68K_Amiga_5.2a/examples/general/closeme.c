/*
	CloseMe - a display hack by Charlie Gibbs

	This version was compiled on April 13, 1988.

	This program started out as a simple exercise in using
	Intuition's facilities, but I decided that if I'm going to
	learn about Intuition, I might as well have fun doing it.

	Special thanks goes to Larry Phillips for providing the basic
	idea, and to Leo Schwab for inspiring me to such perversions.

	This program opens up a screen of its own unless you run it
	from the CLI with a -w switch on the command line.  For some
	reason, it bogs down horribly when running on the Workbench
	screen, and steals some memory that it never gives back,
	although it behaves itself when run in a screen of its own.
	If anyone can tell me why it does this, I'd really appreciate it.
*/

#include <intuition/intuition.h>

#ifdef AZTEC_C
#   include <functions.h>
#endif

struct IntuitionBase *IntuitionBase;
struct GfxBase *GfxBase;

#define INTUITION_REV 0
#define GRAPHICS_REV  0
#define IMSG	struct IntuiMessage

int SeparateScreen = 1; /* Set to zero to play on the Workbench screen. */

SHORT bounce[] = {21, 15, 13, 9, 7, 5, 3, 1, 0};

struct NewScreen NewScreen = {
    0, 0, 640, 200, 2,		/* LeftEdge, TopEdge, Width, Height, Depth */
    0, 1,			/* DetailPen, BlockPen */
    HIRES, CUSTOMSCREEN,	/* ViewModes, Type */
    NULL,			/* Font */
    (UBYTE *)"Oh no, Charlie's acting strange again.",  /* DefaultTitle */
    NULL, NULL };		/* Gadgets, CustomBitMap */

struct NewWindow NewWindow = {
    20, 20, 300, 50,		/* LeftEdge, TopEdge, Width, Height */
    0, 1,			/* DetailPen, BlockPen */
    CLOSEWINDOW | MOUSEMOVE,	/* IDCMPFlags */
    WINDOWCLOSE | SMART_REFRESH | ACTIVATE | NOCAREREFRESH,	/* Flags */
    NULL, NULL, 		/* FirstGadget, CheckMark */
    (UBYTE *)"CloseMe",         /*
 Title */
    NULL, NULL, 		/* Screen, BitMap */
    1, 1, 640, 200,		/* MinWidth, MinHeight, MaxWidth, MaxHeight */
    WBENCHSCREEN } ;		/* Type */


main(argc, argv) int argc; char *argv[];
{
    struct Screen *Screen;
    struct Window *Window;
    IMSG  *message;
    ULONG cl;			/* Current message class */
    SHORT mx, my;		/* Current mouse co-ordinates */
    SHORT dx, dy;		/* Distance to move the window */
    SHORT maxx, maxy;		/* Don't move the window past here! */
    BOOL mousemove;		/* We got a MOUSEMOVE event. */
    int i;

    maxx = NewWindow.MaxWidth - NewWindow.Width - 20;
    maxy = NewWindow.MaxHeight - NewWindow.Height - 10;

/* Open libraries (the startup module already took care of dos.library) */

    IntuitionBase = (struct IntuitionBase *)
	OpenLibrary ("intuition.library", INTUITION_REV);
    if (IntuitionBase == NULL)
	exit (10);
    GfxBase = (struct GfxBase *) OpenLibrary ("graphics.library", GRAPHICS_REV);
    if (GfxBase == NULL)
	exit (10)
;

/* If desired, open a custom screen to work in.
    The -w command-line switch makes it go to the Workbench screen. */

    for (i = 1; i < argc; i++) {
	if ((argv[i][0] == '-')
	&& (argv[i][2] == '\0')
	&& (toupper (argv[i][1]) == 'W')) {
	    SeparateScreen = FALSE;
	    break;
	}
    }
    if (SeparateScreen) {
	if ((Screen = (struct Screen *) OpenScreen (&NewScreen)) == NULL)
	    exit (10);
	NewWindow.Screen = Screen;
	NewWindow.Type = CUSTOMSCREEN;
    }

/* Open a window and display some text. */

    if ((Window = (struct Window *) OpenWindow (&NewWindow)) == NULL)
	exit (10);
    Move (Window->RPort, 20, 20);
    Text (Window->RPort, "Go ahead, try to close me.", 26);


/* If the user tries to close the window, jump out of the way.
    Since the only event that can happen right now is WINDOWCLOSE,
    we can Wait() for anything and not bother testing what we get. */

    Wait (1 << Window->UserPort->mp_SigBit);
    MoveWindow (Window, 100L, 60L);
    NewWindow.LeftEdge += 100;
    NewWindow.TopEdge += 60;
    Move (Window->RPort, 20, 20);
    Text (Window->RPort, "Ha ha, you missed.  Try again.", 30);


/* Jump away when he tries the next time too. */

    Wait (1 << Window->UserPort->mp_SigBit);
    MoveWindow (Window, 100L, -30L);
    NewWindow.LeftEdge += 100;
    NewWindow.TopEdge -= 30;
    Move (Window->RPort, 20, 20);
    Text (Window->RPort, "Catch me if you can!          ", 30);


/* Run away from the mouse.  We CAN be cornered, though. */

    ReportMouse (TRUE, Window); /* Turn on reporting of mouse movements. */
    mousemove = FALSE;
    FOREVER {
	Wait (1 << Window->UserPort->mp_SigBit);        /* Wait for action. */
	while (message = (IMSG *)GetMsg (Window->UserPort)) {
	    if ((cl = message->Class) & MOUSEMOVE) {
		mousemove = TRUE;		/* It's a mouse movement. */
		mx = message->MouseX;		/* Save mouse co-ordinates. */
		my = message->MouseY;
	    }
	    ReplyMsg ((struct Message *)message);/* Reply ASAP-there may be more! */

	    if ((cl & CLOSEWINDOW)      /* If he caught the close gadget   */
	    && !mousemove		/*  in the middle of the screen... */
	    && (((NewWindow.LeftEdge > 0) && (NewWindow.LeftEdge < maxx))
		|| ((NewWindow.TopEdge > 0) && (NewWindow.TopEdge < maxy)))) {
		    mousemove = TRUE;		/*  ...fake a mouse movement. */
		    if (NewWindow.LeftEdge + 20 > maxx)
			mx = 17;
		    else
			mx = 15;
		    if (NewWindow.TopEdge + 10 > maxy)
			my = 6;
		    else
			my = 4;
	    }
	}
	if (mousemove) {
	    dx = mx - 16;
	/* Adjust to center of close gadget. */
	    dy = my - 5;
	    if (((dx * dx) / 4 + dy * dy) < 400) {      /* If he's near it... */
		if (dx > 0)
		    if (NewWindow.LeftEdge < 20)
			dx = -NewWindow.LeftEdge;	/* Stay on screen! */
		    else
			dx = -20;
		else
		    if (NewWindow.LeftEdge + 20 > maxx)
			dx = maxx - NewWindow.LeftEdge;
		    else
			dx = 20;
		if (dy > 0)
		    if (NewWindow.TopEdge < 10)
			dy = -NewWindow.TopEdge;
		    else
			dy = -10;
		else
		    if (NewWindow.TopEdge + 10 > maxy)
			dy = maxy - NewWindow.TopEdge;
		    else
			dy = 10;
		MoveWindow (Window, (long) dx, (long) dy);      /* Run away. */
		NewWindow.LeftEdge += dx;	/* Remember where we are. */
		NewWindow.TopEdge += dy;
	    }
	    mousemove = FALSE;
	}
	if ((dx == 0) && (dy == 0)      /* He cornered us... */
	&& (cl & CLOSEWINDOW))          /* ...and hit the close gadget. */
	    break;
    }
    ReportMouse (FALSE, Window);        /* Turn off mouse reporting. */
    Move (Window->RPort, 20, 20);
    Text (Window->RPort, "Arrgh!  I'm cornered!", 21);


/* Make him think he got rid of us. */

    Delay (100L);                       /* Wait two seconds... */
    CloseWindow (Window);               /*  ...then disappear. */
    if (SeparateScreen)
	CloseScreen (Screen);
    Delay (150L);                       /* Wait another three seconds. */
    NewWindow.LeftEdge = NewWindow.TopEdge = 0;
    if (SeparateScreen)
	Screen = (struct Screen *) OpenScreen (&NewScreen);
    Window = (struct Window *) OpenWindow (&NewWindow);
    Move (Window->RPort, 20, 20);
    Text (Window->RPort, "Bet you thought you had me.", 27);


/* The next time he hits the close gadget, roll up the window. */

    Wait (1 << Window->UserPort->mp_SigBit);
    Move (Window->RPort, 20, 20);
    Text (Window->RPort, "Augghhh!  I'm melting!     ", 27);
    while (NewWindow.Height > 10) {
	SizeWindow (Window, 0L, -5L);   /* Shrink vertically... */
	NewWindow.Height -= 5;
    }
    while (NewWindow.Width > 30) {
	SizeWindow (Window, -10L, 0L);  /*  ...then horizontally. */
	NewWindow.Width -= 10;
    }


/* Now fall and bounce across the floor. */

    Wait (1 << Window->UserPort->mp_SigBit);
    for (i = 0, dy = 1; i < 190; dy += 2) {     /* Fall down... */
	if (i + dy > 190)                       /*  ...but don't go    */
	    dy = 190 - i;			/*  through the floor! */
	MoveWindow (Window, 6L, (long) dy);
	i += dy;
    }
    for (i = 0; bounce[i]; i++) {
	for (dy = -bounce[i]; dy < 0; dy += 2)
	    MoveWindow (Window, 6L, (long) dy);         /* Bounce up. */
	for (dy = 1; dy <= bounce[i]; dy += 2)
	    MoveWindow (Window, 6L, (long) dy);         /* Fall back down. */
    }


/* Let him finally get rid of us. */

    Wait (1 << Window->UserPort->mp_SigBit);
    ModifyIDCMP (Window, (long) NEWSIZE);       /* Listen for sizing only */

    while (NewWindow.Height > 1) {
	SizeWindow (Window, -3L, -1L);  /* Shrink the close gadget... */
	Wait (1 << Window->UserPort->mp_SigBit);
	NewWindow.Height -= 1;
	NewWindow.Width -= 3;
    }
    SizeWindow (Window, -2L, 0L);       /*  ...down to a single pixel... */
    WaitPort (Window->UserPort);
    message = (IMSG *)GetMsg (Window->UserPort);
    ReplyMsg ((struct Message *)message);
    Delay (50);
    CloseWindow (Window);               /*  ...then close it completely. */

    if (SeparateScreen)
	CloseScreen (Screen);
    CloseLibrary ((struct Library *)IntuitionBase);
    CloseLibrary ((struct Library *)GfxBase);
}
