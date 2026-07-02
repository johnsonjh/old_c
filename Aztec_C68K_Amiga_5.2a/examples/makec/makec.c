/*
	MakeC v1.5

		This is a program to allow "clipping" parts of pictures into
	C source code structures.  It will display an IFF picture or brush,
	then allow the user to "clip" sections of it with the mouse.  The
	section is then converted to C source code and written to a file.
		The program runs from the CLI only (after all, if you're doing any
	C programming, you are probably using the CLI anyway).
		Syntax is:

		MakeC iff_file

	New version 1.5 now includes scrolling support for SuperBitMaps, as
	well as gadget selection of output format.

	In order to get this thing to work, you have to link with iff_stuff.o.
*/


#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <exec/types.h>
#include <exec/ports.h>
#include <exec/memory.h>
#include <intuition/intuition.h>
#include <intuition/screens.h>
#include <graphics/gfxmacros.h>
#include <graphics/gfx.h>
#include "iff.h"

char iffname[40];		/* iff filename 					       */
char savename[41] = "C_clip";
char basename[40];

void ImageOut();
void BitMapOut();
struct BitMap *create_bitmap();

UWORD colortable[64];		/* save color map for later...	       */
SHORT colorcount = 0;		/* and the color count...	       */

FILE *ifffile = NULL;		/* This is the input picture	       */
FILE *outputfile = NULL;	/* This is the output source file(s).  */


BitMapHeader header;		/* This will hold the bitmap info...	  */

struct Screen *screen = NULL;	/* This will be the screen for the picture */
struct Window *window = NULL;	/* and the window to hold it	  */
struct BitMap *sbmap  = NULL;	/* and the actual bitmap */
struct RastPort *rport;

struct Rectangle clip;		/* the desired clip						   */

BOOL IMAGE_OUT = FALSE; 	/* flag for Image output				   */

struct GfxBase *GfxBase = NULL;     /* library stuff		       */
struct IntuitionBase *IntuitionBase = NULL;
struct LayersBase *LayersBase = NULL;

BOOL OpenStuff(void);           /* some prototypes                                                 */
void CloseStuff(void);
void MakeItC(void);
BOOL GetClip(struct Rectangle *clipit);
UBYTE GetName(char *name);
void RubberBand(struct Rectangle *clipit,BOOL show);
void WriteCode(char *savename);
void FindBaseName(char *base,char *name);
void close_bitmap(struct BitMap *bitmap);


/*
	Here's the main function. Doesn't seem to do a whole lot, does it?
*/

void main(argc,argv)
int argc;
char **argv;
{
	BOOL trouble = FALSE;

	if((argc<2) || (argv[1][0] == '?'))
		{
			printf("\n%s -- by Robert Kesterson",argv[0]);
			printf("\nThis program creates C source code from IFF pictures.");
			printf("\nThe picture is displayed as you clip areas with the mouse.");
			printf("\nWhile the window is active, pressing 'b' sends the screen");
			printf("\nto the back, 'f' brings it to the front, 'q' brings up the ");
			printf("\nsave/cancel/quit window, and 'h' homes the picture.");
			printf("\nfor further information, read the documentation.");
			printf("\nUsage is:  %s iff_file.\n",argv[0]);
			exit(0);
		}
	strcpy(iffname,argv[1]);
	trouble = OpenStuff();  /* open screen, window, file, libraries, etc */
	if(!trouble)
		MakeItC();                      /* do the clipping stuff */
	CloseStuff();                   /* close everything down */
}

/*
	OpenStuff() is a rather bloated routine that tries to handle just about
	everything.  It reads the IFF file and sets up a screen big enough to
	hold it (according to the file's BitMapHeader).  Then it allocates
	a bitmap for the image and opens a SuperBitMap window to put it in.
	Then it sets the colormap for the screen and reads the picture into
	the SuperBitMap.  Then it does some Layers fiddling to refresh the
	initial window, and returns to the caller.
*/

