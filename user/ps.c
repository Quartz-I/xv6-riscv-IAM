#include "kernel/types.h"
#include "kernel/param.h"
#include "user/user.h"

// Process states
#define UNUSED    0
#define USED      1
#define SLEEPING  2
#define RUNNABLE  3
#define RUNNING   4
#define ZOMBIE    5

// Process information structure
struct proc_info {
  int pid;
  int ppid;
  int state;
  char name[16];
  uint64 sz;
};

int main(int argc, char *argv[]) {
  // Check for help command - must be exactly "?"
  if(argc == 2 && strcmp(argv[1], "?") == 0){
    printf("Usage: ps\n");
    printf("Display information about all active processes\n");
    printf("Shows: PID, PPID, STATE, SIZE, NAME\n");
    exit(0);
  }

  // Check if anything follows the question mark
  if(argc >= 2 && argv[1][0] == '?'){
    printf("Error: invalid input after '?'\n");
    exit(1);
  }

  // ps takes no arguments
  if(argc != 1){
    printf("Usage: ps\n");
    printf("ps takes no arguments. Use 'ps ?' for help\n");
    exit(1);
  }

  struct proc_info procs[NPROC];
  int nproc;

  nproc = getptable(NPROC, procs);

  if(nproc < 0){
    printf("ps: getptable failed\n");
    exit(1);
  }

  printf("PID\tPPID\tSTATE\tSIZE\tNAME\n");

  for(int i = 0; i < nproc; i++){
    char *state;
    switch(procs[i].state){
      case UNUSED:    state = "unused"; break;
      case USED:      state = "used"; break;
      case SLEEPING:  state = "sleep"; break;
      case RUNNABLE:  state = "runble"; break;
      case RUNNING:   state = "run"; break;
      case ZOMBIE:    state = "zombie"; break;
      default:        state = "???"; break;
    }

    printf("%d\t%d\t%s\t%d\t%s\n", procs[i].pid, procs[i].ppid, state, (int)procs[i].sz, procs[i].name);
  }

  exit(0);
}
