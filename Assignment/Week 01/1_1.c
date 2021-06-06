#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef unsigned char* byte_pointer;

void show_bytes(byte_pointer start, size_t len) {
    int i;
    for (i = 0; i < len; i++)
        printf(" %.2x ", start[i]);
    printf("\n");
}

void show_int(uint64_t x) {
    show_bytes((byte_pointer)&x, sizeof(uint64_t));

}

int main() {
    uint64_t x, y;
    printf("Input a long number x : ");
    scanf("%ld", &x);
    printf("Input a long number y : ");
    scanf("%ld", &y);
    printf("your input(%ld) is %lx in hexadecimal.\n", x, x);
    printf("your input(%ld) is %lx in hexadecimal.\n", y, y);
    printf("x : %lx\n", x);
    printf("x<<8 : %lx\n", x << 8);
    printf("x>>8 : %lx\n", x >> 8);
    printf("x&y : %lx\n", x & y);
    printf("x|y : %lx\n", x | y);
    printf("x&!y : %lx\n", x & !y);
    printf("x&&y : %x\n", x&&y);
    printf("x||y : %x\n", x||y);
    printf("x&&~y : %x\n",x&&~y);

    printf("x in Bytes order : "); show_int(x); 
    printf("x << 8 in Bytes order : "); show_int(x << 8); 
    printf("x >> 8 in Bytes order : "); show_int(x >> 8);
}
