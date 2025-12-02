#include <stdio.h>
#include <stdlib.h>

#define MAX_INT 200000

int has_repeat(long int x) {
    int n = 0;
    int* digit = malloc(MAX_INT * sizeof(int));
    while (x > 0) {
        digit[n] = x % 10;
        n++;
        x /= 10;
    }
    if (n%2 == 1) {
        free(digit);
        return 0;
    }

    n /= 2;
    for (int i = 0; i < n; i++) {
        if (digit[i] != digit[n + i]) {
            free(digit);
            return 0;
        }
    }
    free(digit);
    return 1;
}

int main(){
    long int n1, n2;
    long int res = 0;
    while(scanf("%ld-%ld,", &n1, &n2) > 0) {
        for (long int i = n1; i <= n2; i++) {
            if (has_repeat(i)){
                res+= i;
            }
        }
    }
    printf("%ld\n", res);
    return 0;
}
