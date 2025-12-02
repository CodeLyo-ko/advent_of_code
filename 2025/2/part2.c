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
    int n_;
    int end;
    for (int j = 2; j <= n; j++) {
        if (n%j){
            continue;
        }
        end = 0;
        n_ = n / j; 
        for (int i = 0; i < n_; i++) {
            for (int k = n_ + i; k < n_ * j; k += n_) {
                if (digit[i] != digit[k]) {
                    end = 1;
                    break;
                }
             }
            if (end) break;
        }
        if (!end) {
            free(digit);
            return 1;
        }
    }
    free(digit);
    return 0;
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
