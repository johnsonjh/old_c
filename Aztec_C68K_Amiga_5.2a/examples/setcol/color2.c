/*
**     Brian D. Moffet
**     June 13, 1988 
**
**     Placed in the Public domain. 
**     Please allow me to retain credit for this, and please 
**     distribute source with the binaries. 
*/

#include <intuition/intuition.h>
#include <intuition/screens.h> 
#include <functions.h>


extern struct Screen *S;
extern int MaxBit;
extern USHORT colortable[]; 

extern struct Window *Set_Win; 

/*
**     This sets the colors when the mouse is moved. 
*/

Set_Color( pen )
int pen;
{
    register struct IntuiMessage *I;
    struct Gadget *G;
    USHORT *g, *b, *r, class; 
    unsigned int color; 
 
    G = Set_Win->FirstGadget; 

    while( G != NULL ){
        switch( G->GadgetID ){ 
            case 'R': 
               r = &( (struct PropInfo *)G->SpecialInfo )->HorizPot; 
                break; 
            case 'G': 
               g = &( (struct PropInfo *)G->SpecialInfo )->HorizPot; 
                break; 
            case 'B': 
               b = &( (struct PropInfo *)G->SpecialInfo )->HorizPot; 
            default: 
                break; 
         }
         G = G->NextGadget; 
    }
         
/*
**     Mouse Movement while Gadget is down loop 
*/

    while( TRUE ){

        I = (struct IntuiMessage *) GetMsg( Set_Win->UserPort ); 

       class = I->Class;
 
       if( I != NULL ) ReplyMsg( (struct Message *)I ); 

        color = ( ( ( *r ) >> 12 ) << 8 ) | 
                ( ( ( *g ) >> 12 ) << 4 ) | 
                ( ( ( *b ) >> 12 )      ); 

        if( (color) != colortable[ pen ] ){ 
 
                SetRGB4( &S->ViewPort, pen, (color>>8)&0x000f, 
                       (color>>4)&0x000f, (color)&0x000f ); 
                colortable[ pen ] = color; 
        }

        if( class == GADGETUP ) return( 1 ); 
    }

}
