// Ashraf

#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char *argv[])
{
  if(argc == 2 && argv[1][0] == '?'){
    printf("Usage: add number1 number2\n");
    exit(0);
  }

  if(argc != 3){
    printf("error can only take 2 integers \n");
    exit(1);
  }

  int num1 = atoi(argv[1]);
  int num2 = atoi(argv[2]);
  int sum = num1 + num2;
  printf("sum = %d\n", sum);

  exit(0);
}
