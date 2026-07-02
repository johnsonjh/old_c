/* 3D library - By Steve Ludtke  */
/* cre : 8/14/89   mod : 1/5/90  */
/*           ver 1.0             */
/*       Copyright 1990          */


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

#include <stdio.h>
#include <exec/types.h>
#include <exec/lists.h>
#include <exec/memory.h>
#include <graphics/gfx.h>
#include <graphics/rastport.h>
#include <graphics/gfxbase.h>
#include <graphics/gfxmacros.h>
#include <graphics/text.h>
#define INTUITION_INTUITIONBASE_H TRUE
#include <intuition/intuition.h>
#include<math.h>

#define PI      3.141592

typedef struct { long *x,*y,*z; long *tx,*ty,*tz;} VECTOR;

/* this structure is used to sort surfaces for hidden line removal */
typedef struct { long d,n; } SORTS;

typedef struct { unsigned int l; unsigned int nl : 1;
    unsigned int nc : 1; unsigned int nco : 1; } LINES;

long xfm[3][4];              /* transformation matrix */
struct TmpRas TR;            /* TmpRas and AreaInfo for filled polygons */
struct AreaInfo AI;
WORD LB[500];                /* Line buffer. Polygons limited to 100 lines */

/* comparison routine for qsort() */
cmp(x,y)
SORTS *x,*y;
{
return(y->d - x->d);
}

/* set new x-form matrix  a1=x/y  a2=z/xy  a3=z'/x'y' (see Goldstein 146) */
/* tx,ty,tz are translsations after rotation                               */
setxfm(a1,a2,a3,tx,ty,tz,n,d)
double a1,a2,a3;
long tx,ty,tz,n,d;
{
xfm[0][0]=(long) (( cos(a3)*cos(a1)-cos(a2)*sin(a1)*sin(a3))*REZ)*n/d;
xfm[1][0]=(long) ((-sin(a3)*cos(a1)-cos(a2)*sin(a1)*cos(a3))*REZ)*n/d;
xfm[2][0]=(long) ( sin(a2)*sin(a1)*REZ)*n/d;
xfm[0][1]=(long) (( cos(a3)*sin(a1)+cos(a2)*cos(a1)*sin(a3))*REZ)*n/d;
xfm[1][1]=(long) ((-sin(a3)*sin(a1)+cos(a2)*cos(a1)*cos(a3))*REZ)*n/d;
xfm[2][1]=(long) (-sin(a2)*cos(a1)*REZ)*n/d;
xfm[0][2]=(long) ( sin(a3)*sin(a2)*REZ)*n/d;
xfm[1][2]=(long) ( cos(a3)*sin(a2)*REZ)*n/d;
xfm[2][2]=(long) ( cos(a2)*REZ)*n/d;
xfm[0][3]=tx;
xfm[1][3]=ty;
xfm[2][3]=tz;
return(0);
}

/* rotate without perspective */
rotate(v,n)
VECTOR *v;
int n;
{
int i;
for (i=0; i<n; i++) {
v->ty[i]=(v->x[i]*xfm[1][0]+v->y[i]*xfm[1][1]+v->z[i]*xfm[1][2])/REZ+xfm[1][3];
v->tx[i]=((v->x[i]*xfm[0][0]+v->y[i]*xfm[0][1]+v->z[i]*xfm[0][2])/REZ+xfm[0][3])*ASPECT+XCEN;
v->tz[i]=((v->x[i]*xfm[2][0]+v->y[i]*xfm[2][1]+v->z[i]*xfm[2][2])/REZ+xfm[2][3])+YCEN;
}
return(0);
}

