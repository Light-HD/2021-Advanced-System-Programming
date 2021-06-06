#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define TMAX 2147483647
#define UMAX 4294967295
#define TMIN -2147483648
#define UMIN 0

int main() {

        int x,y;
        unsigned ux,uy;
        x = TMIN;  // 수정
        if (x<0 && x*2>=0)
                printf("#1 Passed! (x:%d)\n", x);
        else
                printf("#1 Failed! (x:%d)\n", x);

        ux = UMAX;  // 수정
        if (ux > -2)
                printf("#1 Passed! (ux:%u)\n", ux);
        else
                printf("#1 Failed! (ux:%u)\n", ux);
        x = 2016124087;  // 수정
        y = TMIN;  // 수정
        if (x>y && -x>-y)
                printf("#1 Passed! (x,y:%d,%d)\n", x,y);
        else
                printf("#1 Failed! (x,y:%d,%d)\n", x,y);

        x = 2016124087;  // 수정
        y = -2016124087;  // 수정
        if (x>>3 == x/8 && y>>3 != y/8)
                printf("#1 Passed! (x,y:%d,%d)\n", x,y);
        else
                printf("#1 Failed! (x,y:%d,%d)\n", x,y);
}

