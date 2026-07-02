/* :ts=8 bk=0
 * ing.c:  The next logical step in "Boing"-type display hacks.
 *
 * Written by Leo L. Schwab		8702.3
 * Released into the public domain, but please keep the original author's
 * name on it.
 *
 * Note: After preliminary experiments, I get the impression that this could
 * somehow be faster.  Suggestions appreciated.
 */

#include <exec/types.h>
#include <intuition/intuition.h>
#include <math.h>

#define	DEPTH		2


extern void	*OpenLibrary(), *OpenWindow(), *OpenScreen(), *AllocRaster(),
		*GetMsg(), *malloc();
extern long	VBeamPos();


struct NewScreen scrdef = {
	0, 0, 0, 0, DEPTH,	/*  Size filled in later  */
	0, 1,
	HIRES,
	CUSTOMSCREEN,
	NULL,
	NULL,			/*  Title filled in later  */
	NULL, NULL
};

struct NewWindow windef = {
	0, 30, 150, 10,
	-1, -1,
	CLOSEWINDOW,
	WINDOWCLOSE | WINDOWDRAG | WINDOWDEPTH | SMART_REFRESH | ACTIVATE,
	NULL, NULL,
	(UBYTE *)"Ing!",
	NULL, NULL,
	0, 0, 0, 0,
	WBENCHSCREEN
};


struct wlist {
	struct wlist *next, *prev;
	struct BitMap bitmap;
	long sizx, sizy;
	int maxx, maxy;
	int x, y, dx, dy;
	int maxdy;
};


struct Screen	*scr, *wb;
struct Window	*win;
struct BitMap	*bm1, bm2, barmap;
struct wlist	*listbase;
void		*IntuitionBase, *GfxBase;


