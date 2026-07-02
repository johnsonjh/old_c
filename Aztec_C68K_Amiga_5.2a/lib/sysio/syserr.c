/* Copyright (C) 1987 by Manx Software Systems */

char *sys_errlist[] = {
	"No error",
	"File not found",
	"Bad file handle",
	"Insufficient memory",
	"File exists",
	"Invalid function number",
	"Too many open files",
	"Not a console device",
	"Invalid access code",
	/* math library */
	"Result too large",
	"Argument out of domain"
};

int sys_nerr =  sizeof (sys_errlist) / sizeof (char *);

