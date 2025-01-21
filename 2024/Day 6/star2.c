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

    int x_beg = x; int y_beg = y;

    int new_x, new_y;

    int counter = 0;
    int total = 0;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (grid[i][j] == '#' || grid[i][j] == '^') {
                continue;
            }

            grid[i][j] = '#';

            x = x_beg; y = y_beg;
            counter = 0;

            do {
                counter ++;
                if (counter > 9999) {
                    total ++;
                    break;
                }
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
                    x = new_x;
                    y = new_y;
                }

            } while (1);

            for (int k = 0; k < n; k++) {
                for (int l = 0; l < m; l++) {
                    if (grid[k][l] != '#')
                    grid[k][l] = '.';
                }
            }

            grid[x_beg][y_beg] = '^';
            grid[i][j] = '.';
        }
    }

    printf("%d\n", total);

    return 0;
}
