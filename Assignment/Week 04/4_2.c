#include <stdio.h>
int f(int x1, int x2, int x3, int x4, int x5) {
        int temp;
        temp = x1+x2+x3+x4+x5;
        if (x1>x2)
                return temp;
        else
           return temp + (f(x1+1, x2-1, x3, x4, x5) + x1);
}
int main()  {
        printf("%d\n", f(1,2,3,4,5));
}

