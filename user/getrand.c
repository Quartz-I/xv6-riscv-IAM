#include "kernel/types.h"
#include "user/user.h"

int main(int argc, char *argv[])
{
  if(argc == 2 && argv[1][0] == '?'){
    printf("Usage: getrand\n");
    printf("Returns a pseudo-random integer\n");
    exit(0);
  }

  printf("Random number: %d\n", getrand());
  printf("Random number: %d\n", getrand());
  printf("Random number: %d\n", getrand());

  exit(0);
}
