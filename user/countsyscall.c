#include "kernel/types.h"
#include "user/user.h"

int main(int argc, char *argv[]) {
  // Check for help command - must be exactly "?"
  if(argc == 2 && strcmp(argv[1], "?") == 0){
    printf("Usage: countsyscall\n");
    printf("Display the number of system calls made since boot\n");
    exit(0);
  }

  // Check if anything follows the question mark
  if(argc >= 2 && argv[1][0] == '?'){
    printf("Error: invalid input after '?'\n");
    exit(1);
  }

  // countsyscall takes no arguments
  if(argc != 1){
    printf("Usage: countsyscall\n");
    printf("countsyscall takes no arguments. Use 'countsyscall ?' for help\n");
    exit(1);
  }

  int count = countsyscall();
  printf("System calls since boot: %d\n", count);
  exit(0);
}
