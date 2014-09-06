/* printprocstks.c -- PA0 task 4 */

#include <stdio.h>
#include <kernel.h>
#include <proc.h>
#include <lab0.h>

unsigned long *sp;

void
printprocstks(int priority)
{
    int pid = 0;
    struct pentry *ptab;

    kprintf("Task 4 (printprocstks)\n");
    kprintf("# Filter: %d\n", priority);

    for (pid = 0; pid < NPROC; ++pid) {
        ptab = &proctab[pid];
        if (!ptab || (ptab->pprio <= priority)) {
           continue;
        }
        kprintf("Process [%s]\n", ptab->pname);
        kprintf("\tpid: %d\n", pid);
        kprintf("\tpriority: %d\n", ptab->pprio);
        kprintf("\tbase: 0x%08x\n", (int) ptab->pbase);
        kprintf("\tlimit: 0x%08x\n", (int) ptab->plimit);
        kprintf("\tlen: %d\n", ptab->pstklen);
        if (getpid() == pid) {
            /* Current process' entry in proctab wouldn't have the updated sp.
             * Grab it from the register directly.
             */
            asm("movl %esp, sp");
        } else {
            sp = (unsigned long *) ptab->pesp;
        }
        kprintf("\tpointer: 0x%08x\n", sp);
    }
    return;
}
