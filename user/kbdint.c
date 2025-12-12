#include "kernel/types.h"
#include "user/user.h"

int main(int argc, char *argv[]) {
  // Check for help command - must be exactly "?"
  if(argc == 2 && strcmp(argv[1], "?") == 0){
    printf("Usage: kbdint\n");
    printf("Display the number of keyboard interrupts since boot\n");
    exit(0);
  }

  // Check if anything follows the question mark
  if(argc >= 2 && argv[1][0] == '?'){
    printf("Error: invalid input after '?'\n");
    exit(1);
  }

  // kbdint takes no arguments
  if(argc != 1){
    printf("Usage: kbdint\n");
    printf("kbdint takes no arguments. Use 'kbdint ?' for help\n");
    exit(1);
  }

  int count = kbdint();
  printf("Keyboard interrupts since boot: %d\n", count);

  exit(0);
}
