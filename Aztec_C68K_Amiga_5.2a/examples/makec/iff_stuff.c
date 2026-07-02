
/*
	These are some IFF file handler routines...
*/

#ifndef IFF_H
	#include "iff.h"
#endif

UBYTE iff_disk_buffer[4096];   /* a 4K disk buffer to speed I/O to file  */
SHORT iff_buffer_size;			/*  these are not used at the moment     */
SHORT iff_buffer_position;		/*  but I figure they may come in handy  */
ULONG iff_file_position;		/*  sometime.  Only 6 bytes, no biggie   */



/*
	PullID() is done here as an actual subroutine, although it could just
	as easily be set up as a macro with a #define.  All it does is takes
	a pointer to a text buffer and yanks out the first four bytes and
	shifts them into a ULONG, then returns it.
*/

ULONG PullID(what)
UBYTE *what;
{
	return (ULONG)((ULONG)what[0]<<24 | (ULONG)what[1]<<16 | (ULONG)what[2]<<8 | (ULONG)what[3]);
}


/*
	GetBMHD() takes a FILE pointer to an IFF file, and a pointer to a 
	BitMapHeader.  It then searches the IFF file for the header and reads
	the information into the BitMapHeader, one field at a time.  This 
	coud be made considerably faster and simpler by doing a memcpy() from
	the disk buffer instead, but this way makes it more clear what is in
	the BitMapHeader and the relative positions within the file, so I'll
	leave it like it is.
*/
	
BOOL GetBMHD(ifffile,header)
FILE *ifffile;
BitMapHeader *header;
{
	Chunk bmhdchunk;
	BOOL error;
										/* first find the chunk */
	error=FindChunk(ifffile,MakeID('B','M','H','D'),&bmhdchunk);
	if(error)
		return TRUE;					/* read the data into header */
	header->w = ((UWORD)(bmhdchunk.ckdata[0]) << 8) | (bmhdchunk.ckdata[1]);
	header->h = ((UWORD)(bmhdchunk.ckdata[2]) << 8) | (bmhdchunk.ckdata[3]);
	header->x = ((WORD)(bmhdchunk.ckdata[4]) << 8) | (bmhdchunk.ckdata[5]);
	header->y = ((WORD)(bmhdchunk.ckdata[6]) << 8) | (bmhdchunk.ckdata[7]);
	header->nplanes = bmhdchunk.ckdata[8];
	header->masking = bmhdchunk.ckdata[9];
	header->compression = bmhdchunk.ckdata[10];
	header->pad1 = 0;					/* set to 0 and skip over a byte */
	header->TransparentColor = (UWORD)(bmhdchunk.ckdata[12] << 8) | (bmhdchunk.ckdata[13]);
	header->xAspect = bmhdchunk.ckdata[14];
	header->yAspect = bmhdchunk.ckdata[15];
	header->pageWidth = ((WORD)(bmhdchunk.ckdata[16]) << 8) | (bmhdchunk.ckdata[17]);
	header->pageHeight = ((WORD)(bmhdchunk.ckdata[18]) << 8) | (bmhdchunk.ckdata[19]);
	FreeMem(bmhdchunk.ckdata,bmhdchunk.cksize);		/* free memory */
	return FALSE;
}

/* 
	GetViewModes() looks for a CAMG chunk in the IFF file.  If it finds
	one, it stores the ViewModes word into the NewScreen structure.  If
	there isn't, it sets up the minimal assumptions necessary to open the
	screen properly (i.e. lace or not and hires or not).
*/

BOOL GetViewModes(newscreen,ifffile)
struct NewScreen *newscreen;
FILE *ifffile;
{
	BOOL error = FALSE;
	Chunk camgchunk;
	
	error = FindChunk(ifffile,MakeID('C','A','M','G'),&camgchunk);
	if(!error)
		{
			newscreen->ViewModes = PullID(camgchunk.ckdata) & CAMGMASK;
			FreeMem(camgchunk.ckdata,camgchunk.cksize);
		}
	if(newscreen->Width > 384)			/* if no CAMG chunk, make it up */
		newscreen->ViewModes |= HIRES;	/* if there was one, this won't */
	if(newscreen->Height > 200)			/* hurt anything to double-check */
		newscreen->ViewModes |= LACE;
	return FALSE;	
}

/*
	FindChunk searches an IFF file for a chunk of type chunktype.  It 
	makes use of the iff_disk_buffer for speedier I/O.  The buffer 
	could be diddled with a little to improve speed, but you might wind
	up with overkill on the reads (probably already a lot of that at 4K).
	If it finds the chunk, it allocates memory for the chunk body 
	UNLESS it is a BODY type chunk.  It then reads the data into the 
	chunkdata section and returns.  It is up to the caller to free the 
	allocated memory.  If it is looking for a BODY type chunk, rather than
	allocate memory for the body, it leaves this part up to the caller
	(useful for on-the-fly decompression), and instead positions the 
	IFF file pointer so that it points to the start of the BODY chunk data.
*/

