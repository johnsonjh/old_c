/* fmalloc.c */

#include <exec/memory.h>
#include <libraries/arpbase.h>
#include <functions.h>
#include <stdlib.h>

/* !!! could add a magic # to this to make free() more robust */
struct mem {
    struct DefaultTracker *tracker;
};


/*doc fmalloc
NAME
    fmalloc -- arp'd fmalloc()

SYNOPSIS
    void *fmalloc (size_t size, ULONG flags)

FUNCTION
    Allocates memory using Amiga memory flags (defined in
    <exec/memory.h>).  Memory allocated this way can later be freed by
    calling free().  These allocations use Arp resource tracking an
    therefore will be freed by ArpExit().

INPUTS
    size - number of bytes to allocate
    flags - memory (MEMF_) flags

RESULTS
    pointer to memory block or NULL on failure

SEE ALSO
    malloc(), free(), fmalloc()

MODULE
    fmalloc.c
*end */

void *fmalloc (size_t size, ULONG flags)
{
    register struct mem *mp;

    if (!(mp = ArpAllocMem(size+sizeof(struct mem), flags))) return NULL;

    mp->tracker = LastTracker;

    return (void *)((ULONG)mp + sizeof(struct mem));
}

void *calloc (size_t nelem, size_t size)
{
    return fmalloc (nelem * size, MEMF_CLEAR);
}

void *malloc (size_t size)
{
    return fmalloc (size, 0L);
}


#if 0
void *lcalloc (nelem,size)
unsigned long nelem, size;
{
    return fmalloc (nelem * size, MEMF_CLEAR);
}

void *lmalloc(size_t size)
{
    return fmalloc (size,0L);
}
#endif


void free (void *blk)
{
    struct mem *mp = (void *)((ULONG)blk - sizeof(struct mem));

    FreeTrackedItem (mp->tracker);
}
