/* setnok.c - setnok */

#include <conf.h>
#include <kernel.h>
#include <proc.h>
#include <stdio.h>
#include <lab0.h>

/*------------------------------------------------------------------------
 *  setnok  -  set next-of-kin (notified at death) for a given process
 *------------------------------------------------------------------------
 */
SYSCALL	setnok(int nok, int pid)
{
	STATWORD ps;    
	struct	pentry	*pptr;
	unsigned long stime = ctr1000;

	UPDATE_SCALL_FREQ(currpid, SCALL_SETNOK);
	disable(ps);
	if (isbadpid(pid)) {
		restore(ps);
		UPDATE_SCALL_TIME(currpid, SCALL_SETNOK, stime);
		return(SYSERR);
	}
	pptr = &proctab[pid];
	pptr->pnxtkin = nok;
	restore(ps);
	UPDATE_SCALL_TIME(currpid, SCALL_SETNOK, stime);
	return(OK);
}
