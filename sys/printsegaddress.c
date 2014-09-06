/* printsegaddress.c -- PA0 task 2 */

#include <stdio.h>
#include <kernel.h>
#include <mem.h>
#include <lab0.h>

void
printsegaddress(void)
{
    kprintf("Task 2 (printsegaddress)\n");

    /* The etext, edata and end pointers point to one location past 
     * the text, data and BSS segments respectively.
     */
    kprintf("Current: ");
    kprintf("etext[0x%08x]: 0x%08x, ", (&etext - 1), *(&etext - 1));
    kprintf("edata[0x%08x]: 0x%08x, ", (&edata - 1), *(&edata - 1));
    kprintf("end[0x%08x]: 0x%08x\n", (&end - 1), *(&end - 1));

    kprintf("Before: ");
    kprintf("etext[0x%08x]: 0x%08x, ", (&etext - 2), *(&etext - 2));
    kprintf("edata[0x%08x]: 0x%08x, ", (&edata - 2), *(&edata - 2));
    kprintf("end[0x%08x]: 0x%08x\n", (&end - 2), *(&end - 2));

    kprintf("After: ");
    kprintf("etext[0x%08x]: 0x%08x, ", (&etext), *(&etext));
    kprintf("edata[0x%08x]: 0x%08x, ", (&edata), *(&edata));
    kprintf("end[0x%08x]: 0x%08x\n", (&end), *(&end));

    kprintf("\n");

    return;
}
