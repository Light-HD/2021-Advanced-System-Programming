#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>

void mmapcopy(int fd, int size)
{
    char *bufp, *korea;

    bufp = mmap(NULL, size, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);
    korea = "Hello, KOREA!\n";
    memcpy(bufp, korea, size);
    munmap(bufp, size);
    close(fd);
}
int main(int argc, char **argv){
    struct stat stat;
    int fd;

    if(argc !=2){
        printf("usage:%s <filename>\n",argv[0]);
        exit(0);
    }

    fd = open(argv[1], O_RDWR, 0);
    fstat(fd, &stat);
    mmapcopy(fd, stat.st_size);
    exit(0);
}
