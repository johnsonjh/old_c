/*
**     Brian D. Moffet
**     June 13, 1988
**
**     Placed in the Public domain.
**     Please allow me to retain credit for this, and please
**     distribute source with the binaries. 
*/

#include <intuition/intuition.h>
#include <graphics/rastport.h> 
#include <functions.h>
 
#define        BETWEEN 5
 
extern int pen, bpen;
extern int MaxBit;
extern unsigned short colortable[]; 
extern unsigned short oldcolortable[]; 
extern struct Window *Set_Win; 

Do_Gadget( addr )
register struct Gadget *addr; 
{
       switch( addr->GadgetID ) 
       {
               case 1:                 /* Make Black and White */ 
               { 
                       unsigned long r, g, b; 
                       int i; 
                       for (i = 0; i < (1<<MaxBit); i++) 
                       { 
                               r = (colortable[i]>>8) & 0x0f; 
                               g = (colortable[i]>>4) & 0x0f; 
                               b = (colortable[i]>>0) & 0x0f; 
                               make_bw(&r, &g, &b); 
                               colortable[i] = ((r&15)<<8) | ((g&15)<<4) 
                                       | ((b&15)); 
                               SetRGB4((struct ViewPort *)ViewPortAddress(
							       Set_Win), i, r, g, b); 
                       } 
                       break; 
               } 
               case 2:         /* Smear of Colors */ 
               { 
                       int i; 
                       if ( pen > bpen) 
                               smear( colortable, bpen, pen ); 
                       else 
                               smear( colortable, pen, bpen ); 
 
                       for (i = 0; i < (1<<MaxBit); i++)
                       { 
                               unsigned long r, g, b; 
                               r = (colortable[i]>>8) & 0x0f; 
                               g = (colortable[i]>>4) & 0x0f; 
                               b = (colortable[i]>>0) & 0x0f; 
                               SetRGB4((struct ViewPort *)ViewPortAddress(
							       Set_Win), i, r, g, b); 
                       } 
                       break; 
               } 
               case 3:         /* Switch Colors */ 
               { 
                       int j, i; 
                       unsigned long r, g, b; 

                       j = colortable[pen]; 
                       colortable[pen] = colortable[bpen]; 
                       colortable[bpen] = j; 
                       for (i = 0; i < (1<<MaxBit); i++) 
                       { 
                               r = (colortable[i]>>8) & 0x0f; 
                               g = (colortable[i]>>4) & 0x0f; 
                               b = (colortable[i]>>0) & 0x0f; 
                               SetRGB4((struct ViewPort *)ViewPortAddress(
					                Set_Win), i, r, g, b); 
                       } 
                       break; 
               } 
               case 4:         /* Make the default palette good */ 
               { 
                       int i; 
                       for (i = 0; i < (1<<MaxBit); i++) 
                               oldcolortable[i] = colortable[i]; 
                       break; 
               } 
               case 5:         /* Copy Foreground to Background */ 
               { 
                       int i; 
                       unsigned long r, g, b; 
 
                       colortable[bpen] = colortable[pen]; 
                       for (i = 0; i < (1<<MaxBit); i++) 
                       { 
                               r = (colortable[i]>>8) & 0x0f; 
                               g = (colortable[i]>>4) & 0x0f; 
                               b = (colortable[i]>>0) & 0x0f; 
                               SetRGB4((struct ViewPort *)ViewPortAddress
							       (Set_Win), i, r, g, b); 
                       } 
                       break; 
               } 
               case 6:         /* Make Palette Original */ 
               { 
                       int i; 
                       unsigned long r, g, b; 

                       for (i = 0; i < (1<<MaxBit); i++) 
                       { 
                               colortable[i] = oldcolortable[i]; 
                               r = (colortable[i]>>8) & 0x0f; 
                               g = (colortable[i]>>4) & 0x0f; 
                               b = (colortable[i]>>0) & 0x0f; 
                               SetRGB4((struct ViewPort *)ViewPortAddress(
							   		Set_Win), i, r, g, b); 
                       } 
                       break; 
               } 
               default: 
                       break; 
       }
}
 

Add_Gadgets( W )
struct Window *W;
{
       Add_BW( W );
       Add_Smear( W );
       Add_Ex( W );
       Add_Copy( W );
       Add_OK( W );
       Add_Undo( W );
}
 

struct IntuiText BWText = {
       1, 0,
       COMPLEMENT,
       0, 0,
       NULL,
       (UBYTE *)"B/W",
       NULL,
};

struct Gadget BWGadget = {
       NULL,
       10, -9, 0, 8, 
       GADGHBOX | GRELBOTTOM,
       RELVERIFY,
       BOOLGADGET,
       NULL,
       NULL,
       NULL,
       0, 
       NULL, 
       1,
       NULL
};