BOOL OpenStuff()
{
	struct NewScreen newscreen;
	struct NewWindow newwindow =
		{
			0,0,0,0,		/* left, top, width, height (fill in below) */
			-1,-1,			/* use default pens */
			MOUSEMOVE|MOUSEBUTTONS|VANILLAKEY,		/* IDCMP flags */
			BACKDROP|RMBTRAP|SUPER_BITMAP|BORDERLESS|ACTIVATE|GIMMEZEROZERO|REPORTMOUSE,
			NULL,			/* no gadgets */
			NULL,			/* no checkmark */
			NULL,			/* no title	*/
			NULL,			/* screen -- fill in below */
			NULL,			/* not superbitmap  ...yet...  */
			0,0,0,0,		/* max and min sizes */
			CUSTOMSCREEN
		};
	BOOL error;
	SHORT count;

	for(count=0;count<64;count++)
		colortable[count] = 0x0000;		/* initialize color table */
	IntuitionBase = (struct IntuitionBase *)OpenLibrary("intuition.library",0);
	GfxBase = (struct GfxBase *)OpenLibrary("graphics.library",0);
	LayersBase = (struct Library *)OpenLibrary("layers.library",0);
	if((!IntuitionBase) || (!GfxBase) || (!LayersBase))
		return TRUE;		/*  Like maybe you yanked your ROMs out?  */
	if((ifffile = fopen(iffname,"rb")) == NULL)
		{					/* hey dude, get the name right... */
			printf("\nCan't open IFF file!!\n");
			return TRUE;
		}					/* Open the IFF file and set up the screen */
	error = GetBMHD(ifffile,&header);
	if(error)
		{
			printf("\nFile error or invalid IFF file.\n");
			return TRUE;
		}
	newscreen.LeftEdge = header.x;		/* figure out what the screen */
	newscreen.TopEdge = header.y;		/* needs to look like */
	newscreen.ViewModes = 0;
	newscreen.Type = CUSTOMSCREEN | SCREENBEHIND | SCREENQUIET;
	newscreen.Width = header.pageWidth;
	newscreen.Height = header.pageHeight;
	newscreen.Depth = header.nplanes;
	newscreen.DetailPen = 0;
	newscreen.BlockPen = 1;
	newscreen.DefaultTitle = NULL;
	newscreen.Gadgets = NULL;
	newscreen.Font = NULL;				/* probably should declare one... */
	newscreen.CustomBitMap = NULL;
	error = GetViewModes(&newscreen, ifffile);
	if(error)
		{
			printf("\nProblem with viewmodes!\n");
			return TRUE;
		}
	if(newscreen.ViewModes & HIRES)                 /* prevent overscan and such */
		newscreen.Width = 640;				/* for this application */
	else
		newscreen.Width = 320;
	if(newscreen.ViewModes & LACE)
		newscreen.Height = 400;
	else
		newscreen.Height = 200;
	screen = (struct Screen *)OpenScreen(&newscreen);
	if(!screen)
		{									/* low on RAM, maybe? */
			printf("\nCan't open the screen!\n");
			return TRUE;
		}
	newwindow.Height = newscreen.Height;	/* make a screen-sized window */
	newwindow.Width = newscreen.Width;
	newwindow.Screen = screen;
	sbmap = create_bitmap(header.w,header.h,header.nplanes);
	if(sbmap == NULL)
		{
			printf("\nNo Memory for SuperBitMap!!\n");
			return TRUE;
		}
	newwindow.BitMap = sbmap;				/* jam it into the window */
	window = (struct Window *)OpenWindow(&newwindow);
	if(!window)
		{
			printf("\nCan't open a window!!\n");
			return TRUE;
		}
	rport = window->RPort;						/* need this later */
	colorcount = GetColorMap(ifffile,colortable);   /* fix the colors  */
	LoadRGB4(&screen->ViewPort,colortable,colorcount);
	error = ReadPic(sbmap,ifffile,&header);         /* read the image  */
	if(error)
		{
			printf("\nError decoding IFF file!\n");
			return TRUE;
		}
	LockLayerRom(window->WLayer);           /* refresh the window */
	CopySBitMap(window->WLayer);            /* (only do it this way the */
	UnlockLayerRom(window->WLayer);         /* first time.  After that, */
	ScreenToFront(screen);                          /* Intuition handles it) */
	return FALSE;
}


/*
	CloseStuff() attempts to figure out all the garbage I didn't already
	close somewhere and clean up after me.	Important when closing things
	elsewhere to set them to NULL so they don't get re-closed here.  Good
	way to get a lesson in meditation....
*/

void CloseStuff()
{
	if(ifffile)
		fclose(ifffile);
	if(sbmap)
		close_bitmap(sbmap);
	if(window)
		CloseWindow(window);
	if(screen)
		CloseScreen(screen);
	if(LayersBase)
		CloseLibrary(LayersBase);
	if(GfxBase)
		CloseLibrary(GfxBase);
	if(IntuitionBase)
		CloseLibrary(IntuitionBase);
}


/*
	MakeItC() lets you do the actual clipping of areas of the picture
	It keeps track of your clip and your motion around the superbitmap
	so things don't get confused.
*/