/* rotate with perspective */
rotatev(v,n)
VECTOR *v;
int n;
{
long i,j;
for (i=0; i<n; i++) {
if (0==(v->ty[i]=(v->x[i]*xfm[1][0]+v->y[i]*xfm[1][1]+v->z[i]*xfm[1][2])/REZ+xfm[1][3])) v->ty[i]= -1;
j=D3VDIST- v->ty[i];
if (j<=0) j=1000000L;
v->tx[i]=((v->x[i]*xfm[0][0]+v->y[i]*xfm[0][1]+v->z[i]*xfm[0][2])/REZ+xfm[0][3])*j/D3VDIST*ASPECT+XCEN;
v->tz[i]=((v->x[i]*xfm[2][0]+v->y[i]*xfm[2][1]+v->z[i]*xfm[2][2])/REZ+xfm[2][3])*j/D3VDIST+YCEN;
}
return(0);
}

/* set up 1 or 2 rastports for filled shape drawing */
Init3Ras(rp,rp2)
struct RastPort *rp,*rp2;
{
PLANEPTR buf;
InitArea(&AI,(short *)&LB,200);
rp->AreaInfo=&AI;
if (rp2!=NULL) rp2->AreaInfo=&AI;
buf=(PLANEPTR)AllocRaster(XHI,YHI);
InitTmpRas(&TR,(char *)buf,RASSIZE(XHI,YHI));
rp->TmpRas=&TR;
if (rp2!=NULL) rp2->TmpRas=&TR;
return(0);
}

/* free memory allocated by Init3Ras */
Exit3d(rp)
struct RastPort *rp;
{
FreeRaster(rp->TmpRas->RasPtr,XHI,YHI);
return(0);
}

/* draw outlines of 3d shapes */
d3lines(v,l,n,rp)
VECTOR *v;
int n;
LINES *l;
struct RastPort *rp;
{
int i,flag;

flag=0;
for (i=0; i<n; i++) {

while (l[i].nc || l[i].nco) {                    /* change colors if necc. */
    if (l[i].nco) SetAPen(rp,l[i].l);
    i++;
    }
if (v->tx[l[i].l]>XLO && v->tx[l[i].l]<XHI &&    /* clip to defined region */
    v->tz[l[i].l]>YLO && v->tz[l[i].l]<YHI ) {
if (l[i].nl) { Move(rp,v->tx[l[i].l],v->tz[l[i].l]); flag=0; }
else {
    if (v->ty[l[i].l]<0) flag=1;
    else if (flag==1) { Move(rp,v->tx[l[i].l],v->tz[l[i].l]); flag=0; }
    else Draw(rp,v->tx[l[i].l],v->tz[l[i].l]);
    }
}
else flag=1;

}
return(0);
}

/* draw filled 3d shapes with hidden lie removal */
d3surf(v,l,n,rp)
VECTOR *v;
LINES *l;
int n;
struct RastPort *rp;
{
int i,j,flag,c;
int cmp();
SORTS s[100];

c= -1;
for (i=0; i<n; i++) {                                /* set up SORTS for */
    if (l[i].nl)  { c++; s[c].n=i; s[c].d=0; }       /* qsort, HLR       */
    if (!l[i].nc && !l[i].nco) s[c].d+=v->ty[l[i].l];
    }
qsort(s,c+1,sizeof(SORTS),cmp);                    /* sort lines for HLR */

for (j=0; j<c+1; j++) {                            /* draw shapes in order */
flag=0;
i=s[j].n;
while(!l[i].nl && i!=n || i==s[j].n) {
while (l[i].nc || l[i].nco) {
    if (l[i].nc) SetAPen(rp,l[i].l);
    if (l[i].nco) SetOPen(rp,l[i].l);
    i++;
    }
if (v->tx[l[i].l]>XLO && v->tx[l[i].l]<XHI &&
    v->tz[l[i].l]>YLO && v->tz[l[i].l]<YHI ) {
if (l[i].nl) { AreaMove(rp,v->tx[l[i].l],v->tz[l[i].l]); flag=0; }
else {
    if (v->ty[l[i].l]<0) flag=1;
    else if (flag==1) { AreaMove(rp,v->tx[l[i].l],v->tz[l[i].l]); flag=0; }
    else AreaDraw(rp,v->tx[l[i].l],v->tz[l[i].l]);
    }
}
else flag=1;
i++;
}
AreaEnd(rp);

}
return(0);
}




