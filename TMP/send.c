/* send.c - send */

#include <conf.h>
#include <kernel.h>
#include <proc.h>
#include <stdio.h>
#include <lab0.h>

/*------------------------------------------------------------------------
 *  send  --  send a message to another process
 *------------------------------------------------------------------------
 */
SYSCALL	send(int pid, WORD msg)
{
	STATWORD ps;    
	struct	pentry	*pptr;
	unsigned long stime = ctr1000;

	UPDATE_SCALL_FREQ(currpid, SCALL_SEND);
	disable(ps);
	if (isbadpid(pid) || ( (pptr= &proctab[pid])->pstate == PRFREE)
	   || pptr->phasmsg != 0) {
		restore(ps);
		UPDATE_SCALL_TIME(currpid, SCALL_SEND, stime);
		return(SYSERR);
	}
	pptr->pmsg = msg;
	pptr->phasmsg = TRUE;
	if (pptr->pstate == PRRECV) 	/* if receiver waits, start it	*/
		ready(pid, RESCHYES);
	else if (pptr->pstate == PRTRECV) {
		unsleep(pid);
		ready(pid, RESCHYES);
	}
	restore(ps);
	UPDATE_SCALL_TIME(currpid, SCALL_SEND, stime);
	return(OK);
}
