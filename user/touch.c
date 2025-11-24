#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fcntl.h"

int main(int argc, char *argv[])
{
    int fd;
    struct stat st;
    int i;
    int errors = 0;

    if(argc >= 2 && argv[1][0] == '?'){
        printf("Usage: touch filename [filename2 ...]\n");
        printf("Creates empty files\n");
        exit(0);
    }

    if(argc < 2){
        fprintf(2, "touch: missing filename\n");
        exit(1);
    }

    // Loop through all filenames (starting from argv[1])
    for(i = 1; i < argc; i++){
        // Check if file already exists
        if(stat(argv[i], &st) == 0){
            fprintf(2, "touch: %s already exists\n", argv[i]);
            errors++;
            continue;  // Skip to next file
        }

        // Create the file with O_CREATE flag
        fd = open(argv[i], O_CREATE | O_RDWR);
        if(fd < 0){
            fprintf(2, "touch: cannot create %s\n", argv[i]);
            errors++;
            continue;  // Skip to next file
        }

        close(fd);
    }

    // Exit with error if any files failed
    exit(errors > 0 ? 1 : 0);
}
