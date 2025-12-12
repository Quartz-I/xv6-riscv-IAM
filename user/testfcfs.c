#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char *argv[]) {
  printf("=== Testing FCFS Scheduler ===\n");
  setsched(1);  // Switch to FCFS

  int pid;
  int k, nprocess = 5;
  int z, steps = 500000;
  char buffer_src[1024], buffer_dst[1024];

  for (k = 0; k < nprocess; k++) {
    sleep(2);  // Different creation times
    pid = fork();
    if (pid < 0) {
      printf("%d failed in fork!\n", getpid());
      exit(0);
    }
    else if (pid == 0) {
      printf("[FCFS] [pid=%d] created\n", getpid());
      // The child process performs a busy work loop
      for (z = 0; z < steps; z += 1) {
        // Repeatedly moves data between two buffers
        memmove(buffer_dst, buffer_src, 1024);
        memmove(buffer_src, buffer_dst, 1024);
      }
      printf("[FCFS] [pid=%d] finished work\n", getpid());
      exit(0);
    }
  }

  // The parent process waits for all child processes to terminate
  for (k = 0; k < nprocess; k++) {
    pid = wait(0);
    printf("[FCFS] [pid=%d] terminated\n", pid);
  }

  printf("\n=== Final Metrics ===\n");
  getschedmetrics();
  exit(0);
}
