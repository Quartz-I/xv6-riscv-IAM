#include "kernel/types.h"
#include "user/user.h"

int main(int argc, char *argv[])
{
  if(argc == 2 && argv[1][0] == '?'){
    printf("Usage: getuptime\n");
    printf("Gets the uptime system call\n");
    exit(0);
  }

  printf("System uptime: %d ticks\n", uptime());

  exit(0);
}
