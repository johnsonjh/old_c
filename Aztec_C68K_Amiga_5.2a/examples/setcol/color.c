/*
**     Brian D. Moffet
**     June 13, 1988 
**
**     Placed in the Public Domain, Please keep my name on it 
**     and provide source when you provide the binary. 
**
**     uunet!sco!alar!brian
*/

#include <intuition/intuition.h>
#include <graphics/rastport.h> 
#include <functions.h>


#define        WINWIDTH        260
#define        WINHEIGHT       100 

extern char Version[];
extern char Author[]; 

int    pen = 0, bpen = 1;
struct Window *Set_Win = NULL; 
struct NewWindow NW;

extern struct Screen *S;
extern int MaxBit;
extern USHORT colortable[]; 

Color_Window( S )
struct Screen *S;
{
       register int class;
       register int code;
       APTR    ptr; 
       struct IntuiMessage *mess; 
       int i; 
/*
**     Many hard coded numbers are in here, they shouldn't 
**     be.  I should take the size of the window and scale that, 
**     But this was a quick hack... 
**
**     The window allows mouse buttons and gadget movement. 
**     Instead of waiting for a gadget, when I get the first one 
**     I enter a fast loop to track the mouse.  I could get better 
**     color updating this way. 
*/

       NW.LeftEdge = NW.TopEdge        =       0; 
       NW.Width                        =       WINWIDTH; 
       NW.Height                       =       WINHEIGHT;
       NW.DetailPen = NW.BlockPen      =       -1; 
       NW.IDCMPFlags                   =       MOUSEBUTTONS
                                               | CLOSEWINDOW | GADGETDOWN
                                               | GADGETUP; 
       NW.Flags                        =       WINDOWCLOSE | WINDOWDRAG | 
                                               WINDOWDEPTH | SMART_REFRESH 
                                               | ACTIVATE | NOCAREREFRESH | 
                                               RMBTRAP; 
       NW.FirstGadget                  =       NULL; 
       NW.CheckMark                    =       NULL; 
       NW.Title                        =       (UBYTE *)Version; 
       NW.Screen                       =       S; 
       NW.Type                         =       CUSTOMSCREEN; 

       Set_Win = (struct Window *) OpenWindow( &NW ); 
 
       if( Set_Win == NULL ) return( -1 ); 

/*
**     Draw Boxes for individual colors.  This will handle to 32 
**     colors.
*/


       pen = 1 << MaxBit;
       for( i = 0; i < pen; i++)
       {
               short sx, sy, w, h; 
               unsigned short color = colortable[i]; 

                SetRGB4( &S->ViewPort, i, (color>>8)&0x000f, 
                       (color>>4)&0x000f, (color)&0x000f ); 

               sx = ((i % (pen/2)) + 1) * WINWIDTH / (pen/2+2); 
               sy = (i < (pen/2)) ? 54 : 63; 
               w = WINWIDTH / (pen/2 + 2) - 2; 
               h = 5; 
               Draw_Box( i, sx, sy, w, h );
       }

/*
**     Draw the border
*/

       Move(Set_Win->RPort,  40, 19);
       Draw(Set_Win->RPort, 250, 19); 
       Draw(Set_Win->RPort, 250, 52); 
       Draw(Set_Win->RPort,  40, 52); 
       Draw(Set_Win->RPort,  40, 19);

/*
**     Add Misc Gadgets
*/

       Add_Gadgets( Set_Win );
/*
**     Add the proportional gadgets for the individual colors. 
*/

       Add_Prop( 0, 45, 21, 200, 10 ); 
       Add_Prop( 1, 45, 31, 200, 10 );
       Add_Prop( 2, 45, 41, 200, 10 ); 
 
       pen = 0;
       Set_Gadg_Color();
 
/*     Process Mouse   */

       while( TRUE ){

/*     Wait for message, the loop until no more movement       */ 

               Wait( 1 << Set_Win->UserPort->mp_SigBit );

               while( mess = (struct IntuiMessage *)
                                       GetMsg( Set_Win->UserPort ) ){ 

                       class = mess->Class; 
                       code = mess->Code; 
                       ptr = mess->IAddress;
                       ReplyMsg( (struct Message *)mess );

                       switch( class ){
                               case CLOSEWINDOW: 
                                       CloseWindow( Set_Win ); 
                                       return( 0 ); 
                               case MOUSEBUTTONS: 
                                       Work_Mouse( code ); 
                                       break; 
                               case GADGETDOWN: 
                                       Set_Color( pen ); 
                                       break; 
                               case GADGETUP: 
                                       Do_Gadget( ptr );
                                       Set_Gadg_Color(); 
                               default: 
                                       break; 
                       } 
               } 
       }
}

