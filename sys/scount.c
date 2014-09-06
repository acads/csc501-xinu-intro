/* scount.c - scount */

#include <conf.h>
#include <kernel.h>
#include <sem.h>
#include <lab0.h>
#include <proc.h>

/*------------------------------------------------------------------------
 *  scount  --  return a semaphore count
 *------------------------------------------------------------------------
 */
SYSCALL scount(int sem)
{
	extern	struct	sentry	semaph[];
	unsigned long stime = ctr1000;

	UPDATE_SCALL_FREQ(currpid, SCALL_SCOUNT);
	if (isbadsem(sem) || semaph[sem].sstate==SFREE) {
		UPDATE_SCALL_TIME(currpid, SCALL_SCOUNT, stime);
		return(SYSERR);
	}
	UPDATE_SCALL_TIME(currpid, SCALL_SCOUNT, stime);
	return(semaph[sem].semcnt);
}
