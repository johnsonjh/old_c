#include <sgtty.h>
#include <time.h>
clock_t last, t;
long delta;
struct sgttyb tty;
int c;

main()
{

	ioctl(1, TIOCGETP, &tty);
	tty.sg_flags |= RAW;
	ioctl(1, TIOCSETP, &tty);
	last = clock();
	for (;;){
		t = clock();
		delta = t-last;
		last = t;
		printf("%ld ", delta);
		c = getchar();
		if (c=='q')
			break;
	}
	tty.sg_flags &= ~RAW;
	ioctl(1, TIOCSETP, &tty);
}
