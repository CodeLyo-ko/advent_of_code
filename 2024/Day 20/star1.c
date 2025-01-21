#include <stdio.h>
#include <stdlib.h>

int shortest_path(char** map, int n, int m, int x, int y) {
    if (map[x][y] == 'E')
        return 0;

    map[x][y] = '#';
    int min = -1;
    int temp;

    if (map[x - 1][y] != '#') {
        temp = shortest_path(map, n, m, x - 1, y);
        if (min == -1 || temp < min) {
            min = temp;
        }
    }
    if (map[x + 1][y] != '#') {
        temp = shortest_path(map, n, m, x + 1, y);
        if (min == -1 || temp < min) {
            min = temp;
        }
    }
    if (map[x][y - 1] != '#') {
        temp = shortest_path(map, n, m, x, y - 1);
        if (min == -1 || temp < min) {
            min = temp;
        }
    }
    if (map[x][y + 1] != '#') {
        temp = shortest_path(map, n, m, x, y + 1);
        if (min == -1 || temp < min) {
            min = temp;
        }
    }

    // printf("%d\n", min);
    map[x][y] = '.';
    if (min == -1) {
        return 999999;
    }
    return min + 1;

}


int main(){
    char** map = malloc(150 * 150 * sizeof(char));
    int n = 0;
    int m = 0;

    while(getchar() != EOF) {
        fseek(stdin, -1, SEEK_CUR);
        m = 0;
        map[n] = malloc(150 * sizeof(char));
        while(getchar() != '\n') {
            fseek(stdin, -1, SEEK_CUR);
            map[n][m] = getchar();
            m++;
        }
        n++;
    }

    int x, y;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (map[i][j] == 'S') {
                x = i;
                y = j;
            }
        }
    }

    int time = shortest_path(map, n, m, x, y);
    int total = 0;

    // for (int i = 0; i < n; i++) {
    //     for (int j = 0; j < m; j++) {
    //         printf("%c", map[i][j]);
    //     }
    //     printf("\n");
    // }
    for (int i = 1; i < n - 1; i++) {
        for (int j = 1; j < m - 1; j++) {
            if (map[i][j] != '#') continue;
            map[i][j] = '.';
            int temp = shortest_path(map, n, m, x, y);
            // for (int i = 0; i < n; i++) {
            //     for (int j = 0; j < m; j++) {
            //         printf("%c", map[i][j]);
            //     }
            //     printf("\n");
            // }
            // printf("%d %d %d\n", time, temp, time - temp);
            if (time - temp >= 100) {
                total ++;
            }
            map[i][j] = '#';
        }
    }

    printf("%d\n", total);
    return 0;
}
