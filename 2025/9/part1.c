#include <stdio.h>
#include <stdlib.h>
#define MAX_ 1000

long int size_rec(long int a1, long int a2, long int b1, long int b2) {
    if (a1 < b1) {
        long int c = a1;
        a1 = b1;
        b1 = c;
    }
    if (a2 < b2) {
        long int c = a2;
        a2 = b2;
        b2 = c;
    }
    return ((1 + a1 - b1) * (1 + a2 - b2));
}

int main() {
    long int** rec = malloc(MAX_ * 2 * sizeof(long int));
    int n = -1;

    do {
        n++;
        rec[n] = malloc(2 * sizeof(long int));
    } while(scanf("%ld,%ld\n", &rec[n][0], &rec[n][1]) > 0);

    long int max = 0;
    long int size;

    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            size = size_rec(rec[i][0], rec[i][1], rec[j][0], rec[j][1]);
            if (size > max) max = size;
        }
    }
    printf("%ld\n", max);
    

    return 0;
}
