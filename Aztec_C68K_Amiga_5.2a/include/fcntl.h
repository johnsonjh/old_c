/* Copyright Manx Software Systems, Inc. 1988.  All rights reserved */

#ifndef __FCNTL_H 
#define __FCNTL_H 

#ifndef _SIZE_T
#define _SIZE_T
typedef unsigned long size_t;
#endif

#include <libraries/dos.h>

#define O_RDONLY	0
#define O_WRONLY	1
#define O_RDWR		2
#define O_CREAT		0x0100
#define O_TRUNC		0x0200
#define O_EXCL		0x0400
#define O_APPEND	0x0800
#define	O_TEXT		0x1000

#define	O_CONRAW	0x4000
#define	O_STDIO		0x8000

extern struct _dev {
	BPTR fd;
	short	mode;
} *_devtab;

extern short _numdev;

int creat(const char *_name, int _mode);
int _creat(const char *_name, int _mode);
int open(const char * _name, int _mode, ...);
int _open(const char * _name, int _mode, ...);
int access(char *, int);
int _access(char *, int);
int close(int);
int _close(int);

size_t read(int, void *, size_t);
size_t _read(int, void *, size_t);
int _rename(const char *, const char *);
size_t write(int, void *, size_t);
size_t _write(int, void *, size_t);
long lseek(int, long, int);
long _lseek(int, long, int);
struct sgttyb;
int ioctl(int, int, struct sgttyb *);
int _ioctl(int, int, struct sgttyb *);
struct MsgPort;
long dos_packet(struct MsgPort *, long, ...);
int isatty(int);
int _isatty(int);
int setenv(char *, char *);

int unlink(const char *);
int _unlink(const char *);
void _exit(int _code);

void set_con(void);
void set_raw(void);

int chdir(char *_path);
char *getcwd(char *_path, int _size);
int mkdir(char *_name);

char *mktemp(char *template);
char *scdir(char *_pat);
void _abort(void);

void pokeb(unsigned long, int);
int peekb(unsigned long);
void pokew(unsigned long, int);
int peekw(unsigned long);
void pokel(unsigned long, long);
long peekl(unsigned long);

int wait(void);
int fexecl(char *, char *, ...);
int fexecv(char *, char **);

int execl(char *, char *, ...);
int execv(char *, char **);
int execlp(char *, char *, ...);
int execvp(char *, char **);

short segload(void *);
void freeseg(void *);

void geta4 (void);

int kputchar(int);
int KPutChar(int);
int kputc(int);
int kputch(int);
int KPutCh(int);
void kputstr(char *);
void KPutStr(char *);
void kputs(char *);
void KPutS(char *);
int kgetchar(void);
int KGetChar(void);
int kgetc(void);
int KGetCh(void);
int kgetch(void);
int KMayGetChar(void);
int KMayGetCh(void);
void KPutFmt(char *, char *);
void kprintf(char *, ...);
void KPrintF(char *, ...);
KDoFmt(char *, char *, void *, char *);

int cmpstrexec(char *, char *);
int KCmpStr(char *, char *);

int KGetNum(void);
int kgetnum(void);

long Chk_Abort(void);
extern int Enable_Abort;

#endif

