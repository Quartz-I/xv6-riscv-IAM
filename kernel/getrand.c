#include "types.h"
#include "riscv.h"

// LCG parameters
#define LCG_A 1103515245
#define LCG_C 12345
#define LCG_M 2147483648  // 2^31

static uint64 seed = 0;

uint64
sys_getrand(void)
{
  // Initialize seed on first call
  if(seed == 0) {
    seed = r_time();
  }

  // LCG formula: seed = (A * seed + C) % M
  seed = (LCG_A * seed + LCG_C) % LCG_M;

  return seed;
}
