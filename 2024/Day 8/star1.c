#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int x;
    int y;
} pos_t;

typedef struct {
    char f; //frequency
    pos_t* pos;
    int n;
} antenna_t;

void add_antenna(antenna_t* antennas, int* n_antenna, char f, int x, int y) {
    for (int i = 0; i < *n_antenna; i++) {
        if (antennas[i].f == f) {
            antennas[i].pos[antennas[i].n].x = x;
            antennas[i].pos[antennas[i].n++].y = y;
            return;
        }
    }

    antennas[*n_antenna].f = f;
    antennas[*n_antenna].n = 1;
    antennas[*n_antenna].pos = malloc(100 * 100 * sizeof(pos_t));
    antennas[*n_antenna].pos[0].x = x;
    antennas[*n_antenna].pos[0].y = y;
    (*n_antenna)++;
    return;
}

void add_antinode(pos_t* antinodes, int* n_antinodes, int x, int y, int n, int m) {
    if (x < 0 || x >= n || y < 0 || y >= m) {
        return;
    }

    for (int i = 0; i < *n_antinodes; i++) {
        if (antinodes[i].x == x && antinodes[i].y == y) {
            return;
        }
    }

    antinodes[*n_antinodes].x = x;
    antinodes[(*n_antinodes)++].y = y;
}


int main() {
    char** grid = malloc(100 * 100 * sizeof(char));
    int n = 0;
    int m = 0;

    antenna_t* antennas = malloc(100 * 100 * sizeof(antenna_t));
    int n_antenna = 0;

    pos_t* antinodes = malloc(100 * 100 * sizeof(pos_t));
    int n_antinodes = 0;

    while (getchar() != EOF) {
        fseek(stdin, -1, SEEK_CUR);
        grid[n] = malloc(100 * sizeof(char));
        fgets(grid[n++], 100, stdin);
    }
    while (grid[0][m++] != '\n');
    m--;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (grid[i][j] != '.') {
                add_antenna(antennas, &n_antenna, grid[i][j], i, j);
            }
        }
    }

    for (int i = 0; i < n_antenna; i++) {
        for (int j = 0; j < antennas[i].n - 1; j++) {
            for (int k = j + 1; k < antennas[i].n; k++) {
                int x1 = antennas[i].pos[j].x;
                int x2 = antennas[i].pos[k].x;
                int y1 = antennas[i].pos[j].y;
                int y2 = antennas[i].pos[k].y;
                add_antinode(antinodes, &n_antinodes, 2 * x1 - x2, 2 * y1 - y2, n, m);
                add_antinode(antinodes, &n_antinodes, 2 * x2 - x1, 2 * y2 - y1, n, m);
            }
        }
    }

    printf("%d\n", n_antinodes);

    return 0;
}
