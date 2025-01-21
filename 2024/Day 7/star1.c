#include <stdio.h>
#include <stdlib.h>
#include <math.h>

long long calculate(int* equation, int n, int number) {
    long long result = equation[0];
    int bit;
    for (int i = 1; i < n; i++) {
        bit = number & 1;
        number >>= 1;
        //printf("%d %d\n", bit, number);
        if (bit) {
            result += equation[i];
        }
        else {
            result *= equation[i];
        }
    }
    return result;
}

int main() {
    int* equation = malloc(100 * sizeof(int));
    long long result;
    int n;
    long long total = 0;

    while (getchar() != EOF) {
        n = 0;
        fseek(stdin, -1, SEEK_CUR);
        scanf("%lld:", &result);
        while (getchar() != '\n') {
            scanf("%d", &equation[n++]);
        }

        for (int i = 0; i < pow(2, n - 1); i++) {
            if (result == calculate(equation, n, i)) {
                total += result;
                break;
            }
        }
    }

    printf("%lld\n", total);

    return 0;
}
