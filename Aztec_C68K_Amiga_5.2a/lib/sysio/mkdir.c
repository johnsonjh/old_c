#include <libraries/dos.h>
#include <functions.h>

/*--------------------------------------------------------------*/
/*	mkdir(name): make a directory with the given name.	*/
/*--------------------------------------------------------------*/

int
mkdir(char *name)
{
	register BPTR lock;

	if (*name == 0)
		return(0);
	if ((lock = CreateDir((UBYTE *)name)) == 0)
		return((int)IoErr());
	else 
		UnLock(lock);
	return(0);
}

