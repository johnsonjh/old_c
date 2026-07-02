#include <fcntl.h>
main()
{
	int i;
	i = lseek(0, 1024L, 0);
	printf("i=%d\n", i);
}
