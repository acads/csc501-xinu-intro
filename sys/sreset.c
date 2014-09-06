/* sreset.c - sreset */

#include <conf.h>
#include <kernel.h>
#include <proc.h>
#include <q.h>
#include <sem.h>
#include <stdio.h>
#include <lab0.h>

/*------------------------------------------------------------------------
 *  sreset  --  reset the count and queue of a semaphore
 *------------------------------------------------------------------------
 */
SYSCALL sreset(int sem, int count)
{
	STATWORD ps;    
	struct	sentry	*sptr;
	int	pid;
	int	slist;
	unsigned long stime = ctr1000;

	UPDATE_SCALL_FREQ(currpid, SCALL_SRESET);
	disable(ps);
	if (isbadsem(sem) || count<0 || semaph[sem].sstate==SFREE) {
		restore(ps);
		UPDATE_SCALL_TIME(currpid, SCALL_SRESET, stime);
		return(SYSERR);
	}
	sptr = &semaph[sem];
	slist = sptr->sqhead;
	while ((pid=getfirst(slist)) != EMPTY)
		ready(pid,RESCHNO);
	sptr->semcnt = count;
	resched();
	restore(ps);
	UPDATE_SCALL_TIME(currpid, SCALL_SRESET, stime);
	return(OK);
}
