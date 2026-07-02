/*
			BioMorph
			By:  Chris MacDonald & Steve Martin
			Version:  1.0
			Last Revision:  28 July 89

	
*/





#include <exec/types.h>
#include <intuition/intuition.h>
#include <stdio.h>
#include <graphics/gfxmacros.h>
#include <math.h>


/* 
system functions 
*/

extern struct Screen *OpenScreen ();
extern struct Window *OpenWindow();
extern struct Library *OpenLibrary();
extern struct ViewPort *ViewPortAddress();



/* 
system variables 
*/

struct IntuitionBase *IntuitionBase;
struct GfxBase *GfxBase;
struct MathBase *MathBase;
struct Screen *s;
struct Window *w;
struct IntuiMessage *msg;
struct RastPort *rp;
struct ViewPort *vp;

/*  
menu stuff
*/

struct TextAttr Font = 
{
	(STRPTR)"topaz.font",
	TOPAZ_SIXTY,
	FS_NORMAL,
	FPF_ROMFONT
};

struct IntuiText GenerateText = {4,1,JAM1,1,1,&Font,
				(UBYTE *)               "  Generate",NULL};
struct IntuiText StopText ={4,1,JAM1,1,1,&Font,(UBYTE *)"  Stop",NULL};
struct IntuiText QuitText ={4,1,JAM1,1,1,&Font,(UBYTE *)"  Quit",NULL};
	
struct IntuiText GreyText = {4,1,JAM1,1,1,&Font,(UBYTE *) "  Grey",NULL};
struct IntuiText RedText = {4,1,JAM1,1,1,&Font,(UBYTE *)  "  Red",NULL};
struct IntuiText GreenText = {4,1,JAM1,1,1,&Font,(UBYTE *)"  Green",NULL};
struct IntuiText BlueText = {4,1,JAM1,1,1,&Font,(UBYTE *) "  Blue",NULL};


struct IntuiText TwoText = {4,1,JAM1,1,1,&Font,(UBYTE *)    "   2",NULL};
struct IntuiText FourText = {4,1,JAM1,1,1,&Font,(UBYTE *)   "   4",NULL};
struct IntuiText EightText = {4,1,JAM1,1,1,&Font,(UBYTE *)  "   8",NULL};
struct IntuiText SixteenText = {4,1,JAM1,1,1,&Font,(UBYTE *)"  16",NULL};
struct IntuiText TwentyText = {4,1,JAM1,1,1,&Font,(UBYTE *) "  20",NULL};


struct IntuiText SquareText ={4,1,JAM1,1,1,&Font,(UBYTE *)"  z^2 + c",NULL};
struct IntuiText CubeText = {4,1,JAM1,1,1,&Font,(UBYTE *) "  z^3 + c",NULL};
struct IntuiText FifthText = {4,1,JAM1,1,1,&Font,(UBYTE *)"  z^5 + c",NULL};

	
struct MenuItem Quit = 
{
	NULL,1,26,140,10,ITEMTEXT | ITEMENABLED | HIGHCOMP | COMMSEQ,
	0,(APTR) &QuitText,NULL,0x51,NULL,0
};

struct MenuItem Stop = 
{
	&Quit,1,14,140,10,ITEMTEXT | ITEMENABLED | HIGHCOMP |
	CHECKIT | COMMSEQ,0xfffffff9,(APTR) &StopText,NULL,0x53,NULL,0
};

struct MenuItem Generate = 
{
	&Stop,1,2,140,10,ITEMTEXT | ITEMENABLED | HIGHCOMP | 
	CHECKIT | CHECKED | COMMSEQ,0xfffffffa,(APTR) &GenerateText,
	NULL,0x47,NULL,0
};


struct MenuItem Blue = 
{
	NULL,1,38,70,10,ITEMTEXT | ITEMENABLED | HIGHCOMP 
	| CHECKIT,0xfffffff7,(APTR) &BlueText,NULL,0,NULL,0
};