void MakeItC()
{
	UBYTE ready;
	BOOL contin = TRUE;

	do
		{
			clip.MaxX = clip.MaxY = clip.MinY = clip.MaxY = 0;
			ready = GetClip(&clip);         /* get the real clip */
			if(!ready)
				continue;
			ready = GetName(savename);      /* what should we call it? */
			switch(ready)
				{
					case 1:
						WriteCode(savename);    /* save */
						break;
					case 2:
						contin = FALSE; 		/* quit */
						break;
					case 3:
						break;					/* cancel */
				}
		}
	while(contin);
	return;
}

/*
	pointer data (see GetClip(), below).
*/

UWORD hand_data[] =
	{
		0x0000,0x0000,		/* control words */
		0x0000,0x0340,		/* data words	 */
		0x0340,0x0CB0,
		0x0550,0x0AA8,
		0x0558,0x0AA4,
		0x02A8,0x0554,
		0x02F8,0x6504,
		0x61F8,0x9204,
		0x73F8,0x8C04,
		0x3FF8,0x4004,
		0x1FF8,0x2004,
		0x1FF0,0x2008,
		0x07F0,0x1808,
		0x01E0,0x0610,
		0x00E0,0x0110,
		0x00C0,0x0100,
		0x0000,0x0000		/* more control words */
	};


/*
	purpose of this routine ( GetClip() ) is to rubberband an area of the
	picture to clip, or to scroll the bitmap around.  RubberBanding is
	done with the left button, while scrolling is done with the right.

	Mouse moves are handled more quickly by "looking ahead" until either
	the mouse stops moving or something besides a mousemove comes in.

	While scrolling around in the picture, the pointer is changed to a
	hand (a la MacPaint) to indicate scrolling is active.  Otherwise,
	the default system pointer is used.

	I should probably be shot for allowing a routine to be this large, but
	it really isn't as bad as it looks...
*/

BOOL GetClip(clipit)
struct Rectangle *clipit;
{
	struct IntuiMessage *msg = NULL;
	struct IntuiMessage tempmsg;
	BOOL mousedown = FALSE; 		/* TRUE if left mouse down */
	BOOL scrolldown = FALSE;		/* TRUE if right mouse down */
	BOOL message_ready = FALSE;		/* TRUE if tempmsg has a valid message */
	SHORT x,y;
	SHORT dx,dy;
	SHORT oldx,oldy;
										/* clear the port first thing */
	while(msg = (struct IntuiMessage *)GetMsg(window->UserPort));
	oldx = oldy = x = y = 0;
	do
		{
			oldx = x;
			oldy = y;
			if(!message_ready)
				{
					WaitPort(window->UserPort);             /* call me sometime */
					msg = (struct IntuiMessage *)GetMsg(window->UserPort);
					memcpy(&tempmsg,msg,(unsigned int)sizeof(struct IntuiMessage));
					ReplyMsg(msg);                          /* send it back */
				}
			else
				message_ready = FALSE;	/* fixin' to use tempmsg */
			x = tempmsg.MouseX;			/* where's the mouse? */
			y = tempmsg.MouseY;
			if(tempmsg.Class == MOUSEMOVE)  /* got a mouse in motion */
				{
					if(mousedown || scrolldown)     /* got a button down */
						{
							while(msg = (struct IntuiMessage *)GetMsg(window->UserPort))
								{				/* look ahead while moving */
									if(msg->Class == MOUSEMOVE)
										{
											x = msg->MouseX;
											y = msg->MouseY;
											ReplyMsg(msg);
											continue;
										}
									else		/* not moving anymore */
										{
											memcpy(&tempmsg,msg,(unsigned int)sizeof(struct IntuiMessage));
											ReplyMsg(msg);
											message_ready = TRUE;
											break;
										}
								}
						}
					if(mousedown)           /* clipping a piece already? */
						{
							clipit->MaxX = x + window->WLayer->Scroll_X;
							clipit->MaxY = y + window->WLayer->Scroll_Y;
							RubberBand(clipit,TRUE);        /* show it */
						}
					else if (scrolldown)    /* scrolling, are we? */
						{
							dx = (oldx - x);        /* get offsets */
							dy = (oldy - y);
/* bounds checks */			if(window->WLayer->Scroll_X + dx <0)
								dx = window->WLayer->Scroll_X;
							if(window->WLayer->Scroll_Y + dy <0)
								dy = window->WLayer->Scroll_Y;
							if(window->WLayer->Scroll_X +dx > (window->WLayer->SuperBitMap->BytesPerRow * 8-window->Width))
								dx = window->WLayer->SuperBitMap->BytesPerRow * 8-window->Width-window->WLayer->Scroll_X;
							if(window->WLayer->Scroll_Y + dy > window->WLayer->SuperBitMap->Rows-window->Height)
								dy = window->WLayer->SuperBitMap->Rows-window->Height-window->WLayer->Scroll_Y;
							if(window->WLayer->SuperBitMap->BytesPerRow*8 <= window->Width)
								dx = 0;
							if(window->WLayer->SuperBitMap->Rows <= window->Height)
								dy = 0;
/* Scroll BitMap */			ScrollLayer(window->WLayer->LayerInfo,window->WLayer,dx,dy);
							continue;
						}
				}
			if(tempmsg.Class == MOUSEBUTTONS)
				{
					if((mousedown) && (tempmsg.Code == SELECTUP))
						{					/* done drawing a clip */
							clipit->MaxX = x + window->WLayer->Scroll_X;	/* finished clip */
							clipit->MaxY = y + window->WLayer->Scroll_Y;
							mousedown = FALSE;			/* not clipping */
							RubberBand(clipit,FALSE);       /* erase border */
							if(clipit->MaxX <clipit->MinX)
								{						/* fix absolutes */
									x = clipit->MaxX;	/* min and max	 */
									clipit->MaxX = clipit->MinX;
									clipit->MinX = x;
								}
							if(clipit->MaxY <clipit->MinY)
								{
									y = clipit->MaxY;
									clipit->MaxY = clipit->MinY;
									clipit->MinY = y;
								}
							return TRUE;
						}
					if(!mousedown)
						{
							if(tempmsg.Code == SELECTDOWN)
								{					/* begin clipping */
									clipit->MinX = x + window->WLayer->Scroll_X;
									clipit->MinY = y + window->WLayer->Scroll_Y;
									mousedown = TRUE;
									continue;
								}
							else if(tempmsg.Code == MENUDOWN)
								{					/* begin scrolling */
									scrolldown = TRUE;
									SetPointer(window,&hand_data,15,14,0,0);
								}
							else if(tempmsg.Code == MENUUP)
								{					/* stop scrolling */
									scrolldown = FALSE;
									ClearPointer(window);   /* get that */
								}					/* hand outta there */
						}
				}
			if(tempmsg.Class == VANILLAKEY)
				switch(toupper(tempmsg.Code))
					{
						case 'B':
							ScreenToBack(screen);
							break;
						case 'F':
							ScreenToFront(screen);
							break;
						case 'H':                               /* home the bitmap */
							ScrollLayer(window->WLayer->LayerInfo,
								window->WLayer,0-window->WLayer->Scroll_X,0-window->WLayer->Scroll_Y);
							break;
						case 'Q':
							return TRUE;
					}
		}
	while(TRUE);
}

