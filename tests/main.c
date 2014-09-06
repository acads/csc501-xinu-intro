/* user.c - main */

#include <conf.h>
#include <kernel.h>
#include <proc.h>
#include <stdio.h>
#include <q.h>

/* test1.c
 * This test program creates three processes, prA, prB, and prC, at
 * priority 20.  The main process also has priority 20.
 */

int prch(), prA, prB, prC;
void halt();

/*------------------------------------------------------------------------
 *  main  --  user main program
 *------------------------------------------------------------------------
 */
int main()
{
	kprintf("\n\nHello World, Xinu lives\n\n");
	int i;
	setschedclass(2);
	kprintf("\n\nTEST1:\n");
	resume(prA = create(prch,2000,10,"proc A",1,'A'));kprintf("\n\nA created:\n");
	resume(prB = create(prch,2000,9,"proc B",1,'B'));kprintf("\n\nB created:\n");
	resume(prC = create(prch,2000,10,"proc C",1,'C'));kprintf("\n\nC created:\n");

        chprio(prB,      45);
      chprio(getpid(),  5);
   

	while (1) {
		kprintf("%c", 'D');
		for (i=0; i< 10000; i++);
	}
        return 0;

}
prch(c)
char c;
{
	int i;

	while(1) {
		kprintf("%c", c);
		for (i=0; i< 10000; i++);
	}
}