struct MenuItem Green = 
{
	&Blue,1,26,70,10,ITEMTEXT | ITEMENABLED | HIGHCOMP
	| CHECKIT,0xfffffffb,(APTR) &GreenText,NULL,0,NULL,0
};

struct MenuItem Red = 
{
	&Green,1,14,70,10,ITEMTEXT | ITEMENABLED | HIGHCOMP
	| CHECKIT,0xfffffffd,(APTR) &RedText,NULL,0,NULL,0
};

struct MenuItem Grey = 
{
	&Red,1,2,70,10,ITEMTEXT | ITEMENABLED | HIGHCOMP | CHECKED
	| CHECKIT,0xfffffffe,(APTR) &GreyText,NULL,0,NULL,0
};


struct MenuItem Twenty = 
{
	NULL,1,50,60,10,ITEMTEXT | ITEMENABLED | HIGHCOMP | CHECKED 
	| CHECKIT,0xffffffef,(APTR) &TwentyText,NULL,0,NULL,0
};

struct MenuItem Sixteen = 
{
	&Twenty,1,38,60,10,ITEMTEXT | ITEMENABLED | HIGHCOMP
	| CHECKIT,0xfffffff7,(APTR) &SixteenText,NULL,0,NULL,0
};

struct MenuItem Eight = 
{
	&Sixteen,1,26,60,10,ITEMTEXT | ITEMENABLED | HIGHCOMP
	| CHECKIT,0xfffffffb,(APTR) &EightText,NULL,0,NULL,0
};

struct MenuItem Four = 
{
	&Eight,1,14,60,10,ITEMTEXT | ITEMENABLED | HIGHCOMP
	| CHECKIT,0xfffffffd,(APTR) &FourText,NULL,0,NULL,0
};

struct MenuItem Two = 
{
	&Four,1,2,60,10,ITEMTEXT | ITEMENABLED | HIGHCOMP
	| CHECKIT,0xfffffffe,(APTR) &TwoText,NULL,0,NULL,0
};


struct MenuItem Fifth = 
{
	NULL,1,26,100,10,ITEMTEXT | ITEMENABLED | HIGHCOMP
	| CHECKIT,0xfffffffb,(APTR) &FifthText,NULL,0,NULL,0
};

struct MenuItem Cube = 
{
	&Fifth,1,14,100,10,ITEMTEXT | ITEMENABLED | HIGHCOMP
	| CHECKED | CHECKIT,0xfffffffd,(APTR) &CubeText,NULL,0,NULL,0
};

struct MenuItem Square = 
{
	&Cube,1,2,100,10,ITEMTEXT | ITEMENABLED | HIGHCOMP
	| CHECKIT,0xfffffffe,(APTR) &SquareText,NULL,0,NULL,0
};




struct Menu Zx = {NULL,165,0,80,0,NULL,(BYTE *) "Equation",&Square};
struct Menu Zoom = {&Zx,115,0,50,0,NULL,(BYTE *) "Zoom",&Two};
struct Menu Colors = {&Zoom,55,0,60,0,MENUENABLED,(BYTE *) "Colors",&Grey};
struct Menu File = {&Colors,10,0,45,10,MENUENABLED,
			(BYTE *) "File",&Generate};



/*
voidoids
*/

void open_all(), close_all(), initmenu();
void addplex(),multplex(),sqrplex(),cubeplex(),analyze(),genmorph();
void mousezoom();



/*
window and screen  (windscreen?)
*/

struct NewScreen myScreen = 
{
	0,0,
	320,200,
	4,
	1,0,
	0,
	CUSTOMSCREEN,
	NULL,
	(UBYTE *)"BioMorph 1.0",
	NULL,
	NULL
};


struct NewWindow myWindow =
{
      80,9,
      165, 160,
      0,
      1,
      MENUPICK | MOUSEBUTTONS,
      SMART_REFRESH | ACTIVATE | WINDOWSIZING | 
      WINDOWDRAG | GIMMEZEROZERO,
      NULL,
      NULL,
      (UBYTE *)"z^3 + c",
      NULL,
      NULL,
      50, 40,
      210, 200,
      WBENCHSCREEN
};