void RubberBand(struct Rectangle *clipit, BOOL show)
{
	static BOOL already_drawn = FALSE;		/* for first time draw */
	static struct Rectangle last;			/* for removing previous */

	SetDrMd(rport,COMPLEMENT);
	if(already_drawn)
		{									/* box exists - erase old */
			Move(rport,last.MinX,last.MinY);
			Draw(rport,last.MinX,last.MaxY);
			Draw(rport,last.MaxX,last.MaxY);
			Draw(rport,last.MaxX,last.MinY);
			Draw(rport,last.MinX,last.MinY);
		}
	if(!show)
		{
			already_drawn = FALSE;
			return;
		}
	else
		{									/* draw the box */
			Move(rport,clipit->MinX,clipit->MinY);
			Draw(rport,clipit->MinX,clipit->MaxY);
			Draw(rport,clipit->MaxX,clipit->MaxY);
			Draw(rport,clipit->MaxX,clipit->MinY);
			Draw(rport,clipit->MinX,clipit->MinY);
			already_drawn = TRUE;
		}
	last.MinX = clipit->MinX;				/* save for next time */
	last.MinY = clipit->MinY;
	last.MaxX = clipit->MaxX;
	last.MaxY = clipit->MaxY;
	return;
}

/*
	The following structures are all used in the GetName routine.
	The routine opens another window on top of the graphic image,
	with a string gadget for the filename to save, and five boolean
	gadgets (IMAGE, BITMAP, SAVE, CANCEL, and QUIT).
*/

struct IntuiText nametext =
	{	1,0,JAM1,2,2,NULL,NULL,NULL	};	/* fill out later */
SHORT namepairs[] =
	{	0,0, 241,0, 241,9, 0,9, 0,0	};
struct Border nameborder =
	{	-1,-1,3,0,JAM1,5,namepairs,NULL };
