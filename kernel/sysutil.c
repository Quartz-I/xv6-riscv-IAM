#include "types.h"
extern int kbd_intr_count;

uint64
sys_kbdint(void)
{
  return kbd_intr_count;
}

// QEMU test device address for poweroff
#define QEMU_TEST_DEV 0x100000

uint64
sys_shutdown(void)
{

  (*(volatile uint32 *)QEMU_TEST_DEV) = 0x5555;

  // Should not return, but just in case
  return 0;
}
