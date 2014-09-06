/* signal.c - signal */

#include <conf.h>
#include <kernel.h>
#include <proc.h>
#include <q.h>
#include <sem.h>
#include <stdio.h>
#include <lab0.h>

/*------------------------------------------------------------------------
 * signal  --  signal a semaphore, releasing one waiting process
 *------------------------------------------------------------------------
 */
SYSCALL signal(int sem)
{
	STATWORD ps;    
	register struct	sentry	*sptr;
	unsigned long stime = ctr1000;

	UPDATE_SCALL_FREQ(currpid, SCALL_SIGNAL);
	disable(ps);
	if (isbadsem(sem) || (sptr= &semaph[sem])->sstate==SFREE) {
		restore(ps);
		UPDATE_SCALL_TIME(currpid, SCALL_SIGNAL, stime);
		return(SYSERR);
	}
	if ((sptr->semcnt++) < 0) 
		ready(getfirst(sptr->sqhead), RESCHYES);
	restore(ps);
	UPDATE_SCALL_TIME(currpid, SCALL_SIGNAL, stime);
	return(OK);
}
