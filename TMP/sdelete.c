/* sdelete.c - sdelete */

#include <conf.h>
#include <kernel.h>
#include <proc.h>
#include <q.h>
#include <sem.h>
#include <stdio.h>
#include <lab0.h>

/*------------------------------------------------------------------------
 * sdelete  --  delete a semaphore by releasing its table entry
 *------------------------------------------------------------------------
 */
SYSCALL sdelete(int sem)
{
	STATWORD ps;    
	int	pid;
	struct	sentry	*sptr;
	unsigned long stime = ctr1000;

	UPDATE_SCALL_FREQ(currpid, SCALL_SDELETE);
	disable(ps);
	if (isbadsem(sem) || semaph[sem].sstate==SFREE) {
		restore(ps);
		UPDATE_SCALL_TIME(currpid, SCALL_SDELETE, stime);
		return(SYSERR);
	}
	sptr = &semaph[sem];
	sptr->sstate = SFREE;
	if (nonempty(sptr->sqhead)) {
		while( (pid=getfirst(sptr->sqhead)) != EMPTY)
		  {
		    proctab[pid].pwaitret = DELETED;
		    ready(pid,RESCHNO);
		  }
		resched();
	}
	restore(ps);
	UPDATE_SCALL_TIME(currpid, SCALL_SDELETE, stime);
	return(OK);
}
