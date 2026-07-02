/* Test Demo Program - By Steve Ludtke */
/*     cre : 1/3/90    mod : 1/5/90    */
/*           Copyright 1990            */

/*
	MOD: 
		1/9/89 Mike Spille -- Manx Software Systems
	Changes:
		- Minor changes for clean compilation under Aztec C 5.0a
		- Added VANILLAKEY IDCMP support (console I/O sux!)
*/

/*
          The 3d library and all associated software in this distribution
          is Copyright 1990 by Steven J. Ludtke. You have permission to
          use and/or modify this code for any purpose commercial or non-
          commercial with two conditions : I must be given credit in any
          distributed product's documentation, and if any part of this
          package is used in any commercial product (even Shareware) one
          free copy of said software must be sent to me at the following
          address : Steven Ludtke, 406 Yale Cir., Glenwood Springs, CO
          81601; all other royalties are waived. This Copyright notice
          must accompany any distributions of any part of this package,
          and in general, the package should be distributed intact, with
          no modifications. This notice must not be removed from the 3d.c,
          test.c, and cube.c source code in this release.
*/

/*
INSTRUCTIONS : This program will display shapes stored in a standard file
format from any perspective. It does not use double buffered animation. The
user changes his viewpoint using the keys on the numeric keypad as is shown
in the code. Also, the '5' key toggles filling on and off, and 'q' exits
the program. Console i/o is used, so you have to press return before
anything will take effect. Run the program as follows :
'test <file.3d> <scale, usu 1>'

The 3d file format is :
number of vertices (n)
x0,y0,z0
x1,y1,z1
.
.
.
xn,yn,zn
number of line array elements (m)
a0 b0
a1 b1
.
.
.
am bm
<EOF>

where a are vertex numbers or colors, and b is : <0> - continue shape/line,
<1> - begin new line, <2> - change fill color, <3> - change outline color.

look at the color changing warnings in the docs.
*/

#include <stdio.h>
#include <stdlib.h>
#include <functions.h>

#define D3VDIST 5000        /* distance to vanishing point */
#define REZ     128         /* calc resolution must be 2^x */
#define REZB    7           /* number of bits in REZ */
#define XCEN    250         /* center of bitmap X */
#define YCEN    80          /* center of bitmap Y */
#define XHI     600
#define YHI     180
#define XLO     0
#define YLO     0
#define ASPECT  22/10       /* aspect ratio */
#include "3d.c"

APTR IntuitionBase,GfxBase;


struct NewWindow NW = {
	0,1,			/* LeftEdge & TopEdge */
	620,190,		/* Width & Height */
	1,1,			/* Detail & Block Pens */
	VANILLAKEY,		/* IDCMP flags */
    WINDOWDEPTH|WINDOWDRAG|ACTIVATE|SMART_REFRESH,
    NULL,NULL,(UBYTE *)"3D test window",NULL,NULL,0,0,0,0,WBENCHSCREEN
};

long *xxx;   /* points to x vertex data */
long *yyy;   /* ... */
long *zzz;

LINES *line; /* points to beginning of LINES array */
double a1,a2,a3;
int i,p,m,t,nl,nv,sca,f;
VECTOR v;
struct Window *win;

main(argc,argv)
int argc;
char *argv[];
{
	FILE *in;
	ULONG MessageClass;
	USHORT code;
	struct IntuiMessage		*message;

	GfxBase=(APTR) OpenLibrary("graphics.library",0);
	IntuitionBase=(APTR) OpenLibrary("intuition.library",0);

	f=0;
	if (argc != 3)
	{
		printf("Usage: test <file> <scale>\n");
		exit(0);
	}

	in=fopen(argv[1],"r");                      /* read 3d data */
	if (in==NULL)
	{
		printf("fnf\n");
		exit(0);
	}
	sscanf(argv[2]," %d",&sca);
	fscanf(in," %d",&nv);
	xxx=malloc(nv*sizeof(long));
	yyy=malloc(nv*sizeof(long));
	zzz=malloc(nv*sizeof(long));
	if (xxx==NULL || yyy==NULL || zzz==NULL)
	{
		printf("Out of memory\n");
		exit(0);
	}
	for (p=0; p<nv; p++)
		fscanf(in," %ld , %ld , %ld",&xxx[p],&yyy[p],&zzz[p]);
	fscanf(in," %d",&nl);
	line=(LINES *)malloc(nl*sizeof(LINES));
	if (line==NULL)
	{
		printf("Out of memory\n");
		exit(0);
	}
	for (p=0; p<nl; p++)
	{
		fscanf(in," %d %d",&t,&m);
	    line[p].l=t;
	    if (m==1)
			line[p].nl=1; 
		else
			line[p].nl=0;
	    if (m==2)
			line[p].nc=1;
		else
			line[p].nc=0;
	    if (m==3)
			line[p].nco=1;
		else 
			line[p].nco=0;
	}

	win=OpenWindow(&NW);	/* open a window and prepare for d3surf() */
	Init3Ras(win->RPort,NULL);
	if (win==NULL)
	{
		printf("Window err\n");
		exit(1);
	}
	v.x=xxx;		/* set up VECTOR structure */
	v.y=yyy;
	v.z=zzz;
	v.tx=(long *) malloc(nv*sizeof(long));
	v.ty=(long *) malloc(nv*sizeof(long));
	v.tz=(long *) malloc(nv*sizeof(long));

	a1=a2=a3=0;
	p=0;
	SetAPen(win->RPort,1);	/* set pens, in case no color data in file */
	SetOPen(win->RPort,2);
	SetDrMd(win->RPort,JAM1);

	for (;;)
	{
		if ((message = (struct IntuiMessage *)
				GetMsg (win->UserPort)) == NULL)
		{
			Wait (1L << win->UserPort->mp_SigBit);
			continue;
		}
		MessageClass = message->Class;
		code = message->Code;

		ReplyMsg ((struct Message *)message);

		if (MessageClass == VANILLAKEY)
		{
			if (check_keys (code))
				break;
		}
	}

	Exit3d(win->RPort);                       /* free up scratch memory */
	CloseWindow(win);
	free(v.tx);
	free(v.ty);
	free(v.tz);
	free(xxx);
	free(yyy);
	free(zzz);
	free(line);
}

check_keys (int code)
{
	if (code == 'q')
		return (1);
	switch(code) {
	case '9': 
		a1+=PI/20;
		break;
	case '7': 
		a1-=PI/20;
		break;
	case '6': 
		a2+=PI/20;
		break;
	case '4': 
		a2-=PI/20;
		break;
	case '3': 
		a3+=PI/20;
		break;
	case '1': 
		a3-=PI/20;
		break;
	case '8': 
		p+=100;
		break;
	case '2': 
		p-=100;
		break;
	case '5': 
		f^=1;
		break;
	}

	setxfm(a1,a2,a3,0,p,0,sca,1);	/* set new rotation matrix */
	rotatev(&v,nv);					/* rotate with perspective */
	SetRast(win->RPort,0);			/* clear window */
	if (f==0)
		d3lines(&v,line,nl,win->RPort); /* draw lines or filled shapes */
	else
		d3surf(&v,line,nl,win->RPort);
	return (0);
}
