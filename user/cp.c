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
    printf("Usage: cp source destination\n");
    exit(0);
  }

  // Check if anything follows the question mark
  if(argc >= 2 && argv[1][0] == '?'){
    printf("Error: invalid input after '?'\n");
    exit(1);
  }

  // Check for correct number of arguments
  if(argc != 3){
    printf("Error: only takes 2 arguments\n");
    exit(1);
  }

  char *source = argv[1];
  char *dest = argv[2];
  int fd_src, fd_dest;
  char buf[512];
  int n;

  // Open source file for reading
  fd_src = open(source, O_RDONLY);
  if(fd_src < 0){
    printf("cp: cannot open %s\n", source);
    exit(1);
  }

  // Open/create destination file for writing
  fd_dest = open(dest, O_CREATE | O_WRONLY | O_TRUNC);
  if(fd_dest < 0){
    printf("cp: cannot create %s\n", dest);
    close(fd_src);
    exit(1);
  }

  // Copy data from source to destination
  while((n = read(fd_src, buf, sizeof(buf))) > 0){
    if(write(fd_dest, buf, n) != n){
      printf("cp: write error\n");
      close(fd_src);
      close(fd_dest);
      exit(1);
    }
  }

  if(n < 0){
    printf("cp: read error\n");
    close(fd_src);
    close(fd_dest);
    exit(1);
  }

  close(fd_src);
  close(fd_dest);

  exit(0);
}
