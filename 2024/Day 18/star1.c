#include <stdio.h>
#include <stdlib.h>

void free_tab(char** t, int n) {
    for (int i = 0; i < n; i++) {
        free(t[i]);
    }
    free(t);
}

void copy_tab(char** in, int n, char** out) {
    out = malloc((n+1) * (n+1) * sizeof(char));
    for (int i = 0; i <n;i++) {
        out[i] = malloc((n+1) * sizeof(char));
        for (int j = 0; j < n; j++) {
            out[i][j] = in[i][j];
        }
    }
}

void path(char** grid, int n, int** min_dist, int x, int y, int step) {

    if (grid[x][y] == 'O' || grid[x][y] == '#') {
        return;
    }

    if (min_dist[x][y] == -1 || min_dist[x][y] > step) {
        min_dist[x][y] = step;
    }
    else{
        return;
    }


    grid[x][y] = 'O';
    if (x < n - 1)
        path(grid, n, min_dist, x + 1, y, step + 1);
    if (y < n - 1)
        path(grid, n, min_dist, x, y + 1, step + 1);
    if (x > 0)
        path(grid, n, min_dist, x - 1, y, step + 1);
    if (y > 0)
        path(grid, n, min_dist, x, y - 1, step + 1);

    grid[x][y] = '.';

}

int main() {
    char** memory = malloc(72 * 72 * sizeof(char));
    int n = 71;
    int** min_dist = malloc(72 * 72 * sizeof(int));

    for (int i = 0; i < n; i++) {
        memory[i] = malloc(72 * sizeof(char));
        min_dist[i] = malloc(72 * sizeof(int));
        for (int j = 0; j < n; j++) {
            memory[i][j] = '.';
            min_dist[i][j] = -1;
        }
    }



    int x, y;
    for (int i = 0; i < 1024; i++) {
        scanf("%d,%d\n", &x, &y);
        memory[x][y] = '#';
    }
    path(memory, n, min_dist, 0, 0, 0 );

printf("%d\n", min_dist[70][70]);
    return 0;
}
