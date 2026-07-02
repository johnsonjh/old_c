/************************************************************************
 * Moire.c -- Yet another graphics dazzler for the Amiga.  This one draws
 *            Moire Patterns in Black and White - they tend to look better
 *            that way.  Uses a borderless backdrop window to make life
 *            easier, and so we get the whole screen if we want it.
 *
 *            Copyright (c) 1985 by Scott Ballantyne
 *            (I.E. Ok to give away for nothing )
 ************************************************************************/

						/* Not all of these are used -- I include them */
						/* 'cause I'm sick of compiler warnings.       */
#include <exec/types.h>
#include <exec/nodes.h>
#include <exec/lists.h>
#include <exec/exec.h>
#include <exec/execbase.h>
#include <exec/ports.h>
#include <exec/devices.h>
#include <exec/memory.h>
#include <hardware/blit.h>
#include <graphics/copper.h>
#include <graphics/regions.h>
#include <graphics/rastport.h>
#include <graphics/gfxbase.h>
#include <graphics/gfxmacros.h>
#include <graphics/gels.h>
#include <intuition/intuition.h>
#include <functions.h>

struct IntuitionBase *IntuitionBase = NULL;
struct GfxBase *GfxBase = NULL;


#define MAXX   640
#define MAXY   200
struct NewScreen MyScreen =
{ 0,0,MAXX,MAXY,1,0,1,HIRES,CUSTOMSCREEN,NULL,(UBYTE*)"Moire Patterns",0,0,};

   struct NewWindow DrawWindow = {
      0,0,MAXX,MAXY,
      0,1,
      MENUPICK,
      BORDERLESS | BACKDROP | ACTIVATE,
      NULL,
      NULL,
      NULL,
      NULL,
      NULL,
      0,0,0,0,
      CUSTOMSCREEN,
   };

struct Screen *Screen = NULL;
struct Window *Backdrop = NULL;
struct RastPort *DrawRP;
struct ViewPort *DrawVP;
struct IntuiMessage  *message;

struct MenuItem OnlyMenuItems[4];
struct IntuiText OnlyMenuText[4];
struct Menu OnlyMenu[1];

#define SHOW      1
#define ERASE     0

main()
{
   ULONG class;
   USHORT code, ItemNum;

   if (!(IntuitionBase = (struct IntuitionBase *)OpenLibrary("intuition.library",0)))
         exit(1);

   if(!(GfxBase = (struct GfxBase *)OpenLibrary("graphics.library",0)))
      cleanitup(2);

   if(!(Screen = (struct Screen *)OpenScreen(&MyScreen)))
      cleanitup(3);

   DrawWindow.Screen = Screen;

   if(!(Backdrop = (struct Window *)OpenWindow(&DrawWindow)))
      cleanitup(4);


   DrawRP = Backdrop->RPort;     /* Draw into backdrop window */
   DrawVP = &Screen->ViewPort;   /* Set colors in Screens VP  */
   SetBPen(DrawRP, 0);           /* For clean text */
   setcolors();

   initmenuitems();
   initmenu();
   SetMenuStrip(Backdrop, &OnlyMenu[0]);
   moire();

   FOREVER {
      while(message = (struct IntuiMessage *)GetMsg(Backdrop->UserPort)) {
         class = message->Class;
         code = message->Code;
         ReplyMsg((struct Message *)message);

         if (class == MENUPICK && code != MENUNULL) {
            ItemNum = ITEMNUM( code );
            switch (ItemNum) {
               case 0:
                  clearRP();
                  moire();
                  break;
               case 1:
                  ShowTitle(Screen, FALSE);
                  break;
               case 2:
                  ShowTitle(Screen, TRUE);
                  break;
               case 3:
                  ClearMenuStrip(Backdrop);
                  cleanitup(0);
            }
         }
      }
   }
}

