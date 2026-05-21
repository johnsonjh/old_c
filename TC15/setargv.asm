	NAME	setargv
	PAGE	60,132
;[]------------------------------------------------------------[]
;|	SETARGV.ASM -- Parse Command Line			|
;|								|
;|	Turbo-C Run Time Library	version 1.5		|
;|								|
;|	Copyright (c) 1987 by Borland International Inc.	|
;|	All Rights Reserved.					|
;[]------------------------------------------------------------[]

	INCLUDE RULES.ASI

;	Segment and Group declarations

Header@

;	External references

ExtSym@		_argc, WORD, __CDECL__
dPtrExt@	_argv, __CDECL__
ExtSym@		_psp, WORD, __CDECL__
ExtSym@		_envseg, WORD, __CDECL__
ExtSym@		_envLng, WORD, __CDECL__
ExtSym@		_osmajor, BYTE, __CDECL__
ExtProc@	abort, __CDECL__

	SUBTTL	Parse Command Line
	PAGE
;/*							*/
;/*-----------------------------------------------------*/
;/*							*/
;/*	Parse Command Line				*/
;/*	------------------				*/
;/*							*/
;/*-----------------------------------------------------*/
;/*							*/
PSPCmd		equ	00080h


CSeg@

IF	LPROG
SavedReturn	dd	?
ELSE
SavedReturn	dw	?
ENDIF
SavedDS		dw	?
SavedBP		dw	?

PubProc@	_setargv, __CDECL__

;	First, save caller context and Return Address

		pop	word ptr SavedReturn
IF	LPROG
		pop	word ptr SavedReturn+2
ENDIF
		mov	SavedDS, ds
		cld

;	Compute Command Line size

		mov	es, _psp@
		mov	si, PSPCmd	; ES: SI = Command Line address
		xor	ax, ax
		lods	byte ptr es:[si]
		inc	ax		; CX = Command Line size including \r
		mov	bp, es
		xchg	dx, si		; BP:DX = Command Line address
		xchg	bx, ax		; BX	= Command line size

;	Compute Program Name size

		mov	si, _envLng@
		add	si, 2		; SI = Program name offset
		mov	cx, 1		; CX = Filename size (includes \0)
		cmp	_osmajor@, 3
		jb	NoProgramName
		mov	es, _envseg@
		mov	di, si		; SI = argv[0] address
		mov	cl, 07fh
		xor	al, al
	repnz	scasb
		jcxz	BadProgName
		xor	cl, 07fh	; CX = Filename size (includes \0)
NoProgramName	label	near

;	Reserve space for the arguments

		sub	sp, 2		; To be sure nothing in SS:FFFF
		mov	ax, 1
		add	ax, bx
		add	ax, cx
		and	ax, not 1
		mov	di, sp
		sub	di, ax
		jb	BadProgName
		mov	sp, di		; SS:DI = Command Line storage address

;	Copy ProgName to the stack

		mov	ax, es
		mov	ds, ax
		mov	ax, ss
		mov	es, ax
		push	cx
		dec	cx
	rep	movsb
		xor	al, al
		stosb			; ASCIIZ string

;	Process Command Line copying it to the stack

		mov	ds, bp
		xchg	si, dx		; DS: SI = Command Line address
		xchg	bx, cx		; CX = Command Line size including \r
		mov	ax, bx
		mov	dx, ax		; AX = BX = DX = 0
		inc	bx		; BX = Nb of arguments (at least 1)
Processing	label	near
		call	NextChar
		ja	NotQuote	; Not a quote and there are more
InString	label	near
		jb	BuildArgv	; Command line is empty now
		call	NextChar
		ja	InString	; Not a quote and there are more
NotQuote	label	near
		cmp	al, ' '
		je	EndArgument	; Space is an argument separator
		cmp	al, 13
		je	EndArgument	; \r	is an argument separator
		cmp	al, 9
		jne	Processing	; \t	is an argument separator
EndArgument	label	near
		xor	al, al		; Space and TAB are argument separators
		jmp	short Processing

;	Character test function used in SetArgs
;		On entry AL holds the previous character
;		On exit	 AL holds the next character
;			 ZF on if the next character is quote (") and AL = 0
;			 CF on if end of command line and AL = 0

NextChar	PROC	NEAR
		or	ax, ax
		jz	NextChar0
		inc	dx		; DX = Actual length of CmdLine
		stosb
		or	al, al
		jnz	NextChar0
		inc	bx		; BX = Number of parameters
NextChar0	label	near
		xchg	ah, al
		xor	al, al
		stc
		jcxz	NextChar2	; End of command line --> CF ON
		lodsb
		dec	cx
		sub	al, '"'
		jz	NextChar2	; Quote found --> AL = 0 and ZF ON
		add	al, '"'
		cmp	al,'\'
		jne	NextChar1	; It is not a \
		cmp	byte ptr ds:[si], '"'
		jne	NextChar1	; Only " is transparent after \
		lodsb
		dec	cx
NextChar1	label	near
		or	si, si		; Be sure both CF & ZF are OFF
NextChar2	label	near
		ret
NextChar	ENDP

;	Invalid program name

BadProgName	label	near
		jmp	abort@

;	Now, build the argv array

BuildArgv	label	near
		pop	cx
		add	cx, dx		; CX = Argument area size
		mov	ds, SavedDS
		mov	_argc@, bx
		inc	bx		; argv ends with a NULL pointer
		add	bx, bx		;	 argc * 2	(LDATA = 0)
IF	LDATA
		add	bx, bx		;	 argc * 4	(LDATA = 1)
ENDIF
		mov	si, sp
		mov	bp, sp
		sub	bp, bx
		jb	BadProgName
		mov	sp, bp		; SS:BP = argv array address
		mov	word ptr _argv@, bp
IF	LDATA
		mov	word ptr _argv@+2, ss
ENDIF
SetArgvX	label	near
		jcxz	SetLastArg
		mov	[bp], si	; Set argv[n]
IF	LDATA
		mov	[bp+2], ss
ENDIF
		add	bp, dPtrSize
CopyArg		label	near
		lods	byte ptr ss:[si]
		or	al, al
		loopnz	CopyArg
		jz	SetArgvX
SetLastArg	label	near
		xor	ax, ax
		mov	[bp], ax
IF	LDATA
		mov	[bp+2], ax
ENDIF

;	Restore caller context and exit

IF	LPROG
		jmp	dword ptr SavedReturn
ELSE
		jmp	word ptr SavedReturn
ENDIF
EndProc@	_setargv, __CDECL__
CSegEnd@
	END
