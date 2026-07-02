/* Copyright (C) 1986,1987 by Manx Software Systems, Inc. */

/*
 *	This routine is called from the _main() routine and is used to
 *	open a window for standard I/O to use. The window is actually
 *	defined by setting the ToolType, "WINDOW", to the desired window
 *	specification. If this is not required, this routine may be
 *	replaced by a stub in the users main program. Note that even if
 *	this code is called by _main(), if the WINDOW tool type is not
 *	defined, there will be no window.
 *
 *	EXAMPLE:	WINDOW=CON:0/0/640/200/Test Window
 */

#include <libraries/dos.h>
#include <libraries/dosextens.h>
#include <workbench/workbench.h>
#include <workbench/startup.h>
#include <workbench/icon.h>
#include <functions.h>

void *IconBase;

void
_wb_parse(register struct Process *pp, struct WBStartup *wbm)
{
	register char *cp;
	register struct DiskObject *dop;
	register struct FileHandle *fhp;
	BPTR wind;

	if ((IconBase = OpenLibrary((UBYTE *)"icon.library", 0L)) == 0)
		return;
	if ((dop = GetDiskObject((UBYTE *)wbm->sm_ArgList->wa_Name)) == 0)
		goto closeit;
	if (cp = (char *)FindToolType((UBYTE **)dop->do_ToolTypes, 
											(UBYTE *)"WINDOW")) {
		if (wind = Open((UBYTE *)cp, (long)MODE_OLDFILE)) {
			fhp = (struct FileHandle *) ((long)wind << 2);
			pp->pr_ConsoleTask = (APTR) fhp->fh_Type;
			pp->pr_CIS = (BPTR)wind;
			pp->pr_COS = (BPTR)Open((UBYTE *)"*", (long)MODE_OLDFILE);
		}
	}
	FreeDiskObject(dop);
closeit:
	CloseLibrary(IconBase);
	IconBase = 0;
}

