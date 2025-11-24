#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"

void usage() {
  printf("Usage: find [directory] [filename]\n");
}

void
find(char *path, char *filename) {
  int fd; // file descriptor for directory
  struct stat st; // to hold file status
  struct dirent de; // directory entry
  char buf[512], *p;  //storage for path building


  //opens directory at path
  fd = open(path, 0);
  if (fd < 0) {
    printf("find: cannot open %s\n", path);
    return;
  }

  //gets the file status
  if (fstat(fd, &st) < 0) {
    printf("find: cannot stat %s\n", path);
    close(fd);
    return;
  }

  //if not a directory
  if (st.type != T_DIR) {
    close(fd);
    return;
  }

  //read directory entries
  while (read(fd, &de, sizeof(de)) == sizeof(de)) {

    if (de.inum == 0) // skip empty entries
      continue;

      // skips the . and .. entries(current and parent directories)
    if (strcmp(de.name, ".") == 0 || strcmp(de.name, "..") == 0)
      continue;

    // Build path for entry: path/de.name
    strcpy(buf, path);
    p = buf + strlen(buf);
    *p++ = '/';
    memmove(p, de.name, DIRSIZ);
    p[DIRSIZ] = 0;

    // Get file status of the entry
    if (stat(buf, &st) < 0)
      continue;

    if (st.type == T_DIR)
      find(buf, filename);  // Recursive call for subdirectory

    else if (strcmp(de.name, filename) == 0) {
      printf("%s\n", buf);  // Print the full path if name matches
    }

  }

  close(fd);  // Close directory file descriptor
}

int
main(int argc, char *argv[]) {
  // check for help option
  if (argc == 2 && (strcmp(argv[1], "?") == 0 || strcmp(argv[1], "-?") == 0)) {
    usage();
    exit(0);
  }

  // check for correct number of arguments
  if (argc != 3) {
    printf("Error: incorrect number of arguments!\n");
    usage();
    exit(1);
  }

  find(argv[1], argv[2]);
  exit(0);
}
