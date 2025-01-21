#include <stdio.h>
#include <stdlib.h>

int main() {
    char** grid = malloc(1000 * 1000 * sizeof(char));
    int n = 0;
    int m = 0;

    do {
        grid[n] =  malloc(1000 * sizeof(char));
    } while(fgets(grid[n++], 1000, stdin));

    n--;

    while (grid[0][m++] != '\n');
    m--;

    int x, y;

    for (int i = 0; i < n; i ++) {
        for (int j = 0; j < m; j++) {
            if (grid[i][j] == '^') {
                x = i; y =  j;
                break;
            }
        }
    }

    int new_x, new_y;

    while (x >= 0 && x < n && y >= 0 && y < m) {
        switch (grid[x][y]) {
            case '^':
                new_x = x - 1;
                new_y = y;
                break;
            case 'v':
                new_x = x + 1;
                new_y = y;
                break;
            case '>':
                new_x = x;
                new_y = y + 1;
                break;
            case '<':
                new_x = x;
                new_y = y - 1;
                break;
        }


        if (new_x < 0 || new_x >= n || new_y < 0 || new_y >= m) {
            grid[x][y] = 'X';
            break;
        }

        if (grid[new_x][new_y] == '#') {
           switch (grid[x][y]) {
                case '^':
                    grid[x][y] = '>';
                    break;
                case 'v':
                    grid[x][y] = '<';
                    break;
                case '>':
                    grid[x][y] = 'v';
                    break;
                case '<':
                    grid[x][y] = '^';
                    break;
            }
        }

        else {
            grid[new_x][new_y] = grid[x][y];
            grid[x][y] = 'X';
            x = new_x;
            y = new_y;
        }

    }

    int total = 0;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (grid[i][j] == 'X') {
                total++;
            }
        }
    }

    printf("%d\n", total);

    return 0;
}
