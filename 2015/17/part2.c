#include <stdio.h>
#include <stdlib.h>

int n_combinations (int* containers, int n, int liters, int k, int n_containers) {
    if (liters == 0 && n_containers == 0) {
        return 1;
    }
    if (k == n || liters <= 0) {
        return 0;
    }

    return n_combinations(containers, n, liters - containers[k], k + 1, n_containers - 1) + n_combinations(containers, n, liters, k + 1, n_containers);
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

    int n_ways;

    int i = 1;

    do {
        n_ways = n_combinations(containers, n, liters_to_store, 0, i);
        i++;
    } while(!n_ways);

    printf("%d\n", n_ways);

    return 0;
}