char namebuffer[40];
char undobuffer[40];
struct StringInfo nameinfo =				/* updated later  */
	{
		namebuffer,
		undobuffer,
		0,41,				/* buffer pos, max #chars. */
		0,					/* display position	   */
		0,0,0,0,0,NULL,0L,NULL, 	/* Intuition handles these... */
	};

/* these are for the BOOLGADGETS */

SHORT gadget_boxes[] =
	{
		  0,  0,
		 50,  0,
		 50, 12,
		  0, 12,
		  0,  0,
		  0, 12,
		  3, 12,
		  3, 13,
		 53, 13,
		 53,  2,
		 52,  2,
		 52, 13,
		 51, 13,
		 51,  2,
	};

struct Border gadget_border = { 0,0,3,0,JAM1,14,gadget_boxes,NULL };

struct IntuiText bitmap_text =
	{
		1,0,			/* FrontPen, BackPen */
		JAM1,			/* DrawMode */
		1,3,			/* left, top */
		NULL,			/* font */
		"BITMAP",                       /* the text */
		NULL,			/* next text */
	};

struct Gadget bitmap_gadget =
	{
		NULL,					/* next gadget (none) */
		133,28, 				/* left, top edges    */
		54,14,					/* width, height      */
		GADGHCOMP,				/* flag for highlighting */
		RELVERIFY|TOGGLESELECT, /* make sure they really want it */
		BOOLGADGET,			    /* boolean gadget */
		(APTR) &gadget_border,  /* GadgetRender */
		NULL,					/* SelectRender */
		&bitmap_text,			/* Gadget Text */
		NULL,NULL,				/* Mutual Exclude, special Info */
		6,NULL					/* ID, Userdata */
	};


struct IntuiText image_text =
	{
		1,0,			/* FrontPen, BackPen */
		JAM1,			/* DrawMode */
		5,3,			/* left, top */
		NULL,			/* font */
		"IMAGE",                /* the text */
		NULL,			/* next text */
	};

struct Gadget image_gadget =
	{
		&bitmap_gadget, 		/* next gadget (none) */
		43,28,					/* left, top edges    */
		54,14,					/* width, height      */
		GADGHCOMP,				/* flag for highlighting */
		RELVERIFY|TOGGLESELECT, /* make sure they really want it */
		BOOLGADGET,			    /* boolean gadget */
		(APTR) &gadget_border,  /* GadgetRender */
		NULL,					/* SelectRender */
		&image_text,			/* Gadget Text */
		0xFFFF,NULL,			/* Mutual Exclude, special Info */
		5,NULL					/* ID, Userdata */
	};


struct IntuiText save_text =
	{
		1,0,			/* FrontPen, BackPen */
		JAM1,			/* DrawMode */
		9,3,			/* left, top */
		NULL,			/* font */
		"SAVE",                 /* the text */
		NULL,			/* next text */
	};

struct Gadget save_gadget =
	{
		&image_gadget,			/* next gadget (none) */
		13,45,					/* left, top edges    */
		50,12,					/* width, height      */
		GADGHCOMP,				/* flag for highlighting */
		RELVERIFY,				/* make sure they really want it */
		BOOLGADGET,			    /* boolean gadget */
		(APTR) &gadget_border,  /* GadgetRender */
		NULL,					/* SelectRender */
		&save_text,				/* Gadget Text */
		NULL,NULL,				/* Mutual Exclude, special Info */
		1,NULL					/* ID, Userdata */
	};

struct IntuiText cancel_text =
	{
		1,0,			/* FrontPen, BackPen */
		JAM1,			/* DrawMode */
		1, 3,			/* left, top */
		NULL,			/* font */
		"CANCEL",                       /* the text */
		NULL,			/* next text */
	};

struct Gadget cancel_gadget =
	{
		&save_gadget,			/* next gadget */
		93,45,					/* left, top edges    */
		50,12,					/* width, height      */
		GADGHCOMP,				/* flag for highlighting */
		RELVERIFY,				/* make sure they really want it */
		BOOLGADGET,			    /* boolean gadget */
		(APTR) &gadget_border,  /* GadgetRender */
		NULL,					/* SelectRender */
		&cancel_text,			/* Gadget Text */
		NULL,NULL,				/* Mutual Exclude, special Info */
		3,NULL					/* ID, Userdata */
	};

struct IntuiText quit_text =
	{
		1,0,			/* FrontPen, BackPen */
		JAM1,			/* DrawMode */
		9, 3,			/* left, top */
		NULL,			/* font */
		"QUIT",                 /* the text */
		NULL,			/* next text */
	};

