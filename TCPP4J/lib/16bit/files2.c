/*-----------------------------------------------------------------------*
 * filename - files2.c
 *
 * function(s)
 *    none
 *----------------------------------------------------------------------*/

/*
 *      C/C++ Run Time Library - Version 6.02
 *
 *      Copyright (c) 1987, 1993 by Borland International
 *      All Rights Reserved.
 *
 */


#if defined(__HUGE__)
#pragma -zC_TEXT
#pragma -zR_DATA
#pragma -zTDATA
#endif

#include <io.h>
#include <fcntl.h>
#include <_nfile.h>

unsigned _nfile = _NFILE_;

/*---------------------------------------------------------------------*

Name            _openfd

Usage           unsigned int _openfd[];

Prototype in    not prototyped.

Description     array of access modes for file/devices

*---------------------------------------------------------------------*/
unsigned int    _openfd[_NFILE_] =
{
    O_RDONLY | O_DEVICE | O_TEXT,
    O_WRONLY | O_DEVICE | O_TEXT,
    O_WRONLY | O_DEVICE | O_TEXT,
    O_RDWR   | O_DEVICE | O_BINARY,
    O_WRONLY | O_DEVICE | O_BINARY
};
