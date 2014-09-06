/* wait.c - wait */

#include <conf.h>
#include <kernel.h>
#include <proc.h>
#include <q.h>
#include <sem.h>
#include <stdio.h>
#include <lab0.h>

/*------------------------------------------------------------------------
 * wait  --  make current process wait on a semaphore
 *------------------------------------------------------------------------
 */
SYSCALL	wait(int sem)
{
	STATWORD ps;    
	struct	sentry	*sptr;
	struct	pentry	*pptr;
	unsigned long stime = ctr1000;

	UPDATE_SCALL_FREQ(currpid, SCALL_WAIT);
	disable(ps);
	if (isbadsem(sem) || (sptr= &semaph[sem])->sstate==SFREE) {
		restore(ps);
		UPDATE_SCALL_TIME(currpid, SCALL_WAIT, stime);
		return(SYSERR);
	}
	
	if (--(sptr->semcnt) < 0) {
		(pptr = &proctab[currpid])->pstate = PRWAIT;
		pptr->psem = sem;
		enqueue(currpid,sptr->sqtail);
		pptr->pwaitret = OK;
		resched();
		restore(ps);
		UPDATE_SCALL_TIME(currpid, SCALL_WAIT, stime);
		return pptr->pwaitret;
	}
	restore(ps);
	UPDATE_SCALL_TIME(currpid, SCALL_WAIT, stime);
	return(OK);
}
