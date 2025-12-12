#include "kernel/types.h"
#include "kernel/stat.h"
#include "kernel/fcntl.h"
#include "user/user.h"

#define MAXLINE 512

char buf1[MAXLINE];
char buf2[MAXLINE];

int readline(int fd, char *buf, int max) {
  int i, cc;
  char c;

  for(i = 0; i < max - 1; i++) {
    cc = read(fd, &c, 1);
    if(cc < 1)
      break;
    buf[i] = c;
    if(c == '\n') {
      i++;
      break;
    }
  }

  buf[i] = '\0';
  return i;
}

void diff(int fd1, int fd2) {
  int line = 1;
  int n1, n2;
  int identical = 1;

  while(1) {
    n1 = readline(fd1, buf1, MAXLINE);
    n2 = readline(fd2, buf2, MAXLINE);

    if(n1 == 0 && n2 == 0)
      break;

    if(n1 == 0) {
      printf("Line %d only in file2:\n", line);
      printf("> %s", buf2);
      identical = 0;
      while((n2 = readline(fd2, buf2, MAXLINE)) > 0) {
        line++;
        printf("Line %d only in file2:\n", line);
        printf("> %s", buf2);
      }
      break;
    }

    if(n2 == 0) {
      printf("Line %d only in file1:\n", line);
      printf("> %s", buf1);
      identical = 0;
      while((n1 = readline(fd1, buf1, MAXLINE)) > 0) {
        line++;
        printf("Line %d only in file1:\n", line);
        printf("> %s", buf1);
      }
      break;
    }

    if(strcmp(buf1, buf2) != 0) {
      printf("Line %d differs:\n", line);
      printf("< %s", buf1);
      printf("> %s", buf2);
      identical = 0;
    }

    line++;
  }

  if(identical) {
    printf("Files are identical\n");
  }
}

int main(int argc, char *argv[]) {
  int fd1, fd2;

  // Check for help command
  if(argc == 2 && strcmp(argv[1], "?") == 0) {
    printf("Usage: diff filename1 filename2\n");
    printf("  < shows lines from the first file\n");
    printf("  > shows lines from the second file\n");
    exit(0);
  }

  // Check if anything follows the question mark
  if(argc >= 2 && argv[1][0] == '?') {
    printf("Error: invalid input after '?'\n");
    exit(1);
  }

  // diff requires exactly two arguments
  if(argc != 3) {
    printf("diff requires exactly two file arguments. Use 'diff ?' for help\n");
    exit(1);
  }

  if((fd1 = open(argv[1], O_RDONLY)) < 0) {
    fprintf(2, "diff: cannot open %s\n", argv[1]);
    exit(1);
  }

  if((fd2 = open(argv[2], O_RDONLY)) < 0) {
    fprintf(2, "diff: cannot open %s\n", argv[2]);
    close(fd1);
    exit(1);
  }

  diff(fd1, fd2);

  close(fd1);
  close(fd2);
  exit(0);
}
