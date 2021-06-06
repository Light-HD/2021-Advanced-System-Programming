#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char a[27];
int main() {
        char* b = "abcdefghijklmnopqrstuvwxyz";
        int num = 0;

        scanf("%d", &num);

        if (num > 26)
                memcpy(a, b, 26);
	else if (num < -26)
		memcpy(a, b, 26);
	else if (num < 0) {
		num *= -1;
		memcpy(a, b, num); }
        else
                memcpy(a, b, num);
        printf("%s\n", a);
}

