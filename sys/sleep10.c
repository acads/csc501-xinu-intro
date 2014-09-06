/* sleep10.c - sleep10 */

#include <conf.h>
#include <kernel.h>
#include <proc.h>
#include <q.h>
#include <sleep.h>
#include <stdio.h>
#include <lab0.h>

/*------------------------------------------------------------------------
 * sleep10  --  delay the caller for a time specified in tenths of seconds
 *------------------------------------------------------------------------
 */
SYSCALL	sleep10(int n)
{
	STATWORD ps;    
	unsigned long stime = ctr1000;

	UPDATE_SCALL_FREQ(currpid, SCALL_SLEEP10);
	if (n < 0  || clkruns==0) {
		UPDATE_SCALL_TIME(currpid, SCALL_SLEEP10, stime);
		return(SYSERR);
	}
	disable(ps);
	if (n == 0) {		/* sleep10(0) -> end time slice */
	        ;
	} else {
		insertd(currpid,clockq,n*100);
		slnempty = TRUE;
		sltop = &q[q[clockq].qnext].qkey;
		proctab[currpid].pstate = PRSLEEP;
	}
	resched();
        restore(ps);
	UPDATE_SCALL_TIME(currpid, SCALL_SLEEP10, stime);
	return(OK);
}
