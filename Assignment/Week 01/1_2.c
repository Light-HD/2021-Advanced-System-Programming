#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef unsigned char* byte_pointer;

void show_bytes(byte_pointer start, size_t len) {
    if (start[0] == 0x44) {
	printf("little endian\n");
    }
    else printf("big endian\n");
}

int main() {
    uint64_t x = 0x11223344;
    show_bytes((byte_pointer)&x, sizeof(uint64_t));
}
