/*
	A quick program to let you know what a picture looks like
	as far as size, colors, etc.  Must link with "iff_stuff.o"
*/

#include "iff.h"
#include <stdio.h>

main(argc,argv)
int argc;
char **argv;
{
	BitMapHeader header;	/* somewhere to put the info */
	int error;				/* bailout flag */
	FILE *ifffile;			/* the file */
	
	if(argc<2)				/* hey bonehead -- RTFM !! */
		{
			printf("\nUsage is:  %s <iff_filename>.\n",argv[0]);
			exit(5);
		}
	if((ifffile=fopen(argv[1],"rb"))==NULL)	/* open up the file */
		{
			printf("\nIFF file could not be opened!\n");
			exit(5);
		}
	if(error=GetBMHD(ifffile,&header))		/* scan the info into header */
		{
			printf("\nFile is invalid or not IFF.\n");
			fclose(ifffile);
			exit(5);
		}								/* tell it like it is.... */
	printf("\nInformation for IFF file %s -->\n\n",argv[1]);
	printf("Picture is %u pixels wide by %u pixels high.\n",
					header.w,header.h);
	printf("Picture is displayed at %d, %d relative to screen.\n",
					header.x,header.y);
	printf("Picture has %d bitplanes.\n",header.nplanes);
	if(header.masking & mskHasMask)
		printf("Picture has a mask plane.\n");
	if(header.masking & mskHasTransparentColor)
		printf("Picture has a transparent color in register %d.\n",
					header.TransparentColor);
	if(header.masking & mskLasso)
		printf("Picture has a lasso-style mask.\n");
	if(header.compression == cmpByteRun1)
		printf("Picture is compressed with ByteRun1 encoding.\n");
	printf("Picture has an aspect ratio of %u : %u. (x:y)\n",
					header.xAspect,header.yAspect);
	printf("Picture has a page size of %d pixels wide by %d pixels high.\n\n",
					header.pageWidth,header.pageHeight);
	fclose(ifffile);
	exit(0);
}