struct Gadget quit_gadget =
	{
		&cancel_gadget, 		/* next gadget (none) */
		173,45, 				/* left, top edges    */
		50,12,					/* width, height      */
		GADGHCOMP,				/* flag for highlighting */
		RELVERIFY,				/* make sure they really want it */
		BOOLGADGET,			    /* boolean gadget */
		(APTR) &gadget_border,  /* GadgetRender */
		NULL,					/* SelectRender */
		&quit_text,				/* Gadget Text */
		NULL,NULL,				/* Mutual Exclude, special Info */
		2,NULL					/* ID, Userdata */
	};

struct Gadget name_gadget =
	{
		&quit_gadget,
		5,10,
		240,10,
		GADGHCOMP,
		RELVERIFY,
		STRGADGET,
		(APTR) &nameborder,
		NULL,
		&nametext,
		NULL,
		(APTR)&nameinfo,
		4,NULL,
	};

struct NewWindow newnamewindow =
	{
		0,0,				/* left, top */
		260,75, 			/* width, height */
		0,1,				/* detail pen, block pen */
		INACTIVEWINDOW|WINDOWDRAG|GADGETUP,/* just use gadgets, with title bar */
		SMART_REFRESH|ACTIVATE|GIMMEZEROZERO,	/* IDCMP stuff */
		&name_gadget,		/* gadget list */
		NULL,				/* checkmark */
		"Enter SAVE filename",  /* title */
		NULL,				/* screen (fill later) */
		NULL,				/* bitmap */
		0,0,0,0,			/* max and min sizes */
		CUSTOMSCREEN,		/* screen type */
	};

/*
	GetName() is another of those rather bloated routines.  It gets a
	filename for the save, lets you specify Image or Bitmap output, and
	allows you to save it, cancel and continue, or quit the program
*/

UBYTE GetName(name)
char *name;
{
	struct Window *namewindow;
	struct IntuiMessage *msg;
	struct Gadget *gadg;
	UBYTE gadget_number;
	UWORD tempcolors[] = { 0x0888, 0x0FFF, 0x0F00, 0x0000 };
	ULONG class;

	strcpy(namebuffer,name);
	newnamewindow.Screen = screen;
	newnamewindow.LeftEdge = screen->Width/2-130;	/* center the window */
	newnamewindow.TopEdge = screen->Height/2-40;	/* visually, that is */
	image_gadget.Flags &= ~SELECTED;
	bitmap_gadget.Flags &= ~SELECTED;
	LoadRGB4(&screen->ViewPort,tempcolors,4);               /* set some colors */
	namewindow = (struct Window *)OpenWindow(&newnamewindow);
	if(!namewindow)
		{
			printf("\nError opening filename window!!\n");
			return 3;
		}
	do
		{
			WaitPort(namewindow->UserPort);
			msg = (struct IntuiMessage *)GetMsg(namewindow->UserPort);
			class = msg->Class;			/* I love messages with class */
			if(class != GADGETUP)           /* I only care about gadgets */
				continue;
			gadg = (struct Gadget *)msg->IAddress;  /* what gadget? */
			gadget_number = gadg->GadgetID; 		/* oh, that gadget */
			ReplyMsg(msg);
			switch(gadget_number)
				{
					case 1:
					case 2:
					case 3:
						CloseWindow(namewindow);
						strcpy(name,namebuffer);                /* restore colors */
						LoadRGB4(&screen->ViewPort,colortable,colorcount);
						return gadget_number;
					case 4: 			/* could lump this in with case 3 */
						break;			/* if you wanted to...		  */
					case 5:
						IMAGE_OUT = TRUE;	/* hit the Image gadget */
						image_gadget.Flags |= SELECTED;
						bitmap_gadget.Flags &= ~SELECTED;
						RefreshGadgets(&image_gadget,namewindow,NULL);
						break;
					case 6:
						IMAGE_OUT = FALSE;	/* hit the BitMap gadget */
						image_gadget.Flags &= ~SELECTED;
						bitmap_gadget.Flags |= SELECTED;
						RefreshGadgets(&image_gadget,namewindow,NULL);
						break;
				}
		}
	while(TRUE);
}


/*
	WriteCode() handles the actual code generation for whatever was clipped
	out.  If nothing was clipped out, it ignores the request.
	It takes the easy way out for word-alignment of the clipped image by
	creating an off-screen bitmap and using the blitter to yank out the
	image so it will align properly.
*/


