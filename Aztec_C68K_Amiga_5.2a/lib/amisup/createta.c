/* Copyright (C) 1986 by Manx Software Systems, Inc. */
#include <exec/memory.h>
#include <exec/tasks.h>
#include <functions.h>

struct   TaskMemList {
    struct  Node ml_Node;
    UWORD   ml_NumEntries;
    struct  MemEntry ml_ME[2];
};

struct TaskMemList TaskMemTemplate = { 0, 0, 0, 0, 0, 2,
		MEMF_PUBLIC|MEMF_CLEAR, sizeof(struct Task), MEMF_CLEAR, 0 };

struct Task *
CreateTask(UBYTE *name, long pri, void *start_pc, unsigned long stksiz)
{
	struct TaskMemList ml;
	register struct Task *tp;
	register struct TaskMemList *mlp;

	stksiz = (stksiz+3)&~3;
	ml = TaskMemTemplate;
	ml.ml_ME[1].me_Length = stksiz;
	if ((mlp = (struct TaskMemList *)AllocEntry((struct MemList *)&ml)) == 0)
		return(0);
	tp = (struct Task *)mlp->ml_ME[0].me_Addr;
	tp->tc_SPLower = mlp->ml_ME[1].me_Addr;
	tp->tc_SPReg =
	tp->tc_SPUpper = (APTR)((char *)tp->tc_SPLower + stksiz);
	tp->tc_Node.ln_Type = NT_TASK;
	tp->tc_Node.ln_Pri = pri;
	tp->tc_Node.ln_Name = (char *)name;
	NewList(&tp->tc_MemEntry);
	AddHead(&tp->tc_MemEntry, (struct Node *)mlp);
	AddTask(tp, start_pc, (void *)0);
	return(tp);
}

void
DeleteTask(struct Task *tp)
{
	RemTask(tp);
}

