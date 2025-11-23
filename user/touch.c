#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fcntl.h"

int main(int argc, char *argv[])
{
    int fd;
    struct stat st;

    if(argc == 2 && argv[1][0] == '?'){
        printf("Usage: creates an empty file \n");
        exit(0);
    }

    if(argc != 2){
        fprintf(2, "touch: missing filename\n");
        exit(1);
    }

    // Check if file already exists
    if(stat(argv[1], &st) == 0){
        fprintf(2, "touch: %s already exists\n", argv[1]);
        exit(1);
    }

    // Create the file with O_CREATE flag
    fd = open(argv[1], O_CREATE | O_RDWR);
    if(fd < 0){
        fprintf(2, "touch: cannot create %s\n", argv[1]);
        exit(1);
    }

    close(fd);
    exit(0);
}
