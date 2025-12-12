// Ashraf

#include "kernel/types.h"
#include "kernel/stat.h"
#include "kernel/fcntl.h"
#include "user/user.h"

char buf[512];

// Flags for which counts to display
int show_lines = 1;
int show_words = 1;
int show_chars = 1;
int show_longest = 0;

// Totals across all files
int total_lines = 0;
int total_words = 0;
int total_chars = 0;
int total_longest = 0;

void
wc(int fd, char *name)
{
  int i, n;
  int l, w, c, inword;
  int longest, current_line_len;

  l = w = c = 0;
  longest = 0;
  current_line_len = 0;
  inword = 0;

  while((n = read(fd, buf, sizeof(buf))) > 0){
    for(i=0; i<n; i++){
      c++;
      current_line_len++;

      if(buf[i] == '\n'){
        l++;
        if(current_line_len - 1 > longest){
          longest = current_line_len - 1;
        }
        current_line_len = 0;
      }

      if(strchr(" \r\t\n\v", buf[i]))
        inword = 0;
      else if(!inword){
        w++;
        inword = 1;
      }
    }
  }

  if(n < 0){
    printf("wc: read error\n");
    exit(1);
  }

  // Update totals
  total_lines += l;
  total_words += w;
  total_chars += c;
  if(longest > total_longest)
    total_longest = longest;

  // Print selected counts
  if(show_lines)
    printf("%d ", l);
  if(show_words)
    printf("%d ", w);
  if(show_chars)
    printf("%d ", c);
  if(show_longest)
    printf("%d ", longest);

  printf("%s\n", name);
}

int
main(int argc, char *argv[])
{
  int fd, i;
  int file_count = 0;
  int first_file_arg = 1;

  // Check for help command
  if(argc == 2 && strcmp(argv[1], "?") == 0){
    printf("Usage: wc [-l] [-w] [-c] [-L] [file ...]\n");
    printf("  -l: lines only\n");
    printf("  -w: words only\n");
    printf("  -c: characters only\n");
    printf("  -L: longest line length\n");
    exit(0);
  }

  // Parse flags
  int flags_specified = 0;
  for(i = 1; i < argc; i++){
    char *flag = argv[i];
    if(flag[0] != '-' || flag[1] == '\0')
      break;

    // If any flag is specified, turn off defaults
    if(!flags_specified){
      show_lines = 0;
      show_words = 0;
      show_chars = 0;
      flags_specified = 1;
    }

    // Parse each character in the flag
    for(int j = 1; flag[j] != '\0'; j++){
      if(flag[j] == 'l')
        show_lines = 1;
      else if(flag[j] == 'w')
        show_words = 1;
      else if(flag[j] == 'c')
        show_chars = 1;
      else if(flag[j] == 'L')
        show_longest = 1;
      else{
        printf("wc: invalid option '%c'\n", flag[j]);
        exit(1);
      }
    }
  }

  first_file_arg = i;

  // No files specified, read from stdin
  if(first_file_arg >= argc){
    wc(0, "");
    exit(0);
  }

  // Process each file
  for(i = first_file_arg; i < argc; i++){
    if((fd = open(argv[i], O_RDONLY)) < 0){
      printf("wc: cannot open %s\n", argv[i]);
      exit(1);
    }
    wc(fd, argv[i]);
    close(fd);
    file_count++;
  }

  // Print total line if multiple files
  if(file_count > 1){
    if(show_lines)
      printf("%d ", total_lines);
    if(show_words)
      printf("%d ", total_words);
    if(show_chars)
      printf("%d ", total_chars);
    if(show_longest)
      printf("%d ", total_longest);
    printf("total\n");
  }

  exit(0);
}
