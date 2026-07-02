/*
	This is a bunch of the IFF stuff from the ROM Kernal Manual.
*/

#define IFF_H	1

#include <stdio.h>
#ifndef EXEC_TYPES_H
	#include <exec/types.h>
#endif
#ifndef EXEC_MEMORY_H
	#include <exec/memory.h>
#endif
#ifndef INTUITION_INTUITION_H
	#include <intuition/intuition.h>
#endif
#ifndef INTUITION_SCREENS_H
	#include <intuition/screens.h>
#endif

#define SEEK_SET 0



typedef struct
	{
		LONG  ckID;
		LONG  cksize;
		UBYTE *ckdata;
	}
Chunk;

typedef LONG ID;

#define MakeID(a,b,c,d)	  ((LONG)(a)<<24 | (LONG)(b)<<16 | (c)<<8 | (d))


#define ID_FORM		MakeID('F','O','R','M')		/* chunk types */
#define ID_LIST		MakeID('L','I','S','T')
#define ID_PROP		MakeID('P','R','O','P')
#define ID_CAT		MakeID('C','A','T',' ')

#define ID_BMHD		MakeID('B','M','H','D')		/* sub-types     */
#define ID_BODY		MakeID('B','O','D','Y')		/* for IFF ILBMs */
#define ID_CMAP		MakeID('C','M','A','P')
#define ID_GRAB		MakeID('G','R','A','B')
#define ID_DEST		MakeID('D','E','S','T')
#define ID_SPRT		MakeID('S','P','R','T')
#define ID_CAMG		MakeID('C','A','M','G')

typedef UBYTE Masking;							/* more ILBM stuff */

#define mskNone					0
#define mskHasMask				1
#define mskHasTransparentColor	2
#define mskLasso				3

typedef UBYTE Compression;

#define cmpNone		0
#define cmpByteRun1	1

typedef struct 
	{
		UWORD w,h;			/* width, height */
		WORD  x,y;			/* pixel display position */
		UBYTE nplanes;		/* number of bitplanes    */
		Masking masking;	
		Compression compression;
		UBYTE pad1;			/* word-align next item */
		UWORD TransparentColor;		/* transparent color... */
		UBYTE xAspect, yAspect;		/* aspect ratio width:height */
		WORD pageWidth,pageHeight;	/* source page size, in pixels */
	}
BitMapHeader;

typedef struct
	{
		UBYTE red, green, blue;
	}
ColorRegister;

typedef ColorRegister ColorMap[64];	
										
typedef struct 
	{
		unsigned pad1 :4, red :4, green :4, blue :4;
	}
Color4;

typedef struct
	{
		WORD x,y;
	}
Point2D;

typedef struct
	{
		UBYTE depth;		/* bitplanes in source image */
		UBYTE pad1;
		UWORD planePick;
		UWORD planeOnOff;
		UWORD planeMask;
	}
DestMerge;

typedef UWORD SpritePrecedence;

/* for viewmodes and the CAMG chunk type */

#define BADFLAGS	(SPRITES|VP_HIDE|GENLOCK_AUDIO|GENLOCK_VIDEO)
#define FLAGMASK	(~BADFLAGS)
#define CAMGMASK	(FLAGMASK & 0x0000FFFFL)


BOOL GetBMHD(FILE *ifffile,BitMapHeader *header);
ULONG PullID(UBYTE *data);
BOOL GetViewModes(struct NewScreen *newscreen,FILE *ifffile);
BOOL FindChunk(FILE *ifffile,ULONG chunktype,Chunk *chunk);
#ifdef FOOP
SHORT GetColorMap(FILE *ifffile,UWORD *colortable);
#endif
BOOL ReadPic(struct BitMap *bitmap,FILE *ifffile,BitMapHeader *header);
