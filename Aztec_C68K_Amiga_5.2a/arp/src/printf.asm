	public	_LVOPrintf
	public	_ArpBase

	public	_Printf
_Printf
	move.l	4(sp),a0                ; format string
	lea.l	8(sp),a1                ; data stream
	move.l	a6,-(sp)
	move.l	_ArpBase,a6
	jsr	_LVOPrintf(a6)
	move.l	(sp)+,a6
	rts

	end

