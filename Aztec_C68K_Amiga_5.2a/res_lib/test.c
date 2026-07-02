#include "mylib.h"
#include <functions.h>
#include <stdio.h>

int 
main(int argc, char **argv)
{
	long v;
	struct mylibBase *mylibBase;

	if ((mylibBase = (struct mylibBase *)
						OpenLibrary((UBYTE *)"mylib.library", 0L)) == 0) {
		printf("Couldn't open library!\n");
		return(1);
	}
	Func1(12345L);
	v = Func2(54321L);
	printf("sum=%ld\n", v);
	CloseLibrary((struct Library *)mylibBase);
	return(0);
}

