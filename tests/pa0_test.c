/* user.c - main */

#include <conf.h>
#include <kernel.h>
#include <proc.h>
#include <stdio.h>
#include <lab0.h>

int prX;
void halt();

/*------------------------------------------------------------------------
 *  main  --  user main program
 *------------------------------------------------------------------------
 */
prch(c)
char c;
{
	int i;
	sleep(5);	
}
int main()
{
    kprintf("Task 5 (printsyscallsummary)\n");
	syssummary_start();        
	resume(prX = create(prch,2000,20,"proc X",1,'A'));
	sleep(10);
	syssummary_stop();
	printsyssummary();
	return 0;
}