/*
**     Draw a Box of the appropriate color
*/

Draw_Box( i, x, y, w, h )
int x, y, i, w, h;
{
       SetDrMd( Set_Win->RPort, COMPLEMENT );
       SetAPen( Set_Win->RPort, i ); 
       RectFill( Set_Win->RPort, x, y, x+w+2, y+h+2 ); 
       SetDrMd( Set_Win->RPort, JAM1 ); 
       SetAPen( Set_Win->RPort, i ); 
       RectFill( Set_Win->RPort, x+1, y+1, x+w+1, y+h+1 ); 
}

/*
**     Do the mouse tracking
*/


Work_Mouse( arg )
int arg;
{
       int penno;

       if( Set_Win->MouseY < 52 )
               return;

       if( arg == SELECTDOWN || arg == MENUDOWN )
               return;

       if (arg == SELECTUP)
               pen = ReadPixel( Set_Win->RPort, Set_Win->MouseX, 
                                               Set_Win->MouseY ); 
       else
               bpen = ReadPixel( Set_Win->RPort, Set_Win->MouseX, 
                                               Set_Win->MouseY ); 

       Set_Gadg_Color();
} 

/*
 *     The current color box.  The foreground color is
 *     color 1 and the background color is color 2 
 */

struct IntuiText CColor = {
       1, 0,
       JAM2,
       0, 0,
       NULL,
       (UBYTE *)" -Current Color- ", 
       NULL,
};


Set_Gadg_Color()
{
       unsigned short c[3];
       struct Gadget *G;
       int i;

       c[0] = colortable[ pen ] & 0x000f;
       c[1] = ( colortable[ pen ] >> 4 ) & 0x000f; 
       c[2] = ( colortable[ pen ] >> 8 ) & 0x000f; 

       G = Set_Win->FirstGadget; 

       i = 0;

       while( G != NULL ){

               if( G->GadgetType == PROPGADGET ){ 
 
                       if( G->GadgetID == 'R' ) i = 2; 
                       if( G->GadgetID == 'G' ) i = 1; 
                       if( G->GadgetID == 'B' ) i = 0; 
                       ModifyProp( G, Set_Win, NULL, FREEHORIZ, 
                               (USHORT)((0x1110) * c[i]) , 0,  
                                       (USHORT)(0x0fff), 0 ); 
               } 

               G = G->NextGadget; 
 
       }

       CColor.FrontPen = pen;
       CColor.BackPen = bpen;

       PrintIText( Set_Win->RPort, &CColor, 
               (WINWIDTH-IntuiTextLength(&CColor))/2, 75 ); 
}


/*
**     This produces a line
*/

extern USHORT  SData[];
char *Color_Name[] = {"Red ", "Grn ", "Blu " };

struct IntuiText IT = {
       1, 0,
       COMPLEMENT,
       0, 0, 
       NULL, 
       NULL,
       NULL,
};

/*
**     This adds the horizontally moving Proportional Gadgets. 
**     The HorizBody was found mostly by trial and error, 
**     As I found the Doc to be less than helpful. 
*/

Add_Prop( color, sx, sy, w, h )
int color;
int sx, sy, w, h;
{
 
       static struct Gadget G[3];
       static struct PropInfo P[3]; 
       static struct Image I[3]; 
 
       P[color].Flags = FREEHORIZ; 
       P[color].HorizBody = (USHORT)(0x0fff); 

       I[color].Width = 4;
       I[color].Height = 6; 
       I[color].Depth = 1; 
       I[color].ImageData = &SData[0]; 
       I[color].PlanePick = 0x01; 

       G[color].LeftEdge = sx; 
       G[color].TopEdge  = sy; 
       G[color].Width    = w; 
       G[color].Height   = h; 

       G[color].Flags = GADGHBOX | GADGIMAGE; 
       G[color].Activation = GADGIMMEDIATE | RELVERIFY; 
       G[color].GadgetType = PROPGADGET; 
       G[color].GadgetRender = (APTR)&I[color]; 
       G[color].SelectRender = NULL; 
       G[color].SpecialInfo = (APTR)&P[color]; 
       G[color].GadgetText = NULL; 
       G[color].GadgetID = (int)(*Color_Name[color]); 

       IT.IText = (UBYTE *)Color_Name[color]; 
       PrintIText(Set_Win->RPort, &IT, sx - IntuiTextLength(&IT), sy ); 

       AddGadget( Set_Win, &G[color], -1 ); 
       OnGadget( &G[color], Set_Win, NULL ); 

}
