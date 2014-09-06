/* sleep1000.c - sleep1000 */

#include <conf.h>
#include <kernel.h>
#include <proc.h>
#include <q.h>
#include <sleep.h>
#include <stdio.h>
#include <lab0.h>

/*------------------------------------------------------------------------
 * sleep1000 --  delay the caller for a time specified in 1/100 of seconds
 *------------------------------------------------------------------------
 */
SYSCALL sleep1000(int n)
{
	STATWORD ps;    
	unsigned long stime = ctr1000;

	UPDATE_SCALL_FREQ(currpid, SCALL_SLEEP1000);
	if (n < 0  || clkruns==0) {
		UPDATE_SCALL_TIME(currpid, SCALL_SLEEP1000, stime);
	        return(SYSERR);
	}
	disable(ps);
	if (n == 0) {		/* sleep1000(0) -> end time slice */
	        ;
	} else {
		insertd(currpid,clockq,n);
		slnempty = TRUE;
		sltop = &q[q[clockq].qnext].qkey;
		proctab[currpid].pstate = PRSLEEP;
	}
	resched();
        restore(ps);
	UPDATE_SCALL_TIME(currpid, SCALL_SLEEP1000, stime);
	return(OK);
}
