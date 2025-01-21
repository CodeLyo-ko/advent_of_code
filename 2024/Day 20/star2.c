#include <stdio.h>
#include <stdlib.h>
#include "uthash.h"

#define abs(n) (n > 0?n:-n)

int shortest_path_no_cheat(char** map, int n, int m, int x, int y, int** map_min) {
    if (map[x][y] == 'E') {
        map_min[x][y] = 0;
        return 0;
    }

    map[x][y] = '#';
    int min;

    if (map[x - 1][y] != '#') {
        min = shortest_path_no_cheat(map, n, m, x - 1, y, map_min);
    }
    if (map[x + 1][y] != '#') {
        min = shortest_path_no_cheat(map, n, m, x + 1, y, map_min);
    }
    if (map[x][y - 1] != '#') {
        min = shortest_path_no_cheat(map, n, m, x, y - 1, map_min);
    }
    if (map[x][y + 1] != '#') {
        min = shortest_path_no_cheat(map, n, m, x, y + 1, map_min);
    }
    map_min[x][y] = min + 1;
    map[x][y] = '.';
    return min + 1;
}

int shortest_path(char** map, int n, int m, int x, int y, int cheat, int* cheats, int* n_cheat, int step, int** map_min) {
    if (map[x][y] == 'E')
        return 0;

    int min = -1;
    int temp;

    if (cheat) {
        for (int i = -20; i <= 20; i++) {
            for (int j = -(20-abs(i)); j <= 20 - abs(i); j++) {
                if (x + i < 0 || x + i >= n || y + j < 0 || y + j >=m || map[x+i][y+j] == '#') {
                    continue;
                }
                cheats[*n_cheat] = step + abs(i) + abs(j) + shortest_path(map, n, m, x + i, y + j, 0, cheats, n_cheat, step, map_min);
                // if (cheats[*n_cheat] ==84 - 20) printf("%d %d %d %d %d %d\n", x, y, x+i, y +j, i, j);
                (*n_cheat)++;
            }
        }
    }
    else {
        return map_min[x][y];
    }

    map[x][y] = '#';
    if (map[x - 1][y] != '#') {
        temp = shortest_path(map, n, m, x - 1, y, cheat, cheats, n_cheat, step + 1, map_min);
        if (min == -1 || temp < min) {
            min = temp;
        }
    }
    if (map[x + 1][y] != '#') {
        temp = shortest_path(map, n,m,  x + 1, y, cheat, cheats, n_cheat, step + 1, map_min);
        if (min == -1 || temp < min) {
            min = temp;
        }
    }
    if (map[x][y - 1] != '#') {
        temp = shortest_path(map, n, m, x, y - 1, cheat, cheats, n_cheat, step + 1, map_min);
        if (min == -1 || temp < min) {
            min = temp;
        }
    }
    if (map[x][y + 1] != '#') {
        temp = shortest_path(map, n, m, x, y + 1, cheat, cheats, n_cheat, step + 1, map_min);
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

    int** map_min = malloc(150 * 150 * sizeof(int));
    for (int i = 0; i < n ; i++) {
        map_min[i] = malloc(150 * sizeof(int));
        for (int j = 0; j < m; j++) {
            map_min[i][j] = 0;
        }
    }
    int time = shortest_path_no_cheat(map, n, m, x, y, map_min);
    int total = 0;
    int temp;
/*
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            printf("%2d ", map_min[i][j]);
        }
        printf("\n");
    }*/

    int* cheats = malloc(150 * 150 * 150 * sizeof(int));
    int n_cheat = 0;

    shortest_path(map, n, m, x, y, 1, cheats, &n_cheat, 0, map_min);

    for (int i = 0; i < n_cheat; i++) {
        if (time - cheats[i] >= 100) {
            total++;
        }
    }

    printf("%d\n", total);
    return 0;
}
