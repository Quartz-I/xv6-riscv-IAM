#include "kernel/types.h"
#include "user/user.h"

int main(int argc, char *argv[])
{
  struct datetime dt;

  if(argc == 2 && argv[1][0] == '?'){
    printf("Usage: datetime\n");
    printf("Displays current date and time\n");
    exit(0);
  }

  if(datetime(&dt) < 0) {
    printf("datetime: failed\n");
    exit(1);
  }

  printf("Date: %d-%d-%d\n", dt.year, dt.month, dt.day);
  printf("Time: %d:%d:%d\n", dt.hour, dt.minute, dt.second);

  exit(0);
}
