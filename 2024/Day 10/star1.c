#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int x;
    int y;
} pos_t;

void add_pos(pos_t* reachable, int* n, int x, int y) {
    for (int i = 0; i < *n; i++) {
        if (reachable[i].x == x && reachable[i].y == y) {
            return;
        }
    }

    reachable[*n].x = x;
    reachable[*n].y = y;
    (*n)++;
}

void score_trailhead(char** input, int n, int m, int i, int j, pos_t* reachable, int* k) {
    if (i < 0 || j < 0 || i >= n || j >= m) {
        return;
    }

    if (input[i][j] == '9') {
        add_pos(reachable, k, i, j);
        return;
    }

    if (i > 0)
    if (input[i - 1][j] == input[i][j] + 1) {
        score_trailhead(input, n, m, i - 1, j, reachable, k);
    }

    if (i < n - 1)
    if (input[i + 1][j] == input[i][j] + 1) {
        score_trailhead(input, n, m, i + 1, j, reachable, k);
    }

    if (j > 0)
    if (input[i][j - 1] == input[i][j] + 1) {
        score_trailhead(input, n, m, i, j - 1, reachable, k);
    }

    if (j < m - 1)
    if (input[i][j + 1] == input[i][j] + 1) {
        score_trailhead(input, n, m, i, j + 1, reachable, k);
    }
}

int main() {
    char** input = malloc(100 * 100 * sizeof(char));
    int n = 0;
    int m = 0;

    while (getchar() != EOF) {
        fseek(stdin, -1, SEEK_CUR);
        input[n] = malloc(100 * sizeof(char));
        m = 0;
        while((input[n][m] = getchar()) != '\n'){
            m++;
        }
        n++;
    }

    int total = 0;

    pos_t* reachable = malloc(100 * 100 * sizeof(pos_t));
    int k = 0;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (input[i][j] == '0') {
                k = 0;
                score_trailhead(input, n, m, i, j, reachable, &k);
                total += k;
            }
        }
    }
    printf("%d\n", total);
    return 0;
}
