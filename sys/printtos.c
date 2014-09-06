/* printtos.c -- PA0 task 3 */

#include <stdio.h>
#include <lab0.h>

unsigned long *tsp;
unsigned long *tbp;

void
printtos(void)
{
    asm("movl %esp, tsp");
    asm("movl %ebp, tbp");

    int a = 0xaaaa;
    int b = 0xbbbb;
    int c = 0xcccc;
    int d = 0xdddd;
    int e = 0;

    kprintf("Task 3 (printtos)\n");

    kprintf("Before[0x%08x]: 0x%08x\n", (tbp + 2), *(tbp + 2));
    kprintf("After[0x%08x]: 0x%08x\n", tbp, *tbp);
    
    e = a + b + c + d + e;
    asm("movl %esp, tsp");

    kprintf("\telement[0x%08x]: 0x%08x\n", (tsp + 3), *(tsp + 3));
    kprintf("\telement[0x%08x]: 0x%08x\n", (tsp + 2), *(tsp + 2));
    kprintf("\telement[0x%08x]: 0x%08x\n", (tsp + 1), *(tsp + 1));
    kprintf("\telement[0x%08x]: 0x%08x\n", (tsp), *(tbp));

    kprintf("\n");
    return;
}
