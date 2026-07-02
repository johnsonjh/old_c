/* mylib.c	-- exec library routines for mylib 	*/

#include <exec/lists.h>
#include <exec/resident.h>
#include <functions.h>
#include "mylib.h"

void myInit(void);
long myOpen(void);
long myClose(int);
long myExpunge(void);

#pragma amicall(mylibBase, 0x06, myOpen())
#pragma amicall(mylibBase, 0x0c, myClose(d3))
#pragma amicall(mylibBase, 0x12, myExpunge())

/* library initialization table, used for AUTOINIT libraries			*/
struct InitTable {
	unsigned long	it_DataSize;		  /* library data space size		*/
	void			**it_FuncTable;		  /* table of entry points			*/
	void 			*it_DataInit;		  /* table of data initializers		*/
	void			(*it_InitFunc)(void); /* initialization function to run	*/
};

void *libfunctab[] = {	/* my function table */
	myOpen,					/* standard open	*/
	myClose,				/* standard close	*/
	myExpunge,				/* standard expunge	*/
	0,

	/* ------	user UTILITIES */
	Func1,					/* user defined function 1 */
	Func2,					/* user defined function 2 */

	(void *)-1				/* end of function vector table */
};

struct InitTable myInitTab =  {
	sizeof (struct mylibBase),
	libfunctab,
	0,						/* will initialize my data in funkymain()	*/
	myInit
};

#define MYREVISION	4		/* would be nice to auto-increment this		*/

char myname[] = "mylib.library";
char myid[] = "MYLIB 0.4 (17 Oct 1989)\r\n";

extern struct Resident	myRomTag;

long
_main(struct mylibBase *mylibBase, unsigned long seglist)
{
	mylibBase->ml_SegList = seglist;

	/* ----- init. library structure  -----		*/
	mylibBase->ml_Lib.lib_Node.ln_Type = NT_LIBRARY;
	mylibBase->ml_Lib.lib_Node.ln_Name = (char *) myname;	
	mylibBase->ml_Lib.lib_Flags = LIBF_SUMUSED | LIBF_CHANGED;
	mylibBase->ml_Lib.lib_Version = myRomTag.rt_Version;
	mylibBase->ml_Lib.lib_Revision = MYREVISION;
	mylibBase->ml_Lib.lib_IdString = (APTR) myid;
}

long
myOpen(void)
{
	struct mylibBase *mylibBase;

	/* mark us as having another customer					*/
	mylibBase->ml_Lib.lib_OpenCnt++;

	/* prevent delayed expunges (standard procedure)		*/
	mylibBase->ml_Lib.lib_Flags &= ~LIBF_DELEXP;

	return ((long) mylibBase);
}

long
myClose(int foo)
{
	struct mylibBase *mylibBase;
	long retval = 0;

	if (--mylibBase->ml_Lib.lib_OpenCnt == 0) {

		if  (mylibBase->ml_Lib.lib_Flags & LIBF_DELEXP) {
			/* no more people have me open,
			 * and I have a delayed expunge pending
			 */
			retval = myExpunge(); /* return segment list	*/
		}
	}

	return (retval);
}

long
myExpunge(void)
{
	struct mylibBase *mylibBase;
	unsigned long seglist = 0;
	long libsize;
	extern struct Library *DOSBase;

	if (mylibBase->ml_Lib.lib_OpenCnt == 0) {
		/* really expunge: remove libbase and freemem	*/

		seglist	= mylibBase->ml_SegList;

		Remove(&mylibBase->ml_Lib.lib_Node);
								/* i'm no longer an installed library	*/

		libsize = mylibBase->ml_Lib.lib_NegSize+mylibBase->ml_Lib.lib_PosSize;
		FreeMem((char *)mylibBase-mylibBase->ml_Lib.lib_NegSize, libsize);
		CloseLibrary(DOSBase);		/* keep the counts even */
	}
	else
		mylibBase->ml_Lib.lib_Flags |= LIBF_DELEXP;

	/* return NULL or real seglist				*/
	return ((long) seglist);
}

