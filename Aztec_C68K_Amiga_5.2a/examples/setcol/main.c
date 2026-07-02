/*
**     Brian D. Moffet
**     June 13, 1988 
**
**     Placed in the Public domain. 
**     Please allow me to retain credit for this, and please 
**     distribute source with the binaries. 
**
*/

#include <intuition/intuition.h>
#include <graphics/gfxbase.h>
#include <intuition/intuitionbase.h> 
#include <intuition/screens.h> 
#include <functions.h>

#include <stdio.h>

/*
**     Easier to type IB than IntuitionBase
*/

#define IB IntuitionBase
#define GB GfxBase

struct IntuitionBase *IntuitionBase; 
struct GfxBase *GfxBase=NULL; 

struct Screen *S;
int MaxBit;
USHORT oldcolortable[32]; 
USHORT colortable[32]; 

char Version[]="Setcolor 1.1  PD"; 
char Author[]="Brian Moffet sco!brianm"; 

char *Usage[] = {
       "setcolor [-num]", 
       "       -num: number of seconds to delay before attaching to the", 
       "             active window.", 
       " Gadget Definitions:", 
       "       B/W: make the palette a grey scale palette",
       "       Smear: blend from color 1 (letters in box) to color 2", 
       "       Exchange: exchange color 1 and color 2", 
       "       Copy: copy color 1 and color 2", 
       "       OK: Set the palette with your new colors", 
       "       Undo: reset colors from last OK or beginning", 
       NULL
}; 

/*
**     setcolor [num]
**     where num is the number of seconds befor program takes 
**     action and attaches itself to your window. 
*/

main( argc, argv )
int argc;
char *argv[];
{
       int i;
       int del;

       if (!strcmp( argv[1], "-h"))
       {
               puts( Version );
               puts( Author ); 
               for (i = 0; Usage[i]; i++) 
                       puts( Usage[i] ); 
               exit( 0 ); 
       }

       del  = atoi( argv[1] );
       if( del <= 0 ) del = 0; 

       IB = (struct IB *)OpenLibrary( (UBYTE *)"intuition.library", 0 ); 
       if( IB == NULL ) 
       {
               fprintf( stderr, "Error Opening IB\n" ); 
               exit( 1 ); 
       }
       GB = (struct GB *)OpenLibrary( (UBYTE *)"graphics.library", 0 ); 
       if( GB == NULL ) 
       {
               CloseLibrary( (struct Library *) IB ); 
               fprintf( stderr, "Error Opening GB\n" ); 
               exit( 2 ); 
       }

/*
**     Avoid the Delay( 0 ) bug
**     Part of my background is to avoid system calls whenever 
**     Possible.  I would have never found the Delay( 0 ) problem.. 
*/

       if( del )       Delay( del * 50 ); 

       S = IB->ActiveScreen;
       MaxBit = S->BitMap.Depth; 

       for( i = 0; i < 32; i++ )  
               oldcolortable[i] = colortable[i] = 
                       GetRGB4( S->ViewPort.ColorMap, i ); 
 
       Color_Window( S );
 
       i = 32; 
       while( --i >= 0 )
       {
               unsigned short color = oldcolortable[i]; 
 
                SetRGB4( &S->ViewPort, i, (color>>8)&0x000f, 
                       (color>>4)&0x000f, (color)&0x000f ); 
       }

       CloseLibrary( (struct Library *) GB );
       CloseLibrary( (struct Library *) IB ); 
}

/*
 *     Make a color palette into a gray-scale palette. 
 */

make_bw( r, g, b )
unsigned short *r, *g, *b;
{
       unsigned short v;

       if (*r == *g && *g == *b) 
               return;                 /* only shades of grey. */ 

       v = (*r * 298 + *g * 588 + *b * 114) / 1000; 
       *r = v; 
       *g = v;
       *b = v; 
}

/*
 *     get colors to go "smoothly" from color 1 to color 2 
 */

smear( c, begin, end )
unsigned short *c;
int begin, end;
{
       int d = (end - begin);
       int rd, gd, bd;
       unsigned short r, g, b; 
       int i;

       r = (c[begin] >> 8) & 0x0f; 
       g = (c[begin] >> 4) & 0x0f; 
       b = (c[begin] >> 0) & 0x0f; 

       rd = ((c[end] >> 8) & 0x0f) - r; 
       gd = ((c[end] >> 4) & 0x0f) - g; 
       bd = ((c[end] >> 0) & 0x0f) - b; 

       for (i = 0; i < d; i++) 
       {
               int j = (i + begin); 
 
               c[j] = ((r + (i * rd) / d) & 0x0f) << 8 
                       | ((g + (i * gd) / d) & 0x0f) << 4 
                       | ((b + (i * bd) / d) & 0x0f); 
                
       }
}
