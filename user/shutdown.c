#include "kernel/types.h"
#include "user/user.h"

int main(int argc, char *argv[])
{
  // Check for help command - must be exactly "?"
  if(argc == 2 && strcmp(argv[1], "?") == 0){
    printf("Usage: shutdown\n");
    printf("Initiates a clean shutdown of the xv6 operating system\n");
    printf("This command halts the system and causes QEMU to exit gracefully\n");
    exit(0);
  }

  // Check if anything follows the question mark
  if(argc >= 2 && argv[1][0] == '?'){
    printf("Error: invalid input after '?'\n");
    exit(1);
  }

  // shutdown takes no arguments
  if(argc != 1){
    printf("Usage: shutdown\n");
    printf("shutdown takes no arguments. Use 'shutdown ?' for help\n");
    exit(1);
  }

  printf("Shutting down the system...\n");
  shutdown();

  // Should not reach here
  printf("Error: shutdown failed\n");
  exit(1);
}
