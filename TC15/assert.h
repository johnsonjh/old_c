/*	assert.h

	assert macro

	Copyright (c) Borland International 1987
	All Rights Reserved.
*/

#if	!defined(NDEBUG)
#define assert(p)	if(!(p)){fprintf(stderr,\
		"Assertion failed: %s, file %s, line %d\n",\
		#p, __FILE__, __LINE__);abort();}
#else
#define assert(p)
#endif
