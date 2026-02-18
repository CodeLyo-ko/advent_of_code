#include <stdio.h>
#include <stdlib.h>
#define MAX_ 100

void add_step(int** steps, int n_steps, int* banks, int n) {
    steps[n_steps] = malloc(n * sizeof(int));
    for (int i = 0; i < n;  i++) {
        steps[n_steps][i] = banks[i];
    }
}

int is_in_steps(int** steps, int n_steps, int* banks, int n) {
    for (int i = 0; i < n_steps; i++) {
        int is_eq = 1;
        for (int j = 0; j < n; j++) {
            if (steps[i][j] != banks[j]) {
                is_eq = 0;
                break;
            }
        }
        if (is_eq) return 1;
    }
    return 0;
}

int max_banks(int* banks, int n) {
    int max = 0;
    int k;
    for (int i = 0; i < n; i++) {
        if (banks[i] > max) {
            max = banks[i];
            k = i;
        }
    }
    return k;
}


void next_step(int* banks, int n) {
    int k = max_banks(banks, n);
    int m = banks[k];
    banks[k] = 0;
    k++;
    k%= n;
    while (m > 0) {
        banks[k]++;
        k++;
        k %= n;
        m--;
    }
}

int main(){
    int* banks = malloc(MAX_ * sizeof(int));
    int n = 0;

    while(getchar() != '\n') {
        fseek(stdin, -1, SEEK_CUR);
        scanf("%d", &banks[n++]);
    }

    int** steps = malloc(MAX_ * n * sizeof(int));
    int n_steps = 0;

    while (!is_in_steps(steps, n_steps, banks, n)){
            add_step(steps, n_steps, banks, n);
            n_steps++;
            next_step(banks, n);
    }

    printf("%d\n", n_steps);
}
