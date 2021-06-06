#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>

void mmapcopy(int fd1, int fd2, int size1, int size2)
{
    char *cp, *t;

    cp = mmap(NULL, size1, PROT_READ, MAP_SHARED, fd1, 0);
    t = mmap(NULL, size2, PROT_WRITE, MAP_SHARED, fd2, 0);
    memcpy(t, cp, size1);
    munmap(cp, size1);
    munmap(t, size2);
    close(fd1);
    close(fd2);
}
int main(int argc, char **argv){
    struct stat stat1,stat2;
    int fd1,fd2;

    if(argc < 3){
        printf("usage:%s <filename> or %s <filename>\n",argv[1],argv[2]);
        exit(0);
    }

    fd1 = open(argv[1], O_RDONLY, 0);
    fd2 = open(argv[2], O_RDWR, 0);
    fstat(fd1, &stat1);
    fstat(fd2, &stat2);
    mmapcopy(fd1, fd2, stat1.st_size, stat2.st_size);

    exit(0);
}
