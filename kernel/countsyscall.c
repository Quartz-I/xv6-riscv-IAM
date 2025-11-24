#include "types.h"

extern int total_syscall_count;

uint64
sys_countsyscall(void)
{
  return total_syscall_count;
}
