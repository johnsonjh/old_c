/* Cube Demo Program - By Steve Ludtke */
/*     cre : 1/3/90    mod : 1/5/90    */
/*           Copyright 1990            */

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

/* This program works almost exactly like test.c with 2 exceptions. First,
This program reads from a predefined string in memory instead of the
keyboard. The moves are rather grainy, so the animation isn't very smooth
looking. The other difference is double buffering. This program opens
two screens, then alternates which one it draws on. (It always draws on
the hidden one, then brings it up front.) In general, look at the comments
in test.c for more info. */


#include<stdio.h>

#define D3VDIST 1000        /* distance to vanishing point */
#define REZ     1024        /* calc resolution must be 2^x */
#define REZB    7           /* number of bits in REZ */
#define XCEN    320         /* center of bitmap X */
#define YCEN    90          /* center of bitmap Y */
#define XHI     639
#define YHI     189
#define XLO     0
#define YLO     0
#define ASPECT  22/10       /* aspect ratio */
#include "3d.c"

#define NUMVEC 10

APTR IntuitionBase,GfxBase;

struct NewScreen NS = { 0,0,640,200,2,1,0,HIRES,CUSTOMSCREEN,NULL,(UBYTE *)"cube",NULL,
    NULL };

long xxx[NUMVEC] = { 1, 1, 1, 1,-1,-1,-1,-1 };
long yyy[NUMVEC] = { 1, 1,-1,-1, 1, 1,-1,-1 };
long zzz[NUMVEC] = { 1,-1, 1,-1, 1,-1, 1,-1 };

LINES line[20] = { {0,1,0,0},{1,0,0,0},{5,0,0,0},{4,0,0,0},{0,0,0,0},
    {0,1,0,0},{4,0,0,0},{6,0,0,0},{2,0,0,0},{0,0,0,0},
    {2,1,0,0},{6,0,0,0},{7,0,0,0},{3,0,0,0},{2,0,0,0},
    {7,1,0,0},{3,0,0,0},{1,0,0,0},{5,0,0,0},{7,0,0,0} };

char *todo = "88888888888888886kikikiki6666663339369666jjjjmmmmpp5333333333333333333333333333533333333333333333333333335666636363636363693996969696ppppq";

int pt = 0;

nextc()
{
return(todo[pt++]);
}

main()
{
VECTOR v;
double a1,a2,a3;
char c;
int i,p,q,r,f,crp;
struct RastPort *rp[2];
struct Screen *s1,*s2, *OpenScreen ();

crp=f=0;
GfxBase=(APTR) OpenLibrary("graphics.library",0);
IntuitionBase=(APTR) OpenLibrary("intuition.library",0);

s1=OpenScreen(&NS);
s2=OpenScreen(&NS);
if (s1==NULL || s2==NULL) { printf("Can't open screen(s)\n"); exit(0); }
rp[0]=&s1->RastPort;
rp[1]=&s2->RastPort;

v.x=xxx;
v.y=yyy;
v.z=zzz;
v.tx=(long *) malloc(NUMVEC*sizeof(long));
v.ty=(long *) malloc(NUMVEC*sizeof(long));
v.tz=(long *) malloc(NUMVEC*sizeof(long));

for(i=0; i<8; i++) { xxx[i]*=40; yyy[i]*=40; zzz[i]*=40; }

a1=a2=a3=0;
p=q=r=0;
Init3Ras(rp[0],rp[1]);
SetAPen(rp[0],1);
SetOPen(rp[0],2);
SetDrMd(rp[0],JAM1);
SetAPen(rp[1],1);
SetOPen(rp[1],2);
SetDrMd(rp[1],JAM1);

while ((c=nextc())!='q') {
switch(c) {
case '9': a1+=PI/20; break;
case '7': a1-=PI/20; break;
case '6': a2+=PI/20; break;
case '4': a2-=PI/20; break;
case '3': a3+=PI/20; break;
case '1': a3-=PI/20; break;
case '5': f^=1;      break;
case 'k': q+=5;     break;
case 'j': q-=5;     break;
case 'm': r+=5;     break;
case 'i': r-=5;     break;
case '8': p+=10;     break;
case '2': p-=10;     break;
case 'p': for (i=0; i<30; i++) WaitTOF(); break;
}
setxfm(a1,a2,a3,q,p,r,1,1);
rotatev(&v,8);
SetRast(rp[crp],0);
if (f==0) d3lines(&v,line,20,rp[crp]);
else d3surf(&v,line,20,rp[crp]);
if (crp==1) ScreenToFront(s2);
else ScreenToFront(s1);
crp^=1;
}

Exit3d(rp[0]);
CloseScreen(s1);
CloseScreen(s2);
free(v.tx);
free(v.ty);
free(v.tz);
}


