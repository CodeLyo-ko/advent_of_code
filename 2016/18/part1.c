#include <stdio.h>
#include <stdlib.h>
#define MAX_ 1000
//example
//#define N_ROW 10
//input
#define N_ROW 40

int is_trap(char* row, int n, int x) {
    if (x < 0 || x >= n) return 0;
    return (row[x] == '^');
}

int is_safe(char* row, int n, int x) {
    int left = is_trap(row, n, x - 1);
    int center = is_trap(row, n, x);
    int right = is_trap(row, n, x + 1);

    if (left && center && !right) return 0;
    if (center && right && !left) return 0;
    if (left && !center && !right) return 0;
    if (right && !center && !left) return 0;

    return 1;
}

void next_row(char* row, int n) {
    char* next_row = malloc(n * sizeof(char));
    for (int i = 0; i < n; i++) {
        if (is_safe(row, n, i)) {
            next_row[i] = '.';
        }
        else {
            next_row[i] = '^';
        }
    }
    for (int i = 0; i < n; i++) {
        row[i] = next_row[i];
    }
    free(next_row);
}

int n_safe(char* row, int n) {
    int res = 0;
    for (int i = 0; i < n; i++) {
        res += !is_trap(row, n, i);
    }
    return res;
}

int main(){
    char* row = malloc(MAX_ * sizeof(char));
    int n = 0;
    while((row[n] = getchar()) != '\n') {
        n++;
    }

    int res = 0;
    res += n_safe(row, n);

    for (int i = 0; i < N_ROW - 1; i++) {
        next_row(row, n);
        res += n_safe(row, n);
    }

    printf("%d\n", res);

    return 0;
}
