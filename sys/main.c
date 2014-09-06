/* user.c - main */

#include <conf.h>
#include <kernel.h>
#include <proc.h>
#include <stdio.h>
#include <lab0.h>

void halt();

void create_task4_test_procs(void);
void proc10(int);
void proc20(int);
void proc30(int);
void proc40(int);
void proc50(int);

void create_task5_test_procs(void);
void proc_t5_A(int data);
void proc_t5_B(int data);
void proc_t5_C(int data);
void proc_t5_D(int data);
void proc_t5_E(int data);
void proc_t5_H(int data);
int t5_A;
int t5_B;
int t5_C;
int t5_D;
int t5_E;
int t5_H;
int pid_main;

/*------------------------------------------------------------------------
 *  main  --  user main program
 *------------------------------------------------------------------------
 */
int main()
{
    int msg = 0;
    long param = 0;

    kprintf("\n\nHello World, Xinu lives\n\n");

    pid_main = getpid();
    syscallsummary_start();

    /* PA0 task 1 */
    kprintf("Task 1 (zfunction)\n");
    kprintf("Input: 0x%08x\n", 0xffffffff);
    param = zfunction(0xffffffff);
    kprintf("Output: 0x%08x\n\n", param);

    kprintf("Input: 0x%08x\n", 0xaabbccdd);
    param = zfunction(0xaabbccdd);
    kprintf("Output: 0x%08x\n\n", param);

    kprintf("Input: 0x%08x\n", 0xaaffffdd);
    param = zfunction(0xaaffffdd);
    kprintf("Output: 0x%08x\n\n", param);

    kprintf("Input: 0x%08x\n", 0xa802aaa0);
    param = zfunction(0xa802aaa0);
    kprintf("Output: 0x%08x\n\n", param);

    kprintf("Input: 0x%08x\n", 0xaaaaaaaa);
    param = zfunction(0xaaaaaaaa);
    kprintf("Output: 0x%08x\n\n", param);

    /* PA0 task 2 */
    printsegaddress();

    /* PA0 task 3 */
    printtos();

    /* PA0 task 4 */
    create_task4_test_procs();
    printprocstks(21);

    /* PA0 task 5 */
    sleep(20);
    create_task5_test_procs();
    while (1) {
        msg = (int) receive();
        if (msg == t5_A) {
            kprintf("main: procA is dead\n");
            t5_A = -1;
        } else if (msg == t5_B) {
            kprintf("main: procB is dead\n");
            t5_B = -1;
        } else if (msg == t5_C) {
            kprintf("main: procC is dead\n");
            t5_C = -1;
        } else if (msg == t5_D) {
            kprintf("main: procD is dead\n");
            t5_D = -1;
        } else if (msg == t5_E) {
            kprintf("main: procE is dead\n");
            t5_E = -1;
        } else if (msg == t5_H) {
            kprintf("main: procH is dead\n");
            t5_H = -1;
        }

        resume(t5_E);
        if ((-1 == t5_A) && (-1 == t5_B) && (-1 == t5_C) && (-1 == t5_D) &&
            (-1 == t5_E) && (-1 == t5_H)) {
            kprintf("main: all dead\n");
            break;
        }
    }
    printsyscallsummary();
    syscallsummary_stop();

    return 0;
}

void
proc10(int delay)
{
    sleep(delay);
    sleep100(delay);
}

void
proc20(int delay)
{
    sleep(delay);
    sleep1000(delay);
}

void
proc30(int delay)
{
    sleep10(delay);
    sleep1000(delay);
}

void
proc40(int delay)
{
    sleep100(delay);
    sleep1000(delay);
}

void
proc50(int delay)
{
    sleep100(delay);
    sleep1000(delay);
}

void
create_task4_test_procs(void)
{
    resume(create((int *) &proc10, 256, 10, "proc10", 1, 10));
    resume(create((int *) &proc20, 256, 20, "proc20", 1, 20));
    resume(create((int *) &proc30, 256, 30, "proc30", 1, 30));
    resume(create((int *) &proc40, 256, 40, "proc40", 1, 40));
    resume(create((int *) &proc50, 256, 50, "proc50", 1, 50));
}

void
proc_t5_A(int data)
{
    int mypid;
    int myprio;
    void *ptr;

    mypid = getpid();
    myprio = getprio(mypid);

    /* Change the priority to data + 5 */
    if (SYSERR == (myprio = chprio(mypid, myprio + 1))) {
    } else {
        kprintf("procA: new priority: %d\n", myprio);
    }

    ptr = getmem(data);
    freemem((struct mblock *) ptr, data);

    setnok(pid_main, mypid);
    sleep(10);
    kprintf("procA: B just woke me up!\n");
    send(t5_B, mypid);
    kill(mypid);
}

void
proc_t5_B(int data)
{
    int mypid = 0;
    int msg = 0;

    mypid = getpid();
    unsleep(t5_A);
    sleep(3);
    msg = receive();
    kprintf("procB: msg from procA: %d\n", msg);
    sleep100(12);
    setnok(pid_main, mypid);
    kill(mypid);
}

void
proc_t5_C(int data)
{
    int mypid = 0;

    mypid = getpid();
    stacktrace(mypid);
    suspend(mypid);
    sleep1000(10);
    kprintf("procC: I just woke up!\n");
    setnok(pid_main, mypid);
    kill(mypid);
}

void
dummyd(int data)
{
    send(t5_D, data);
}

void
proc_t5_D(int data)
{
    int mypid = 0;
    int msg = 0;

    mypid = getpid();
    resume(t5_C);
    resume(create((int *) &dummyd, 256, data, "dd", 1, data));
    sleep10(30);
    msg = recvclr();
    kprintf("procD: dummyd sent: %d\n", msg);
    setnok(pid_main, mypid);
    kill(mypid);
}

void
proc_t5_E(int data)
{
    int mypid = 0;

    mypid = getpid();
    suspend(getpid());
    setnok(pid_main, mypid);
    kill(mypid);
}

void
proc_t5_H(int data)
{
    int sem = 0;
    int mypid = 0;
    int i = 0;

    for (i = 0; i < 5; ++i) {
        sem = screate(1);
        sreset(sem, i + 1);
        kprintf("proc_H: sem count %d\n", scount(sem));
        sdelete(sem);
    }

    mypid = getpid();
    setnok(pid_main, mypid);
    kill(mypid);
}

void
create_task5_test_procs(void)
{
    resume((t5_A = create((int *) &proc_t5_A, 256, 10, "proc_t5_A", 1, 10)));
    resume((t5_B = create((int *) &proc_t5_B, 256, 20, "proc_t5_B", 1, 20)));
    resume((t5_C = create((int *) &proc_t5_C, 256, 30, "proc_t5_C", 1, 30)));
    resume((t5_D = create((int *) &proc_t5_D, 256, 40, "proc_t5_D", 1, 40)));
    resume((t5_E = create((int *) &proc_t5_E, 256, 50, "proc_t5_E", 1, 50)));
    resume((t5_H = create((int *) &proc_t5_H, 256, 50, "proc_t5_H", 1, 80)));
}

