/* Copyright (C) 1986,1987 by Manx Software Systems, Inc. */

#include <stdio.h>
#include <string.h>
#include <fcntl.h>

int
setenv(char *name, char *arg)
{
	char *cp;
	char buf[128];
	int fd;

	strcpy(buf, "ENV:");
	strcat(buf, name);
	if (cp=strrchr(buf, '/')) {
		*cp = 0;
		mkdir(buf);
		*cp = '/';
	}
	if (*arg == 0)
		remove(buf);
	else {
		if ((fd = creat(buf, 0666)) < 0)
			return (-1);
		write(fd, arg, strlen(arg));
		close(fd);
	}
	return (0);
}

