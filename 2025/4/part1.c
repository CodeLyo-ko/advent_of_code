#include <stdio.h>
#include <stdlib.h>
#define MAX_ROW 5000

int main() {
    char** grid = malloc(MAX_ROW * MAX_ROW * sizeof(char));
    int n = 0;
    int m = 0;

    char c;
    while ((c = getchar()) != EOF) {
        fseek(stdin, -1, SEEK_CUR);
        m = 0;
        grid[n] = malloc(MAX_ROW * sizeof(char));
        while((c = getchar()) != '\n'){
            grid[n][m] = c;
            m++;
        }
        n++;
    }

    int res = 0;
    int n_roll = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            n_roll = 0;
            if (grid[i][j] != '@') continue;

            if (i > 0 && grid[i - 1][j] == '@') n_roll++;
            if (i < n - 1 && grid[i + 1][j] == '@') n_roll++;
            if (j > 0 && grid[i][j - 1] == '@') n_roll++;
            if (j < m - 1 && grid[i][j + 1] == '@') n_roll++;
            if (i > 0 && j > 0 && grid[i - 1][j - 1] == '@') n_roll++;
            if (i > 0 && j < m - 1 && grid[i - 1][j + 1] == '@') n_roll++;
            if (i < n - 1 && j > 0 && grid[i + 1][j - 1] == '@') n_roll++;
            if (i < n - 1 && j < m - 1 && grid[i + 1][j + 1] == '@') n_roll++;

            if (n_roll < 4) res++;
        }
    }

    printf("%d\n", res);

    return 0;
}
