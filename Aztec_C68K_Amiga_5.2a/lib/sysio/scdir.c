/* Copyright 1986,1987,1988 by Manx Software Systems, Inc.	*/

#include <exec/exec.h>
#include <libraries/dosextens.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <functions.h>
#include <fcntl.h>

static struct FileInfoBlock *getdir(char *path);
static struct FileInfoBlock *getnxt(void);
static int jive(char *nam, char *pat);

char *
scdir(char *pat)
{
	register struct FileInfoBlock *fp;
	register char *cp;
	static int time = 0;
	static char name[80];
	static char path[40];
	static char patn[40];

	if (pat==0){
		time = 0;
		return 0;
	}
	for (;;) {
		Chk_Abort();
		if (time == 0) {
			if (strchr(pat, '*') == 0 && strchr(pat, '?') == 0) {
				time = 2;
				return(pat);
			}
			time = 1;
			strcpy(name, pat);
			if (cp=strrchr(name, '/')) {
				if ((cp > name && *(cp-1) == '/') || cp == name)
					goto colon;
				*cp = 0;
				fp = getdir(name);
				*cp++ = '/';
				strcpy(patn, cp);
				*cp = 0;
				strcpy(path, name);
			}
			else if (cp=strrchr(name, ':')) {
colon:
				strcpy(patn, ++cp);
				*cp = 0;
				strcpy(path, name);
				fp = getdir(path);
			}
			else {
				strcpy(patn, name);
				*path = 0;
				fp = getdir(path);
			}
		}
		else if (time == 2) {
			time = 0;
			return(0);
		}
		else
			fp = getnxt();
		if (fp == 0) {
			time = 0;
			return(0);
		}
		if (jive(fp->fib_FileName, patn) == 0) {
			strcpy(name, path);
			strcat(name, fp->fib_FileName);
			break;
		}
	}
	return(name);
}

static struct fibsav {
	struct fibsav *next;
	struct FileInfoBlock fib;
} *chain, *ptr;

static struct FileInfoBlock *
getdir(char *path)
{
	register struct fibsav *fsp;
	register struct FileInfoBlock *fibp, *ret = 0;
	register BPTR lock;

	while (fsp=chain) {
		fsp = chain;
		chain = chain->next;
		free(fsp);
	}
	if ((fibp = malloc(sizeof(struct FileInfoBlock))) == 0)
		return(0);
	if (lock = Lock((UBYTE *)path, (long)ACCESS_READ)) {
		Examine(lock, fibp);
		if (fibp->fib_DirEntryType > 0) {
			while (ExNext(lock, fibp)) {
				if (fibp->fib_DirEntryType > 0)
					continue;
				if ((fsp = malloc(sizeof(struct fibsav))) == 0)
					break;
				fsp->fib = *fibp;
				fsp->next = chain;
				chain = fsp;
			}
			ptr = chain;
			ret = getnxt();
		}
		UnLock(lock);
	}
	free(fibp);
	return(ret);
}

static struct FileInfoBlock *
getnxt(void)
{
	register struct FileInfoBlock *fibp;

	if (ptr) {
		fibp = &ptr->fib;
		ptr = ptr->next;
		return(fibp);
	}
	while (ptr=chain) {
		chain = chain->next;
		free(ptr);
	}
	return(0);
}

static int
jive(char *nam, char *pat)
{
	register char *p;

	for (;;) {
		if (tolower((int)*nam) == tolower((int)*pat)) {
			if(*nam++ == '\0')
				return(0);
			pat++;
		}
		else if (*pat == '?' && *nam != 0) {
			nam++;
			pat++;
		}
		else
			break;
	}
	if (*pat != '*')
		return(1);
	while (*pat == '*') {
		if (*++pat == '\0')
			return(0);
	}
	
	for (p=nam+strlen(nam)-1;p>=nam;p--) {
		if (*p == *pat)
			if (jive(p,pat) == 0)
				return(0);
	}
	return(1);
}

