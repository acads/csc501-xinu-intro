/* printsyscallsummary.c -- PA0 task 5 */

#include <stdio.h>
#include <kernel.h>
#include <proc.h>
#include <lab0.h>

int g_scall_trace = FALSE;    /* to trace or not to trace syscalls */

/* Table to hold the syscall names, indexed by SCALLS enum. */
char *g_scall_names[NUM_SCALLS] = {
    "sys_chprio",
    "sys_freemem",
    "sys_getpid",
    "sys_getprio",
    "sys_gettime",
    "sys_kill",
    "sys_receive",
    "sys_recvclr",
    "sys_recvtim",
    "sys_resume",
    "sys_scount",
    "sys_screate",
    "sys_sdelete",
    "sys_send",
    "sys_setdev",
    "sys_setnok",
    "sys_signal",
    "sys_signaln",
    "sys_sleep",
    "sys_sleep10",
    "sys_sleep100",
    "sys_sleep1000",
    "sys_sreset",
    "sys_stacktrace",
    "sys_suspend",
    "sys_unsleep",
    "sys_wait"
};

void
syscallsummary_start()
{
    g_scall_trace = TRUE;
}

void
syscallsummary_stop()
{
    int pid = 0;
    
    g_scall_trace = FALSE;
    for (pid = 0; pid < NPROC; ++pid) {
        bzero(proctab[pid].freq, (NUM_SCALLS * sizeof(int)));
        bzero(proctab[pid].ttime, (NUM_SCALLS * sizeof(unsigned long)));
    }
}

void
printsyscallsummary()
{
    int pid = 0;
    int flag = FALSE;
    int scall = 0;
    struct pentry *ptab;

    kprintf("Task 5 (printsyssummary)\n");

    for (pid = 0; pid < NPROC; ++pid) {
        ptab = &proctab[pid];
        for (scall = 0; scall < NUM_SCALLS; ++scall) {
           if (0 == ptab->freq[scall]) {
               continue;
           }
           if (FALSE == flag) {
               kprintf("Process [pid: %d]\n", pid);
               flag = TRUE;
           }
           kprintf("\tSyscall: %s, ", g_scall_names[scall]);
           kprintf("count: %d, ", ptab->freq[scall]);
           kprintf("average execution time: %u (ms)\n",
                    (ptab->ttime[scall]/ptab->freq[scall]));
        }
        flag = FALSE; 
    }

    kprintf("\n");
    return;
}

