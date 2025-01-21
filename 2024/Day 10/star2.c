#include <stdio.h>
#include <stdlib.h>

void score_trailhead(char** input, int n, int m, int i, int j, int* k) {
    if (i < 0 || j < 0 || i >= n || j >= m) {
        return;
    }

    if (input[i][j] == '9') {
        (*k)++;
        return;
    }

    if (i > 0)
    if (input[i - 1][j] == input[i][j] + 1) {
        score_trailhead(input, n, m, i - 1, j, k);
    }

    if (i < n - 1)
    if (input[i + 1][j] == input[i][j] + 1) {
        score_trailhead(input, n, m, i + 1, j, k);
    }

    if (j > 0)
    if (input[i][j - 1] == input[i][j] + 1) {
        score_trailhead(input, n, m, i, j - 1, k);
    }

    if (j < m - 1)
    if (input[i][j + 1] == input[i][j] + 1) {
        score_trailhead(input, n, m, i, j + 1, k);
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

    int k = 0;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (input[i][j] == '0') {
                k = 0;
                score_trailhead(input, n, m, i, j, &k);
                total += k;
            }
        }
    }
    printf("%d\n", total);
    return 0;
}
