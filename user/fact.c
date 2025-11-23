// Ashraf

#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
factorial(int n)
{
  if(n == 0 || n == 1)
    return 1;
  return n * factorial(n - 1);
}

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
    printf("Usage: fact number\n");
    exit(0);
  }

  // Check if anything follows the question mark (with or without space)
  if(argc >= 2 && argv[1][0] == '?'){
    printf("Error: invalid input after '?'\n");
    exit(1);
  }

  // Check for correct number of arguments
  if(argc != 2){
    printf("Error: You can only get the factorial of a single positive number\n");
    exit(1);
  }

  // Check for negative number
  if(argv[1][0] == '-'){
    printf("Error: You can only get the factorial of a single positive number\n");
    exit(1);
  }

  // Check if input is a valid number
  if(!is_valid_number(argv[1])){
    printf("Error: input is not a valid number\n");
    exit(1);
  }

  int num = atoi(argv[1]);
  int result = factorial(num);
  printf("factorial = %d\n", result);

  exit(0);
}