/*
color maps
*/


UWORD greycolortable[] =
{
	0x004,0xfff,0x990,0x059,
	0x666,0x777,0x888,0x999,
	0xaaa,0xbbb,0xccc,0xddd,
	0xeee,0xfff,0x000
};

UWORD redcolortable[] =
{
	0x004,0xfff,0x990,0x059,
	0x600,0x700,0x800,0x900,
	0xa00,0xb00,0xc00,0xd00,
	0xe00,0xf00,0x000
};

UWORD greencolortable[] =
{
	0x004,0xfff,0x990,0x059,
	0x060,0x070,0x080,0x090,
	0x0a0,0x0b0,0x0c0,0x0d0,
	0x0e0,0x0f0,0x000
};

UWORD bluecolortable[] =
{
	0x004,0xfff,0x990,0x059,
	0x006,0x007,0x008,0x009,
	0x00a,0x00b,0x00c,0x00d,
	0x00e,0x00f,0x000
};

/*
IDCMP stuff
*/

struct IntuiMessage *message;
USHORT MessageClass, MessageCode, MousX, MousY;




/*		
global variable descriptions		


	creal,	  =	real & imaginary portion of 
	cimag		constant

	magfactor =	magnification factor of graph
	
	fnum	  =	function power value (2 = square,
			3 = cube, 4 = z ^ 5)
			
	stopflag  =	flag which tells genmorph() to
			quit when Stop is selected from
			File menu
			
	minwinx,  =	minimum window size values, set
	minwiny		to insure user can't size window
			down while generating graph
			
	winx,     =	size of window user selects for
	winy		next graph

	mxstart,  =	upper left corner value for mouse
	mystart		zoom box.  transferred to xstart, ystart
			in genmorph()

	xstart,   =	upper left corner value of last generated
	ystart		or currently generating graph
	
	increment =	distance between adjacent graph points
	
	size	  = 	size in pixels of most recently computed
			or currently computing graph
		
*/


float creal, cimag, magfactor, xstart, ystart, mxstart, mystart, increment;
short fnum,stopflag,minwinx,minwiny,winx,winy,size;



main(argc,argv)
int argc;
UBYTE *argv[];
{
/* 
user can enter a '?' or a complex constant 
when starting the program
*/

	printf("\nBioMorph 1.0\n\nby Chris MacDonald & Steve Martin\n\n");

	if (argc == 1)    /* no arguments */
	{
		creal = 0.5;
		cimag = 0.0;

		printf("Using default constant:   real      = 0.5\n");
		printf("                          imaginary = 0.0\n\n");
		printf("Next time, try your own constant!\n\n");
		printf("Usage:  Biomorph (real) (imaginary)\n");
		printf("Where real and imaginary are a complex constant\n\n");
		Delay(125);
	}
	else if (argc == 2 && (*argv[1] == '?'))   /* user types '?' */
	{
		printf("\nUsage:  Biomorph (real) (imaginary)\n");
		printf("Where real and imaginary are a complex constant\n\n");
		exit(TRUE);
	}
	else
	{	
		creal = atof((char *)argv[1]);   /* user enters complex constant */
		cimag = 0.0;
		if(argc >= 3) cimag = atof((char *)argv[2]);
		printf("\nComplex constant:\n");
		printf("real      = %f\n",creal);
		printf("imaginary = %f\n\n",cimag);
		Delay(130);
	}
		
	open_all();              /* opens libraries, screen and window */

	LoadRGB4(vp,&greycolortable[0],15);     /* load color table */

	SetRast(rp,3);                          /* clear window */

			/* default graph drawn when program starts */
	magfactor = 20;

			/*where upper left corner of graph should be */
	mxstart = -1.0 * magfactor / 2.0;
	mystart = mxstart;

	fnum = 3;                       /* function is cube (z^3 + c) */
	genmorph();                     /* generate graph */
	
	
			/* loop which waits for user to access menu */
	while (1)
	{
		if((message = (struct IntuiMessage *)
			GetMsg(w->UserPort)) == NULL)
		{
			Wait(1L << w->UserPort->mp_SigBit);
			continue;
		}
		stopflag = 0;
		MessageClass = message->Class; /* get needed data */
		MessageCode = message->Code;
		MousX = w->GZZMouseX;
		MousY = w->GZZMouseY;
		ReplyMsg(message);              /* respond to message */
		
		switch(MessageClass)
		{
			case MENUPICK :		analyze(MessageCode);
			break;			       /* accessed menu */
			
			case MOUSEBUTTONS :	mousezoom(MessageCode);
			break;			 /* pressed mouse button */
		}
		
	}
	
}




