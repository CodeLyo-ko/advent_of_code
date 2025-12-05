#include <stdio.h>
#include <stdlib.h>
#define MAX_ 5000

int comp_interval(const void *a, const void *b) {
    long int* a_ = *(long int**)a;
    long int* b_ = *(long int**)b;
    return a_[0] > b_[0];
}

int main(){
    long int** fresh = malloc(2 * MAX_ * sizeof(long int));
    int n_f = 0;

    long int res = 0;
    char buffer[MAX_];

    while(getchar() != '\n') {
        fseek(stdin, -1, SEEK_CUR);

        fresh[n_f] = malloc(2 * sizeof(int));
        fgets(buffer, sizeof(buffer), stdin);
        sscanf(buffer, "%ld-%ld", &fresh[n_f][0], &fresh[n_f][1]);
        n_f++;
    }

    qsort(fresh, n_f, sizeof(fresh[0]), comp_interval);

    for (int i = 0; i < n_f; i++) {
        if (i == 0) {
            res += fresh[i][1] - fresh[i][0] + 1;
            continue;
        }

        if (fresh[i][0] <= fresh[i - 1][1]) {
            fresh[i][0] = fresh[i - 1][1] + 1;
        }

        if (fresh[i][1] < fresh[i][0]) {
            fresh[i][1] = fresh[i - 1][1];
            continue;
        }

        res += fresh[i][1] - fresh[i][0] + 1;
            
    }


    printf("%ld\n", res);

    return 0;
}
