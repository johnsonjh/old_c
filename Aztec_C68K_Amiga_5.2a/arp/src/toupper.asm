	xref	_LVOToupper
	xref	_ArpBase

	xdef	_Toupper
_Toupper
	IFD	INT32
	move.l	4(sp),d0
	ENDC
	IFND	INT32
	move.w	4(sp),d0
	ENDC
	move.l	a6,-(sp)
	move.l	_ArpBase,a6
	jsr	_LVOToupper(a6)
	move.l	(sp)+,a6
	rts

	end
