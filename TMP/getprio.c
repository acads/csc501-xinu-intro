/* getprio.c - getprio */

#include <conf.h>
#include <kernel.h>
#include <proc.h>
#include <stdio.h>
#include <lab0.h>

/*------------------------------------------------------------------------
 * getprio -- return the scheduling priority of a given process
 *------------------------------------------------------------------------
 */
SYSCALL getprio(int pid)
{
	STATWORD ps;    
	struct	pentry	*pptr;
        unsigned long stime = ctr1000;

        UPDATE_SCALL_FREQ(currpid, SCALL_GETPRIO);
	disable(ps);
	if (isbadpid(pid) || (pptr = &proctab[pid])->pstate == PRFREE) {
		restore(ps);
                UPDATE_SCALL_TIME(currpid, SCALL_GETPRIO, stime);
		return(SYSERR);
	}
	restore(ps);
        UPDATE_SCALL_TIME(currpid, SCALL_GETPRIO, stime);
	return(pptr->pprio);
}