/*
mousezoom()'s purpose is to generate a "zoom box" while mouse button is
pressed and held down.  When the button is released, the starting 
coordinates and magnification of the selected box are computed.
*/

/*		mousezoom variable descriptions

	loop	=	flag indicating end of zoom
			box loop
	
	setx,	=	the starting window coordinates
	sety		of the zoom box
	
	mx	=	x distance mouse moves from setx
*/


void mousezoom(code)
USHORT code;		/* message code  */
{
	short loop = 1;
	USHORT mx,setx,sety; 
	
	switch(code)
	{
		case SELECTDOWN :			/*left button down*/
		
			setx = MousX;		/*set starting point of*/
			sety = MousY;		/*zoom box             */
			
			if(setx >= 215) setx = 0;  /*fixes problem when mouse*/
			if(sety >= 215) sety = 0;  /*points to left | up edge*/
			
			mx = w->GZZMouseX;	/*get current mouse x position*/
			
			SetWindowTitles(w,"Zooming!",-1);
			
			SetDrMd(rp,COMPLEMENT);	/* "self erasing" mode*/
			SetAPen(rp,1);
			Move(rp,setx,sety);		/*  draw the zoom box */
			Draw(rp,mx,sety);
			Draw(rp,mx,sety + mx - setx);
			Draw(rp,setx,sety + mx -setx);
			Draw(rp,setx,sety);
			
			while (loop)    /*adjusts zoom box while button down*/
			
			{
				while((message = (struct IntuiMessage *)
					GetMsg(w->UserPort)) == NULL)
				{
					Move(rp,setx,sety);   /* erase old box */
					Draw(rp,mx,sety);
					Draw(rp,mx,sety + mx - setx);
					Draw(rp,setx,sety + mx -setx);
					Draw(rp,setx,sety);

					mx = w->GZZMouseX;  /* get new x value */

					/*stops dragging box to the left*/
					if((mx < setx) || (mx > 400)) mx = setx;

					Move(rp,setx,sety);  /* draw new box */
					Draw(rp,mx,sety);
					Draw(rp,mx,sety + mx - setx);
					Draw(rp,setx,sety + mx -setx);
					Draw(rp,setx,sety);

				}
				MessageClass = message->Class; /*drops out of loop*/
				MessageCode = message->Code;   /*when a message   */
				ReplyMsg(message);             /*occurs           */
				
				switch(MessageClass)
				
				{
					case MOUSEBUTTONS:
					
					switch(MessageCode)
					
					{
					case SELECTUP:   /* user releases button */
					
				/* set new mag & position based on zoom box */
					magfactor =(mx - setx) * increment;
					mxstart = xstart +
						  ((setx - 2) * increment);
					mystart = ystart +
						  ((sety - 1) * increment);

					SetWindowTitles(w,"Got it.",-1);
					Delay(20);
					
					switch(fnum)  /* put window title back */
					{
					case 2:
					SetWindowTitles(w,"z^2 + c",-1);
					break;
					
					case 3:
					SetWindowTitles(w,"z^3 + c",-1);
					break;
					
					case 4:
					SetWindowTitles(w,"z^5 + c",-1);
					break;
					}
					
					Move(rp,setx,sety);  /* erase box */
					Draw(rp,mx,sety);
					Draw(rp,mx,sety + mx - setx);
					Draw(rp,setx,sety + mx -setx);
					Draw(rp,setx,sety);

					loop = 0;   /* set flag to end loop */
					break;
					}
					break;
					
				}
			}	
	}
}



