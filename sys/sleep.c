/* sleep.c - sleep */

#include <conf.h>
#include <kernel.h>
#include <proc.h>
#include <q.h>
#include <sleep.h>
#include <stdio.h>
#include <lab0.h>

/*------------------------------------------------------------------------
 * sleep  --  delay the calling process n seconds
 *------------------------------------------------------------------------
 */
SYSCALL	sleep(int n)
{
	STATWORD ps;    
	unsigned long stime = ctr1000;

	UPDATE_SCALL_FREQ(currpid, SCALL_SLEEP);

	if (n<0 || clkruns==0) {
		UPDATE_SCALL_TIME(currpid, SCALL_SLEEP, stime);
		return(SYSERR);
	}
	if (n == 0) {
	        disable(ps);
		resched();
		restore(ps);
	        UPDATE_SCALL_TIME(currpid, SCALL_SLEEP, stime);
		return(OK);
	}
	while (n >= 1000) {
		sleep10(10000);
		n -= 1000;
	}
	if (n > 0) {
		sleep10(10*n);
        }
	UPDATE_SCALL_TIME(currpid, SCALL_SLEEP, stime);
	return(OK);
}
