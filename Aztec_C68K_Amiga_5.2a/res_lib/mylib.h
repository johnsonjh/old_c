#include <exec/libraries.h>

void Func1(long value);
long Func2(long value);

#pragma amicall(mylibBase, 0x1e, Func1(d0))
#pragma amicall(mylibBase, 0x24, Func2(d0))

struct mylibBase {
	struct Library			ml_Lib;
	unsigned long			ml_SegList;	/* seg list of mylib itself*/
	long					ml_value;
};


