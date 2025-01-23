#include <stdio.h>
#include <stdlib.h>

int n_combinations (int* containers, int n, int liters, int k) {
    if (liters == 0) {
        return 1;
    }
    if (k == n || liters < 0) {
        return 0;
    }

    return n_combinations(containers, n, liters - containers[k], k + 1) + n_combinations(containers, n, liters, k + 1);
}

int main() {
    int liters_to_store = 150;

    int* containers = malloc(50 * sizeof(int));
    int n = 0;

    while (getchar() != EOF) {
        fseek(stdin, -1, SEEK_CUR);

        scanf("%d\n", &containers[n]);
        n++;
    }

    printf("%d\n",n_combinations(containers, n, liters_to_store, 0));

    return 0;
}