moire()
{
   register int x, y;
   int endx;
   UBYTE endy;
   double rnd();

   OffMenu(Backdrop, NOITEM << 5);

   endx = MAXX * rnd();
   endy = MAXY * rnd();

   for(x = 0; x <= MAXX; x++) {
      doline(SHOW, x, 0, endx, endy, x, MAXY);
      x++;
      doline(ERASE, x, 0, endx, endy, x, MAXY);
   }
   for(y = 0; y <= MAXY; y++) {
      doline(SHOW, 0, y, endx, endy, MAXX, y);
      y++;
      doline(ERASE, 0, y, endx, endy, MAXX, y);
   }
      OnMenu(Backdrop, NOITEM << 5);
}

clearRP()
{
   SetAPen(DrawRP, ERASE);
   SetDrMd(DrawRP, JAM1);
   RectFill(DrawRP, 0, 0, MAXX, MAXY);
}

doline(color, x0, y0, x1, y1, x2, y2)
UBYTE color, y0, y1, y2;
int x0, x1, x2;
{
   SetAPen(DrawRP, color);
   SetDrMd(DrawRP, JAM1);
   Move(DrawRP, x0, y0);
   Draw(DrawRP, x1, y1);
   Draw(DrawRP, x2, y2);
}

cleanitup(error_code)
int error_code;
{
   if (Backdrop)
      CloseWindow(Backdrop);
   if (Screen)
      CloseScreen(Screen);
   if (GfxBase)
      CloseLibrary((struct Library *)GfxBase);
   if (IntuitionBase)
      CloseLibrary((struct Library *)IntuitionBase);
   exit(error_code);
}


setcolors()
{
   SetRGB4(DrawVP, 0, 0, 0, 0);
   SetRGB4(DrawVP, 1, 15, 15, 15);
}

initmenuitems()
{
   short n;

   for(n = 0; n < 4; n++) {  /* One struct for each item */
      OnlyMenuItems[n].NextItem = &OnlyMenuItems[n + 1]; /* next item */
      OnlyMenuItems[n].LeftEdge = 0;
      OnlyMenuItems[n].TopEdge = 10 * n;
      OnlyMenuItems[n].Width = 112;
      OnlyMenuItems[n].Height = 10;
      OnlyMenuItems[n].Flags = ITEMTEXT | ITEMENABLED | HIGHCOMP;
      OnlyMenuItems[n].MutualExclude = 0;
      OnlyMenuItems[n].ItemFill = (APTR)&OnlyMenuText[n];
      OnlyMenuItems[n].SelectFill = NULL;
      OnlyMenuItems[n].Command = 0;
      OnlyMenuItems[n].SubItem = NULL;
      OnlyMenuItems[n].NextSelect = 0;

      OnlyMenuText[n].FrontPen = 0;
      OnlyMenuText[n].BackPen = 1;
      OnlyMenuText[n].DrawMode = JAM2;
      OnlyMenuText[n].LeftEdge = 0;
      OnlyMenuText[n].TopEdge = 1;
      OnlyMenuText[n].ITextFont = NULL;
      OnlyMenuText[n].NextText = NULL;
   }
   OnlyMenuItems[3].NextItem = NULL; /* Last item */

   OnlyMenuText[0].IText = (UBYTE *)"New Moire";
   OnlyMenuText[1].IText = (UBYTE *)"Hide Title Bar";
   OnlyMenuText[2].IText = (UBYTE *)"Show Title Bar";
   OnlyMenuText[3].IText = (UBYTE *)"QUIT!";
}
initmenu()
{
   OnlyMenu[0].NextMenu = NULL;                 /* No more menus */
   OnlyMenu[0].LeftEdge = 0;
   OnlyMenu[0].TopEdge = 0;
   OnlyMenu[0].Width = 85;
   OnlyMenu[0].Height = 10;
   OnlyMenu[0].Flags = MENUENABLED;             /* All items selectable */
   OnlyMenu[0].MenuName = "Actions";
   OnlyMenu[0].FirstItem = &OnlyMenuItems[0];   /* Pointer to first item */
}

double
rnd ()
{
	static int seed;
	register int i, n;
	double d;

	i = (seed & 1<<27) ? 1 : 0;
	n = (seed & 1<<30) ? 1 : 0;
	seed <<= 1;
	seed |= (i ^ n);
	if (seed == 0)
		d = 1;
	else
		d = seed;
	return (1.0 / d);
}

