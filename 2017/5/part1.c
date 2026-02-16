#include <stdio.h>
#include <stdlib.h>
#define MAX_ 10000

int main() {
    int* jumps = malloc(MAX_ * sizeof(int));
    int n = 0;

    while(getchar() != EOF) {
        fseek(stdin, -1, SEEK_CUR);
        scanf("%d\n", &jumps[n++]);
    }

    int k = 0;
    int res = 0;
    while (k >= 0 && k < n) {
        res++;
        jumps[k]++;
        k += jumps[k] - 1;
    }

    printf("%d\n", res);


    return 0;
}
