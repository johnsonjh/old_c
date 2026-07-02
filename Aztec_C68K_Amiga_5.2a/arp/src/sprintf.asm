	public	_LVOSPrintf
	public	_ArpBase

	public	_SPrintf
_SPrintf
	movem.l 4(sp),d0/a0             ; buffer, format string
	lea.l	12(sp),a1               ; data stream
	move.l	a6,-(sp)
	move.l	_ArpBase,a6
	jsr	_LVOSPrintf(a6)
	move.l	(sp)+,a6
	rts

	end

