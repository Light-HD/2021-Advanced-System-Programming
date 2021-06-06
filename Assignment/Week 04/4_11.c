#include <stdio.h>
int inc(int x, int y) {
        register int s = 0;
        while ((x*x)<y) { // x^2 <y
                if ( x % 2 == 0) // 짝수
                        s = s+2;
                else		 // 홀수
                        s = s+1;
                x++;
        }
        return s;
}

void main() {
        printf("%d\n\n", inc(1, 100));
}

