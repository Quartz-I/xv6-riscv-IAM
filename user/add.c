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
my_atoi(char *s)
{
  int n = 0;
  int negative = 0;

  // Check for negative sign
  if(*s == '-'){
    negative = 1;
    s++;
  }

  // Convert digits
  while('0' <= *s && *s <= '9'){
    n = n * 10 + (*s - '0');
    s++;
  }

  return negative ? -n : n;
}

int
main(int argc, char *argv[])
{
  // Check for help command - must be exactly "?"
  if(argc == 2 && strcmp(argv[1], "?") == 0){
    printf("Usage: add number1 number2\n");
    exit(0);
  }

  // Check if anything follows the question mark
  if(argc >= 2 && argv[1][0] == '?'){
    printf("Error: invalid input after '?'\n");
    exit(1);
  }

  // Check for correct number of arguments
  if(argc != 3){
    printf("error can only take 2 integers \n");
    exit(1);
  }

  // Check if both inputs are valid numbers
  if(!is_valid_number(argv[1]) || !is_valid_number(argv[2])){
    printf("Error: inputs are not valid numbers\n");
    exit(1);
  }

  int num1 = my_atoi(argv[1]);
  int num2 = my_atoi(argv[2]);
  int sum = num1 + num2;
  printf("sum = %d\n", sum);

  exit(0);
}
