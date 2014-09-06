/* lab0.h -- header file for PA0 */

#ifndef _LAB0_H_
#define _LAB0_H_

/* Task 1 */
extern long zfunction(long);

/* Task 2 */
extern void printsegaddress(void);
extern int edata;
extern int etext;

/* Task 3 */
extern void printtos(void);

/* Task 4 */
extern void printprocstks(int);

/* Task 5 */
#define MAX_PROCS  50      /* max # of processes supported by scall stats */
#define NUM_SCALLS 27      /* total number of system calls to be traced   */
extern int g_scall_trace;  /* flag to hold whether to trace or not        */
extern unsigned long ctr1000;
extern char *g_scall_names[];

extern void syscallsummary_start(void);
extern void syscallsummary_stop(void);
extern void printsyscallsummary(void);

/* Enum to hold the syscalls names */
typedef enum {
    SCALL_CHPRIO = 0,
    SCALL_FREEMEM,
    SCALL_GETPID,
    SCALL_GETPRIO,
    SCALL_GETTIME,
    SCALL_KILL,
    SCALL_RECEIVE,
    SCALL_RECVCLR,
    SCALL_RECVTIM,
    SCALL_RESUME,
    SCALL_SCOUNT,
    SCALL_SCREATE,
    SCALL_SDELETE,
    SCALL_SEND,
    SCALL_SETDEV,
    SCALL_SETNOK,
    SCALL_SIGNAL,
    SCALL_SIGNALN,
    SCALL_SLEEP,
    SCALL_SLEEP10,
    SCALL_SLEEP100,
    SCALL_SLEEP1000,
    SCALL_SRESET,
    SCALL_STACKTRACE,
    SCALL_SUSPEND,
    SCALL_UNSLEEP,
    SCALL_WAIT
} SCALLS;

/* Util macro to increment syscall frequency */
#define UPDATE_SCALL_FREQ(PID, SCALL)            \
{                                                \
    if (TRUE == g_scall_trace) {                 \
        proctab[PID].freq[SCALL] += 1;           \
    }                                            \
}

/* Util macro to increment time taken by syscall */
#define UPDATE_SCALL_TIME(PID, SCALL, START_TIME)               \
{                                                               \
    if (TRUE == g_scall_trace) {                                \
        proctab[PID].ttime[SCALL] += (ctr1000 - START_TIME);    \
    }                                                           \
}

#endif /* _LAB0_H_ */

