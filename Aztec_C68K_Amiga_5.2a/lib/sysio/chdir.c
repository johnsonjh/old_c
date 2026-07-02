#include <libraries/dos.h>
#include <functions.h>

/*------------------------------------------------------------------*/
/*	chdir(path): make path the current directory. Return Ok/Not */
/*------------------------------------------------------------------*/

int
chdir(char *path)
{
	register BPTR lock;
	register BPTR oldLock;

	if (*path == 0)
		return(0);
	if ((lock = Lock((UBYTE *)path, (long)ACCESS_READ)) == 0)
		return((int)IoErr());
	if (oldLock = CurrentDir(lock))
		UnLock(oldLock);
	return(0);
}

