#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void f() {
        char s1[4];
        char s2[4];
        char *result;
        gets(s1);
        gets(s2);
        result = malloc(strlen(s1)+strlen(s2));
        strcat(result,s1);
        strcat(result,s2);
        printf("%s\n", result);
}

int main() {
        f();
}

