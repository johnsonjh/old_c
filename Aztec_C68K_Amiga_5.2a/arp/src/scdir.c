/* Copyright (C) 1986,1987 Manx Software Systems, Inc.  */

/* not exactly re-entrant, is it?  it does make a simple directory scanner though */

#include <exec/memory.h>
#include <libraries/arpbase.h>
#include <errno.h>
#include <stdlib.h>
#include <functions.h>

#define MAXNAMELEN 256

struct AnchorPath *findfirst(char *), *findnext(void);

char *scdir (char *pat)
{
    register struct AnchorPath *ap;
    static int time = 0;

    Chk_Abort();

    do {
	if (!time) {        /* new pattern */
	    time = 1;
	    ap = findfirst(pat);
	}
	else {		    /* continue pattern */
	    ap = findnext();
	}
    } while (ap && ap->ap_Info.fib_DirEntryType > 0);

    if (!ap) {          /* no more (return null) */
	time = 0;
	return NULL;
    }

    return ap->ap_Buf;	/* return ptr to name */
}


struct AnchorPath *allocap(void);
struct AnchorPath *findrtn(ULONG rc);
static struct AnchorPath *_ap;

static
struct AnchorPath *findfirst (char *path)
{
    if (!_ap && !allocap()) return NULL;

    return findrtn (FindFirst (path,_ap));
}

static
struct AnchorPath *findnext(void)
{
    return findrtn (FindNext (_ap));
}

static
struct AnchorPath *findrtn(ULONG rc)
{
    switch (rc) {
	case 0:
		return _ap;

	case ERROR_BREAK:
		abort();
	case ERROR_NO_MORE_ENTRIES:
		errno = 0;
		break;

	default:
		errno = rc;
		break;
    }

    FreeAnchorChain (_ap);

    return NULL;
}


static
struct AnchorPath *allocap(void)
{
    register struct AnchorPath *ap = NULL;

    if ( (ap = ArpAlloc((long)sizeof *ap + MAXNAMELEN)) ) {
	SET_ID(ap,TRAK_ANCHOR);

	if (Enable_Abort) ap->ap_BreakBits = SIGBREAKF_CTRL_C;
	ap->ap_StrLen = MAXNAMELEN;
	_ap = ap;
    }
    else errno = ENOMEM;

    return ap;
}
