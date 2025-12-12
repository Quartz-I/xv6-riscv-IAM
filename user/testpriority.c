#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char *argv[]) {
  printf("=== Testing Priority Scheduler ===\n");
  setsched(2);  // Switch to Priority

  int pid;
  int k, nprocess = 5;
  int z, steps = 500000;
  char buffer_src[1024], buffer_dst[1024];

  for (k = 0; k < nprocess; k++) {
    sleep(2);
    pid = fork();
    if (pid < 0) {
      printf("%d failed in fork!\n", getpid());
      exit(0);
    }
    else if (pid == 0) {
      // Set different priorities (lower = higher priority)
      int priority = 10 + (k * 5);  // 10, 15, 20, 25, 30
      setpriority(getpid(), priority);
      printf("[Priority=%d] [pid=%d] created\n", priority, getpid());

      for (z = 0; z < steps; z += 1) {
        memmove(buffer_dst, buffer_src, 1024);
        memmove(buffer_src, buffer_dst, 1024);
      }

      printf("[Priority=%d] [pid=%d] finished work\n", priority, getpid());
      exit(0);
    }
  }

  for (k = 0; k < nprocess; k++) {
    pid = wait(0);
    printf("[pid=%d] terminated\n", pid);
  }

  printf("\n=== Final Metrics ===\n");
  getschedmetrics();

  exit(0);
}
