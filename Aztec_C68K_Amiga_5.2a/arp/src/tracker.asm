; Glue routines for arp.library and MANX/AZTEC 'C'
; Copyright (C) 1987, Scott Ballantyne
; Use at your own risk, etc., etc.
; May be freely used.

; updated for Aztec C v5.0a (also works w/ Lattice) by Bill Barton (peabody)

      nolist
	INCLUDE "exec/types.i"
	INCLUDE "exec/execbase.i"
	INCLUDE "libraries/arpbase.i"
	INCLUDE "libraries/dosextens.i"
      list

; Variables used by 'C' to access certain extra arplibrary returns

	section tracker,data
	xref	_ArpBase
	xref	_AbsExecBase
	section tracker,code

****************************************************************
*
*   Tracker (macro)
*
*   SYNOPSIS
*	Tracker funcname[,savecnt,saveregs[,rcnt1,rset1
*		[,rcnt2,rset2[,patch]]]]
*
*   FUNCTION
*	Link to Arp Tracker function
*
*   INPUTS
*	funcname - Name of function.
*	saveregs - 68000 register mask of registers that need
*		   to be saved (subset of regset1 & 2)
*	regset1, regset2
*		 - 68000 register masks (for MOVEM) in the order
*		   that they are to appear to the C function.
*	patch	 - patch includes a MOVE.L D0,A1 to correct a bug
*		   in ArpAlloc().
*
*   RESULTS
*	None
*
****************************************************************

Tracker macro
	xref	_LVO\1
	xdef	_\1
_\1
	ifnc	'\3',''
	movem.l \3/a6,-(sp)
	endc
	ifc	'\3',''
	move.l	a6,-(sp)
	endc

	ifnc	'\5',''
	ifne	\4-1
	movem.l \2*4+8(sp),\5
	endc
	ifeq	\4-1
	move.l	\2*4+8(sp),\5
	endc
	endc

	ifnc	'\7',''
	ifne	\6-1
	movem.l (\2+\4)*4+8(sp),\7
	endc
	ifeq	\6-1
	move.l	(\2+\4)*4+8(sp),\7
	endc
	endc

	move.l	_ArpBase,a6
	jsr	_LVO\1(a6)

	ifnc	'\8',''
	move.l	d0,a1			; this fixes w/ an error in ArpAlloc()
	endc

	ifnc	'\3',''
	movem.l (sp)+,\3/a6
	endc
	ifc	'\3',''
	move.l	(sp)+,a6
	endc

	bra.s	Check_Save

	endm


	; GetTracker()

	xref	_LVOGetTracker
	xdef	_GetTracker
_GetTracker
	move.l	a6,-(sp)
	move.l	_ArpBase,a6
	jsr	_LVOGetTracker(a6)
	move.l	(sp)+,a6                ; (doesn't affect flags)

	beq.s	No_Tracker		; No tracker, ERROR!
	move.w	6(sp),dt_ID(a1)         ; Save ID  (It was LONG)
	move.l	a1,d0			; Put into return register
	bra.s	Save_Second		; Also save it...


	; Tracked resource functions

	Tracker ArpAllocMem,0,,2,d0-d1
	Tracker ArpOpen,1,d2,2,d1-d2
	Tracker ArpDupLock,0,,1,d1
	Tracker ArpLock,1,d2,2,d1-d2
	Tracker ArpAlloc,0,,1,d0,0,,PATCH	; ArpAlloc() fails to setup A1, PATCH here patches it
	Tracker RListAlloc,0,,1,a0,1,d0
	Tracker ArpOpenLibrary,0,,1,a1,1,d0
	Tracker ArpAllocFreq


	; Common result handler code

	far data

Check_Save
	tst.l	d0			; Check for return error...
	beq.s	Exit_Save		; If error, skip setting...

Save_Second
	move.l	_AbsExecBase,a0
	move.l	ThisTask(a0),a0
	move.l	a1,pr_Result2(a0)

No_Tracker
Exit_Save
	rts


	END