main ()
{
	struct Window		*wbwin;
	struct ViewPort		*svp;
	register struct BitMap	*abm;
	struct BitMap		*wbbm, **vbm;
	register struct wlist	*this = NULL;
	struct wlist		*new;
	long			wide, high, barhigh, wbhigh;
	int			i;
	void			*msg;

	openstuff ();
	rnd ((short) -VBeamPos());
	wb = win -> WScreen;	/*  Workbench screen  */
	wbbm = wb -> RastPort.BitMap;
	scrdef.LeftEdge = wb -> LeftEdge;
	scrdef.TopEdge	= wb -> TopEdge;
	scrdef.Width	= wb -> Width;
	scrdef.Height	= wbhigh = wb -> Height;

	/*  Scan all windows in workbench screen  */
	for (wbwin = wb -> FirstWindow; wbwin; wbwin = wbwin -> NextWindow) {
		if (wbwin->Flags & BACKDROP && wbwin->Flags & WBENCHWINDOW) {
			scrdef.DefaultTitle = wbwin -> ScreenTitle;
			continue;
		}

		if (wbwin -> Height > wbhigh-21)
			continue;	/*  too tall, no fun  */
		if (wbwin -> Width > wb->Width - 40)
			continue;	/*  too wide, no fun  */

		/*  Allocate new entry in list  */
		if (!(new = malloc (sizeof (*new))))
			die ("malloc failed.");
		new -> prev = this;
		new -> next = NULL;
		if (this)
			this -> next = new;
		listbase = new;

		/*  Grab necessary info  */
		wide = new -> sizx = wbwin -> Width;
		high = new -> sizy = wbwin -> Height;
		new -> maxx = wb -> Width - wide;
		new -> maxy = wb -> Height - high;
		new -> x = wbwin -> LeftEdge;
		new -> y = wbwin -> TopEdge;
		new -> dx = new -> dy = 0;

		/*
		 * Compute maximum initial vertical velocity.
		 * (Do you know how long it took me to arrive at this
		 * formula?)
		 * Note:  If gravity is anything other than one, this
		 * formula falls apart.
		 */
		new -> maxdy = sqrt (2 * new->maxy + 0.25) - 0.5 + 1.0;

		/*  Create bitmap and copy window into it  */
		InitBitMap (&new -> bitmap, (long) DEPTH, wide, high);
		for (i=0; i<DEPTH; i++)
		if (!(new -> bitmap.Planes[i] = AllocRaster (wide, high)))
			die ("AllocRaster failed.");

		WindowToFront (wbwin);	/*  WindowToFront() doesn't happen  */
		Delay (5L);		/*  immediately, so wait.  */
		BltBitMap
		 (wbbm, (long) wbwin -> LeftEdge, (long) wbwin -> TopEdge,
		  &new -> bitmap, 0L, 0L,
		  wide, high, 0xC0L, 0xffL, NULL);

		this = new;
	}

	/*  All windows scanned and copied, now to do the hard part  */
	scr = OpenScreen (&scrdef);	/*  Clone WorkBench  */
	bm1 = scr -> ViewPort.RasInfo -> BitMap;
	svp = &scr -> ViewPort;

	/*  Make second set of bitplanes for double buffering  */
	wide = wb -> Width;
	InitBitMap (&bm2, (long) DEPTH, wide, wbhigh);
	for (i=0; i<DEPTH; i++)
		if (!(bm2.Planes[i] = AllocRaster (wide, wbhigh)))
			die ("AllocRaster 2 failed.");
	BltBitMap
	 (bm1, 0L, 0L, &bm2, 0L, 0L, wide, wbhigh, 0xc0L, 0xffL, NULL);

	/*  Create private bitmap to hold screen title bar  */
	barhigh = wb -> BarHeight;
	InitBitMap (&barmap, (long) DEPTH, wide, barhigh);
	for (i=0; i<DEPTH; i++)
		if (!(barmap.Planes[i] = AllocRaster (wide, barhigh)))
			die ("AllocRaster 3 failed.");
	BltBitMap
	 (bm1, 0L, 0L, &barmap, 0L, 0L, wide, barhigh, 0xc0L, 0xffL, NULL);

	i = 0;
	vbm = &scr -> ViewPort.RasInfo -> BitMap;
	abm = &bm2;
	while (1) {
		/*  Copy screen bar  */
		BltBitMap (&barmap, 0L, 0L,
			   abm, 0L, 0L,
			   wide, barhigh, 0xc0L, 0xffL, NULL);
		/*  Clear rest of screen  */
		BltBitMap (abm, 0L, 0L,
			   abm, 0L, barhigh,
			   wide, wbhigh-barhigh, 0L, 0xffL, NULL);

		/*  Scan window copies backwards  */
		for (this = listbase; this; this = this -> prev) {
			if ((this -> x += this -> dx) > this -> maxx) {
				this -> x = this->maxx * 2 - this->x;
				this -> dx = -this -> dx;
			} else if (this -> x < 0) {
				this -> x = -this -> x;
				this -> dx = -this -> dx;
			}

			if ((this -> y += this -> dy) > this -> maxy) {
				this -> y = this -> maxy;
				this -> dy = -rnd (this->maxdy - 4) - 4;
				this -> dx = rnd (31) - 15;
			} else
				this -> dy++;

			/*  Copy window image  */
			BltBitMap
			 (&this -> bitmap, 0L, 0L,
			  abm, (long) this -> x, (long) this -> y,
			  this -> sizx, this -> sizy, 0xc0L, 0xffL, NULL);
		}

		/*
		 * This is the hairy part.  I've tried to arrange things so
		 * that there will be a minimum of hashing, but under certain
		 * phases of the moon, it's unavoidable.  Sorry.
		 */
		Forbid ();
		if (i) {	/*  Ping  */
			*vbm = bm1;
			abm = &bm2;
		} else {	/*  Pong  */
			*vbm = &bm2;
			abm = bm1;
		}
		i = !i;
		/*  Surprise!  Intuition doesn't mind this!  */
		ScrollVPort (svp);
		Permit ();

		if (msg = GetMsg (win -> UserPort)) {
			ReplyMsg (msg);
			break;
		}
		WaitTOF ();
	}

	/*  Restore the original  */
	Forbid ();
	*vbm = bm1;
	ScrollVPort (svp);	/*  Ping!  */
	Permit ();

	closestuff ();
}


openstuff ()
{
	if (!(IntuitionBase = OpenLibrary ("intuition.library", 0L))) {
		printf ("Intuition missing.\n");
		exit (100);
	}

	if (!(GfxBase = OpenLibrary ("graphics.library", 0L))) {
		printf ("Art shop closed.\n");
		closestuff ();
		exit (100);
	}

	if (!(win = OpenWindow (&windef))) {
		printf ("Window painted shut.\n");
		closestuff ();
		exit (100);
	}
}

die (str)
char *str;
{
	puts (str);
	closestuff ();
	exit (100);
}

closestuff ()
{
	register int i;

	for (i=0; i<DEPTH; i++) {
		if (barmap.Planes[i])
			FreeRaster (barmap.Planes[i],
				    (long) wb->Width, (long) wb->BarHeight);
		if (bm2.Planes[i])
			FreeRaster (bm2.Planes[i],
			 	    (long) wb->Width, (long) wb->Height);
	}

	if (listbase)		freelist ();
	if (scr)		CloseScreen (scr);
	if (win)		CloseWindow (win);
	if (GfxBase)		CloseLibrary (GfxBase);
	if (IntuitionBase)	CloseLibrary (IntuitionBase);
}

freelist ()
{
	register struct wlist *this = listbase, *tmp;
	register int i;

	while (this) {
		for (i=0; i<DEPTH; i++)
			if (this -> bitmap.Planes[i])
				FreeRaster (this -> bitmap.Planes[i],
					    this -> sizx, this -> sizy);
		tmp = this;
		this = this -> prev;
		free (tmp);
	}
}