Add_BW( W )
struct Window *W;
{
       BWGadget.GadgetText = &BWText;
       BWGadget.Width = IntuiTextLength(&BWText);
       AddGadget( W, &BWGadget, -1 ); 
       OnGadget( &BWGadget, W, NULL ); 
}

struct IntuiText SmearText = {
       1, 0,
       COMPLEMENT,
       0, 0,
       NULL,
       (UBYTE *)"Smear",
       NULL,
};
 
struct Gadget SmearGadget = { 
       NULL,
       30, -9, 0, 8,
       GADGHBOX | GRELBOTTOM, 
       RELVERIFY, 
       BOOLGADGET, 
       NULL,
       NULL,
       NULL,
       0,
       NULL,
       2,
       NULL
};


Add_Smear( W )
struct Window *W;
{
       SmearGadget.GadgetText = &SmearText;
       SmearGadget.Width = IntuiTextLength(&SmearText); 
       SmearGadget.LeftEdge = BWGadget.LeftEdge + BETWEEN + 
               IntuiTextLength(&BWText);
       AddGadget( W, &SmearGadget, -1 ); 
       OnGadget( &SmearGadget, W, NULL ); 
}

struct IntuiText ExText = {
       1, 0,
       COMPLEMENT,
       0, 0,
       NULL,
       (UBYTE *)"Exchange",
       NULL,
};

struct Gadget ExGadget = { 
       NULL,
       30, -9, 0, 8,
       GADGHBOX | GRELBOTTOM, 
       RELVERIFY, 
       BOOLGADGET, 
       NULL,
       NULL,
       NULL,
       0,
       NULL,
       3,
       NULL 
};


Add_Ex( W )
struct Window *W;
{
       ExGadget.GadgetText = &ExText;
       ExGadget.Width = IntuiTextLength(&ExText);
       ExGadget.LeftEdge = SmearGadget.LeftEdge + BETWEEN + 
               IntuiTextLength(&SmearText); 
       AddGadget( W, &ExGadget, -1 ); 
       OnGadget( &ExGadget, W, NULL ); 
}


struct IntuiText CopyText = {
       1, 0,
       COMPLEMENT,
       0, 0,
       NULL,
       (UBYTE *)"Copy",
       NULL,
};

struct Gadget CopyGadget = {
       NULL,
       30, -9, 0, 8,
       GADGHBOX | GRELBOTTOM,
       RELVERIFY,
       BOOLGADGET, 
       NULL,
       NULL,
       NULL,
       0,
       NULL,
       5,
       NULL 
};


Add_Copy( W )
struct Window *W;
{
       CopyGadget.GadgetText = &CopyText;
       CopyGadget.Width = IntuiTextLength(&CopyText); 
       CopyGadget.LeftEdge = ExGadget.LeftEdge + BETWEEN + 
               IntuiTextLength(&ExText); 
       AddGadget( W, &CopyGadget, -1 ); 
       OnGadget( &CopyGadget, W, NULL ); 
}

struct IntuiText OKText = {
       1, 0,
       COMPLEMENT,
       0, 0,
       NULL,
       (UBYTE *)"OK",
       NULL,
};

struct Gadget OKGadget = {
       NULL,
       30, -9, 0, 8,
       GADGHBOX | GRELBOTTOM,
       RELVERIFY,
       BOOLGADGET, 
       NULL,
       NULL,
       NULL,
       0,
       NULL,
       4, 
       NULL
};


Add_OK( W )
struct Window *W;
{
       OKGadget.GadgetText = &OKText;
       OKGadget.Width = IntuiTextLength(&OKText);
       OKGadget.LeftEdge = CopyGadget.LeftEdge + BETWEEN + 
               IntuiTextLength(&CopyText); 
       AddGadget( W, &OKGadget, -1 ); 
       OnGadget( &OKGadget, W, NULL ); 
}



struct IntuiText UndoText = {
       1, 0,
       COMPLEMENT,
       0, 0,
       NULL,
       (UBYTE *)"Undo",
       NULL,
};

struct Gadget UndoGadget = {
       NULL,
       30, -9, 0, 8,
       GADGHBOX | GRELBOTTOM,
       RELVERIFY,
       BOOLGADGET,
       NULL,
       NULL,
       NULL,
       0,
       NULL,
       6,
       NULL
};


Add_Undo( W )
struct Window *W;
{
       UndoGadget.GadgetText = &UndoText;
       UndoGadget.Width = IntuiTextLength(&UndoText);
       UndoGadget.LeftEdge = OKGadget.LeftEdge + BETWEEN + 
               IntuiTextLength(&OKText); 
       AddGadget( W, &UndoGadget, -1 ); 
       OnGadget( &UndoGadget, W, NULL ); 
}
