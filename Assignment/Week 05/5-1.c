#include <stdio.h>
#define N 7
#define M 5

int sum_element(int a[][N], long i, long j) {
        return a[i][j]+a[j][i];
}


int main() {
        int arr[M][N];
        printf("%d\n", sum_element(arr, 3,5));
}