BOOL FindChunk(ifffile,chunktype,chunk)
FILE *ifffile;
ULONG chunktype;
Chunk *chunk;
{
	SHORT temppos;
	BOOL foundchunk= FALSE;
	ULONG bytes_read=0,seek_spot=0;
	SHORT buffer_size=0;
	
	rewind(ifffile);				/* start at top of file  */
	buffer_size = fread(iff_disk_buffer,1,4096,ifffile);	/* fill buffer */
	while(TRUE)		/* search whole file for chunk */
		{
			for(temppos=0;temppos<buffer_size;temppos++)	/* scan buffer */
				if(PullID(&iff_disk_buffer[temppos]) == chunktype)
					{
						foundchunk = TRUE;	/* found chunk type ? */
						break;
					}
			if((foundchunk) || feof(ifffile))	/* done ? */
				break;
			buffer_size = fread(iff_disk_buffer,1,4096,ifffile);
			bytes_read += buffer_size;		/* how far are we into file? */
		};	
	seek_spot = bytes_read + temppos + 8;	/* for a BODY chunk */
	if(foundchunk)	
		{
			chunk->ckID = PullID(&iff_disk_buffer[temppos]);
			chunk->cksize = PullID(&iff_disk_buffer[temppos+4]);
			if(chunk->ckID == MakeID('B','O','D','Y'))
				{
					chunk->ckdata = NULL;		/* fix file pointer */
					fseek(ifffile,seek_spot,SEEK_SET);
					return FALSE;				/* I'm outta here... */
				}
			chunk->ckdata = (UBYTE *)AllocMem(chunk->cksize,MEMF_CLEAR);
			if(chunk->ckdata == NULL)	/* not a BODY chunk at this point */
				{
					printf("\nNo memory for chunk!!\n");
					return TRUE;
				}
			temppos += 8;	/* read the data into the chunkdata section */
			for(bytes_read=0;bytes_read<chunk->cksize;bytes_read++)
				chunk->ckdata[bytes_read] = iff_disk_buffer[temppos++];
		}	
	else
		return TRUE;	/* hey, somethin' ain't right */
	return FALSE;		/* everything's fine */
}

/*
	GetColorMap scans an IFF file for a colormap, loading it into the
	colortable given.  It returns the number of colors in the table.
*/

SHORT GetColorMap(ifffile,colortable)
FILE *ifffile;
UWORD *colortable;
{
	Chunk cmapchunk;
	SHORT count=0;
	BOOL error = FALSE;

	error = FindChunk(ifffile,MakeID('C','M','A','P'),&cmapchunk);
	if(!error)								/* found colormap? */
		{									/* make RGB4's out of it */
			for(;count<cmapchunk.cksize/3;count++)
				{
					colortable[count] = (UWORD)cmapchunk.ckdata[(count*3)]<<4;
					colortable[count] |= (UWORD)cmapchunk.ckdata[(count*3)+1];
					colortable[count] |= (UWORD)cmapchunk.ckdata[(count*3)+2]>>4;
				}
			FreeMem(cmapchunk.ckdata,cmapchunk.cksize);
		}
	return (count);
}

/*
	ReadPic() is the picture reader.  It takes a pointer to a bitmap, a
	pointer to a file which need not be at any particular position, (it
	will find the data with FindChunk()), and a pointer to a BitMapHeader
	describing the picture being read.
	It doesn't matter whether the picture is on or off screen or whether
	it is not the same size as the bitmap.  If it is too small, it is read
	anyway.  If it is too large, it is clipped at the BitMap boundaries.
	Compressed and masked images are handled correctly.
*/

BOOL ReadPic(bitmap,ifffile,header)
struct BitMap *bitmap;
FILE *ifffile;
BitMapHeader *header;
{
	BOOL error = FALSE;
	BOOL mask = FALSE;
	BOOL compress = FALSE;
	Chunk bodychunk;
	SHORT scanline,plane,count,needed,read;
	BYTE data,run;
	UBYTE bit_bucket[255];
	UBYTE *dest;
	
	if(header->masking == mskHasMask)
		mask = TRUE;					/* got a mask on it ?*/
	if(header->compression == cmpByteRun1)
		compress = TRUE;				/* compressed via ByteRun1? */
	needed = header->w/8;				/* how many BYTES do we need? */
	if(header->w%8)						/* if odd number of pixels, */
		needed++;						/* adjust that number */
	error = FindChunk(ifffile,MakeID('B','O','D','Y'),&bodychunk);
	if(error)
		return TRUE;					/* YIKES!  No Body! */
	for(scanline=0;scanline<header->h;scanline++)	/* lines first */
		for(plane=0;plane<header->nplanes;plane++)	/* then planes */
			{
				if(mask & scanline%2)			/* ignore mask */
					dest = bit_bucket;			/* toss mask planes */
				else						/* figure scanline in bitmap */
					dest = bitmap->Planes[plane]+(scanline*bitmap->BytesPerRow);
				if(!compress)				/* not too likely, but easy */
					for(count=0;count<needed;count++)
						*dest++ = fgetc(ifffile);
				else						/* image is compressed */
					{
						count=0;			/* count is bytes decompressed */
						while(count<needed)	
							{
								run = fgetc(ifffile);	/* size of run */
								if(run>=0)				/* literal run */
									{
										count += run+1;
										for(read=0;read<=run;read++)
											*dest++ = fgetc(ifffile);
									}
								else if (run != 128)	/* repeat run */
									{
										run = run*(-1);
										count += run+1;
										data = fgetc(ifffile);
										for(read=0;read<=run;read++)
											*dest++ = data;
									}
							}
					}
		}
	return FALSE;
}


