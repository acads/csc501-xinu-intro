/* gettime.c - gettime */

#include <conf.h>
#include <kernel.h>
#include <date.h>
#include <lab0.h>
#include <proc.h>

extern int getutim(unsigned long *);

/*------------------------------------------------------------------------
 *  gettime  -  get local time in seconds past Jan 1, 1970
 *------------------------------------------------------------------------
 */
SYSCALL	gettime(long *timvar)
{
	unsigned long stime = ctr1000;

	UPDATE_SCALL_FREQ(currpid, SCALL_GETTIME);

	/* long	now; */
	/* FIXME -- no getutim */

	UPDATE_SCALL_TIME(currpid, SCALL_GETTIME, stime);
	return OK;
}
