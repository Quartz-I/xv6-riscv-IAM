#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

#define DEFAULT_LINES 10
#define MAX_LINES 1000
#define BUF_SIZE 512

char buf[BUF_SIZE];
char *lines[MAX_LINES];
int line_count = 0;


void
usage(void)
{
  printf("Usage: tail [-n number_of_lines] [file]\n deafult number_of_lines is 10");
}


void
tail(int fd, int n)
{
  int i, j, k;
  int bytes_read;
  char temp_buf[BUF_SIZE];
  int char_count = 0;

  line_count = 0;

  // Read the entire file and store line pointers
  while((bytes_read = read(fd, temp_buf, sizeof(temp_buf))) > 0) {
    for(i = 0; i < bytes_read; i++) {
      char c = temp_buf[i];

      // Store character temporarily
      if(char_count < BUF_SIZE) {
        buf[char_count++] = c;
      }

      // Check for newline
      if(c == '\n') {
        // Allocate memory for the line
        lines[line_count] = malloc(char_count + 1);
        if(lines[line_count] == 0) {
          fprintf(2, "tail: out of memory\n");
          exit(1);
        }

        // Copy the line (including newline)
        for(j = 0; j < char_count; j++) {
          lines[line_count][j] = buf[j];
        }
        lines[line_count][char_count] = '\0';

        // If we've reached max lines, free the oldest and shift
        if(line_count >= MAX_LINES) {
          free(lines[0]);
          for(k = 0; k < MAX_LINES - 1; k++) {
            lines[k] = lines[k + 1];
          }
          line_count = MAX_LINES - 1;
        } else {
          line_count++;
        }

        // Reset buffer for next line
        char_count = 0;
      }
    }
  }

  // Handle last line if it doesn't end with newline
  if(char_count > 0) {
    lines[line_count] = malloc(char_count + 1);
    if(lines[line_count] == 0) {
      fprintf(2, "tail: out of memory\n");
      exit(1);
    }

    for(j = 0; j < char_count; j++) {
      lines[line_count][j] = buf[j];
    }
    lines[line_count][char_count] = '\0';

    if(line_count >= MAX_LINES) {
      free(lines[0]);
      for(k = 0; k < MAX_LINES - 1; k++) {
        lines[k] = lines[k + 1];
      }
      line_count = MAX_LINES - 1;
    } else {
      line_count++;
    }
  }

  if(bytes_read < 0) {
    fprintf(2, "tail: read error\n");
    exit(1);
  }

  // Print the last n lines
  int start = (line_count > n) ? (line_count - n) : 0;
  for(i = start; i < line_count; i++) {
    printf("%s", lines[i]);
  }

  // Free allocated memory
  for(i = 0; i < line_count; i++) {
    free(lines[i]);
  }
}

int
main(int argc, char *argv[])
{
  int fd;
  int n = DEFAULT_LINES;
  int arg_idx = 1;

  if (argc > 1 && (strcmp(argv[1], "?") == 0 || strcmp(argv[1], "-?") == 0)) {
  usage();
  exit(0);
}

  // Parse -n flag
  if(argc > 1 && argv[1][0] == '-') {
    // Check if it's -n with space (e.g., -n 5)
    if(argv[1][1] == 'n' && argv[1][2] == '\0') {
      if(argc < 3) {
        fprintf(2, "tail: -n requires an argument\n");
        exit(1);
      }
      n = atoi(argv[2]);
      if(n <= 0 || n > MAX_LINES) {
        fprintf(2, "tail: invalid number of lines\n");
        exit(1);
      }
      arg_idx = 3;
    }
    // Check if it's -n5 format (number directly after n)
    else if(argv[1][1] == 'n') {
      n = atoi(argv[1] + 2);
      if(n <= 0 || n > MAX_LINES) {
        fprintf(2, "tail: invalid number of lines\n");
        exit(1);
      }
      arg_idx = 2;
    }
    // Check if it's -5 format (just dash and number)
    else if(argv[1][1] >= '0' && argv[1][1] <= '9') {
      n = atoi(argv[1] + 1);
      if(n <= 0 || n > MAX_LINES) {
        fprintf(2, "tail: invalid number of lines\n");
        exit(1);
      }
      arg_idx = 2;
    }
    else {
      fprintf(2, "tail: invalid option %s\n", argv[1]);
      exit(1);
    }
  }

  // Process file or stdin
  if(argc == arg_idx) {
    // Read from stdin
    tail(0, n);
  } else {
    // Read from file(s)
    for(; arg_idx < argc; arg_idx++) {
      if((fd = open(argv[arg_idx], 0)) < 0) {
        fprintf(2, "tail: cannot open %s\n", argv[arg_idx]);
        exit(1);
      }

      if(argc - arg_idx > 1) {
        printf("==> %s <==\n", argv[arg_idx]);
      }

      tail(fd, n);
      close(fd);

      if(arg_idx < argc - 1) {
        printf("\n");
      }
    }
  }

  exit(0);
}
