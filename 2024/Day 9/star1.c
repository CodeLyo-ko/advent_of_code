#include <stdio.h>
#include <stdlib.h>

int main() {
    int* line = malloc(100000 * sizeof(int));
    int n = 0;

    char c;

    while ((c = getchar()) != '\n') {
        line[n++] = c - '0';
    }

        //printf("%d\n", n);
    long long total = 0;
    int k = 0;

    for (int i = 0; i < n; i++) {
            //printf("%d %d %d %d\n", i, k, line[i], total);
        if (i%2 == 0) {
            while (line[i] > 0) {
                total += i/2 * k;
                line[i]--;
                k++;
            }
        }
        else {

            while (line[i] > 0) {
                if (line[n - 1] == 0) {
                    n -= 2;
                }
                total += (n-1) / 2 * k;
                //printf("%d %d\n", (n-1)/2, total);

                line[n-1]--;
                k++;
                line[i]--;
            }
        }
    }

    printf("%lld\n", total);

    return 0;
}
