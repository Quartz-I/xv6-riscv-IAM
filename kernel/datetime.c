#include "types.h"
#include "param.h"
#include "memlayout.h"
#include "riscv.h"
#include "spinlock.h"
#include "proc.h"
#include "defs.h"
#ifndef BOOT_EPOCH
#define BOOT_EPOCH 0
#endif


extern struct spinlock tickslock;
extern uint ticks;

// Simple timestamp to datetime conversion
void
timestamp_to_datetime(uint64 timestamp, struct datetime *dt)
{
  uint64 seconds = timestamp;
  uint64 minutes = seconds / 60;
  uint64 hours = minutes / 60;
  uint64 days = hours / 24;

  dt->second = seconds % 60;
  dt->minute = minutes % 60;
  dt->hour = hours % 24;

  // Simple date calculation starting from 1970-01-01
  uint year = 1970;
  uint days_in_year;

  while(1) {
    days_in_year = 365;
    if((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))
      days_in_year = 366;

    if(days < days_in_year)
      break;

    days -= days_in_year;
    year++;
  }

  dt->year = year;

  // Month calculation
  uint days_in_month[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

  if((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))
    days_in_month[1] = 29;

  uint month = 0;
  while(month < 12 && days >= days_in_month[month]) {
    days -= days_in_month[month];
    month++;
  }

  dt->month = month + 1;
  dt->day = days + 1;
}

uint64
sys_datetime(void)
{
  uint64 addr;
  struct datetime dt;

  // Get the user space address - argaddr returns void in xv6-riscv
  argaddr(0, &addr);

  // Use ticks as time source
  uint xticks;
  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);

  // Calculate timestamp from boot epoch + ticks
  uint64 timestamp = BOOT_EPOCH + (xticks / 10) + 7200;

  timestamp_to_datetime(timestamp, &dt);

  // Copy to user space
  struct proc *p = myproc();
  if(copyout(p->pagetable, addr, (char *)&dt, sizeof(dt)) < 0)
    return -1;

  return 0;
}