void WriteCode(savename)
char *savename;
{
	SHORT pixwide,pixhigh;
	SHORT x,y,count,planes;
	struct BitMap tempmap;
	ULONG memsize;

	outputfile = fopen(savename,"w");
	if(!outputfile)
		{
			printf("\nUnable to open save file!!\n");
			return;
		}
	pixwide = clip.MaxX - clip.MinX + 1;
	pixhigh = clip.MaxY - clip.MinY + 1;
	if(!pixwide && !pixhigh)                /* give me something to work with, eh? */
		return;
	x = clip.MinX;
	y = clip.MinY;
	planes = rport->BitMap->Depth;
	InitBitMap(&tempmap,planes,pixwide,pixhigh);
	memsize = tempmap.BytesPerRow * tempmap.Rows;
	for(count=0;count<planes;count++)
		{
			tempmap.Planes[count] = (PLANEPTR)AllocMem(memsize,MEMF_CHIP|MEMF_CLEAR);
			if(tempmap.Planes[count] == NULL)
				{
					for(planes=0;planes<count;planes++)
						FreeMem(tempmap.Planes[count],memsize);
					break;
				}
		}								/* now grab the clipped image */
	BltBitMap(rport->BitMap,x,y,&tempmap,0,0,pixwide,pixhigh,0xC0,0xFF);

/*
	Now tempmap has the word-aligned image we want, so we can just
		write it out.  Simple, eh?
*/

	FindBaseName(basename,savename);
	if(IMAGE_OUT)
		ImageOut(&tempmap,basename,pixwide,pixhigh,planes);
	else
		BitMapOut(&tempmap,basename,pixwide,pixhigh,planes);
	for(count=0;count<planes;count++)                       /* free up some memory */
		FreeMem(tempmap.Planes[count],memsize);
	return;
}


/*
	FindBaseName just takes a filename and rips out the base part of it,
	minus any path information or extensions
*/

void FindBaseName(base,name)
char *base, *name;
{
	char *tcp, *cp;
#ifdef FOOP
	SHORT count;
	for(count=strlen(name)-1;count>0;count--)
		{
			if(name[count] == '.')
				name[count] = '\0';                     /* rip off extension */
			if((name[count] == '/') || (name[count] == ':'))
				{
					strcpy(base,&name[++count]);    /* and path */
					break;
				}
		}
	return;
#else
	cp = name;
	if ((tcp = strrchr(cp, ':')))
		cp = tcp+1;
	if ((tcp = strrchr(cp, '/')))
		*cp = 0;
	if ((tcp = strchr(base, '.')))
		*tcp = 0;

	strcpy (base, cp);
#endif
}


/*
	ImageOut() writes the actual code for an Image structure.  It does
	one bitplane at a time, by row, by word.  Pretty simple, really.
*/

void ImageOut(bitmap,base,width,height,depth)
struct BitMap *bitmap;
char *base;
SHORT width,height,depth;
{
	SHORT planes,row,word,pos = 0;
	USHORT *planeptr;

	fprintf(outputfile,"/*\n\tImage Structure definitions for %s \n*/\n\n",base);
	fprintf(outputfile,"USHORT %s_data[] = \n\t{\n\t\t",base);
	for(planes=0;planes<depth;planes++)
		{
			fprintf(outputfile,"\n\t\t/*  Plane %d */\n\t\t",planes);
			pos=0;
			for(row=0;row<bitmap->Rows;row++)
				{
					planeptr = (USHORT *)bitmap->Planes[planes]+((row*bitmap->BytesPerRow)/2);
					for(word=0;word<((bitmap->BytesPerRow)/2);word++)
						{
							fprintf(outputfile,"0x%04x, ",planeptr[word]);
							if(++pos>6)
								{
									pos = 0;
									fprintf(outputfile,"\n\t\t");
								}
						}
				}
		}
	fprintf(outputfile,"\n\t};\n");
	fprintf(outputfile,"struct Image %s_image = \n\t{\n\t\t",base);
	fprintf(outputfile,"0,0,                        /*  LeftEdge, TopEdge    */\n\t\t");
	fprintf(outputfile,"%d, %d, %d,         /*  Width, Height, Depth */\n\t\t",width,height,depth);
	fprintf(outputfile,"%s_data,            /*  ImageData  */\n\t\t",base);
	fprintf(outputfile,"0xFF,0,                     /*  PlanePick, PlaneOnOff */\n\t\t");
	fprintf(outputfile,"NULL,                       /*  NextImage */\n\t};\n\n");
	fprintf(outputfile,"\n/*  This data created by the MakeC program  */");
	fprintf(outputfile,"\n/*  MakeC (c) 1990 by Robert Kesterson      */");
	fprintf(outputfile,"\n/*                    6418 30th Street      */");
	fprintf(outputfile,"\n/*                    Lubbock, TX 79407     */");
	fprintf(outputfile,"\n/*                    (806)-792-3639        */");
	fprintf(outputfile,"\n/*               BIX: rkesterson            */\n\n");
	fclose(outputfile);
	return;
}

