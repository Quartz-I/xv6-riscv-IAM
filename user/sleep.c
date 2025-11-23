// Ashraf

#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
is_valid_number(char *s)
{
  // Check for negative sign
  if(*s == '-'){
    s++;
  }

  // Must have at least one digit after optional minus
  if(*s == '\0')
    return 0;

  // Check remaining characters are digits
  while(*s != '\0'){
    if(*s < '0' || *s > '9')
      return 0;
    s++;
  }

  return 1;
}

int
main(int argc, char *argv[])
{
  // Check for help command - must be exactly "?"
  if(argc == 2 && strcmp(argv[1], "?") == 0){
    printf("Usage: sleep number\n");
    exit(0);
  }

  // Check if anything follows the question mark
  if(argc >= 2 && argv[1][0] == '?'){
    printf("Error: invalid input after '?'\n");
    exit(1);
  }

  // Check for correct number of arguments
  if(argc != 2){
    printf("Invalid command, you can only use a single number\n");
    exit(1);
  }

  // Check for negative number
  if(argv[1][0] == '-'){
    printf("Error: sleep time must be a positive number\n");
    exit(1);
  }

  // Check if input is a valid number
  if(!is_valid_number(argv[1])){
    printf("Error: input is not a valid number\n");
    exit(1);
  }

  int sleeptime = atoi(argv[1]);

  printf("Starting sleep for %d\n", sleeptime);
  sleep(sleeptime);
  printf("Finished sleeping...\n");

  exit(0);
}
