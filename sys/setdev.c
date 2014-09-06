/* setdev.c - setdev */

#include <conf.h>
#include <kernel.h>
#include <proc.h>
#include <lab0.h>

/*------------------------------------------------------------------------
 *  setdev  -  set the two device entries in the process table entry
 *------------------------------------------------------------------------
 */
SYSCALL	setdev(int pid, int dev1, int dev2)
{
	short	*nxtdev;
	unsigned long stime = ctr1000;

	UPDATE_SCALL_FREQ(currpid, SCALL_SETDEV);
	if (isbadpid(pid)) {
		UPDATE_SCALL_TIME(currpid, SCALL_SETDEV, stime);
		return(SYSERR);
	}
	nxtdev = (short *) proctab[pid].pdevs;
	*nxtdev++ = dev1;
	*nxtdev = dev2;
	UPDATE_SCALL_TIME(currpid, SCALL_SETDEV, stime);
	return(OK);
}
