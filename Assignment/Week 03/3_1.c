#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>

int main() {
        int x;
        float f;
        double d;
        double d1, d2;
        x = 16777217;  // 수정
        if ((int)(float)x != x)
                printf("#1 Passed! (x:%d)\n", x);
        else
                printf("#1 Failed! (x:%d)\n", x);

        d = 16777217;
        if ((double)(float)d != d)
                printf("#1 Passed! (d:%lf)\n", d);
        else
                printf("#1 Failed! (d:%lf)\n", d);

        d1 = 0.01;  // 수정
        d2 = 0.01;  // 수정
        if ((d1+d2)+d != d1+(d2+d))
              printf("#1 Passed! (d1,d2,d:%lf,%lf,%lf)\n", d1, d2, d);
        else
              printf("#1 Failed! (d1,d2,d:%lf,%lf,%lf)\n", d1, d2, d);
        d1 = 1.8*pow(10,308);  // 수정
        d2 = 1.8*pow(10,308);  // 수정
        if ((d1+d2)-d1 != d2)
                printf("#1 Passed! (d1,d2:%lf,%lf)\n", d1, d2);
        else
                printf("#1 Failed!! (d1,d2:%lf,%lf)\n", d1, d2);
}