/*
	BitMapOut() is just like ImageOut, except it does it in BitMap
	format, and by bytes rather than words.
*/

void BitMapOut(bitmap,base,width,height,depth)
struct BitMap *bitmap;
char *base;
SHORT width,height,depth;
{
	SHORT planes,row,byte,pos = 0;
	UWORD count;

	fprintf(outputfile,"/*\n\tBitMap Structure definitions for %s \n*/\n\n",base);
	for(planes=0;planes<depth;planes++)
		{
			fprintf(outputfile,"\nUBYTE %s_plane%d[] = \n\t{\n\t\t",base,planes);
			for(row=0;row<bitmap->Rows;row++)
				for(byte=0;byte<bitmap->BytesPerRow;byte++)
					{
						fprintf(outputfile,"0x%02x, ",(UBYTE)*(bitmap->Planes[planes]+(row*bitmap->BytesPerRow)+byte));
						if(++pos>10)
							{
								pos = 0;
								fprintf(outputfile,"\n\t\t");
							}
					}
			fprintf(outputfile,"\n\t};\n\n");
		}
	fprintf(outputfile,"struct BitMap %s_bitmap = \n\t{\n\t\t",base);
	fprintf(outputfile,"%u,                 /*  BytesPerRow  */\n\t\t",bitmap->BytesPerRow);
	fprintf(outputfile,"%u,                 /*  Rows  */\n\t\t",bitmap->Rows);
	fprintf(outputfile,"%02x,               /*  Flags  */\n\t\t",bitmap->Flags);
	fprintf(outputfile,"%d,                 /*  Depth  */\n\t\t",depth);
	fprintf(outputfile,"0,                  /*  pad    */\n\t\t");
	for(count=0;count<depth;count++)
		fprintf(outputfile,"%s_plane%d,         /*  plane data  */\n\t\t",base,count);
	for(;count<=7;count++)
		fprintf(outputfile,"NULL,\n\t\t");
	fprintf(outputfile,"\n\t};\n\n");
	fprintf(outputfile,"\n/*  This data created by the MakeC program  */");
	fprintf(outputfile,"\n/*  MakeC (c) 1990 by Robert Kesterson      */");
	fprintf(outputfile,"\n/*                    6418 30th Street      */");
	fprintf(outputfile,"\n/*                    Lubbock, TX 79407     */");
	fprintf(outputfile,"\n/*                    (806)-792-3639        */");
	fprintf(outputfile,"\n/*               BIX: rkesterson            */\n\n");
	fclose(outputfile);
	return;
}


/*
	Create_bitmap() is a pretty generic routine to allocate and initialize
	a bitmap.
*/

struct BitMap *create_bitmap(width,height,depth)
UWORD width,height;
UBYTE depth;
{
	short i, error_flag = (SHORT)FALSE;
	struct BitMap *pbitmap = NULL;
	unsigned char *planepointer;

	if((depth>0L) && (width>0L) && (height>0L))
		{
			pbitmap = (struct BitMap *)AllocMem(sizeof(struct BitMap),
						MEMF_CHIP | MEMF_CLEAR);
			if(pbitmap != NULL)
				{
					InitBitMap(pbitmap,depth,width,height);
					for(i=0;i<depth;i++)
						{
							planepointer = (PLANEPTR)AllocMem(RASSIZE(width,height),MEMF_CHIP|MEMF_CLEAR);
							if(planepointer)
								pbitmap->Planes[i] = planepointer;
							else
								error_flag = TRUE;
						}
				}
		}
	if(error_flag == TRUE)
		{
			close_bitmap(pbitmap);
			pbitmap = NULL;
		}
	return(pbitmap);
}

/*
	close_bitmap() just frees up all the memory in a BitMap that was
	previously allocated with create_bitmap().
*/

void close_bitmap(pbitmap)
struct BitMap *pbitmap;
{
	unsigned char *planepointer;
	unsigned long depth,width,height;
	short i;

	if(pbitmap != NULL)
		{
			depth = pbitmap->Depth;
			width = pbitmap->BytesPerRow * 8;
			height = pbitmap->Rows;
			for ( i=0; i<depth; i++)
				{
					planepointer = pbitmap->Planes[i];
					if(planepointer != NULL)
						FreeMem(planepointer,RASSIZE(width,height));
					}
			FreeMem(pbitmap,sizeof(struct BitMap));
		}
}