void genmorph()
{

/*	
	x,	=	graph loop vars. derived from
	y		current window size
			
	n	=	iteration loop variable
	
	value	=	contains result of window sizing
			call
	
	zreal,	=	current equation coordinates
	zimag
	
	a, b	=	temporary storage for math routines
	
*/
	
	
	short x,y,n,value;
	float zreal,zimag,a,b;

	SetDrMd(rp,JAM1);

	stopflag = 0;   /* flag to stop generating */
	
	/* setting limits of window size */
	winx = w->Width;
	winy = w->Height;
	value = WindowLimits(w,winx,winy,210,200);
	
	/* how large the graph should be, based on window size */
	if(winx < winy)
	{
		size = winx - 8;
	}
	else
	{
		size = winy - 8;
	}
	
	/* how much zreal&imag should be incremented each
	   time through loop				  */
	increment = magfactor / size;
	
	xstart = mxstart;	/* assign mousezoom() values */
	ystart = mystart;


	for(y = 0; y <= size - 6; ++y)   /* y graph loop */
	{
		for(x = 0; x <= size; ++x)   /* x graph loop */
		{
			/* setting z value for current coordinates */
			zreal = ((float) xstart + (increment * x));
			zimag = ((float) ystart + (increment * y));
			
			/* iteration loop */	
			for(n = 1; n <= 10; ++n)
			{
				a = zreal;
				b = zimag;
				
				if (fnum == 2)    /* square */
				{
					zreal = a*a - b*b + creal;
					zimag = 2*a*b + cimag;
				}
				
				else if (fnum == 3)   /* cube */
				{
					zreal = a*(a*a - 3*b*b) + creal;
					zimag = b*(3*a*a - b*b) + cimag;
				}

				else if (fnum == 4)   /* fifth */
				{
					a = zreal;
					b = zimag;

		zreal = a * (a*a*a*a - 10*a*a*b*b + 5*b*b*b*b) + creal;
		zimag = b * (5*a*a*a*a - 10*a*a*b*b + b*b*b*b) + cimag;
				}
			
				
	/* break out of loop if result is ever greater than ten	*/
			
				if(fabs(zreal) > 10 || fabs(zimag) > 10 ||
					(zreal*zreal + zimag*zimag) > 100)
					break;
			}

			
	/* setting color of pixel based on value of z after iteration */
			
			if(!(fabs(zreal) < 10 || fabs(zimag) < 10))
			{
				SetAPen(rp,14);
			}
			else if(fabs(zreal) < fabs(zimag)) 
			{
				SetAPen(rp,((short) fabs(zreal)) + 4);
			}
			else
			{
				SetAPen(rp,((short) fabs(zimag)) + 4);
			}
			WritePixel(rp,x,y);
		}

		
		/* test for menu access at end of each x loop */
		/* clears all messages except newest          */
		MessageClass = NULL;
		while(message = (struct IntuiMessage *)GetMsg(w->UserPort))
		{
			MessageClass = message->Class;
			MessageCode = message->Code;
			ReplyMsg(message);
		}	
		
		if(MessageClass)
		{
			switch(MessageClass)
			{
				case MENUPICK :	analyze(MessageCode);
				break;
			}
		}
		

		/* quit generating if user picks Stop from File menu */
		if(stopflag)
		{
			stopflag = 0;
			x = size;
			y = size - 6;
		}

	}
	
	/* set window size limits back to normal */
	value = WindowLimits(w,50,40,210,200);
	
	/* enable zoom and power menus */
	ClearMenuStrip(w);
	Zx.Flags = MENUENABLED;
	Zoom.Flags = MENUENABLED;
	Stop.Flags |= CHECKED;       /* set Stop checkmark */
	Generate.Flags = ITEMTEXT | ITEMENABLED | HIGHCOMP
	| COMMSEQ | CHECKIT;         /* unset Generate checkmark */
	SetMenuStrip(w,&File);
	DisplayBeep(NULL);           /* flash screen when done */

}







