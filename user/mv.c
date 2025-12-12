// Ashraf

#include "kernel/types.h"
#include "kernel/stat.h"
#include "kernel/fcntl.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
  // Check for help command - must be exactly "?"
  if(argc == 2 && strcmp(argv[1], "?") == 0){
    printf("Usage: mv source destination\n");
    exit(0);
  }

  // Check if anything follows the question mark
  if(argc >= 2 && argv[1][0] == '?'){
    printf("Error: invalid input after '?'\n");
    exit(1);
  }

  // Check for correct number of arguments
  if(argc != 3){
    printf("Invalid number of arguments\n");
    exit(1);
  }

  char *source = argv[1];
  char *dest = argv[2];

  // Try to link the source file to the destination
  if(link(source, dest) < 0){
    printf("mv: cannot link %s to %s\n", source, dest);
    exit(1);
  }

  // Unlink (remove) the source file
  if(unlink(source) < 0){
    printf("mv: cannot unlink %s\n", source);
    // Try to clean up the destination link
    unlink(dest);
    exit(1);
  }

  exit(0);
}
