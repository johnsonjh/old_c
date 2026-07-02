#include <libraries/dos.h>
#include <libraries/dosextens.h>
#include <exec/memory.h>
#include <stdlib.h>
#include <string.h>
#include <functions.h>

/*--------------------------------------------------------------
 *	getcwd: return the path name of the current directory	
 *--------------------------------------------------------------
 */

char *
getcwd(char *path, int size)
{
	char s1[ 108 ];
	char *name;
	register BPTR locka, lockb;
	register struct FileInfoBlock *fib;

	if (path == 0)
		if ((path = malloc((size_t)108)) == 0)
			return(0);

	fib = malloc(sizeof(struct FileInfoBlock));
	if (fib == 0)
		return(0);
	
	locka = Lock((UBYTE *)"", (long)ACCESS_READ);
	*path = s1[0] = 0;

	while (locka) {
		Examine(locka, fib);
		name = fib->fib_FileName;
		if (*name == 0)
			strcpy(path, "RAM"); /* Patch for Ram disk bug */
		else
			strcpy(path, name);
		lockb = ParentDir(locka);
		UnLock(locka);

		if (lockb == 0)
			strcat(path, ":");
		else if (s1[0] != 0)
			strcat( path, "/");
		strcat( path, s1 );
		strcpy( s1, path );
		locka = lockb;
	}

	free(fib);
	return(path);
}