/* 
analyze():  responds to user menu access 
*/

void analyze(Menunumber)
USHORT Menunumber;
{
	USHORT Menu, MenuItem;
	
	Menu = MENUNUM(Menunumber);
	MenuItem = ITEMNUM(Menunumber);
	
	switch(Menu)
	{
		case 0	: /* File Menu */
			switch(MenuItem)
			{
				case 0	: /* Generate */
					if (!(stopflag))
					{
						SetRast(rp,0);
						ClearMenuStrip(w);
						Zoom.Flags = NULL;
						Zx.Flags = NULL;
						SetMenuStrip(w,&File);
						genmorph();
					}
					break;
				
				case 1	: /* Stop */
					stopflag = 1;
					ClearMenuStrip(w);
					Zoom.Flags = MENUENABLED;
					Zx.Flags = MENUENABLED;
					SetMenuStrip(w,&File);
					break;
					
				case 2	: /* Quit */
					close_all();
					exit(TRUE);
					break;
			}
		break;
			
		case 1	: /* Colors */
			switch(MenuItem)
			{
				case 0	: /* Grey */
					LoadRGB4(vp,&greycolortable[0],15);
					break;
			
				case 1	: /* Red */
					LoadRGB4(vp,&redcolortable[0],15);
					break;

				case 2	: /* Green */
					LoadRGB4(vp,&greencolortable[0],15);
					break;

				case 3	: /* Blue */
					LoadRGB4(vp,&bluecolortable[0],15);
					break;
			}
		break;

		case 2	: /* Zoom */
			switch(MenuItem)
			{
				case 0	:
					magfactor = 2;
					mxstart = -1.0 * magfactor / 2.0;
					mystart = mxstart;
					break;
					
				case 1	:
					magfactor = 4;
					mxstart = -1.0 * magfactor / 2.0;
					mystart = mxstart;
					break;
				
				case 2	:
					magfactor = 8;
					mxstart = -1.0 * magfactor / 2.0;
					mystart = mxstart;
					break;
				
				case 3	:
					magfactor = 16;
					mxstart = -1.0 * magfactor / 2.0;
					mystart = mxstart;
					break;
				
				case 4	:
					magfactor = 20;
					mxstart = -1.0 * magfactor / 2.0;
					mystart = mxstart;
					break;
			}
		break;

		case 3	: /* Power */
			switch(MenuItem)
			{
				case 0	:
					fnum = 2;
					SetWindowTitles(w,"z^2 + c",-1);
					break;
					
				case 1	:
					fnum = 3;
					SetWindowTitles(w,"z^3 + c",-1);
					break;
				
				case 2	:
					fnum = 4;
					SetWindowTitles(w,"z^5 + c",-1);
					break;
			}
		break;

	}
}	
		
		
		
void open_all()
{
	if((IntuitionBase = (struct IntuitionBase *)
	  	OpenLibrary("intuition.library", 0L)) == NULL)
			exit(1);
	if((MathBase = (struct MathBase *)
	  	OpenLibrary("mathffp.library", 0L)) == NULL)
			exit(1);
	if ((GfxBase = (struct GfxBase *)
		OpenLibrary("graphics.library", 0L)) == NULL)
			exit(1);

if ((s = OpenScreen(&myScreen)) == NULL)
	exit(1);

vp = &(s -> ViewPort);

myWindow.Screen = s;
myWindow.Type = CUSTOMSCREEN;
	
	if ((w = OpenWindow(&myWindow)) == NULL)
		exit(1);
	rp = w->RPort;
	
	SetMenuStrip(w,&File);
}




void close_all()
{
	while(message = (struct IntuiMessage *)GetMsg(w->UserPort))
	{
		ReplyMsg(message);
	}

	if (w) ClearMenuStrip(w);
	if (w) CloseWindow(w);
	if (s) CloseScreen(s);
	if (GfxBase) CloseLibrary(GfxBase);
	if (IntuitionBase) CloseLibrary(IntuitionBase);
}

