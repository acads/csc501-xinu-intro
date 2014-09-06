/* getpid.c - getpid */

#include <conf.h>
#include <kernel.h>
#include <proc.h>
#include <lab0.h>

/*------------------------------------------------------------------------
 * getpid  --  get the process id of currently executing process
 *------------------------------------------------------------------------
 */
SYSCALL getpid()
{
	unsigned long stime = ctr1000;

	UPDATE_SCALL_FREQ(currpid, SCALL_GETPID);
	UPDATE_SCALL_TIME(currpid, SCALL_GETPID, stime);
	return(currpid);
}
