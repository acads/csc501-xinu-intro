/* chprio.c - chprio */

#include <conf.h>
#include <kernel.h>
#include <proc.h>
#include <q.h>
#include <stdio.h>
#include <lab0.h>

/*------------------------------------------------------------------------
 * chprio  --  change the scheduling priority of a process
 *------------------------------------------------------------------------
 */
SYSCALL chprio(int pid, int newprio)
{
	STATWORD ps;    
	struct	pentry	*pptr;
	unsigned long stime = ctr1000;

	UPDATE_SCALL_FREQ(currpid, SCALL_CHPRIO);
	disable(ps);
	if (isbadpid(pid) || newprio<=0 ||
	    (pptr = &proctab[pid])->pstate == PRFREE) {
		restore(ps);
		UPDATE_SCALL_TIME(currpid, SCALL_CHPRIO, stime);
		return(SYSERR);
	}
	pptr->pprio = newprio;
	restore(ps);
	UPDATE_SCALL_TIME(currpid, SCALL_CHPRIO, stime);
	return(newprio);
}
