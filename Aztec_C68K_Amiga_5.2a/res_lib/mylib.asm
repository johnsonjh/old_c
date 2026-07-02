;:ts=8
;#include "mylib.h"
;
;void
;Func1(long value)
;{
	xdef	_Func1
_Func1:
	link	a5,#.2
	movem.l	.3,-(sp)
	move.l	d0,-4(a5)
	move.l	a4,-(sp)
	far	code
	public	_geta4
	jsr	_geta4
	near	code
;	struct mylibBase *mylibBase;
;
;	mylibBase->ml_value = value;
	move.l	-4(a5),38(a6)
;}
.4
	move.l	(sp)+,a4
	movem.l	(sp)+,.3
	unlk	a5
	rts
.2	equ	-4
.3	reg	
;
;long
;Func2(long value)
;{
	xdef	_Func2
_Func2:
	link	a5,#.5
	movem.l	.6,-(sp)
	move.l	d0,-4(a5)
	move.l	a4,-(sp)
	far	code
	public	_geta4
	jsr	_geta4
	near	code
;	struct mylibBase *mylibBase;
;
;	return(mylibBase->ml_value+value);
	move.l	38(a6),d0
	add.l	-4(a5),d0
.7
	move.l	(sp)+,a4
	movem.l	(sp)+,.6
	unlk	a5
	rts
;}
.5	equ	-4
.6	reg	
;
;
	xref	.begin
	dseg
	end
