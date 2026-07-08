	
	include	lmacros.h

ifdef FARPROC
	extrn	_splitpath_:far
else
	extrn	_splitpath_:near
endif

	procdef fnsplit
	jmp	_splitpath_
	pend	fnsplit
	finish
	end
